#include "beziercurve.h"


BezierCurve::BezierCurve(int numOfControlPoints): numOfControlPoints(numOfControlPoints) {
    controlPoints = new QList<ControlPoint*>();
    bezierPoints = new QList<LinePoint*> ();
}

void BezierCurve::drawCurve() {
    for (LinePoint* p : *bezierPoints)    {
        glPointSize(p->getSize());
        QColor c = p->getColor();
        glColor3f(c.red(), c.green(), c.blue());
        glBegin(GL_POINTS);
        glVertex2d(p->getX(), p->getY());
        glEnd();
    }
}


ControlPoint* BezierCurve::getControlPoint(QPointF p)  const {
    QList<ControlPoint*>::const_iterator it = std::find_if(controlPoints->begin(), controlPoints->end(), [&p](const ControlPoint* point)  {
        return point->overlap(p);        });
    if (it != controlPoints->end())
        return *it;
    else return nullptr;
}

QList<ControlPoint*> BezierCurve::getSelectedControlPoints() const   {
    QList<ControlPoint*> selected_points = QList<ControlPoint*>();
    QList<ControlPoint*>::const_iterator it = controlPoints->begin(), end = controlPoints->end();
    while (it != end)   {
        it = std::find_if(it, end, [](const ControlPoint* point)    {
                                                       return point->isSelected();  });
        if (it != end)
        {
            selected_points.push_back(*it);
            it++;
        }
    }

    return selected_points;
}

void BezierCurve::addControlPoint (QPointF& point)  {
    if (controlPoints->size() < numOfControlPoints)  {
        controlPoints->append(new ControlPoint(point));
    }
}

void BezierCurve::addControlPoint (ControlPoint& point)  {
    if (controlPoints->size() < numOfControlPoints)  {
        controlPoints->append(new ControlPoint(point));
    }
}


QList<ControlPoint*>* BezierCurve::getControlPoints()  const {
    return controlPoints;
}

void BezierCurve::updatePoints(int numOfSamples)  {
    if (controlPoints->size() == numOfControlPoints) {
        double increment = 1 / qreal(numOfSamples - 1);
        bezierPoints->clear();
        for (double t = 0; t < qreal(1) || Utils::Equal(t, 1); t+=increment)    {
            bezierPoints->append(calcPoint(t));
        }
    }
}

void BezierCurve::deselect() {
    QList<ControlPoint*> selected_points = getSelectedControlPoints();
    for (ControlPoint* p : selected_points)
        p->deselect();
}

void BezierCurve::dragPoint(QPointF point) {
    QList<ControlPoint*> selected_points = getSelectedControlPoints();
    for (ControlPoint* p : selected_points)
        p->drag(point);
    }

LinePoint* BezierCurve::calcPoint(double t)  const {

    double x = 0, y =0;
    for (int i =0; i<controlPoints->size(); ++i) {
        double tmp = Utils::binomialCoeff(numOfControlPoints - 1, i)
                * pow(1 - t, numOfControlPoints - i - 1) * pow(t,i);
        x += tmp * controlPoints->at(i)->getX();
        y += tmp * controlPoints->at(i)->getY();
    }

    return new LinePoint(t, x, y);
}

QList<LinePoint*>* BezierCurve::getBezierPoints()  const {
    return bezierPoints;
}

void BezierCurve::setBezierPoints(QList<LinePoint*>* bezierPoints) {
    this->bezierPoints = bezierPoints;
}


BezierCurve::~BezierCurve() {

    for (int i = 0; i < bezierPoints->size(); ++i)
        delete bezierPoints->at(i);
    for (int i = 0; i < controlPoints->size(); ++i)
        delete controlPoints->at(i);
}
