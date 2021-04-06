#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H
#include <QList>
#include "../Point/controlpoint.h"
#include "../Point/linepoint.h"
#include "../Utils/Utils.h"

class BezierCurve
{
private:
    int numOfControlPoints;
    QList<ControlPoint*>* controlPoints;
    QList<LinePoint*>* bezierPoints;

public:
    BezierCurve(int numOfControlPoints);

    void drawCurve();

    ControlPoint* getControlPoint(QPointF p)  const;

    QList<ControlPoint*> getSelectedControlPoints() const;

    void addControlPoint (QPointF& point);

    void addControlPoint (ControlPoint& point);

    virtual int getNumOfControlPoints() = 0;

    QList<ControlPoint*>* getControlPoints()  const;

    void updatePoints(int numOfSamples);

    void deselect();

    void dragPoint(QPointF point);


    QList<LinePoint*>* getBezierPoints() const;

    void setBezierPoints(QList<LinePoint*>* bezierPoints);

    ~BezierCurve();

private:


    LinePoint* calcPoint(double t)  const;


};



#endif // BEZIERCURVE_H
