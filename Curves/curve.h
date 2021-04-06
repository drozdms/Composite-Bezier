#ifndef CURVE_H
#define CURVE_H
#include <QtOpenGL>
#include "../Bezier/beziercurve.h"
#include "../Bezier/cubicbeziercurve.h"
#include <boost/optional.hpp>

class Curve : public QGLWidget
{
private:

    int numOfSamples;


public:
    Curve(QWidget* parent) : QGLWidget(parent), scale(1.0)  {
        move_point = boost::none;
    }
    Curve(int numOfSamples) : numOfSamples(numOfSamples), scale(1.0)   {
        move_point = boost::none;
    }
    Curve(Curve& other) : Curve(other.getNumOfSamples()) {}

    int getNumOfSamples() const {
        return numOfSamples;
    }

    void setNumOfSamples(int numOfSamples) {
        this->numOfSamples = numOfSamples;
        update();
    }

    void resizeGL(int w, int h) override;

    virtual void resetCurve() {};


protected:
    virtual void update() {}

    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent * ) override;
    void mouseReleaseEvent(QMouseEvent* ) override;
  //  virtual void



    void initializeGL() override;

    void wheelEvent(QWheelEvent*) override;

    QPointF screen_to_global(QPointF const & screen_pos) const;


protected:
    qreal scale;
    QPointF center_;
    boost::optional<QPointF> move_point;
};

#endif // CURVE_H
