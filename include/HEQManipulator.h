#include "TransferManipulator.h"
#include "Histogram.h"

using namespace std;
#ifndef HEQ_MANIPULATOR
#define HEQ_MANIPULATOR

class HEQManipulator : public TransferManipulator {
public:
    HEQManipulator() : TransferManipulator() { }
    void analyze( const RawImage& );
    void setByHistogram(const Histogram& hist);
};


#endif
