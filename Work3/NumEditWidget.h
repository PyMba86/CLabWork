///////////////////////////////////////////////////////////////////////////////
// Название:    Work2/NumEditWidget.h
// Цель:        Edit для ввода только числовых значений
// Автор:       Артем Матвейчук
// Создан:      05.03.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work2 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_CELLEDIT_H
#define LABWORK_CELLEDIT_H

#include <vaca/vaca.h>

using namespace vaca;

namespace MyWidget {

    //TextEdit с проверкой ввода только числовых значений
    class NumEditWidget : public TextEdit {
    public:

        NumEditWidget(Widget *parent)
                : TextEdit(L"", parent, TextEdit::Styles::Default) {
            isRange = false;
        }

        void setDigit(int digit) {
            setText(digit == 0 ? L"" : convert_to<String>(digit));
            selectAll();
        }

        int getDigit() {
            if (isRange)
                return checkRange();
            else
                return convert_to<int>(getText());
        }

        void setRange(int min, int max) {
            isRange = true;
            this->min = min;
            this->max = max;
        }

        bool getRange() {
            return isRange;
        }

        void removeRange() {
            isRange = false;
        }


    protected:

        int checkRange() {
            int num = convert_to<int>(getText());
            if (num < min) {
                num = min;
                setDigit(min);
            }
            else if (num > max) {
                num = max;
                setDigit(max);
            }
            return num;
        }

        virtual void onKeyDown(KeyEvent &ev) {
            if ((ev.getCharCode() >= '0') && (ev.getCharCode() <= '9') || ev.getCharCode() == '\b') {
                TextEdit::onKeyDown(ev);
            }
            else {
                ev.consume();
            }

        }

    private:
        int max;
        int min;
        bool isRange;

    };
} //namespace MyWidget
#endif //LABWORK_CELLEDIT_H
