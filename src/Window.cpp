#include <set>
#include <utility>
#include "Window.h"
using namespace std;
void Window::setPosition( const int& x , const int& y ) {
    clearPixels();
    _current_x = x;
    _current_y = y;
    for ( int i = x - _halfHeight ; i <= x + _halfHeight ; i++ ) {
        for ( int j = y - _halfWidth ; j <= y + _halfWidth ; j++ ) {
            addPixel( i , j );
        }
    }
}

void Window::slide( const int& x_offset, const int& y_offset ) {
    slideX( x_offset);
    slideY( y_offset);
}

void Window::slideX( const int& x_offset ) {
    if ( x_offset == 0 )
        return;
    int sign = ( x_offset > 0 ) ? 1 : -1;
    for ( int i = _current_x - sign * _halfHeight ; i != _current_x - sign * _halfHeight + x_offset  ; i += sign ) {
        for ( int j = _current_y - _halfWidth ; j <= _current_y + _halfWidth ; j++ ) {
            removePixel( i,j ) ;
            addPixel( i + sign * ( 2 * _halfHeight + 1 ), j );
        }
    }  
    _current_x += x_offset;
}

void Window::slideY( const int& y_offset ) {
    if ( y_offset == 0 )
        return;
    int sign = ( y_offset > 0 ) ? 1 : -1;
    for ( int j = _current_y - sign * _halfWidth ; j != _current_y - sign * _halfWidth + y_offset  ; j += sign ) {
        for ( int i = _current_x - _halfHeight ; i <= _current_x + _halfHeight ; i++ ) {
            removePixel( i,j ) ;
            addPixel( i , j  + sign * ( 2 * _halfWidth + 1 ));
        }
    } 
    _current_y += y_offset; 

}

void Window::clearPixels() {
    if ( _current_x == -1 && _current_y == -1 )
        return;
    for ( int i = _current_x - _halfHeight ; i <= _current_x + _halfHeight ; i++ ) {
        for ( int j = _current_y - _halfWidth ; j <= _current_y + _halfWidth ; j++ ) {
            removePixel( i , j );
        }
    }
    _current_x = _current_y = -1;

}
