#include "mainwindow.h"
#include <QApplication>
#include "ConnA.hpp"

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QSlider>
#include <QLCDNumber>
#include "model.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    /*QLabel *label = new QLabel(
     "<h1><font color=blue>Hello World!</font><font color=red>123<font><h1>");
    label->setWindowTitle("First Qt!");
    label->resize(200,50);
    label->show();*/

    /*QPushButton *btn = new QPushButton("Close");
    btn->setWindowTitle("Signal % Slot");
    btn->setFont(QFont("Courier", 18, QFont::Bold));
    btn->resize(250,50);
    QObject::connect(btn, SIGNAL(clicked()), &a, SLOT(quit()));
    btn->show();*/

    /*QWidget *parent = new QWidget;
    parent->setWindowTitle("Signal & Slot");
    parent->setMinimumSize(240,140);
    parent->setMaximumSize(240,140);

    QLCDNumber *lcd = new QLCDNumber(parent);
    lcd->setGeometry(70,20,100,30);

    QSlider *slider = new QSlider(Qt::Horizontal,parent);
    slider->setRange(0,99);
    slider->setValue(0);
    slider->setGeometry(70,70,100,30);

    Model model;

    //QObject::connect(slider,SIGNAL(valueChanged(int)),lcd,SLOT(display(int)));

    QObject::connect(slider,SIGNAL(valueChanged(int)),
                     &model,SLOT(setValue(int)));

    QObject::connect(&model,SIGNAL(valueChanged(int)),
                     lcd,SLOT(display(int)));

    parent->show();*/

    return a.exec();
}
