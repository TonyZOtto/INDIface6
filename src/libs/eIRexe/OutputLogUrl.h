#pragma once
#include "eIRexe.h"

#include "BaseLogUrl.h"

class EIREXE_EXPORT OutputLogUrl : public BaseLogUrl
{

public: // ctors
    OutputLogUrl();
    OutputLogUrl(const QString &s);
    OutputLogUrl(const QUrl &url);

public: // virtual
    virtual Log::UrlType type() const { return Log::OutputUrl; }

private:
    Log::OutputFormat parseOutFormat();


private:
    Log::OutputFormat mOutputFormat;
};
