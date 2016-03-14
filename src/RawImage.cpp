#include "RawImage.h"


RawImage::RawImage( const RawImage& rawImage ) {
    *this = rawImage; 
}

const RawImage& RawImage::operator=( const RawImage& rawImage ) {
    if ( this == &rawImage )
        return rawImage;
    if ( rawImage.empty() ) {
        clear();
        return *this;
    }
    reshape( rawImage._width , rawImage._height);
    for ( int i = 0 ; i < _width ; i++ ) {
        for ( int j = 0 ; j < _height ; j++ ) {
            this->operator()( i , j ) = rawImage(i , j);
        }
    }
    return *this;
}

unsigned char& RawImage::operator()( const int& x, const int& y) {
    int i = x, j = y;
    if ( x < 0 )
        i = -1 * x;
    else if ( x >= _height )
        i = _height - 1 - ( x - _height);
    if ( y < 0 )
        j = -1 * x;
    else if ( y >= _width )
        j = _width - 1 - ( y - _width );
    return _data[ i * _width + j ];
}
const unsigned char& RawImage::operator()( const int& x, const int& y ) const {
    int i = x, j = y;
    if ( x < 0 )
        i = -1 * x;
    else if ( x >= _height )
        i = _height - 1 - ( x - _height);
    if ( y < 0 )
        j = -1 * x;
    else if ( y >= _width )
        j = _width - 1 - ( y - _width );
    return _data[ i * _width + j ];
}

bool RawImage::readFromFile( const string& filename ) {
    FILE* file;
	if ( !(file=fopen(filename.c_str(),"rb") ) ) {
        clear();
        return false;
    }
    fread( _data, sizeof(unsigned char), _width * _height, file);
    fclose(file); 
    return true; 
}

bool RawImage::writeIntoFile( const string& filename ) const {
    FILE* file;
    if ( !( file = fopen(filename.c_str(), "wb" ) ) ) {
        return false;
    }
    fwrite( _data, sizeof(unsigned char), _width * _height, file);
    fclose(file);
    return true;
}

void RawImage::clear() {
    if ( _data != NULL ) {
        delete [] _data;
        _data = NULL;
    }
    _width = _height = 0; 
}
void RawImage::reshape( const int& x , const int& y ) {
    if (  _width * _height != x * y ) {
        clear();
        _width  = x;
        _height = y; 
        _data =  new unsigned char[_width * _height]; 
    }
}

bool RawImage::empty() const {
    return _data == NULL;
}

Histogram RawImage::getHistogram() const {
    Histogram hist;
    for ( int i = 0 ; i < getHeight(); i++ ) {
        for ( int j = 0 ; j < getWidth() ; j++) {
            hist.modifyCount( this->operator()(i,j) , 1);
        }
    }
    return hist;
}
