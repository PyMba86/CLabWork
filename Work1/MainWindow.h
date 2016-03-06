///////////////////////////////////////////////////////////////////////////////
// Название:    Work1/MainWindow.h
// Цель:        Главное окно приложения "Work1"
// Автор:       Артем Матвейчук
// Создан:      17.02.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work1 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_MAINWINDOW_H
#define LABWORK_MAINWINDOW_H

#include <vaca/vaca.h>
#include "resource.h"
#include "AboutWindow.h"
#include "BoxWidget.h"
#include "HelpWindow.h"
#include <ctime>
#include "PointList.h"
#include "Memory.h"

using namespace vaca;

//Обычный список точек с потоком в память(Memory)
namespace Point {
    class NativePointList : public PointList {
    public:
        NativePointList() {
            streamBehavior = unpStreamBehavior(new Memory);
        };
    };
}


namespace Window {

    //Главное окно(frame) приложения
    class MainFrame : public Frame {
        MyWidget::BoxWidget<int> boxLine;
        MyWidget::BoxWidget<float> boxLCircle;
        MyWidget::BoxWidget<float> boxLFirstPoint;
        Separator sprMain;
        CheckBox chkTangent;
        Button btnAbout;
        Button btnHelp;
        Button btnResult;

    public:
        MainFrame()
                : Frame(L"Work1", nullptr, Frame::Styles::Default - Frame::Styles::Maximizable),
                  boxLine(L"Уравнение прямой : y=kx+b", this, L"k:", L"b:"),
                  boxLCircle(L"Параметры окружности : центр окружности", this, L"x:", L"y:"),
                  boxLFirstPoint(L"Координаты первой точки", this, L"x:", L"y:"), btnAbout(L"О программе", this),
                  btnHelp(L"Помощь", this), chkTangent(L"Параметр 'k' задается в градусах", this), sprMain(this),
                  btnResult(L"Результат", this) {
            setIcon(ResourceId(IDI_APP));
            setLayout(Bix::parse(L"Y[fxY[%,%,%,%],%,X[%,%,f%]]",
                                 &boxLine,
                                 &chkTangent,
                                 &boxLCircle,
                                 &boxLFirstPoint,
                                 &sprMain,
                                 &btnHelp, &btnAbout, &btnResult));

            //Добавление кнопок в слоты
            btnAbout.Click.connect(&MainFrame::btnAboutClick, this);
            btnResult.Click.connect(&MainFrame::btnResultClick, this);
            btnHelp.Click.connect(&MainFrame::btnHelpClick, this);

            // Настройка окна
            setSize(getPreferredSize());
            center();
        }

    protected:

        virtual void onResizing(CardinalDirection dir, Rect &rc) {
            rc.y = getBounds().y;

            if (dir != CardinalDirection::North &&
                dir != CardinalDirection::South) {
                rc.h = getPreferredSize(Size(rc.getSize().w, 0)).h;
            }
            else {
                rc.h = getBounds().h;
            }
        }

    private:

        void btnAboutClick(Event &ev) {
            AboutWindow dlg(this);
            dlg.doModal();
        };

        void btnHelpClick(Event &ev) {
            HelpWindow dlg(this);
            dlg.doModal();
        };

        void btnResultClick(Event &ev) {

            std::shared_ptr<Point::PointList> pointList(new Point::NativePointList());
            float fRadius;
            float k;
            bool flag;
            // Генерация float числа
            std::mt19937 gen(time(0));
            std::uniform_real_distribution<float> uid(RANGE_MIN, RANGE_MAX);
            // Генерация радиуса окружности
            std::uniform_real_distribution<float> aid(RANGE_CIRCLE_MIN, RANGE_CIRCLE_MAX);
            fRadius = aid(gen);

            /////////////// Координаты первой точки ////////////////
            boxLFirstPoint.rangeParamBox(RANGE_MIN, RANGE_MAX);   //Проверка на диапазон
            pointList->addList(boxLFirstPoint.getParamBox().param1, boxLFirstPoint.getParamBox().param2);

            /////////////// Координаты второй точки ////////////////
            pointList->addList(uid(gen), uid(gen));
            ////////////// Координаты центра окружности ////////////
            boxLCircle.rangeParamBox(RANGE_MIN, RANGE_MAX);
            Point::fPoint pCircle{boxLCircle.getParamBox().param1, boxLCircle.getParamBox().param2};

            // Угол наклона в градусах
            if (chkTangent.isSelected())
                k = tan(boxLine.getParamBox().param1 * PI / 180);
            else
                k = boxLine.getParamBox().param1;

            // Сообщение о радусе окружности
            MsgBox::show(this, L"Окружность",
                         L"Радиус: " + convert_to<String>(fRadius));

            // Проход списка точек
            for (auto point : pointList->getList()) {

                flag = false;
                if (point.y < k * point.x + boxLine.getParamBox().param2) {
                    if (point.y >= 0 &&
                        (pow((point.x - pCircle.x), 2) + pow((point.y - pCircle.y), 2) <= pow(fRadius, 2)))
                        flag = true;
                    else if (point.y <= 0 &&
                             (pow((point.x - pCircle.x), 2) + pow((point.y - pCircle.y), 2) >= pow(fRadius, 2)))
                        flag = true;
                }
                MsgBox::show(this, L"Результат",
                             L"Координаты точки: " + convert_to<String>(point.x)
                             + L":" + convert_to<String>(point.y) + L"\r\nПринадлежит области: " +
                             BoolToStr(flag));

            }
        };

        String BoolToStr(bool b) {
            return b ? L"Да" : L"Нет";
        };

    };
} // namespace Window
#endif //LABWORK_MAINWINDOW_H
