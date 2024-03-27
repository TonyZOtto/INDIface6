#include "OutputLogUrl.h"

#include "Log.h"

OutputLogUrl::OutputLogUrl() {;}
OutputLogUrl::OutputLogUrl(const QString &s) : BaseLogUrl(Log::OutputUrl, s) {;}
OutputLogUrl::OutputLogUrl(const QUrl &url)  : BaseLogUrl(Log::OutputUrl, url) {;}
