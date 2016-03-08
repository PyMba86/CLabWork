///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/NumEditWidget.h
// Цель:        Edit для ввода только числовых значений
// Автор:       Артем Матвейчук
// Создан:      07.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_CELLEDIT_H
#define LABWORK_CELLEDIT_H

#include <vaca/vaca.h>

using namespace vaca;

namespace MyWidget {

    //TextEdit с проверкой ввода только числовых значений
    template<typename T>
    class NumEditWidget : public TextEdit {
    public:

        NumEditWidget(Widget *parent)
                : TextEdit(L"", parent, TextEdit::Styles::Default) { }

        void setDigit(T digit) {
            setText(digit == 0 ? L"" : convert_to<String>(digit));
            selectAll();
        }

        T getDigit() {
            return convert_to<T>(getText());
        }

    protected:

        virtual void onKeyDown(KeyEvent &ev) {
            if ((ev.getCharCode() >= '0') && (ev.getCharCode() <= '9') || ev.getCharCode() == '\b') {
                TextEdit::onKeyDown(ev);
                return;
            }
            else if (ev.getCharCode() == '.') {

                if ((getText().find('.') <= getText().length()) || getText().length() == 0) {
                    ev.consume();
                    return;
                }
                TextEdit::onKeyDown(ev);
                return;
            }
            else if (ev.getCharCode() == '-') {
                if (getText().length() > 0) {
                    ev.consume();
                    return;
                }
                TextEdit::onKeyDown(ev);
                return;
            }
            ev.consume();
        }

    };
} //namespace MyWidget
#endif //LABWORK_CELLEDIT_H
