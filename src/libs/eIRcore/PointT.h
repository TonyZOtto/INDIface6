#pragma once

#pragma once

#include <QPoint>
#include <QPointF>

#include "Rational.h"

template <typename U> class PointT
{
public: // ctors
    PointT() : mX(0), mY(0) {;}
    PointT(const U w, const U h) : mX(w), mY(h) {;}
    PointT(const QPoint qpt) : mX(qpt.x()), mY(qpt.y()) {;}
    PointT(const QPointF qptf) : mX(qptf.x()), mY(qptf.y()) {;}

public: // const
    U x() const { return mX; }
    U y() const { return mY; }
    int intX() const { return (int)(x()); }
    int intY() const { return (int)(y()); }
    bool isNull() const { return 0 == x() && 0 == y(); }
    QPoint toQPoint() const { return QPoint(intX(), intY()); }

public: // non-const
    void x(const U xx) { mX = xx; }
    void y(const U yy) { mY = yy; }
    void nullify() { x(0), y(0); }

private:
    U mX = 0;
    U mY = 0;
};

typedef PointT<int> Point;
typedef PointT<qreal> PointF;
typedef PointT<Rational> PointR;
