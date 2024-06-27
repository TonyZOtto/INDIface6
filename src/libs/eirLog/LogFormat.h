#pragma once

#include <QObject>

class LogFormat : public QObject
{
    Q_OBJECT
public:
    explicit LogFormat(QObject *parent = nullptr);

signals:
};
