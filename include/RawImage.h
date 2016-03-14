#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Histogram.h"
#ifndef RAW_IMAGE
#define RAW_IMAGE
using namespace std;
class RawImage {
public:
    RawImage() {}
    RawImage(const int& width, const int& height) {
        reshape( width, height ); 
    }
    RawImage(const string& filename, const int& width, const int& height) 
        : RawImage( width, height ) {
        this->readFromFile(filename);
    }
    RawImage(const RawImage&);
    ~RawImage() { clear(); }
    const RawImage& operator=( const RawImage& );
    unsigned char& operator()( const int& x, const int& y );
    const unsigned char& operator() ( const int& x, const int& y ) const;
    bool readFromFile( const string& filename ) ;
    bool writeIntoFile( const string& filename ) const;
    void clear();
    void reshape( const int&, const int& );
    bool empty() const;
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    Histogram getHistogram() const;
private:
    unsigned char* _data = NULL;
    int _width = 0;
    int _height = 0;
};


#endif
