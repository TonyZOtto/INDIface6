#pragma once

#include "BaseWorkerTask.h"

#include <QFileInfoList>
#include <QDir>
#include <QStringList>


/*  EnumerateDirTask
 *  Key:    /IfCore/Task/EnumerateDir
 *  Input:  /EnumerateDir/Input
 *              ./Path
 *              ./NameFilter = Filename filter
 *  Config: /EnumerateDir/Config
 *              ./TypeFilter = Space delimited list of extensions
 *                  &ed with supported file types list
 *              ./Sort = default name
 *  Output: EnumerateDir/Output
 *              ./Results = QFileInfoList
 *              ./Error = message
 *  Errors: Directory does not exist
 *          Directory is not readable
 *          Parsing filters or sortflags
 *          No image files in directory
 */

class EnumerateDirTask : public BaseWorkerTask
{
public:
    EnumerateDirTask();
    EnumerateDirTask(const KeyMap &input,
                     const KeyMap &config=KeyMap(),
                     KeyMap *output=nullptr);

public: // virtual public
    virtual void run() override final;

private:
    bool openDir();
    bool parseFilterSort();
    bool entryList();

private:
    QDir mDir;
    QStringList mNameFilters;
    QDir::Filters mFilters = QDir::NoFilter;
    QDir::SortFlags mSortFlags = QDir::NoSort;
    QFileInfoList mFileInfoOutput;
};
