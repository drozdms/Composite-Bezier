#ifndef CURVE_H
#define CURVE_H
#include <QtOpenGL>
#include "../Bezier/beziercurve.h"
#include "../Bezier/cubicbeziercurve.h"
#pragma comment( lib, "OpenGL32.lib" )
class Curve : public QGLWidget
{
private:

    int numOfSamples;

public:
    Curve(QWidget* parent) : QGLWidget(parent)  {}
    Curve(int numOfSamples) : numOfSamples(numOfSamples)    {}
    Curve(Curve& other) : numOfSamples(other.getNumOfSamples()) {}
    int getNumOfSamples() const {
        return numOfSamples;
    }
    void setNumOfSamples(int numOfSamples) {
        this->numOfSamples = numOfSamples;
        update();
        updateGL();
    }


protected:
    virtual void update() {}
    virtual void mouseMoveEvent(QMouseEvent *event) override  {};
    virtual void mousePressEvent(QMouseEvent * event) override  {};
    virtual void mouseReleaseEvent(QMouseEvent* event) override {};
  //  virtual void

    void resizeGL(int w, int h)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        QPoint size = (1. / 2) * QPoint(w, h);

        QPoint left_bottom = (-size);
        QPoint right_top   = size;

        glOrtho(0, w, h, 0, .0, 1.0);
        glViewport(0, 0, w, h);

    }

    void initializeGL() override
    {
        assert(doubleBuffer());
        setAutoBufferSwap(true);
        qglClearColor(Qt::white);
        setMouseTracking(true);
        //glEnable(GL_PROGRAM_POINT_SIZE);
    }

};

#endif // CURVE_H
