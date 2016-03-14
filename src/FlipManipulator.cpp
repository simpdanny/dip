#include "FlipManipulator.h"

void FlipManipulator::manipulate( RawImage& img ) {
    int width = img.getWidth();
    int height = img.getHeight();
    if ( _horizontal ) {
        for ( int i = 0 ; i < height ; i++ ) {
            for ( int j = 0 ; j < width / 2 ; j++ ) {
                img(i , j) ^= img(i, width - 1 -j) ^= img(i, j) ^= img( i , width - 1 - j );
            }
        }
    }
    if ( _vertical ) {
        for ( int i = 0 ; i < height / 2 ; i++ ) {
            for ( int j = 0 ; j < width ; j++ ) {
                img(i,j) ^= img(height-1-i,j) ^= img(i,j) ^= img(height-1-i,j);
            }
        }
    }


}

