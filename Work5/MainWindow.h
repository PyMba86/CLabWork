///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/MainWindow.h
// Цель:        Главное окно приложения "Work5"
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

#include "Stream/FileReader.h"
#include "List.h"
#include "EditableList.hpp"

using namespace vaca;
using namespace lab;

namespace Window {

    struct Man
    {
        String name; // Имя
        String surname; // Фамилия
        String patronymic; // Отчество
        String number; // Номер телефона
    };

    class Main : public Frame {
        Widget leftPanel;
        Widget rightPanel;
        GroupBox searchBox;
        Label lblDelim;
        TextEdit editDelim;
        Label lblEncoding;
        ComboBox cbEncoding;
        encoding::TextEncoding encoding;
        Label lblResult;
        MyWidget::EditableListBox listResult;
        Button btnResult;
        Button btnAbout;
    public:
        Main()
                : Frame(L"Work5", nullptr),
                  leftPanel(this),
                  rightPanel(this),
                  searchBox(L"Настройки",&rightPanel),
                  lblDelim(L"Делитель:",&searchBox),
                  editDelim(L"",&searchBox),
                  lblEncoding(L"Кодировка:", &searchBox),
                  cbEncoding(&searchBox),
                  lblResult(L"Результат:", &leftPanel),
                  listResult(&leftPanel),
                  btnResult(L"Составить список",&rightPanel),
                  btnAbout(L"О программе", &rightPanel),
                  encoding(encoding::TextEncoding::Ansi)

        {
            setIcon(ResourceId(IDI_APP));

            cbEncoding.addItem(L"ANSI");
            cbEncoding.addItem(L"UTF8");
            cbEncoding.setSelectedItem(0);
            searchBox.setLayout(new BoxLayout(Orientation::Vertical, false));
            leftPanel.setLayout(Bix::parse(L"Y[%,f%]", &lblResult, &listResult));
            rightPanel.setLayout(Bix::parse(L"Y[f%,%,%]", &searchBox, &btnResult,&btnAbout));

            setLayout(Bix::parse(L"X[f%,%]", &leftPanel, &rightPanel));

            //Размеры панели
            leftPanel.setPreferredSize(leftPanel.getPreferredSize() * 3);
            rightPanel.setPreferredSize(rightPanel.getPreferredSize() * 2);

            //Привязка сигналов
            btnAbout.Click.connect(&Main::btnAboutClick, this);
            btnResult.Click.connect(&Main::btnResultClick, this);
            cbEncoding.SelChange.connect(&Main::onComboChange, this);

            setSize(Size(getPreferredSize().w * 2, getPreferredSize().h));
            center();
        }
    private:

        // ------------------------------------------------------------------
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

        // ------------------------------------------------------------------
        bool checkFindFile(const String& path)
        {
            FindFiles file(path);
            if (file.next() && file.isFile())
                return true;
            MsgBox::show(this, L"labWork", L"Файл " + path + L" не найден!");
            return false;
        }

        // ------------------------------------------------------------------
        void btnResultClick(Event &ev) {
            if (checkFindFile(finFilePath)) {
                // Открытие файла
                std::unique_ptr<stream::FileInputStream> finFile(new stream::FileInputStream(finFilePath));
                if (finFile->isOpen()) {
                    stream::FileReader finReader(finFile.get());
                    finReader.checkEncoding();
                    if (finReader.getDecoder()->getEncoding() != encoding) {
                        MsgBox::Result temp = MsgBox::show(this, finFilePath,
                                                           L"Кодировка файла несовпадает с выбранной\n"
                                                                   L"Возможна потеря данных! Прочитать файл в выбранной кодировке?",
                                                           MsgBox::Type::YesNo, MsgBox::Icon::Warning);
                        if (temp == MsgBox::Result::Yes)
                            finReader.setDecoder(encoding::BaseDecoder::getDecoder(encoding));
                    }
                    // Создание двухсвязного списка
                    List<Man> manList;
                    while (!finReader.isEndOfFile()) {
                        String lineString = finReader.readLine(delim);
                        std::vector<String> tokens = tokenize(lineString, editDelim.getText());
                        manList.push_back(createMan(tokens));
                    }
                    // Вывод двухсвязного списка на экран
                    if (!manList.empty())
                        manView(manList);
                }
            }
            else
                MsgBox::show(this, L"labWork",
                             L"Что-то пошло не так... Операция отменена!",
                             MsgBox::Type::Ok, MsgBox::Icon::Error);
        };

        // ------------------------------------------------------------------
        void manView(const List<Man>& list)
        {
            for (auto& it : list)
                listResult.addItem(L"Имя: "+ it.name + L" "
                        L"Фамилия: "+ it.surname + L" "
                                           L"Отчество: "+ it.patronymic + L" "
                                                         L"Номер телефона: "+ it.number);
        }

        // ------------------------------------------------------------------
        Man createMan(std::vector<String>& vector)
        {
            if (vector.size() < 4)
                vector.resize(4);
            return {vector[0],vector[1],vector[2],vector[3]};
        }

        // ------------------------------------------------------------------
        std::vector<String> tokenize(
                const String& string, const String& delim)
        {
            // Добавляет в массив выделенные части
            //
            // 1. Если найден delim
            //
            // 2.1 Если не найден delim
            //
            // 2.2 Если найден delim,то проверяем с максимальной длиной строки

            String::size_type last_pos = 0,
                    pos = string.find(delim, last_pos);

            std::vector<String> tokens;

            while (last_pos != String::npos) {
                if (pos != last_pos)   /* 1 */
                    tokens.push_back(string.substr(last_pos, pos - last_pos));
                last_pos = pos;
                if (last_pos == String::npos		  /* 2.1 */
                    || (last_pos + 1) == string.length())   /* 2.2 */
                    break;
                pos = string.find(delim, ++last_pos);
            }
            return tokens;
        }

        // ------------------------------------------------------------------
        void btnAboutClick(Event &ev) {
            AboutDialog dlg(this);
            dlg.doModal();
        };

    };
}

#endif //LABWORK_MAINWINDOW_H
