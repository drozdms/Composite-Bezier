#ifndef SIMPLECURVE_H
#define SIMPLECURVE_H

#include "curve.h"

#include "../Bezier/quadraticbeziercurve.h"

class SimpleCurve   :   public Curve
{
private:

    SimpleCurve(SimpleCurve& other) : Curve(other), bezierCurve(other.bezierCurve) {}
    SimpleCurve(int numOfSamples) : Curve(numOfSamples) {}


public:
SimpleCurve(QWidget* parent) : Curve(parent) {}


    void paintGL() override {
    glClear(GL_COLOR_BUFFER_BIT);
        QList<ControlPoint*> control_points = bezierCurve->getControlPoints();
        for (ControlPoint* p : control_points)
            p->draw();
        bezierCurve->drawCurve();
    }


    ~SimpleCurve()  override   {
        bezierCurve->~BezierCurve();
        delete bezierCurve;

    }





    void mousePressEvent(QMouseEvent *event) override   {

        QPointF point = event->pos();
        ControlPoint* controlPoint = bezierCurve->getControlPoint(point);
        if (controlPoint == nullptr)    {
            if (bezierCurve->getControlPoints().size() < bezierCurve->getNumOfControlPoints())  {
                bezierCurve->addControlPoint(point);
                update();
            }
        }
        else controlPoint->select(point);
        event->accept();
    }


    void mouseReleaseEvent(QMouseEvent *event) override {
        bezierCurve->deselect();
    }

    void mouseMoveEvent(QMouseEvent *event) override    {

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

    static SimpleCurve* CreateQuadraticCurve(int numOfSamples)   {
        SimpleCurve* curve = new SimpleCurve(numOfSamples);
        curve->bezierCurve = new QuadraticBezierCurve();
        return curve;
    }

    static SimpleCurve* CreateCubicCurve(int numOfSamples)   {
        SimpleCurve* curve = new SimpleCurve(numOfSamples);
        curve->bezierCurve = new CubicBezierCurve();
        return curve;
    }




protected:
    BezierCurve* bezierCurve;

    void update() override  {
        bezierCurve->updatePoints(getNumOfSamples());
        updateGL();
    }






};

#endif // SIMPLECURVE_H
