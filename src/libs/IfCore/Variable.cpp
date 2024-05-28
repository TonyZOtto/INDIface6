#include "Variable.h"

#include <QtXml/QDomElement>
#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QSizeF>

#include "VariableType.h"

Variable::Variable(void)
{
}
#if 0
Variable::Variable(const VariableKey &key,
                   const QMetaType::Type varType) :
    mKey(key),
    mpType(VariableType::behavior(varType)),
    mCurrentVar(QVariant(varType)),
    mDefaultVar(QVariant(varType))
{
}
#endif
Variable::Variable(const VariableKey &key,
                   const QVariant defaultValue) :
    mKey(key),
    mpType(VariableType::behavior((QMetaType::Type)defaultValue.userType())),
    mCurrentVar(defaultValue),
    mDefaultVar(defaultValue)
{
}

Variable::Variable(const VariableKey &key,
                   const QVariant currentValue,
                   const QVariant defaultValue) :
    mKey(key),
    mpType(VariableType::behavior((QMetaType::Type)defaultValue.userType())),
    mCurrentVar(currentValue),
    mDefaultVar(defaultValue)
{
}

Variable Variable::fromString(const QString & string)
{
    int x = string.indexOf('=');
    if (x < 0)
        return Variable(VariableKey(string), true);
    else
    {
        QString name = string.left(x);
        QString value = string.mid(x+1);
        return Variable(VariableKey(name), value);
    }
}

bool Variable::isNull(void) const
{
    if (mKey.isNull()) return true;
    if ( ! mpType) return true;
    if (mDefaultVar.isNull()) return true;
    return false;
}

VariableKey Variable::key(void) const
{
    return mKey;
}

QVariant Variable::var(void) const
{
    return mCurrentVar;
}

QVariant Variable::defaultVar(void) const
{
    return mDefaultVar;
}

VariableType * Variable::variableType(void) const
{
    return mpType;
}

QString Variable::typeName(void) const
{
    return mpType->typeName();
}

void Variable::reset(void)
{
    mCurrentVar = mDefaultVar;
}

void Variable::clear(void)
{
    mCurrentVar = QVariant(mDefaultVar.metaType());
}

void Variable::set(const QVariant newValue)
{
    mCurrentVar.setValue(newValue);
}

int Variable::csvEntryCount(void) const
{
    return mpType ? mpType->csvColumns() : 0;
}

int Variable::csvHeadingCount(void) const
{
    int result = mKey.count();
    if (mpType && mpType->csvParts())
        ++result;
    return result;
}

QString Variable::csvEntryString(void) const
{
    return mpType
            ? mpType->csvString(mCurrentVar)
            : mCurrentVar.toString();
}

QString Variable::csvEntryHeading(int row) const
{
    if (mKey.isSectioned())
    {
        if (row < (int)(mKey.count()))
            return Key(mKey.segments(row, mpType->csvColumns())).toString();
        else if (row == (int)(mKey.count()))
            return mpType ? mpType->csvHeader() : QString();
    }
    else if (0 == row)
        return mKey;

    return QString();
}
