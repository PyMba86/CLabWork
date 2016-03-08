///////////////////////////////////////////////////////////////////////////////
// Название:    Work2/MainFrame.h
// Цель:        Главное окно приложения "Work1"
// Автор:       Артем Матвейчук
// Создан:      06.03.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work2 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_MAINFRAME_H
#define LABWORK_MAINFRAME_H

#include <ctime>
#include <vaca/vaca.h>
#include <cmath>

#include "resource.h"
#include "NArray.h"
#include "AboutDialog.h"
#include "NumEditWidget.h"

using namespace vaca;

namespace Window {
    class MainFrame : public Frame {
        Widget leftPanel;
        Widget rightPanel;
        TextEdit editGenerateArray;
        TextEdit editResultArray;
        Label lblGenarateArray;
        Label lblResultArray;
        GroupBox gbSizeArray;
        Label lblM;
        MyWidget::NumEditWidget numEditM;
        Label lblK;
        MyWidget::NumEditWidget numEditK;
        Button btnGenerate;
        Button btnAbout;
        StatusBar statusBar;

    public:
        MainFrame()
                : Frame(L"Work2", nullptr),
                  leftPanel(this),
                  rightPanel(this),
                  editGenerateArray(L"", &leftPanel, TextEdit::Styles::TextArea + TextEdit::Styles::ReadOnly),
                  editResultArray(L"", &leftPanel, TextEdit::Styles::TextArea + TextEdit::Styles::ReadOnly),
                  lblGenarateArray(L"Сгенерированный массив:", &leftPanel),
                  lblResultArray(L"Результат:", &leftPanel),
                  gbSizeArray(L"Размер массива", &rightPanel),
                  lblK(L"Число столбцов:", &gbSizeArray),
                  statusBar(this),
                  lblM(L"Число строк:", &gbSizeArray),
                  numEditK(&gbSizeArray),
                  numEditM(&gbSizeArray),
                  btnGenerate(L"Сгенерировать", &rightPanel),
                  btnAbout(L"О программе", &rightPanel) {
            setIcon(ResourceId(IDI_APP));

            leftPanel.setLayout(Bix::parse(L"Y[%,f%,%,f%]", &lblGenarateArray, &editGenerateArray,
                                           &lblResultArray, &editResultArray));
            rightPanel.setLayout(Bix::parse(L"Y[f%,%,%]", &gbSizeArray, &btnAbout, &btnGenerate));

            setLayout(Bix::parse(L"X[f%,%]", &leftPanel, &rightPanel));

            statusBar.setText(L" # Введите размеры массива и нажмите \"Сгенерировать\"");
            gbSizeArray.setLayout(new BoxLayout(Orientation::Vertical, false));

            //Размеры панели
            leftPanel.setPreferredSize(leftPanel.getPreferredSize() * 3);
            rightPanel.setPreferredSize(rightPanel.getPreferredSize() * 2);

            //Добавление кнопок в слоты
            btnAbout.Click.connect(&MainFrame::btnAboutClick, this);
            btnGenerate.Click.connect(&MainFrame::btnResultClick, this);

            // Настройка окна
            setSize(getPreferredSize());
            center();
        }

    private:

        void btnAboutClick(Event &ev) {
            AboutDialog dlg(this);
            dlg.doModal();
        };

        void btnResultClick(Event &ev) {

            editGenerateArray.setText(L"");
            editResultArray.setText(L"");

            if ((numEditM.getText().length() == 0) || (numEditK.getText().length() == 0)) {
                statusBar.setText(L" # Укажите размеры массива");
                return;
            }

            //Диапазон массива
            numEditM.setRange(ARRAY_MIN, ARRAY_MAX);
            numEditK.setRange(ARRAY_MIN, ARRAY_MAX);

            int M = numEditM.getDigit();
            int K = numEditK.getDigit();

            //Создание массива.(В измерении DIMENSION = 2)
            lab::NArray<float, DIMENSION> data({M, K});

            // Координаты минимальной и максимальной точки
            // Мнимальное и максимальное значение
            lab::detail::narray::Point<DIMENSION> p_max;
            float max = RANGE_MIN;

            lab::detail::narray::Point<DIMENSION> p_min;
            float min = RANGE_MAX;

            //Временные координаты значения в массиве
            lab::detail::narray::Point<DIMENSION> p_temp;

            std::mt19937 gen(time(0));
            std::uniform_real_distribution<float> uid(RANGE_MIN, RANGE_MAX);

            //Генерация значений и поиск минимального и максимального
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < K; j++) {
                    p_temp = {i, j};
                    data.at(p_temp) = uid(gen);

                    if (data.at(p_temp) > max) {
                        max = data.at(p_temp);
                        p_max = p_temp;
                    }
                    if (data.at(p_temp) < min) {
                        min = data.at(p_temp);
                        p_min = p_temp;
                    }
                    editGenerateArray.setText(editGenerateArray.getText()
                                              + convert_to<String>(data.at(p_temp))
                                              + L"         "); //FIXME Отступ(табуляция) "\t" не работает нормально
                }
                editGenerateArray.setText(editGenerateArray.getText() + L"\r\n");
            }

            //Поиск и замена значений
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < K; j++) {
                    p_temp = {i, j};
                    if (data.at(p_temp) >= 0) {
                        data.at(p_temp) = max;
                    }
                    else if (data.at(p_temp) < 0) {
                        data.at(p_temp) = min;
                    }
                    editResultArray.setText(editResultArray.getText()
                                            + convert_to<String>(data.at(p_temp))
                                            + L"         ");  //FIXME Отступ(табуляция) "\t" не работает нормально
                }
                editResultArray.setText(editResultArray.getText() + L"\r\n");
            }

            statusBar.setText(L" # Минимальный элемент: "
                              + convert_to<String>(min)
                              + L" позиция [" + convert_to<String>(p_min[0] + 1) + L"][" +
                              convert_to<String>(p_min[1] + 1) + L"]"
                              + L" # Максимальный элемент: "
                              + convert_to<String>(max)
                              + L" позиция [" + convert_to<String>(p_max[0] + 1) + L"][" +
                              convert_to<String>(p_max[1] + 1) + L"]");


        };

    };
}

#endif //LABWORK_MAINFRAME_H
