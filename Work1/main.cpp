///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/main.cpp
// Цель:        Вызов WinMain
// Автор:       Артем Матвейчук
// Создан:      17.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#include "vaca/vaca.h"
#include "MainWindow.h"

using namespace vaca;

// Класс для создании окна MainFrame
class Work1 : public Application {
    Window::MainFrame m_mainFrame;

    virtual void main() {
        m_mainFrame.setVisible(true);
    }

};

// Вызов WinMain через макрос VACA_MAIN
int VACA_MAIN() {
    try {
        Work1 app;
        app.run();
    }
    catch (Exception &e) {
        MsgBox::showException(nullptr, e);
    }
    return 0;
}