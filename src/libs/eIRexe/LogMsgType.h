#pragma once

#include <QtGlobal>
#include <QtDebug>
#include <QDebug>

class LogMsgType
{
public: // types
    enum Type
    {
        $null = -1,
        Debug       = QtDebugMsg,
        Warning     = QtWarningMsg,
        Error       = QtCriticalMsg,
        Fatal       = QtFatalMsg,
        Info        = QtInfoMsg,
    };

public: // ctors
    LogMsgType();
    LogMsgType(const QtMsgType qmt);
    LogMsgType(const int i);
    LogMsgType(const LogMsgType &other);

public: // const
};
