#include "HistogramWindow.h"


void HistogramWindow::addPixel( const int& x , const int& y ) {
    _hist.modifyCount( getImage()(x,y) , 1);

}
void HistogramWindow::removePixel( const int& x , const int& y ) {
    _hist.modifyCount( getImage()(x,y) , -1);
}

double HistogramWindow::getValue() const {
    const RawImage& img = getImage();
    return getHistogram().getHEQValue( img( getCenterX() , getCenterY() ) );

}
