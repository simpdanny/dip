#include "AHEQManipulator.h" 
#include "HistogramWindow.h"
Window* AHEQManipulator::initWindow( const RawImage& img) {
    return new HistogramWindow( img, _halfWidth , _halfHeight);
    
}
