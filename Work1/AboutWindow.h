///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/AboutWindow.h
// Цель:        Окно "О программе"
// Автор:       Артем Матвейчук
// Создан:      06.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_ABOUTDLG_H
#define LABWORK_ABOUTDLG_H

#include "resource.h"
#include <vaca/vaca.h>
#include "LogoWidget.h"

using namespace vaca;

namespace Window {

    //Окно "О программе"
    class AboutWindow : public Dialog {
        MyWidget::LogoWidget LogoImage;
        Widget LabelLayout;
        Label lblName;
        Label lblDescription;
        Label lblAuthor;
        Label lblVersion;
    public:
        AboutWindow(Widget *parent)
                : Dialog(L"О программе labWork", parent), LogoImage(this), LabelLayout(this),
                  lblName(L"Лабораторная работа \r\n Work1 ", &LabelLayout),
                  lblDescription(L"Описание: Лабораторная работа по \r\n" L"основам программиования Си", &LabelLayout),
                  lblAuthor(L"Автор: Матвейчук Артем Олегович", &LabelLayout),
                  lblVersion(L"\r\n Версия: 1.0.0.6", &LabelLayout) {
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
#endif //LABWORK_ABOUTDLG_H
