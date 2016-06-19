///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/main.cpp
// Цель:        Вызов WinMain
// Автор:       Артем Матвейчук
// Создан:      13.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#include <vaca/vaca.h>

#include "MainWindow.h"

using namespace vaca;

// Класс для создании окна MainFrame
class Work5 : public Application {
public:
    void main() override {
        m_mainFrame.setVisible(true);
    }

protected:
    Window::Main m_mainFrame;
};

// Вызов WinMain через макрос VACA_MAIN
int VACA_MAIN() {
    try {
        Work5 app;
        app.run();
    }
    catch (Exception &e) {
        MsgBox::showException(nullptr, e);
    }
    return 0;
};