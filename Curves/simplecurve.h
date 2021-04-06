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


    void paintGL() override;


    ~SimpleCurve()  override;




    void mousePressEvent(QMouseEvent *event) override ;


    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    static SimpleCurve* CreateQuadraticCurve(int numOfSamples);

    static SimpleCurve* CreateCubicCurve(int numOfSamples);




protected:
    BezierCurve* bezierCurve;

    void update() override;



};

#endif // SIMPLECURVE_H
