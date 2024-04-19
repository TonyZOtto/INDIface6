#pragma once

#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>
#include <QSize>
#include <QSizeF>

#include "PointT.h"
#include "Rational.h"
#include "SizeT.h"

template <typename U> class RectT
{
public: // ctors
    RectT() : mCenterX(0), mCenterY(0), mWidth(0), mHeight(0) {;}
    RectT(const PointT tl, const PointT br)
        : mCenterX(0), mCenterY(0), mWidth(0), mHeight(0) {;}
    RectT(const SizeT sz, const PointT c)
        : mCenterX(0), mCenterY(0), mWidth(0), mHeight(0) {;}
    RectT(const PointT tl, const SizeT sz)
        : mCenterX(0), mCenterY(0), mWidth(0), mHeight(0) {;}
    RectT(const QRect qrc)
        : mCenterX(0), mCenterY(0), mWidth(0), mHeight(0) {;}
    RectT(const QRectF qrcf)
        : mCenterX(0), mCenterY(0), mWidth(0), mHeight(0) {;}

public: // const

public: // non-const

private:
    U mCenterX;
    U mCenterY;
    U mWidth;
    U mCenterX;
};

typedef RectT<int> Rect;
typedef RectT<qreal> RectF;
typedef RectT<Rational> RectR;
