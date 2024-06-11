#include "OutputLogUrl.h"

#include "Log.h"

OutputLogUrl::OutputLogUrl() {;}
OutputLogUrl::OutputLogUrl(const QString &s) : BaseLogUrl(Log::OutputUrl, s) {;}
OutputLogUrl::OutputLogUrl(const QUrl &url)  : BaseLogUrl(Log::OutputUrl, url) {;}

Log::OutputFormat OutputLogUrl::parseOutFormat()
{
    Log::OutputFormat result = Log::$nullOutputFormat;
    if (hasQuery("Format"))
    {
        const QString cFormat = queryValue("Format");
        if ("TextFile" == cFormat)
            result = Log::TextFileSingleOutput;
        else if ("TextFileML" == cFormat)
            result = Log::TextFileMultiOutput;
        else if ("XmlFile" == cFormat)
            result = Log::XmlFileOutput;
        else if ("DataStream" == cFormat)
            result = Log::DataFileOutput;
        else if ("TextStream" == cFormat)
            result = Log::StreamFileOutput;
        else if ("XmlRecord" == cFormat)
            result = Log::SqlRecordOutput;
        else if ("XmlSql" == cFormat)
            result = Log::SqlXmlOutput;
        else if ("XmlNoSql" == cFormat)
            result = Log::NoSqlXmlOutput;
        else
            qWarning() << "Unhandled Log Output Format:" << cFormat;
    }
    return result;
}
