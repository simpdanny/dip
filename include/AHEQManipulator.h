#include "Manipulator.h"
#include "Histogram.h"

#ifndef AHEQ_MANIPULATOR
#define AHEQ_MANIPULATOR

class AHEQManipulator : public WindowManipulator {
public:
    AHEQManipulator( const int& window_half_width, const int& window_half_height ) 
        : _halfWidth( window_half_width ) , _halfHeight(  window_half_height ) {}
protected:
    void manipulateFrom( RawImage& , const RawImage& );
    Window* initWindow( const RawImage& );
private:
    int _halfWidth;
    int _halfHeight;

};

#endif
