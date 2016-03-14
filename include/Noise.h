#include <random>
#include <ctime>
using namespace std;

#ifndef NOISE
#define NOISE

class Noise {
public:
    Noise() ;
    virtual void pollute( unsigned char& c);
    virtual int getRandomNoise() = 0;
private:
    
};

class GaussianNoise : public Noise {
public:
    GaussianNoise( double m = 0, double s = 1 ) : _distribution( m , s ) {}
    int getRandomNoise(); 
private:
    normal_distribution<double> _distribution;
};

class UniformNoise : public Noise { 
public:
    UniformNoise( int left = -1, int right  = 1 ) : _distribution(left , right ) {}
    int getRandomNoise(); 

private:
    uniform_int_distribution<int> _distribution;

};

class ImpulseNoise : public Noise {
public:
    ImpulseNoise( double p_white = 0.05 , double p_black = 0.05) 
        : _impulse( p_white + p_black ) , _black( p_black / ( p_black + p_white) ) {}
    void pollute( unsigned char& c );
    int getRandomNoise() ;
    
private:
    bernoulli_distribution _impulse;
    bernoulli_distribution _black;
};
#endif
