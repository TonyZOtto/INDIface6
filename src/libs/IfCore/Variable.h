#ifndef VARIABLE_H
#define VARIABLE_H
#include "IfCore.h"


#include <QObject>

#include <QVariant>

class QDomElement;

#include "VariableKey.h"
class VariableType;

class IFCORE_EXPORT Variable
{
public:
    explicit Variable(void);
//    Variable(const VariableKey & key,
  //           const QMetaType::Type varType);
    // QVariant(QMetaType) deleted in Qt6
    Variable(const VariableKey & key,
             const QVariant defaultValue);
    Variable(const VariableKey & key,
             const QVariant currentValue,
             const QVariant defaultValue);
    static Variable fromString(const QString & string);
    bool isNull(void) const;
    VariableKey key(void) const;
    QVariant var(void) const;
    QVariant defaultVar(void) const;
    VariableType * variableType(void) const;
    QString typeName(void) const;
    void reset(void);
    void clear(void);
    void set(const QVariant newValue);
    int csvEntryCount(void) const;
    int csvHeadingCount(void) const;
    QString csvEntryString(void) const;
    QString csvEntryHeading(int row) const;
    //bool readXml(const QDomElement & de);
    //QDomElement writeXml(void) const;

private:
    VariableKey mKey;
    VariableType * mpType;
    QVariant mCurrentVar;
    QVariant mDefaultVar;
};

#endif // VARIABLE_H
