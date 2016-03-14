#include <cmath>
#include "TransferManipulator.h"
TransferManipulator::TransferManipulator( const TransferManipulator& transfer ) {
    for ( int i = 0 ; i < 256 ; i++ ) {
        _transfer[i] =  transfer._transfer[i];
    }

}

void TransferManipulator::manipulate( RawImage& img) {
    for ( int i = 0 ; i < img.getHeight(); i++ ) {
        for ( int j = 0 ; j < img.getWidth(); j++ ) {
            img(i , j) = _transfer[ (int) img(i,j) ];
        }
    }
}

void TransferManipulator::clear() {
    for ( int i = 0 ; i < 256 ; i++ ) {
        _transfer[i] = i;
    }

}

const unsigned char& TransferManipulator::operator[]( const unsigned char& input ) const {
    return _transfer[ input ];
}

unsigned char& TransferManipulator::operator[]( const unsigned char& input ) {
    return _transfer[ input ];
}

void TransferManipulator::setAsPowerLaw( double p ) {
    if ( p <= 0 )
        return;
    for ( int i = 0 ; i < 256 ; i++ ) {
        _transfer[i] = round( pow( double(i) / 255.0 , p ) * 255.0 );
    }
}

void TransferManipulator::setAsLog( double a ) {
    if ( a <= 0 )
        return;
    for ( int i = 0 ; i < 256 ; i++ ) {
        _transfer[i] = round( log( 1.0 + a * (double)i / 255.0 ) / log ( 1.0 + a ) * 255 );
    }
}

void TransferManipulator::setAsInverseLog( double a ) {
    if ( a <= 0 )
        return;
    for ( int i = 0 ; i < 256 ; i++ ) {
        _transfer[i] = round( (pow(1 + a , (double)i / 255.0 ) / a - 1.0 / a) * 255 );
    }
}

void TransferManipulator::setAsInverse() {
    for ( int i = 0 ; i < 26 ; i++) {
        _transfer[i] = 255;
    }
    for ( int i = 26 ; i < 256 ; i++ ) {
        _transfer[i] = round( 0.1 / double(i) * 255.0 * 255.0);
    }
}
void TransferManipulator::setAsReverse() {
    for ( int i = 0 ; i < 256 ; i++) {
        _transfer[i] = 255 - i;
    }
}
