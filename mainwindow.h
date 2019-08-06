#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent    (QMouseEvent* pe);

    void dumpEvent(QMouseEvent* pe);
    void scanCell();

private slots:


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    int sizeCell = 150;                 //размер клетки
    int statusCell[3][3];               //состояние клетки  //0- кружки, 1 - крестики, 2-пусто
    bool player = false;                //право хода
    int  NumberMoves = 0;               //количество ходов

    void SetArr(int *arr,int number);   //инициализация массива
    void ScanCell();                    //проверка поля
    void End(bool player);
    void NewGame();
};

#endif // MAINWINDOW_H
