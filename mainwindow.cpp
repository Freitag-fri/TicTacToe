#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(sizeCell *4, sizeCell*3);    //фиксирование размеров окна
    SetArr(*statusCell, 2);
    ui->setupUi(this);
}

void MainWindow::SetArr(int *arr, int number)       //инициализация массива
{
    for(int i =0; i < 9; i++)
    {
        arr[i] = number;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)  //рисование
{
    QPainter paint(this);
    paint.setPen(QPen(Qt::black, 5));

    for(int i = 1; i<=2; i++)                                       //поле игры
        paint.drawLine(10, sizeCell*i, sizeCell*3, sizeCell*i);     //
                                                                    //
    for(int i = 1; i<=2; i++)                                       //
        paint.drawLine(sizeCell*i, 10, sizeCell*i, sizeCell*3);     //


    for(int i = 0; i < 3; i++)
    {
        for(int c = 0; c <3; c++)
        {
            if (statusCell[i][c] == 0)      //нолик
            {
                paint.setPen(QPen(Qt::blue, 8));
                paint.drawEllipse(sizeCell*i +10, sizeCell*c +10,sizeCell-20,sizeCell-20)  ;
            }

            else if (statusCell[i][c] == 1)     //крестик
            {
                paint.setPen(QPen(Qt::red, 8));
                paint.drawLine(sizeCell*i +20, sizeCell*c +20, sizeCell*(i+1) -20, sizeCell*(c +1) -20);
                paint.drawLine(sizeCell*(i+1) -20,sizeCell*c +20, sizeCell*i +20, sizeCell*(c +1) -20 );
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent* pe)
{
    dumpEvent(pe);
}

void MainWindow::dumpEvent(QMouseEvent* pe)             //Start
{
    if (player)  ui->label->setText("player 1");        //
    else ui->label->setText("player 2");

    int x = pe->x()/sizeCell;                           //получение координат мышки
    int y = pe->y()/sizeCell;
    if (x < 3 && y <3 && statusCell[x][y] == 2)         //было ли нажатие на свободной клетке
    {
        statusCell[x][y] = player;
        player =!player;                                //смена хода
        NumberMoves++;

        if(NumberMoves == 9)                            //заполнено ли поле
        {
            QMessageBox::information(NULL,QObject::tr("End"),tr("draw"));
            NewGame();
        }
        ScanCell();
    }
    MainWindow::update();
}

void MainWindow::ScanCell()         //проверка на окончание игры
{
    for (int i = 0; i < 3; i++)     //гориз/вериткальные лиинии
    {
        if(statusCell[i][0] != 2 && statusCell[i][0] ==statusCell[i][1]&& statusCell[i][1]==statusCell[i][2])
        {
            End(statusCell[i][0]);
            return;
        }
        if(statusCell[0][i] != 2 && statusCell[0][i] ==statusCell[1][i]&& statusCell[1][i]==statusCell[2][i])
        {
            End(statusCell[0][i]);
            return;
        }
    }

        //проверка по вертикали
    if(statusCell[0][0] != 2 && statusCell[0][0] ==statusCell[1][1]&& statusCell[1][1]==statusCell[2][2])
    {
        End(statusCell[0][0]);
        return;
    }
    if(statusCell[1][1] != 2 && statusCell[0][2] ==statusCell[1][1]&& statusCell[1][1]==statusCell[2][0])
    {
        End(statusCell[1][0]);
        return;
    }
}

void MainWindow::End(bool player)           //окончание игры
{
    if (player)
        QMessageBox::information(NULL,QObject::tr("End"),tr("Player 1 Win"));
    else
        QMessageBox::information(NULL,QObject::tr("End"),tr("Player 2 Win"));
    NewGame();
}

void MainWindow::NewGame()
{
    NumberMoves = 0;
    player = false;
    SetArr(*statusCell, 2);
    ui->label->setText("player 1");
}
void MainWindow::on_pushButton_clicked()        //рестарт
{
    NewGame();
    MainWindow::update();
}
