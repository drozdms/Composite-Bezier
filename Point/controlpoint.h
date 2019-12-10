#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H
#include "point.h"

class ControlPoint : public Point<int>
{

private:

    static const int DEFAULT_SIZE = 8;
    static const QColor DEFAULT_COLOR;
    QPointF selectPoint;
    int dragging;



public:
    ControlPoint();


    ControlPoint(QPointF& p) : ControlPoint(p, DEFAULT_COLOR)
    {}

    ControlPoint(ControlPoint& p) : ControlPoint(p, DEFAULT_COLOR)
    {}

    ControlPoint(ControlPoint& p, QColor color): ControlPoint(p.getX(), p.getY(), color)
    {}


    ControlPoint(QPointF& p, QColor color) : ControlPoint(p.x(), p.y(), color)
    {}

    ControlPoint(int x, int y) : Point(x, y, DEFAULT_COLOR, DEFAULT_SIZE)
    {}

    ControlPoint(int x, int y, QColor color) : Point(x, y, color, DEFAULT_SIZE)
    {
        dragging = 0;
    }


    boolean overlap(QPointF& p) const   {
        return startX() <= p.x() && stopX() >= p.x()
                && startY() <= p.y() && stopY() >= p.y();
    }

    ControlPoint* vectorToPoint(ControlPoint& point)    const {
        return new ControlPoint(getX() - point.getX(), getY() - point.getY());
    }

    ControlPoint* addVector(ControlPoint point) const {
        return new ControlPoint(getX() + point.getX(), getY() + point.getY());
    }

    void select(QPointF point)  {
        this->selectPoint = point;
        dragging = 1;
    }

    void inverseSelect(QPointF point)   {
        this->selectPoint = point;
        dragging = -1;
    }

    void deselect() {
        dragging = 0;
    }

    bool isSelected()   const   {
        return dragging != 0;
    }

    void drag(QPointF& point)    {
        if (isSelected())   {

            this->setX((int)(this->getX()+dragging * (point.x() - selectPoint.x())));
            this->setY((int)(this->getY()+dragging * (point.y() - selectPoint.y())));
            selectPoint = point;
        }
    }

    ~ControlPoint() {}



};




#endif // CONTROLPOINT_H
