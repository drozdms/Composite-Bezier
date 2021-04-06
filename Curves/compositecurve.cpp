/**************************************************************************
** QT Project
**   Author: Mark Drozd Admin
**   Created: 4/6/2021
**   Environment variables:
**************************************************************************/

#include "compositecurve.h"

CompositeCurve::CompositeCurve(int numOfSamples) : Curve(numOfSamples)  {
    bezierCurves = QList<BezierCurve*>();
    bezierCurves.append(new CubicBezierCurve());
    lines = QList<QLineF*>();
}

void CompositeCurve::update()  {
    for (BezierCurve* c: bezierCurves)   {
        c->updatePoints(getNumOfSamples());
    }

    updateLines();
    updateGL();
}


void CompositeCurve::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto curve : bezierCurves) {
        QList<ControlPoint*>* controlPoints = curve->getControlPoints();
        for (auto point : *controlPoints)
            point->draw();
        curve->drawCurve();
    }

    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);

    for (auto l : lines)    {
        glBegin(GL_LINES);
        glVertex2d(l->x1(), l->y1());
        glVertex2d(l->x2(), l->y2());
        glEnd();
    }

    glPopAttrib();


}




void CompositeCurve::mouseReleaseEvent(QMouseEvent* event) {
//    Curve::mouseReleaseEvent(event);
//    if (event->button() == Qt::LeftButton)  {
        for (auto curve : bezierCurves)
            curve->deselect();
//    }
}



void CompositeCurve::mouseMoveEvent(QMouseEvent *event)    {

//    Curve::mouseMoveEvent(event);
    QPointF point = event->pos();
    if (event->buttons() == Qt::LeftButton)  {
        for (BezierCurve* curve : bezierCurves)  {
            QList<ControlPoint*> selected_control_points = curve->getSelectedControlPoints();
            for (ControlPoint* p : selected_control_points)
                p->drag(point);
        }

        update();
        updateGL();

    }   else    {

        QList<BezierCurve*>::iterator it = std::find_if(bezierCurves.begin(), bezierCurves.end(),
                                                  [&point](const BezierCurve* curve){
            ControlPoint* control_point = curve->getControlPoint(point);
            if (control_point != nullptr)
                return true;
            return false;
        });

        if (it != bezierCurves.end())
            setCursor(Qt::OpenHandCursor);
        else setCursor(Qt::ArrowCursor);
    }

}

void CompositeCurve::mousePressEvent(QMouseEvent *event)   {

//    Curve::mousePressEvent(event);

    QPointF point = event->pos();
//    if (event->button() == Qt::LeftButton)    {
        QList<BezierCurve*>::iterator it = std::find_if(bezierCurves.begin(), bezierCurves.end(),
                                                  [&point](const BezierCurve* curve){
            ControlPoint* control_point = curve->getControlPoint(point);
            if (control_point != nullptr)
                return true;
            return false;
        });

        if (it == bezierCurves.end())   {
             addControlPoint(point);
             this->updateGL();
        }
        else
            selectControlPoints(point);
//    }

//    event->accept();

}

CompositeCurve::~CompositeCurve() {

    for (int i = 0; i<bezierCurves.size(); ++i)
        delete bezierCurves[i];
    for (int i = 0; i<lines.size(); ++i)
        delete lines[i];
}



void CompositeCurve::updateLines()  {
    lines.clear();
    for (int i =0; i<bezierCurves.size()-1; ++i)    {
        ControlPoint* from = bezierCurves.at(i)->getControlPoints()->
                at(bezierCurves.at(i)->getControlPoints()->size()-2);
        ControlPoint* to = bezierCurves.at(i+1)->getControlPoints()->
                at(1);
        lines.append(new QLineF(from->getX(), from->getY(), to->getX(), to->getY()));
    }
}

void CompositeCurve::selectControlPoints(QPointF& point)  {

    for (int i = 0; i<bezierCurves.size(); ++i) {

        BezierCurve* previous = i > 0 ? bezierCurves.at(i-1) : nullptr;
        BezierCurve* curve = bezierCurves.at(i);
        BezierCurve* next = i < bezierCurves.size() - 1 ? bezierCurves.at(i+1) : nullptr;

        ControlPoint* cp = curve->getControlPoint(point);
        if (cp != nullptr)  {
            cp->select(point);
            if (next != nullptr && cp == curve->getControlPoints()->at(THIRD))   // THIRD CONTROL POINT -- BINDED TO SECOND OF NEXT
                next->getControlPoints()->at(SECOND)->inverseSelect(point);
            if (previous != nullptr && cp == curve->getControlPoints()->at(SECOND))  // SECOND CONTROL POINT -- BINDED TO THIRD OF PREVIOUS
                previous->getControlPoints()->at(THIRD)->inverseSelect(point);
            if (cp == curve->getControlPoints()->at(FIRST))          // ENSURE THAT TILT VECTOR MOVES ALONG WITH ENDING VERTICES
                    curve->getControlPoints()->at(SECOND)->select(point);
            if (curve->getControlPoints()->size() > LAST && cp == curve->getControlPoints()->at(LAST))
                curve->getControlPoints()->at(THIRD)->select(point);
        }
    }
}

void CompositeCurve::addControlPoint(QPointF& point)    {

    BezierCurve* last = bezierCurves.at(bezierCurves.size() - 1);
    last -> addControlPoint(point);
    last -> updatePoints(getNumOfSamples());
    if (last->getControlPoints()->size() == last->getNumOfControlPoints())   {

        CubicBezierCurve* newCurve = new CubicBezierCurve();
        QList<ControlPoint*>* controlPoints = last->getControlPoints();
        ControlPoint* first = controlPoints->at(LAST);
        newCurve->addControlPoint(*first);
        ControlPoint* previous = controlPoints->at(THIRD);
        ControlPoint* second = first->addVector(*first->vectorToPoint(*previous));
        newCurve->addControlPoint(*second);
        lines.append(new QLineF(previous->getX(), previous->getY(), second->getX(), second->getY()));
        bezierCurves.append(newCurve);
    }
}
