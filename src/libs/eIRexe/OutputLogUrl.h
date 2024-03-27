#pragma once
#include "eIRexe.h"

#include "BaseLogUrl.h"

class EIREXE_EXPORT OutputLogUrl : public BaseLogUrl
{
public:
    OutputLogUrl();
    OutputLogUrl(const QString &s);
    OutputLogUrl(const QUrl &url);

public:
    virtual Log::UrlType type() const { return Log::OutputUrl; }

private:

};
