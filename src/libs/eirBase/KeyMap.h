#pragma once
#include "eIRbase.h"

#include <QMap>
#include <QVariant>

#include "Key.h"

class EIRBASE_EXPORT KeyMap : public QMap<Key, QVariant>
{
public:
    KeyMap();


};

