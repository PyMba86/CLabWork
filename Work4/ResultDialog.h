///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/ResultDialog.h
// Цель:        Оконо результата поиска
// Автор:       Артем Матвейчук
// Создан:      14.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef LABWORK_RESULTDIALOG_H
#define LABWORK_RESULTDIALOG_H

#include <vaca/vaca.h>

#include "resource.h"
#include "Stream/FileReader.h"

using namespace vaca;
using namespace lab;

namespace Window {

    //Окно "О программе"
    class ResultDialog : public Dialog {
        TextEdit editResult;
    public:
        ResultDialog(Widget *parent, encoding::TextEncoding encoding)
                : Dialog(L"Результат", parent),
                  editResult(L"",this, TextEdit::Styles::TextArea + TextEdit::Styles::ReadOnly)
        {
            setLayout(new BoxLayout(Orientation::Vertical, true));
            std::unique_ptr<stream::FileInputStream> foutFile(new stream::FileInputStream(foutFilePath));
            if (foutFile->isOpen()) {
                stream::FileReader finReader(foutFile.get());
                finReader.setDecoder(encoding::BaseDecoder::getDecoder(encoding));
                String result;
                while (!finReader.isEndOfFile()) {
                    result.append(finReader.readLine(delim) + L"\r\n");
                }
                editResult.setText(result);
            }
            // Настройка окна
            setIcon(ResourceId(IDI_APP));
            setSize(Size(800,600));
            center();
        }
    };
} // namespace Window

#endif //LABWORK_RESULTDIALOG_HPP
