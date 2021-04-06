/**************************************************************************
** QT Project
**   Author: Mark Drozd Admin
**   Created: 4/6/2021
**   Environment variables:
**************************************************************************/

#include "simplecurve.h"

void SimpleCurve::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT);
    QList<ControlPoint*>* control_points = bezierCurve->getControlPoints();
    for (ControlPoint* p : *control_points)
        p->draw();
    bezierCurve->drawCurve();
}


SimpleCurve::~SimpleCurve()   {
    bezierCurve->~BezierCurve();
    delete bezierCurve;

}


void SimpleCurve::mousePressEvent(QMouseEvent *event)   {

    Curve::mousePressEvent(event);
    QPointF point = event->pos();
    if (event->button() == Qt::LeftButton)  {
    ControlPoint* controlPoint = bezierCurve->getControlPoint(point);
        if (controlPoint == nullptr)    {
            if (bezierCurve->getControlPoints()->size() < bezierCurve->getNumOfControlPoints())  {
                bezierCurve->addControlPoint(point);
                update();
            }
        }
        else
            controlPoint->select(point);
    }
    event->accept();
}


void SimpleCurve::mouseReleaseEvent(QMouseEvent *event) {
    Curve::mouseReleaseEvent(event);
    bezierCurve->deselect();
}

void SimpleCurve::mouseMoveEvent(QMouseEvent *event)    {

    Curve::mouseMoveEvent(event);

    if (event->buttons() == Qt::LeftButton)  {
        bezierCurve->dragPoint(event->pos());
    }   else    {
        ControlPoint* point = bezierCurve->getControlPoint(event->pos());
        if (point != nullptr)
            setCursor(Qt::OpenHandCursor);
        else setCursor(Qt::ArrowCursor);
    }
    update();
}

SimpleCurve* SimpleCurve::CreateQuadraticCurve(int numOfSamples)   {
    SimpleCurve* curve = new SimpleCurve(numOfSamples);
    curve->bezierCurve = new QuadraticBezierCurve();
    return curve;
}

SimpleCurve* SimpleCurve::CreateCubicCurve(int numOfSamples)   {
    SimpleCurve* curve = new SimpleCurve(numOfSamples);
    curve->bezierCurve = new CubicBezierCurve();
    return curve;
}


BezierCurve* bezierCurve;

void SimpleCurve::update()  {
    bezierCurve->updatePoints(getNumOfSamples());
    updateGL();
}
