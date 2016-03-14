#include "Manipulator.h"

#ifndef FLIP_MANIPULATOR
#define FLIP_MANIPULATOR

class FlipManipulator : public Manipulator {
public:
    FlipManipulator( bool hori = false , bool vert = false) 
        : Manipulator() , _horizontal(hori), _vertical(vert) {}
    void manipulate( RawImage& ) ;
    void setMode( bool horizontal, bool vertical ) { 
        _horizontal = horizontal; 
        _vertical = vertical;
    }

private:
    bool _horizontal;
    bool _vertical;

};

#endif
