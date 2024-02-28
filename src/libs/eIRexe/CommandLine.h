#pragma once
#include"eIRexe.h"

#include <QObject>

class EIREXE_EXPORT CommandLine : public QObject
{
public:
    CommandLine(QObject * parent=nullptr);
};
