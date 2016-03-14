#include "Manipulator.h"
#include "MedianWindow.h"

#ifndef MEDIAN_MANIPULATOR
#define MEDIAN_MANIPULATOR

class MedianManipulator : public WindowManipulator {
public:
    MedianManipulator( const int& halfWidth , const int& halfHeight ) 
        : _halfWidth( halfWidth ) , _halfHeight( halfHeight ) {}
protected:
    Window* initWindow( const RawImage& img ) {
        return new MedianWindow( img , _halfWidth , _halfHeight);
    }

private:
    int _halfWidth;
    int _halfHeight;
     
};

class DirectionalMedianManipulator : public WindowManipulator {
public:
    DirectionalMedianManipulator( const int& halfWidth , const int& halfHeight ) 
        : _halfWidth( halfWidth) , _halfHeight( halfHeight ) {}
    void manipulate( RawImage& img );   
    RawImage generate( const RawImage& copy ) ;     
private:
    int _halfWidth;
    int _halfHeight; 
};
#endif
