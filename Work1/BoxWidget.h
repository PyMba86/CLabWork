///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/BoxWidget.h
// Цель:        Скомпоновать обьекты представления(2 Edit, 3 Label)
// Автор:       Артем Матвейчук
// Создан:      07.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_BOXWIDGET_H
#define LABWORK_BOXWIDGET_H

#include <vaca/vaca.h>
#include "NumEditWidget.h"


using namespace vaca;

namespace MyWidget {


    template<typename T>
    struct strParam {
        T param1;
        T param2;
    };

    template<typename T>
    //Коробка(другого названия нет!!)
    class BoxWidget : public Widget {
        Label lblBoxName;
        Label lblNameParam1;
        NumEditWidget<T> cllParam1;
        Label lblNameParam2;
        NumEditWidget<T> cllParam2;

    public:
        BoxWidget(const String name, Widget *parent, const String name_param1, const String name_param2)
                : Widget(parent), lblBoxName(name, this, Label::Styles::Default +
                                                         Label::Styles::EndEllipsis), lblNameParam1(name_param1, this),
                  cllParam1(this), lblNameParam2(name_param2, this), cllParam2(this) {
            setLayout(Bix::parse(L"Y[%,Y[X[%,f%,%,f%]]]",
                                 &lblBoxName,
                                 &lblNameParam1, &cllParam1, &lblNameParam2, &cllParam2));
        };

        void setParamBox(const T param1, const T param2) {
            cllParam1.setDigit(param1);
            cllParam2.setDigit(param2);
        }

        //Проверка на диапазон
        void rangeParamBox(T min, T max) {
            changeField(cllParam1, min, max);
            changeField(cllParam2, min, max);

        }

        strParam<T> getParamBox() {
            return {cllParam1.getDigit(), cllParam2.getDigit()};
        }

    private:
        //Изменение данных в поле
        void changeField(NumEditWidget<T> &edit, T min, T max) {
            if (edit.getDigit() > max)
                edit.setDigit(max);
            else if (edit.getDigit() < min)
                edit.setDigit(min);
        }
    };
}
#endif //LABWORK_BOXWIDGET_H
