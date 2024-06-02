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
    RectT(const PointT<U> tl, const PointT<U> br)
        : mCenterX((tl.x() + br.x()) / 2.0)
        , mCenterY((tl.y() + br.y()) / 2.0)
        , mWidth(br.x() - tl.x())
        , mHeight(br.y() - tl.y()) {;}
    RectT(const SizeT<U> sz, const PointT<U> c)
        : mCenterX(c.x())
        , mCenterY(c.y())
        , mWidth(sz.width())
        , mHeight(sz.height()) {;}
    RectT(const PointT<U> tl, const SizeT<U> sz)
        : mCenterX(tl.x() + sz.width()  / 2.0)
        , mCenterY(tl.y() + sz.height() / 2.0)
        , mWidth(sz.width())
        , mHeight(sz.height()) {;}
    RectT(const QRect qrc)
        : mCenterX(qrc.center().x())
        , mCenterY(qrc.center().x())
        , mWidth(qrc.width())
        , mHeight(qrc.height()) {;}
    RectT(const QRectF qrcf)
        : mCenterX(qrcf.center().x())
        , mCenterY(qrcf.center().x())
        , mWidth(qrcf.width())
        , mHeight(qrcf.height()) {;}

public: // const
    PointT<U> center() const { return PointT(mCenterX, mCenterY); }
    PointT<U> topLeft() const { return PointT(mCenterX - mWidth / 2.0, mCenterY - mHeight / 2.0); }
    SizeT<U> size() const { return SizeT<U>(mWidth, mHeight); }
    RectT clipped(const U clip) const;
    QRect toQRect() const { return QRect(topLeft().toQPoint(), size().toQSize()); }
    QRectF toQRectF() const { return QRectF(topLeft(), size()); }
    bool operator == (const RectT<U> &other);

public: // non-const
    void size(const U w, const U h) { mWidth = w, mHeight = h; }
    void size(const SizeT<U> sz) { size(sz.width(), sz.height()); }

private:
    U mCenterX;
    U mCenterY;
    U mWidth;
    U mHeight;
};

typedef RectT<int> Rect;
typedef RectT<qreal> RectF;
typedef RectT<Rational> RectR;

template<typename U>
inline RectT<U> RectT<U>::clipped(const U clip) const
{
    U tClipWidth = mWidth, tClipHeight = mHeight;
    if (clip) tClipWidth = (tClipWidth / clip) * clip, tClipHeight = (tClipHeight / clip) * clip;
    return RectT(center(), SizeT(tClipWidth, tClipHeight));
}

template<typename U>
inline bool RectT<U>::operator ==(const RectT<U> &other)
{
    return mCenterX == other.mCenterX && mCenterY == other.mHeight
           && mWidth == other.mWidth && mHeight == other.mCenterY;
}

