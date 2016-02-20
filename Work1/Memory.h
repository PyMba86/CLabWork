///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/Memory.h
// Цель:        Поток->Внутренняя память. Поведение для Списка точек
// Автор:       Артем Матвейчук
// Создан:      18.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_MEMORY_H
#define LABWORK_MEMORY_H

#include "StreamBehavior.h"

namespace Point {
    //Поток Внутренней памяти
    class Memory : public StreamBehavior {
    public:
        fvPoint open() {
            MsgBox::show(nullptr, L"Ошибка", L"Открыть список невозможно! \r\n Будет возвращен пустой список",
                         MsgBox::Type::Ok, MsgBox::Icon::Error);
            return fvPoint(0);
        }

        bool save() {
            MsgBox::show(nullptr, L"Ошибка", L"Сохранить список невозможно!",
                         MsgBox::Type::Ok, MsgBox::Icon::Error);
            return false;
        }
    };
}

#endif //LABWORK_MEMORY_H
