#include "Manipulator.h"
#include "Noise.h"
#ifndef NOISE_MANIPULATOR
#define NOISE_MANIPULATOR

class NoiseManipulator {
public:
    NoiseManipulator( Noise* n = NULL) : _noise(n) {}
    void setNoise( Noise* n ) {
        _noise = n;
    }
    Noise* getNoise() const { return _noise;}
    void manipulate( RawImage& img) {
        if ( _noise == NULL )
            return;
        for ( int i = 0 ; i < img.getHeight() ; i++ ) {
            for ( int j = 0 ; j < img.getWidth() ; j++ ) {
                 _noise->pollute( img(i,j) );
            }
        }

    }
protected:
    Noise* _noise;
};


#endif
