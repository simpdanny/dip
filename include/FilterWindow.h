#include "Window.h"
#include "Filter.h"
#ifndef FILTER_WINDOW
#define FILTER_WINDOW

class FilterWindow : public Window {
public:
    FilterWindow( const RawImage& img , const Filter& filter) 
        : Window( img, filter.getHalfWidth() , filter.getHalfHeight() ) , _filter(filter) {}
    double getValue() const {
        return _filter * (*this);
    }
protected:
    const Filter& _filter;
};


#endif
