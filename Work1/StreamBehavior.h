///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/PointList.h
// Цель:        Интерфейс для поведения вектора точек(потоки: Память, Файл...)
// Автор:       Артем Матвейчук
// Создан:      18.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_STREAMBEHAVIOR_H
#define LABWORK_STREAMBEHAVIOR_H

#include "Point.h"

namespace Point {
    //Поток(ввод, вывод) вектора - Память,Файл(json,xml...)
    class StreamBehavior {
    public:
        virtual fvPoint open() = 0;

        virtual bool save() = 0;

        virtual ~StreamBehavior() { };
    };
}

#endif //LABWORK_STREAMBEHAVIOR_H
