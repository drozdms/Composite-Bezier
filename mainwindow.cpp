#include "mainwindow.h"
#include "QHBoxLayout"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMouseTracking(true);
//    setLayout(new QHBoxLayout(this));
    setupUi(this);
    setCompCurveWidget();
    lineEdit->setValidator(new QIntValidator(2,10000,this));
    connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(changeNumOfSamples()));
    connect(quadCurveButton, SIGNAL(clicked()), this, SLOT(setQuadCurveWidget()));
    connect(cubCurveButton, SIGNAL(clicked()), this, SLOT(setCubicCurveWidget()));
    connect(compCurveButton, SIGNAL(clicked()), this, SLOT(setCompCurveWidget()));
    QShortcut * shortcutReset = new QShortcut(QKeySequence(Qt::Key_Space),this,SLOT(reset()));
    shortcutReset->setAutoRepeat(false);
    lineEdit->setText("1000");
    lineEdit->editingFinished();

}


void MainWindow::initWidget()  {
    centralwidget->setParent(centralWidget());
    centralwidget->setObjectName(QString::fromUtf8("widget"));
    centralwidget->setGeometry(QRect(0, 40, 1920, 1080));
    centralwidget->show();

}

void MainWindow::setQuadCurveWidget()  {
    centralwidget->resetCurve();
    centralwidget = SimpleCurve::CreateQuadraticCurve(numOfSamples);
    initWidget();

  //  this->widget->close()
   // setupUi(this);
}

void MainWindow::setCubicCurveWidget()  {
    centralwidget->resetCurve();
    centralwidget = SimpleCurve::CreateCubicCurve(numOfSamples);
    initWidget();
}

void MainWindow::setCompCurveWidget()    {
    centralwidget->resetCurve();
    centralwidget = new CompositeCurve(numOfSamples);
    initWidget();
}


void MainWindow::changeNumOfSamples()   {

    numOfSamples = lineEdit->text().toInt();
    centralwidget->setNumOfSamples(numOfSamples);
}

void MainWindow::reset()    {

    centralwidget->resetCurve();
    centralwidget = SimpleCurve::CreateQuadraticCurve(numOfSamples);
    initWidget();
}


