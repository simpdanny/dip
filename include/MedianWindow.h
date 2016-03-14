#include <set>
#include "Window.h"
using namespace std;

#ifndef MEDIAN_WINDOW
#define MEDIAN_WINDOW

class MedianWindow : public Window {
public:
    MedianWindow ( const RawImage& img, const int& halfWidth, const int& halfHeight ) 
        : Window( img , halfWidth , halfHeight ) {}
    double getValue() const { return findMedian() ; }    
protected:
    void addPixel( const int& , const int& );
    void removePixel( const int& , const int& );
    unsigned char findMedian() const ;

private:
    multiset<unsigned char> _set; 
};
#endif
