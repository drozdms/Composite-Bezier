#ifndef QUADRATICBEZIERCURVE_H
#define QUADRATICBEZIERCURVE_H
#include "beziercurve.h"

class QuadraticBezierCurve : public BezierCurve
{

private:
    static const int NUM_OF_CONTROL_POINTS = 3;

public:
    QuadraticBezierCurve() : BezierCurve(NUM_OF_CONTROL_POINTS) {}
    ~QuadraticBezierCurve() {}

    int getNumOfControlPoints() override  {
        return NUM_OF_CONTROL_POINTS;
    }
};

#endif // QUADRATICBEZIERCURVE_H
