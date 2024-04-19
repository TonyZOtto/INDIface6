#pragma once

#pragma once

#include <QPoint>
#include <QPointF>

#include "Rational.h"

template <typename U> class PointT
{
public: // ctors
    Point() : mX(0), mY(0) {;}
    Point(const U w, const U h) : mX(w), mY(h) {;}
    Point(const QPoint qpt) : mX(qpt.width()), mY(qpt.height()) {;}
    Point(const QPointF qptf) : mX(qptf.width()), mY(qptf.height()) {;}

public: // const
    U x() const { return mX; }
    U y() const { return mY; }
    bool isNull() const { return 0 == x() && 0 == y(); }

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
