#include <vector>
#include <set>
#include "Window.h"

using namespace std;
#ifndef FILTER
#define FILTER

class Filter {
public:
    Filter( const int& halfWidth, const int& halfHeight ) :
         _halfWidth(halfWidth) , _halfHeight(halfHeight) {}
    ~Filter() {
        clearFilter();
    }
    void initEmptyFilter();
    bool empty() const { return _filter.empty(); }
    int getHalfWidth() const { return _halfWidth;}
    int getHalfHeight() const { return _halfHeight;}
    void clearFilter();
    double& operator() ( const int& , const int& ) ;
    const double& operator() (const int& , const int& ) const ;
    void scale( const double& scale );
    virtual double operator* ( const Window& window ) const; 
protected:
    vector<double> _filter;
    int _halfWidth;
    int _halfHeight;
    
};

class LowPassFilter : public Filter  {
public:
    LowPassFilter( const double& bias )
        : Filter( 1 , 1 ) {
        initEmptyFilter();
        setBias( bias );
    }
    void setBias( const double& ); 
};

#endif
