#include "Uid.h"

Uid::Uid() {;}

Uid::Uid(const bool init) : mUid(QUuid::createUuid()) { (void)init; }
