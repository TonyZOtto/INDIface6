#include "EnumerateDirTask.h"

#include <QString>

#include "../eIRbase/KeyMap.h"
#include "../eIRexe/Log.h"
#include "../IfCore/BaseImage.h"

EnumerateDirTask::EnumerateDirTask() {;}
EnumerateDirTask::EnumerateDirTask(const KeyMap &input, const KeyMap &config, KeyMap *output)
    : BaseWorkerTask("/IfCore/Task/EnumerateDir", input, config, output) {;}

void EnumerateDirTask::run()
{
    if ( ! openDir())   return;
    if ( ! parseFilterSort())   return;
    if ( ! entryList())   return;
}

bool EnumerateDirTask::openDir()
{
    const QString cDirPath = input("/EnumerateDir/Input/Path").toString();
    const QDir cDir(cDirPath);
    if ( ! cDir.exists())
    {
//        WEXPECT(cDir.exists());
        output("EnumerateDir/Output/Error",
               "Directory does not exist: " + cDir.absolutePath());
        return false;
    }
    if ( ! cDir.isReadable())
    {
//        WEXPECT(cDir.isReadable());
        output("EnumerateDir/Output/Error",
               "Directory is not readable: " + cDir.absolutePath());
        return false;
    }
    return true;
}

bool EnumerateDirTask::parseFilterSort()
{
    const QString cNameFilterIn = input("/EnumerateDir/Input/NameFilter").toString();
    const QString cTypeFilterIn = input("/EnumerateDir/Config/TypeFilter").toString();
    const QString cSortFlagsIn = input("/EnumerateDir/Config/Sort").toString();
    // NEEDDO parse strings to enum flags
    const QQStringList cNameFilters = BaseImage::supportedFileExtensionList();
    // NEEDDO intersect with specified strings
    const QDir::Filters cFilters = QDir::Files;
    const QDir::SortFlags cSortFlags = QDir::Time;

    mNameFilters = cNameFilters;
    mFilters = cFilters;
    mSortFlags = cSortFlags;
    return true;
}

bool EnumerateDirTask::entryList()
{
    bool result = false;
    mFileInfoOutput = mDir.entryInfoList(mNameFilters, mFilters, mSortFlags);
    result = ! mFileInfoOutput.isEmpty();
    if ( ! result)
    {
        output("EnumerateDir/Output/Error",
               "No Files exist: " + mNameFilters.join(';') + " in: " + mDir.absolutePath());
    }
    return result;
}

