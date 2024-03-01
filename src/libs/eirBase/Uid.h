#pragma once

#include <QUuid>

class Uid
{
public:
    Uid(); // null
    Uid(const bool init); // time-based

private:
    QUuid mUid;
};
