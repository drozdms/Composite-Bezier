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
    qreal scale;
    QPointF center_;
    boost::optional<QPointF> move_point;

public:
    Curve(QWidget* parent) : QGLWidget(parent)  {
        move_point = boost::none;
    }
    Curve(int numOfSamples) : numOfSamples(numOfSamples)    {
        move_point = boost::none;
    }
    Curve(Curve& other) : Curve(other.getNumOfSamples()) {}

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
    virtual void mouseMoveEvent(QMouseEvent *) override {};
    virtual void mousePressEvent(QMouseEvent * ) override {};
    virtual void mouseReleaseEvent(QMouseEvent* ) override {};
  //  virtual void

//    void resizeGL(int w, int h) override;

    void initializeGL() override;

//    void wheelEvent(QWheelEvent*) override;

//    QPointF screen_to_global(QPointF const & screen_pos) const;
};

#endif // CURVE_H
