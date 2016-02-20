///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/HelpWindow.h
// Цель:        Окно "Помощь"
// Автор:       Артем Матвейчук
// Создан:      10.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_HELPDIALOG_H
#define LABWORK_HELPDIALOG_H

#include "resource.h"
#include <vaca/vaca.h>
#include "LogoWidget.h"

using namespace vaca;

namespace Window {

    //Окно "Помощь"
    class HelpWindow : public Dialog {
        Image imgHelpWork;
    public:
        HelpWindow(Widget *parent)
                : Dialog(L"Помощь", parent), imgHelpWork(ResourceId(IDB_HELP)) {
            setIcon(ResourceId(IDI_APP));
            setBgColor(Color::White);
            setSize(imgHelpWork.getSize() + getPreferredSize());
            center();
        }

    private:
        virtual void onPaint(PaintEvent &ev) {
            Graphics &g = ev.getGraphics();
            g.drawImage(imgHelpWork, Point(getClientBounds().getCenter() - Point(imgHelpWork.getSize() / 2)));
        }

    };
} // namespace Window
#endif //LABWORK_HELPDIALOG_H
