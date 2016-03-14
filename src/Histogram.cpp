#include <iostream>
#include <cmath>
#include "Histogram.h"
using namespace std;


Histogram::Histogram( const Histogram& hist) {
    _min = hist._min;
    _max = hist._max;
    for ( int i = 0 ; i < 256 ; i++ ) {
        _histogram[i] = hist._histogram[i];
        _accumulation[i] = hist._accumulation[i];
    }
}


void Histogram::clear() {
    _min = 255;
    _max = 0;
    for ( int i = 0 ; i < 256 ; i++ )
        _histogram[i] = _accumulation[i] = 0;
}

void Histogram::print(ostream& os, const int& unit) const {
    for ( int i = _min ; i <= _max ; i++ ) {
        os << i << " " << _histogram[i] << endl;
    }

}
 
int Histogram::getCount( const unsigned char& index) const {
    return _histogram[index];

}
  
int Histogram::getTotalCount() const {
    return _accumulation[255];
}

unsigned char Histogram::getMaxX() const {
    return _max;
}

unsigned char Histogram::getMinX() const {
    return _min;
}

int Histogram::modifyCount( const unsigned char& index, const int& c ) {
    int before = _histogram[index];
    _histogram[index] = max( 0, _histogram[index] + c) ;
    _max = max( _max, index );
    _min = min( _min, index );
    for ( int i = index ; i < 256 ;i++)
        _accumulation[i] += _histogram[index] - before;
    return _histogram[index];
}

unsigned char Histogram::getHEQValue( const int& accumulation ) const{
    double cdf_prob = (double) accumulation / (double) _accumulation[255];
    unsigned char mapped_value = round(cdf_prob * 255.0 );
    return mapped_value;

}

unsigned char Histogram::getHEQValue( const unsigned char& c ) const{
    double cdf_prob = (double) _accumulation[c] / (double) _accumulation[255];
    unsigned char mapped_value = round(cdf_prob * 255.0 );
    return mapped_value;

}
