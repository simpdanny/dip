#include "Noise.h"


static default_random_engine rng;

Noise::Noise() {
       rng.seed( time(0) ); 
}

void Noise::pollute( unsigned char& c ) {
        int n = getRandomNoise();
        if ( (int)c + n > 255 )
            c = 255;
        else if ( (int)c + n < 0)
            c = 0;
        else 
            c += n ;
}

int GaussianNoise::getRandomNoise() {
    return round(_distribution(rng) );
}

int UniformNoise::getRandomNoise() {
    return _distribution(rng);
}

void ImpulseNoise::pollute( unsigned char& c ) {
        int n = getRandomNoise();
        c =  ( n == -1 ) ? c : n;
}

int ImpulseNoise::getRandomNoise() {
        if ( !_impulse(rng) )
            return -1;
        if ( _black(rng) )
            return 0;
        else 
            return 255;
}
