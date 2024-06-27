#pragma once

#include <QObject>

class LogOutput : public QObject
{
    Q_OBJECT
public:
    explicit LogOutput(QObject *parent = nullptr);

signals:
};
