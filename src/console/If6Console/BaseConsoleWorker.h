#pragma once

#include <QObject>

class BaseConsoleWorker : public QObject
{
    Q_OBJECT
public:
    explicit BaseConsoleWorker(QObject *parent = nullptr);

signals:
};
