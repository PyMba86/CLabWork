///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/PointList.h
// Цель:        Вектор(массив) для точек
// Автор:       Артем Матвейчук
// Создан:      18.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_POINTLIST_H
#define LABWORK_POINTLIST_H

#include <memory>
#include "Point.h"
#include "StreamBehavior.h"

namespace Point {
    //Умный указатель unique_ptr
    typedef std::unique_ptr<StreamBehavior> unpStreamBehavior;

    class PointList {
    public:

        //Добавление в конец списка
        void addList(float x, float y) {
            list.push_back(fPoint(x, y));
        };

        //Очистка списка
        void clearList() {
            list.clear();
        };

        //Размер списка
        unsigned int sizeList() {
            return list.size();
        };

        //Удаление определенного элемента(отсчет с 1)
        void removeList(int pos) {
            list.erase(list.begin() + pos);
        }

        //////// StreamBehavior //////////////////

        //Открытие списка из потока
        void openList() {
            list = std::move(streamBehavior->open());
        }

        //Сохранение списка в поток
        bool saveList() {
            return streamBehavior->save();
        }

        //Изменение потока(ну или как-то так)
        void setStreamBehavior(unpStreamBehavior upsb) {
            streamBehavior = std::move(upsb);
        }

        //Получение списка(копирование)
        fvPoint getList() {
            return list;
        }

    protected:
        unpStreamBehavior streamBehavior;

    private:
        fvPoint list;
    };
}

#endif //LABWORK_POINTLIST_H
