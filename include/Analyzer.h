#include <cmath>
#include "RawImage.h"
#ifndef ANALYZER
#define ANALYZER

class Analyzer {
public:
    Analyzer( const RawImage& img ) 
        : _img(img) {}
    void analyze( const RawImage& another );
    double getPSNR() const {
        return 10 * log10( 255 * 255 / _mse );
    }
    double getMSE() const {
        return _mse;
    }
    double getStddev() const {
        return sqrt( _mse * getCounts() / ( getCounts() - 1) );
    }
    double getWhiteProb() const {
        return _white / getCounts(); 
    }
    double getBlackProb() const {
        return _black / getCounts(); 
    }
    int getCounts() const {
        return _img.getHeight() * _img.getWidth();
    }
private:
    const RawImage& _img;
    double _mse ;
    double _white;
    double _black;
};

#endif
