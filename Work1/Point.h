///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/Point.h
// Цель:        Структура точки на координатной плоскости
// Автор:       Артем Матвейчук
// Создан:      17.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_POINT_H
#define LABWORK_POINT_H

#include <vector>

namespace Point {

    //Структура координаты точки
    struct fPoint {
        float x;
        float y;

        fPoint() = default;

        fPoint(float x, float y);
    };

    fPoint::fPoint(float x, float y) {
        this->x = x;
        this->y = y;
    }

    typedef std::vector<fPoint> fvPoint;
} // namespace Point

#endif //LABWORK_POINT_H
