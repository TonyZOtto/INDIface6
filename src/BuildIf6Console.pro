TEMPLATE = subdirs
#CONFIG += ORDERED

SUBDIRS =           \
    eIRbase         \
    eIRcore         \
    eIRexe          \
    If6Console      \

If6Console.subdir   =   ./console/If6Console
eIRbase.subdir      =   ./libs/eIRbase
eIRcore.subdir      =   ./libs/eIRcore
eIRexe.subdir       =   ./libs/eIRexe

eIRbase.depends     =
eIRcore.depends     =   eIRbase
eIRexe.depends      =   eIRbase eIRcore
If6Console.depends  =   eIRbase eIRcore eIRexe
