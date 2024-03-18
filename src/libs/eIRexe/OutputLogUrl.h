#pragma once

#include "BaseLogUrl.h"

class OutputLogUrl : public BaseLogUrl
{
public:
    OutputLogUrl();
    OutputLogUrl(const QString &s);

public:
    virtual Log::UrlType type() const { return Log::OutputUrl; }

private:

};
