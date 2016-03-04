#include "RawImage.h"

#ifndef MANIPULATOR
#define MANIPULATOR

class Manipulator {
public:
    Manipulator() {}
    virtual void manipulate( RawImage& ) = 0;
}
#endif
