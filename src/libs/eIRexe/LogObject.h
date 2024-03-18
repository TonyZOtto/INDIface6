#pragma once

#include <QObject>

#include "../eIRbase/AText.h"

class Log : public QObject
{
    Q_OBJECT
public: // types
    enum Level
    {
        $nullLevel = 0,
        Level01,        // 01
        TFnArg,         // 02
        TFnLeave,       // 03
        TFnEnter,       // 04
        Level05,        // 05
        TDetail,        // 06
        Detail,         // 07
        Level08,        // 08
        TDump,          // 09
        Dump,           // 10
        Level11,        // 11
        Level12,        // 12
        TPrefer,        // 13
        Level14,        // 14
        TInfo,          // 15
        Info,           // 16
        Level17,        // 17
        Level18,        // 18
        TProgress,      // 19
        Progress,       // 20
        Level21,        // 21
        TExpect,        // 22
        Expect,         // 23
        Level24,        // 24
        Assert,         // 25
        Level26,        // 26
        TError,         // 27
        Error,          // 28
        TFatal,         // 29
        Fatal,          // 30
        System,         // 31
        $minLevel = Level01,
        $maxLevel = System,
    };
    Q_ENUM(Level);

    enum LevelFlag
    {
        Flag$Null       = 1 << $nullLevel,
        FlagLevel01     = 1 << Level01,
        FlagTFnArg      = 1 << TFnArg,
        FlagTFnLeave    = 1 << TFnLeave,
        FlagTFnEnter    = 1 << TFnEnter,
        FlagLevel05     = 1 << Level05,
        FlagTDetail     = 1 << TDetail,
        FlagDetail      = 1 << Detail,
        FlagLevel08     = 1 << Level08,
        FlagTDump       = 1 << TDump,
        FlagDump        = 1 << Dump,
        FlagLevel11     = 1 << Level11,
        FlagLevel12     = 1 << Level12,
        FlagTPrefer     = 1 << TPrefer,
        FlagLevel14     = 1 << Level14,
        FlagTInfo       = 1 << TInfo,
        FlagInfo        = 1 << Info,
        FlagLevel17     = 1 << Level17,
        FlagLevel18     = 1 << Level18,
        FlagTProgress   = 1 << TProgress,
        FlagProgress    = 1 << Progress,
        FlagLevel21     = 1 << Level21,
        FlagTExpect     = 1 << TExpect,
        FlagExpect      = 1 << Expect,
        FlagLevel24     = 1 << Level24,
        FlagAssert      = 1 << Assert,
        FlagLevel26     = 1 << Level26,
        FlagTError      = 1 << TError,
        FlagError       = 1 << Error,
        FlagTFatal      = 1 << TFatal,
        FlagFatal       = 1 << Fatal,
        FlagSystem      = 1 << System,
    };
    Q_DECLARE_FLAGS(LevelFlags, LevelFlag);
    Q_ENUM(LevelFlag);

    enum Compare
    {
        $nullCompare        = 0,
        EqualityMask        = 0x30000000,
        Equals              = 0x20000000,
        NotEqual            = 0x10000000,
        ValueMask           = 0x03000000,
        GreaterThan         = 0x02000000,
        LessThan            = 0x01000000,
        GreaterEqual        = Equals | GreaterThan,
        LessEqual           = Equals | LessThan,
    };
    Q_ENUM(Compare);

    enum UrlType
    {
        $nullUrlType = 0,
        OutputUrl,
        CacheUrl,
    };
    Q_ENUM(UrlType);

    enum OutputScheme
    {
        $nullOutputScheme = 0,
        FileOutputScheme,
        SqlOutputScheme,
    };
    Q_ENUM(OutputScheme);

    enum FileOutputFormat
    {
        $nullFileOutputFormat = 0,
        TextFileOutput,
        XmlFileOutput,
        DataFileOutput,
        StreamFileOutput,
        TableSqlOutput,
        XmlSqlOutput,
        XmlNoSqlOutput,
    };
    Q_ENUM(FileOutputFormat);

public:
    explicit Log(QObject *parent = nullptr);

public: // static
    static OutputScheme outputScheme(const AText key);

signals:
};
