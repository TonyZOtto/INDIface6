TEMPLATE = subdirs
#CONFIG += ORDERED

SUBDIRS =           \
    ./libs/eIRbase         \
    ./libs/eIRcore         \
    ./libs/eIRexe          \
    ./libs/IfCore          \
    ./console/If6Console      \

eIRbase.depends     =
eIRcore.depends     =   eIRbase
eIRexe.depends      =   eIRbase eIRcore
IfCore.depends      =   eIRbase eIRcore eIRexe
If6Console.depends  =   eIRbase eIRcore eIRexe
