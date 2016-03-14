#include <cmath>
#include "Filter.h"

void Filter::initEmptyFilter() {
    clearFilter();
    _filter.resize( (2 * _halfWidth + 1) * ( 2 * _halfHeight + 1 )  , 0 );
    (*this)( 0 , 0 ) = 1;
}
void Filter::clearFilter() {
}


double& Filter::operator() ( const int& x_offset , const int& y_offset ) {
    if ( empty() )
        initEmptyFilter();
    return _filter[ ( x_offset + _halfHeight ) * ( 2 * _halfWidth + 1 ) + y_offset + _halfHeight ];
}

const double& Filter::operator() ( const int& x_offset, const int& y_offset ) const {
    return _filter[ ( x_offset + _halfHeight ) * ( 2 * _halfWidth + 1 ) + y_offset + _halfHeight ];
}


void Filter::scale( const double& s ) {
    for ( int x = -1 ; x <= 1 ; x ++) {
        for ( int y = -1 ; y <= 1 ; y++ ) {
            (*this)(x,y) *= s;
        }
    }
    
}

double Filter::operator*( const Window& window ) const {
    const RawImage& img = window.getImage();
    double value = 0;
    int x_center = window.getCenterX();
    int y_center = window.getCenterY();
    for ( int x_offset = -1 * _halfHeight ; x_offset <= _halfHeight ; x_offset++ ) {
        for ( int y_offset = -1 * _halfWidth ; y_offset <= _halfWidth ; y_offset++ ) {
            value += (*this)( x_offset , y_offset ) 
                   * (double) ( img( x_center + x_offset , y_center + y_offset ) );
        }
    }
    return value;
}

void LowPassFilter::setBias( const double& b ) {
    for ( int x = -1 ; x <= 1 ; x ++) {
        for ( int y = -1 ; y <= 1 ; y++ ) {
            (*this)(x,y) = pow( b, 2 - abs(x) - abs(y) ) 
                         / pow( b+2 , 2 );
        }
    }

}

