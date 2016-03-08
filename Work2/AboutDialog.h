///////////////////////////////////////////////////////////////////////////////
// Название:    Work2/AboutDialog.h
// Цель:        Окно "О программе"
// Автор:       Артем Матвейчук
// Создан:      06.03.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work2 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_ABOUTDIALOG_H
#define LABWORK_ABOUTDIALOG_H

#include <vaca/vaca.h>

#include "resource.h"
#include "LogoWidget.h"

using namespace vaca;

namespace Window {

    //Окно "О программе"
    class AboutDialog : public Dialog {
        MyWidget::LogoWidget LogoImage;
        Widget LabelLayout;
        Label lblName;
        Label lblDescription;
        Label lblAuthor;
        Label lblVersion;
    public:
        AboutDialog(Widget *parent)
                : Dialog(L"О программе labWork", parent), LogoImage(this), LabelLayout(this),
                  lblName(L"Лабораторная работа \r\n Work2", &LabelLayout),
                  lblDescription(L"Описание: Лабораторная работа по \r\n" L"основам программиования Си", &LabelLayout),
                  lblAuthor(L"Автор: Матвейчук Артем Олегович", &LabelLayout),
                  lblVersion(L"\r\n Версия: 2.0.0.2", &LabelLayout) {
            setLayout(new BoxLayout(Orientation::Horizontal, false));
            setBgColor(Color::White);

            // Настройка TextLayout
            LabelLayout.setLayout(new BoxLayout(Orientation::Vertical, false));
            LabelLayout.setBgColor(Color::White);

            //Настройка Label's
            lblName.setTextAlign(TextAlign::Center);
            lblName.setFont(Font(L"Verdana", 12, FontStyle::Bold));
            lblName.setBgColor(Color::White);
            lblVersion.setTextAlign(TextAlign::Right);
            lblVersion.setBgColor(Color::White);
            lblDescription.setBgColor(Color::White);
            lblAuthor.setBgColor(Color::White);

            // Настройка окна
            setIcon(ResourceId(IDI_APP));
            setSize(getPreferredSize());
            center();
        }
    };
} // namespace Window

#endif //LABWORK_ABOUTDIALOG_H
