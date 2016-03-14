#include "MedianWindow.h"

using namespace std;
void MedianWindow::addPixel( const int& x, const int& y ) {
    _set.insert( getImage()(x,y) );
}
void MedianWindow::removePixel( const int& x, const int& y ) {
    _set.erase(  _set.find( getImage()(x,y) ) );
}

unsigned char MedianWindow::findMedian() const {
    int index = ( 2 * _halfWidth + 1 ) * ( 2* _halfHeight + 1 ) / 2;
    auto it = _set.begin();
    advance( it , index );
    return *it;
}
