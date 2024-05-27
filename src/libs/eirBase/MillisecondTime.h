#ifndef MILLISECONDS_H
#define MILLISECONDS_H
#include "eirBase.h"

#include <QtGlobal>
#include <QDateTime>

class EIRBASE_EXPORT MillisecondTime
{
public: // ctors
    MillisecondTime(void);
    MillisecondTime(qint64 ems);
    MillisecondTime(const QDateTime & dt);

public: // const
    bool isNull(void) const;
    bool isBaseNull(void) const;
    bool isValid(void) const;
    MillisecondTime delta(MillisecondTime ems=current()) const;
    QDateTime toDateTime(void) const;
    QString toString(const QString & format=QString()) const;
    operator qint64(void) const;

public: // const
    void set(const MillisecondTime other);
    MillisecondTime & operator += (const MillisecondTime d);
    MillisecondTime & operator -= (const MillisecondTime d);
    void nullify(void);

public: // static
    static qint64 base(void);
    static MillisecondTime null(void);
    static MillisecondTime deltaBase(MillisecondTime ems=current());
    static QString baseString(const QString & format=QString());
    static MillisecondTime current(void);
    static MillisecondTime fromIso(const QString & isoDateTime);
    static MillisecondTime fromString(const QString & dateTime);

private:
    qint64 mEpochMS;
    static const QDateTime smBaseDateTime;
    static const MillisecondTime smBaseMST;
    static const MillisecondTime smNullMST;
};

#endif // MILLISECONDS_H
