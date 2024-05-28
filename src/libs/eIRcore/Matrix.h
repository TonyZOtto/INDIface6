#ifndef MATRIX_H
#define MATRIX_H

#include <QPoint>
#include <QSize>
#include <QVector>

template <class T> class Matrix
{
public:
    Matrix(void) {}
    Matrix(const QSize size) { resize(size); }
    bool isEmpty(void) const { return mData.isEmpty(); }
    bool hasRow(const int y) { return y >= 0 && y < height(); }
    QSize size(void) const { return mSize; }
    int height(void) const { return mSize.height(); }
    int width(void) const { return mSize.width(); }
    void clear(void) { resize(mSize); }
    bool isValid(const int x, const int y) const
    { return x >= 0 && x < mSize.width() && y >= 0 && y < mSize.height(); }
    T at(const int x, const int y) const
    { return isValid(x, y) ? mData.at(index(x, y)) : T(); }
    T at(const QPoint pt) const
    { return at(pt.x(), pt.y()); }
    void set(const int x, const int y, const T t)
    {
        if (isValid(x, y))
        {
            mData.replace(index(x, y), t);
//          qDebug("Matrix::set(%i,%i,%i)", x, y, t);
        }
        else
            qDebug("Matrix::set(%i,%i) invalid", x, y);
    }
    void resize(const QSize size)
    { fill(T(), size); }
    void fill(T t, QSize size)
    {
        if (size.isValid())
        {
            mSize = size;
            mData.fill(t, mSize.width() * mSize.height());
        }
        else
        {
            mSize = QSize();
            mData.clear();
        }
    }
    T * row(const int y)
    {
        return (y >= 0 && y < mSize.height())
                ? mData.data() + y * mSize.width() : 0;
    }
    const T * constRow(const int y) const
    {
        return (y >= 0 && y < mSize.height())
                ? mData.data() + y * mSize.width() : 0;
    }
    Matrix operator += (Matrix other)
    {
        int n = mData.size();
        for (int x = 0; x < n; ++x)
            mData[x] += other.mData[x];
        return *this;
    }

private:
    int index(const int x, const int y) const
    { return y * mSize.width() + x; }

private:
    QSize mSize;
    QVector<T> mData;
};

#endif // MATRIX_H
