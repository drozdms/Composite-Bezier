#include "mainwindow.h"
#include "QHBoxLayout"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMouseTracking(true);
  //  setLayout(new QHBoxLayout(this));
    setupUi(this);
    setCompCurveWidget();
    lineEdit->setValidator(new QIntValidator(2,10000,this));
    connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(changeNumOfSamples()));
    connect(quadCurveButton, SIGNAL(clicked()), this, SLOT(setQuadCurveWidget()));
    connect(cubCurveButton, SIGNAL(clicked()), this, SLOT(setCubicCurveWidget()));
    connect(compCurveButton, SIGNAL(clicked()), this, SLOT(setCompCurveWidget()));

    lineEdit->setText("1000");
    lineEdit->editingFinished();
    int x = 2;
    x+=1;

}


void MainWindow::initWidget()  {
    this->widget->setParent(centralWidget());
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(0, 40, 801, 541));
    this->widget->show();
}

void MainWindow::setQuadCurveWidget()  {
    this->widget->~Curve();
    this->widget = SimpleCurve::CreateQuadraticCurve(numOfSamples);
    initWidget();

  //  this->widget->close()
   // setupUi(this);
}

void MainWindow::setCubicCurveWidget()  {
    this->widget->~Curve();
    this->widget = SimpleCurve::CreateCubicCurve(numOfSamples);
    initWidget();
}

void MainWindow::setCompCurveWidget()    {
    this->widget->~Curve();
    this->widget = new CompositeCurve(numOfSamples);
    initWidget();
}


void MainWindow::changeNumOfSamples()   {

    numOfSamples = lineEdit->text().toInt();
    this->widget->setNumOfSamples(numOfSamples);
}
