#ifndef POINT_H
#define POINT_H

#include <QColor>
#include <QtOpenGL>

template <typename T>
class Point
{

private:
    T x;
    T y;
    int size;
    QColor color;


public:
    Point(T x, T y, QColor color, int size): x(x), y(y), color(color),
   size(size)    {}

    inline void draw()  {
        glPointSize(size);
        glColor3f(color.red(), color.green(), color.blue());
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
    }

    int startX() const   {
        return x - size / 2;
    }

    int startY() const    {
        return y - size / 2;
    }

    int stopX() const    {
        return x + size/2;
    }

    int stopY() const {
        return y + size/2;
    }

    T const getX() const    {
        return x;
    }

    T const getY() const    {
        return y;
    }

    void setX(T x) {
        this->x = x;
    }

    void setY(T y)  {
        this->y = y;
    }

    int getSize()  const  {
        return size;
    }

    void setSize(int size)  {
        this->size = size;
    }

    QColor getColor()  const  {
        return color;
    }

    void setColor(QColor c)  {
        this->color = c;
    }


    virtual ~Point() = 0;





};

template<typename T>
Point<T>::~Point() {


}

#endif // POINT_H
