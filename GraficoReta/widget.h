#ifndef WIDGET_H
#define WIDGET_H
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include<QChartView>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public slots:
    void slC();
    void txC();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void updatePlot();
    QtCharts::QLineSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    QSlider *slider1;
    QSlider *slider2;
    QLineEdit *linha1;
    QLineEdit *linha2;
    float xmin;
    float xmax;
    QLabel *texto1;
    QLabel *texto2;
    QLabel *texto3;
    QLabel *texto4;
    int a;
    int b;
    float x[21];
    float y[21];
    Ui::Widget *ui;
};
#endif // WIDGET_H
