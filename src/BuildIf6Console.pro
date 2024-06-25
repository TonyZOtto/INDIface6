TEMPLATE = subdirs

SUBDIRS =           \
    eIRLog          \
    eIRbase         \
    eIRcore         \
    eIRexe          \
    IfCore          \
    If6Console      \

eIRLog.subdir       = libs/eIRLog
eIRbase.subdir      = libs/eIRbase
eIRcore.subdir      = libs/eIRcore
eIRexe.subdir       = libs/eIRexe
IfCore.subdir       = libs/IfCore
If6Console.subdir   = console/If6Console

eIRLog.depends      =
eIRbase.depends     =
eIRcore.depends     = eIRbase
eIRexe.depends      = eIRbase   eIRcore
IfCore.depends      = eIRbase   eIRcore     eIRexe
If6Console.depends  = eIRbase   eIRcore     eIRexe  IfCore

