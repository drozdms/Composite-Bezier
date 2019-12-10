#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "Curves/curve.h"
#include "Curves/compositecurve.h"
#include "Curves/simplecurve.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
private:
    void initWidget();
    int numOfSamples;
public slots:
    void setQuadCurveWidget();
    void setCubicCurveWidget();
    void setCompCurveWidget();
    void changeNumOfSamples();

public:
    MainWindow(QWidget *parent = nullptr);

};
#endif // MAINWINDOW_H
