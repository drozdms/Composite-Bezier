#ifndef CUBICBEZIERCURVE_H
#define CUBICBEZIERCURVE_H

#include "beziercurve.h"

class CubicBezierCurve: public BezierCurve
{
private:
    static const int NUM_OF_CONTROL_POINTS = 4;

public:
    CubicBezierCurve() : BezierCurve(NUM_OF_CONTROL_POINTS) {}
    ~CubicBezierCurve() {}

    int getNumOfControlPoints() override  {
        return NUM_OF_CONTROL_POINTS;
    }


};

#endif // CUBICBEZIERCURVE_H
