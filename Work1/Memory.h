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
    //Поток Внутренней памяти // Временные заглушки
    class Memory : public StreamBehavior {
    public:
        fvPoint open() {
            throw std::logic_error("View the list is not possible");
        }

        bool save() {
            throw std::logic_error("Save list can not be!");
        }
    };
}

#endif //LABWORK_MEMORY_H
