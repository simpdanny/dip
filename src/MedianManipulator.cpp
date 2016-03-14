#include "MedianManipulator.h"


void DirectionalMedianManipulator::manipulate( RawImage & img ) {
    const RawImage copy = img;
    _window = new MedianWindow( copy, 0 , _halfHeight );
    RawImage x = img;
    manipulateFromSlidingWindow(x , copy );
    clearWindow();
    _window = new MedianWindow( copy, _halfWidth , 0 );
    RawImage y = img;
    manipulateFromSlidingWindow(y , copy );
    clearWindow();
    for ( int i = 0 ; i < img.getHeight(); i++ ) {
        for ( int j = 0 ; j < img.getWidth() ; j++ ) {
            img(i,j) = double2byte( 0.5 * double( x(i,j) + y(i , j) ) );
        }
    }
}

RawImage DirectionalMedianManipulator::generate( const RawImage& copy ) {
    RawImage img = copy;
    _window = new MedianWindow( copy, 0 , _halfHeight );
    RawImage x = copy;
    manipulateFromSlidingWindow(x , copy );
    clearWindow();
    _window = new MedianWindow( copy, _halfWidth , 0 );
    RawImage y = copy;
    manipulateFromSlidingWindow(y , copy );
    clearWindow();
    for ( int i = 0 ; i < img.getHeight(); i++ ) {
        for ( int j = 0 ; j < img.getWidth() ; j++ ) {
            img(i,j) = double2byte( 0.5 * double( x(i,j) + y(i,j ) ) );
        }
    }
    return img;
}
