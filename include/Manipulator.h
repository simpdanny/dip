#include "RawImage.h"
#include "Window.h"
#ifndef MANIPULATOR
#define MANIPULATOR

class Manipulator {
public:
    Manipulator() {}
    virtual ~Manipulator() {} 
    virtual void manipulate( RawImage& ) = 0;
    virtual RawImage generate( const RawImage& img );
protected:
    unsigned char double2byte( double d );
};

class WindowManipulator : public Manipulator {
public:
    WindowManipulator() : _window(NULL) {}
    virtual void manipulate( RawImage& img)  ;
    virtual RawImage generate( const RawImage& img) ;
protected:
    virtual Window* initWindow( const RawImage& ) { return NULL;}
    void clearWindow() ;
    void manipulateFromSlidingWindow( RawImage& img, const RawImage& copy) ;
    Window* _window;
};
#endif
