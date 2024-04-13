# {Eclipse6}/src/useOCV.pri
CMAJOR = "CV4"
INCLUDEPATH *= ../../../3rdParty/OpenCV-v4.8.0/include  # typical #include's specify opencv2
LIBS *= -L../../../3rdParty/OpenCV-v4.8.0/x64/mingw/bin

LIBS *= -lopencv_core480d         # if DEBUG
LIBS *= -lopencv_highgui480d
LIBS *= -lopencv_imageproc480d
LIBS *= -lopencv_objdetect480d

message(............/src/useOCV.pri = $$CVMAJOR)
