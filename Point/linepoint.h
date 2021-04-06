#ifndef LINEPOINT_H
#define LINEPOINT_H
#include "point.h"
#include "controlpoint.h"

class LinePoint : public Point<double>
{
private:

    static const int DEFAULT_SIZE = 3;
    static const QColor DEFAULT_COLOR;
    double t;



public:
    LinePoint(double t, double x, double y) : LinePoint(t, x, y, DEFAULT_COLOR) {}
    LinePoint(double t, double x, double y, QColor color) : Point(x, y, color, DEFAULT_SIZE), t(t) {}
    LinePoint* perpendicular()   {
        return new LinePoint(t, -getY(), getX());
    }

    double dot(LinePoint& point) {
        return getX() * point.getX() + getY() * point.getY();
    }

    LinePoint* unit()    {
        double magnitude = sqrt(pow(getX(), 2) + pow(getY(), 2));
        return new LinePoint(t, getX() / magnitude, getY() / magnitude);
    }

    LinePoint* vectorToPoint(ControlPoint& point) {
        return new LinePoint(t, getX() - point.getX(), getY() - point.getY());
    }

    double distanceTo(Point* point)  {
        return sqrt(pow(getX()- point->getX(), 2) + pow(getY() - point->getY(), 2));
    }

    double getT()   {
        return t;
    }

    void setT(double t) {
        this->t = t;
    }


    ~LinePoint()    {}


};





#endif // LINEPOINT_H
