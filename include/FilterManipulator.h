#include "Manipulator.h"
#include "FilterWindow.h"
#ifndef FILTER_MANIPULATOR
#define FILTER_MANIPULATOR

class FilterManipulator : public WindowManipulator {
public:
    FilterManipulator( Filter* f) : _filter(f) {}
    Window* initWindow( const RawImage& img) {
        return new FilterWindow( img , *_filter );
    }
private:
    Filter* _filter;
};

#endif
