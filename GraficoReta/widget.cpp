#include "widget.h"
#include "ui_widget.h"
#include <stdio.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QGroupBox>
#include <QObject>
#include <QString>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QPainter>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    a = 1;
    b = 0;
    texto1 = new QLabel("X mínimo");
    texto2 = new QLabel("X máximo");
    texto3 = new QLabel(QString("A = %1").arg(a));
    texto4 = new QLabel(QString("B = %1").arg(b));
    xmin=-10;
    xmax = 10;
    linha1 = new QLineEdit("-10");
    linha2 = new QLineEdit("10");
    QObject::connect(linha1,SIGNAL(textChanged(const QString &)),this,SLOT(txC()));
    QObject::connect(linha2,SIGNAL(textChanged(const QString &)),this,SLOT(txC()));
    slider1 = new QSlider(Qt::Horizontal);
    slider2 = new QSlider(Qt::Horizontal);
    slider1->setValue(1);
    slider1->setTickInterval(1);
    slider1->setMinimum(-10);
    slider1->setMaximum(10);
    slider2->setValue(0);
    slider2->setTickInterval(1);
    slider2->setMinimum(-10);
    slider2->setMaximum(10);
    QObject::connect(slider1,SIGNAL(valueChanged(int)),this,SLOT(slC()));
    QObject::connect(slider2,SIGNAL(valueChanged(int)),this,SLOT(slC()));
    QGroupBox *grupo1 = new QGroupBox("Gerador de Gráficos");
    QGroupBox *grupo2 = new QGroupBox();
    QHBoxLayout *loutPrincipal = new QHBoxLayout();
    QVBoxLayout *lout1 = new QVBoxLayout();
    QVBoxLayout *lout2 = new QVBoxLayout();
    setLayout(loutPrincipal);
    grupo1->setLayout(lout1);
    grupo2->setLayout(lout2);
    loutPrincipal->addWidget(grupo1);
    loutPrincipal->addWidget(grupo2);
    lout1->addWidget(texto1);
    lout1->addWidget(linha1);
    lout1->addWidget(texto2);
    lout1->addWidget(linha2);
    lout1->addWidget(texto3);
    lout1->addWidget(slider1);
    lout1->addWidget(texto4);
    lout1->addWidget(slider2);
    series = new QtCharts::QLineSeries();
    series->append(0,6);
    series->append(2,4);
    series->append(3,8);
    series->append(7,4);
    chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    lout2->addWidget(chartView);

}
Widget::~Widget()
{
    delete ui;
}
void Widget::updatePlot(){
    float deltaX = (xmax-xmin)/20;
    chart->removeSeries(series);
    series = new QtCharts::QLineSeries();
    for (int i=0;i<21;i++){
        x[i] = xmin+i*deltaX;
    }
    for (int i=0;i<21;i++){
        y[i] = a*x[i]+b;
    }
    for (int i=0;i<21;i++){
        series->append(x[i],y[i]);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();
    chartView->setRenderHint(QPainter::Antialiasing);
    printf("\ny = %dx+%d",a,b);
}
void Widget::slC(){
    QObject *obj = sender();
    if (obj==slider1){
        a = slider1->value();
        texto3->setText(QString("A = %1").arg(a));
        updatePlot();
        printf("\nMudou o a: %d",a);
    }
    else if (obj==slider2){
        b = slider2->value();
        texto4->setText(QString("B = %1").arg(b));
        updatePlot();
        printf("\nMudou o b: %d",b);

    }

}
void Widget::txC(){
    QObject *obj = sender();
    if (obj==linha1){
        xmin = linha1->text().toInt();
        updatePlot();
        printf("\nMudou o xmin: %g",xmin);
    }
    else if (obj==linha2){
        xmax = linha2->text().toInt();
        updatePlot();
        printf("\nMudou o xmax: %g",xmax);
    }

}
/*
QObject *obj = sender();
if (obj==slider1){
    a = (texto3->text()).toInt();
    printf("%d",a);
    texto3->setText(QString("A = %1").arg(a));
}*/
