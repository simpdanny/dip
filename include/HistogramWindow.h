#include "Window.h"
#include "Histogram.h"
#ifndef HISTOGRAM_WINDOW
#define HISTOGRAM_WINDOW

class HistogramWindow : public Window {
public:
    HistogramWindow( const RawImage& img, const int& halfWidth , const int& halfHeight ) 
        : Window( img , halfWidth, halfHeight ) { }
    const Histogram& getHistogram() const { return _hist; }
    double getValue() const;
protected:
    void addPixel( const int& , const int& );
    void removePixel( const int&, const int& );
    
private:
    Histogram _hist; 

};


#endif
