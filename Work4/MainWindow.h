///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/MainWindow.h
// Цель:        Главное окно приложения "Work3"
// Автор:       Артем Матвейчук
// Создан:      13.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef LABWORK_MAINWINDOW_H
#define LABWORK_MAINWINDOW_H

#include <vaca/vaca.h>
#include <memory>


#include "resource.h"
#include "AboutDialog.h"
#include "ResultDialog.h"

#include "Stream/FileReader.h"
#include "Stream/FileWriter.h"

using namespace vaca;
using namespace lab;

namespace Window {

    class Main : public Frame {
        GroupBox searchBox;
        GroupBox encodingBox;
        ComboBox cbEncoding;
        encoding::TextEncoding encoding;
        Label lblChar;
        TextEdit editChar;
        Button btnSearch;
        Button btnAbout;
    public:
        Main()
                : Frame(L"Work4", nullptr),
                  searchBox(L"Поиск",this),
                  encodingBox(L"Кодировка",this),
                  cbEncoding(&encodingBox),
                  lblChar(L"Символ:", &searchBox),
                  editChar(L"",&searchBox),
                  btnSearch(L"Поиск",this),
                  btnAbout(L"О программе", this),
                  encoding(encoding::TextEncoding::Ansi)

        {
            setIcon(ResourceId(IDI_APP));
            editChar.setTextLimit(1);

            cbEncoding.addItem(L"ANSI");
            cbEncoding.addItem(L"UTF8");
            cbEncoding.setSelectedItem(0);

            searchBox.setLayout(Bix::parse(L"Y[X[%,f%]]", &lblChar,&editChar));
            encodingBox.setLayout(Bix::parse(L"Y[X[f%]]", &cbEncoding));
            setLayout(Bix::parse(L"Y[f%,f%,x%,x%]", &searchBox,&encodingBox,&btnSearch,&btnAbout));

            //Привязка сигналов
            btnAbout.Click.connect(&Main::btnAboutClick, this);
            btnSearch.Click.connect(&Main::btnSearchClick, this);
            cbEncoding.SelChange.connect(&Main::onComboChange, this);

            setSize(Size(getPreferredSize().w * 2, getPreferredSize().h));
            center();
        }
    protected:

        void onResizing(CardinalDirection dir, Rect &rc) override {
            rc.y = getBounds().y;

            if (dir != CardinalDirection::North &&
                dir != CardinalDirection::South) {
                rc.h = getPreferredSize(Size(rc.getSize().w, 0)).h;
            }
            else {
                rc.h = getBounds().h;
            }
        }

    private:
	
		// ---------------------------------------------------------------------
        void onComboChange(Event& ev)
        {
            switch (cbEncoding.getSelectedItem()) {
                case 0: {
                    encoding = encoding::TextEncoding::Ansi;
                    break;
                }
                case 1: {
                    encoding = encoding::TextEncoding::Utf8;
                    break;
                }
                default: {
                    break;
                }
            }
        }
		
		// ---------------------------------------------------------------------
        bool createFile(const String& path)
        {
            stream::FileOutputStream file(path);
            return file.isOpen();
        }
		
		// ---------------------------------------------------------------------
        bool checkFindFile(const String path)
        {
            FindFiles file(path);
            if (file.next() && file.isFile())
                return true;
            MsgBox::Result temp = MsgBox::show(this, L"labWork",
                         L"Файл " + path + L" не найден!\n"
                         L"Создать новый файл в текущей директории?",
                         MsgBox::Type::YesNo,MsgBox::Icon::Information);
            if(temp == MsgBox::Result::Yes)
               if (createFile(path))
                   return true;
            return false;
        }
		
		// ---------------------------------------------------------------------
        bool search() {
            if (checkFindFile(finFilePath)) {
				// Открытие файла fin.txt
                std::unique_ptr<stream::FileInputStream> finFile(new stream::FileInputStream(finFilePath));
                if (finFile->isOpen()) {
                    stream::FileReader finReader(finFile.get());
					//Проверка файла выбранной кодировке.
                    finReader.checkEncoding();
                    if (finReader.getDecoder()->getEncoding() != encoding) {
                        MsgBox::Result temp = MsgBox::show(this, finFilePath,
                                                           L"Кодировка файла несовпадает с выбранной\n"
                                                                   L"Возможна потеря данных! Прочитать файл в выбранной кодировке?",
                                                           MsgBox::Type::YesNo, MsgBox::Icon::Warning);
                        if (temp == MsgBox::Result::Yes)
                            finReader.setDecoder(encoding::BaseDecoder::getDecoder(encoding));
                    }
					// Открытие файла fout.txt
                    std::unique_ptr<stream::FileOutputStream> foutFile(new stream::FileOutputStream(foutFilePath));
                    stream::FileWriter foutWriter(foutFile.get(), encoding);
					
                    while (!finReader.isEndOfFile()) {
                        String lineString = finReader.readLine(delim);
                        foutWriter.writeString(editChar.getText()
                                               + L" "
                                               + convert_to<String>(searchWordCount(lineString, editChar.getText()))
                                               + L" " + convert_to<String>(lineString.length())
                                               + to_String(delim));
                    }
                }
                return true;
            }
            return false;
        }
		
		// ---------------------------------------------------------------------
        void btnSearchClick(Event &ev) {
            if (search()) {
                ResultDialog dlg(this,encoding);
                dlg.doModal();
            }
            else
                MsgBox::show(this, L"labWork",
                             L"Что-то пошло не так... Операция отменена!",
                             MsgBox::Type::Ok, MsgBox::Icon::Error);
        };
		
		// ---------------------------------------------------------------------
        uint32_t searchWordCount(const String &string, const String& word)
        {
            String::size_type last_pos = 0,
                    pos = string.find(word, last_pos);
            uint32_t countWord = 0;

            while (last_pos != String::npos) {
                if (pos != String::npos)   /* 1 */
                    ++countWord;
                last_pos = pos;
                if (last_pos == String::npos
                    || (last_pos + 1) == string.length())
                    break;
                pos = string.find(word, ++last_pos);
            }
            return countWord;
            }
			
		// ---------------------------------------------------------------------
        void btnAboutClick(Event &ev) {
            AboutDialog dlg(this);
            dlg.doModal();
        };

    };
}

#endif //LABWORK_MAINWINDOW_H
