#include "Analyzer.h"

void Analyzer::analyze( const RawImage& another ) {

    _mse = _white = _black = 0;
    for ( int x = 0 ; x < another.getHeight() ; x++ ) {
        for ( int y = 0 ; y < another.getWidth() ; y++ ) {
            _mse += pow( _img(x,y) - another(x,y) , 2);
            if ( another(x,y) == 0 )
                _black += 1;
            if ( another(x,y) == 255)
                _white += 1;
        }
    }
    _mse /= another.getHeight() * another.getWidth() ;
    

}
