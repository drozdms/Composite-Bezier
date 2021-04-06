/**************************************************************************
** QT Project
**   Author: Mark Drozd Admin
**   Created: 4/6/2021
**   Environment variables:
**************************************************************************/

#include "curve.h"



void Curve::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    QPointF size = (scale / 2) * QPointF(w, h);

    QPointF left_bottom = center_ + (-size);
    QPointF right_top   = center_ + size;


    glOrtho(left_bottom.x(), right_top.x(), left_bottom.y(), right_top.y(), -1.0, 1.0);

//     glOrtho(0, w, h, 0, .0, 1.0);
    glViewport(0, 0, w, h);

}

void Curve::initializeGL()
{
    assert(doubleBuffer());
    setAutoBufferSwap(true);
    qglClearColor(Qt::white);
//    setMouseTracking(true);
//    glEnable(GL_PROGRAM_POINT_SIZE);
}

void Curve::wheelEvent ( QWheelEvent * e )
{
   // scale+=(e->delta()/(qreal)1200);

    double old_zoom = scale;

    int delta = e->delta() / 8 / 15;
    if (delta > 0)
    {
        for (int i = 0; i != delta; ++i)
            scale /= 1.05;
    }
    else if (delta < 0)
    {
        for (int i = 0; i != delta; --i)
            scale *= 1.05;
    }

    QPointF pos(e->pos().x(), e->pos().y());
    QPointF sz(size().width() / (qreal)2, size().height() / (qreal)2);

    QPointF diff = pos - sz;
    center_ += (old_zoom - scale) * QPointF(diff.x(), diff.y());
    mouseMoveEvent(new QMouseEvent(QEvent::MouseMove, screen_to_global(e->pos()),Qt::LeftButton, nullptr, nullptr));
    resizeGL(size().width(), size().height());

   updateGL();
   e->accept();
}


QPointF Curve::screen_to_global(QPointF const & screen_pos) const
{                                                   // global means (0,0) is at the center
    QPointF pos(screen_pos.x(), screen_pos.y());
    QPointF sz(size().width() / (qreal)2, size().height() / (qreal)2);

    QPointF diff = pos - sz;
    diff.setY(-diff.y());
    return center_+scale * diff;
}


void Curve::mouseMoveEvent(QMouseEvent *event) {

    if (move_point)
    {
            const int w = size().width();
            const int h = size().height();

            QPointF pos(event->pos().x(), event->pos().y());
            QPointF sz(w / 2, h / 2);


            QPointF diff = pos - sz;
            diff.setX(-diff.x());

            center_ = *move_point + scale * diff;

            QTextStream cout(stdout);
            cout <<"event pos:" <<event->pos().x() << ' ' << event->pos().y() <<
                   "\nglobpos:" << pos.x() << ' ' << pos.y() <<
                   "\nmovepoint:"<<  move_point->x() << ' ' << move_point->y() <<
                    "\nsize:"<< size().width() << ' ' << size().height() <<

                   "\ncenterpoint:"<<  center_.x() << ' ' << center_.y() << "\n\n";



       //     move_point = pos;
            resizeGL(w, h);
             updateGL();

    }


}


void Curve::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        move_point = screen_to_global(event->pos());
}

void Curve::mouseReleaseEvent(QMouseEvent *event)   {
    if (event->button()==Qt::RightButton)
        move_point = boost::none;
}

