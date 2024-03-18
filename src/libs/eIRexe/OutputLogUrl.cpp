#include "OutputLogUrl.h"

#include "Log.h"

OutputLogUrl::OutputLogUrl() {;}
OutputLogUrl::OutputLogUrl(const QString &s) : BaseLogUrl(Log::OutputUrl, s) {;}
