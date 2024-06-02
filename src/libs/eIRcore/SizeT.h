#pragma once

#include <QSize>
#include <QSizeF>

#include "Rational.h"

template <typename U> class SizeT
{
public: // ctors
    SizeT() : mWidth(0), mHeight(0) {;}
    SizeT(const U w, const U h) : mWidth(w), mHeight(h) {;}
    SizeT(const QSize qsz) : mWidth(qsz.width()), mHeight(qsz.height()) {;}
    SizeT(const QSizeF qszf) : mWidth(qszf.width()), mHeight(qszf.height()) {;}

public: // const
    U width() const { return mWidth; }
    U height() const { return mHeight; }
    QSize toQSize() const { return QSize(int(width()), int(height())); }
    bool isEmpty() const { return 0 == width() || 0 == height(); }
    bool isNull() const { return 0 == width() && 0 == height(); }
    bool isValid() const { return 0 < width() && 0 < height(); }

public: // non-const
    void width(const U w) { mWidth = w; }
    void height(const U h) { mHeight = h; }
    void empty() { width(0), height(0); }
    void nullify() { width(0), height(0); }
    void invalidate() { width(-1), height(-1); }

private:
    U mWidth = 0;
    U mHeight = 0;
};

typedef SizeT<int> Size;
typedef SizeT<qreal> SizeF;
typedef SizeT<Rational> SizeR;
