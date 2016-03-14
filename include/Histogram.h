#include <iostream>
#include <iomanip>
#include <map>
#include <stdexcept>
using namespace std;

#ifndef HISTOGRAM
#define HISTOGRAM

class Histogram {
public:
    Histogram() { clear();}
    Histogram( const Histogram& );
    bool empty() const { return _accumulation[255] == 0; }
    void clear();
    void print(ostream& os, const int& unit = 15) const;
    int getCount( const unsigned char& ) const;
    int getTotalCount() const;
    unsigned char getMaxX() const;
    unsigned char getMinX() const;
    int modifyCount( const unsigned char&, const int&);
    unsigned char getHEQValue( const int& ) const;
    unsigned char getHEQValue( const unsigned char& ) const;
private:
    int _histogram[256];
    int _accumulation[256];
    unsigned char _min;
    unsigned char _max;
};

 
#endif
