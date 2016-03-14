#include "Manipulator.h"

RawImage Manipulator::generate( const RawImage& img ) {
    RawImage ret = img;
    manipulate( ret );
    return ret;
}

unsigned char Manipulator::double2byte( double d ) {
        if ( d >= 255 ) 
            return 255;
        if ( d <= 0 )
            return 0;
        else 
            return d;
}

void WindowManipulator::manipulate(RawImage& img) {
    const RawImage copy = img;
    _window = initWindow(copy);
    manipulateFromSlidingWindow( img , copy);
    clearWindow();
}

RawImage WindowManipulator::generate( const RawImage& img) {
    RawImage ret = img;
    _window = initWindow(img);
    manipulateFromSlidingWindow(ret , img);
    clearWindow();
    return ret; 
}

void WindowManipulator::clearWindow() {
    if (_window == NULL)
        return;
    delete _window;
    _window = NULL;
}

void WindowManipulator::manipulateFromSlidingWindow(RawImage& img, const RawImage& copy) {
    _window->setPosition(0 , 0 );
    int width = img.getWidth();
    int height = img.getHeight();
    int sign = 1;
    for ( int i = 0 ; i < height ; i++ ) {
        for ( int j = 0 ; j < width  ; j++ ) {
            img( _window->getCenterX() , _window->getCenterY() ) 
                =  double2byte( _window->getValue() ); //window.getHistogram()
            if ( j != width -1 )
                _window->slideY(sign);
        }
        _window->slideX(1);
        sign *= -1;
    }
    
}

