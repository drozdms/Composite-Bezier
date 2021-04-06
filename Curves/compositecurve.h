#ifndef COMPOSITECURVE_H
#define COMPOSITECURVE_H

#include "curve.h"
class CompositeCurve  : public Curve
{
private:

    static const int FIRST = 0;
    static const int SECOND = 1;
    static const int THIRD = 2;
    static const int LAST = 3;
    QList<BezierCurve*> bezierCurves;
    QList<QLineF*> lines;
public:
    CompositeCurve(int numOfSamples);

    void resetCurve() override;

    void update() override;


    void paintGL() override;


    void mouseReleaseEvent(QMouseEvent* event) override;


    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    ~CompositeCurve() override;

private:

    void updateLines();

    void selectControlPoints(QPointF& point);

    void addControlPoint(QPointF& point);

    void resizeGL(int w, int h) override;

};

#endif // COMPOSITECURVE_H
