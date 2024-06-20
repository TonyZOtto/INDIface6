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
//    RectT clipped(const U clip) const;
    QRect toQRect() const;
    QRectF toQRectF() const { return QRectF(topLeft(), size()); }
    bool operator == (const RectT<U> &other);

public: // non-const
    void clear() { size(0), center(0, 0); }
    void center(const U x, const U y) { mCenterX = x, mCenterY = y; }
    void size(const U d) { mWidth = d, mHeight = d; }
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
/*
template<typename U>
inline RectT<U> Rect::clipped(const U aClip) const
{
    if (aClip < 2) return *this;
    int tClipWidth = mWidth, tClipHeight = mHeight;
    tClipWidth  = (tClipWidth  / aClip) * aClip,
    tClipHeight = (tClipHeight / aClip) * aClip;
    return RectT<U>(center(), SizeT<U>(tClipWidth, tClipHeight));
}
*/
template<typename U>
inline QRect RectT<U>::toQRect() const
{
    const PointT<U> cPointT = topLeft();
    const SizeT<U> cSizeT = size();
    const QPoint cQPoint = cPointT.toQPoint();
    const QSize cQSize = cSizeT.toQSize();
    return QRect(cQPoint, cQSize);
}

template<typename U>
inline bool RectT<U>::operator ==(const RectT<U> &other)
{
    return mCenterX == other.mCenterX && mCenterY == other.mHeight
           && mWidth == other.mWidth && mHeight == other.mCenterY;
}

