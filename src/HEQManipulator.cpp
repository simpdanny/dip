#include <cmath>
#include "HEQManipulator.h"

void HEQManipulator::analyze( const RawImage& img ) {
    auto hist = img.getHistogram();
    setByHistogram( hist ); 
}

void HEQManipulator::setByHistogram( const Histogram& hist ) {
    if ( hist.empty() )
        return;
    int total_count = hist.getTotalCount();
    auto c = hist.getMinX();
    int accumulative = 0;
    while( true ) {
        int count = hist.getCount(c);
        if ( count == 0) {
            c++;
            continue;
        }
        accumulative += count;
        this->operator[](c) = hist.getHEQValue( accumulative);
        if ( accumulative == total_count )
            break;
        c++;
    }

}
