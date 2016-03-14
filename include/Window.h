#include "RawImage.h"


#ifndef WINDOW
#define WINDOW

// This class is designed to rebind image at NO time.
class Window {
public:
    Window() = delete; // forbid default constructor
    Window( const Window& ) = delete;
    Window& operator=( const Window& ) = delete;
    Window( const RawImage& img, const int& halfWidth, const int& halfHeight)  
        : _img(img) , _halfWidth(halfWidth), _halfHeight(halfHeight) { _current_x =  _current_y = -1  ; }
    virtual ~Window() {  }
    void setPosition( const int& , const int&);
    int getCenterX() const { return _current_x; }
    int getCenterY() const { return _current_y; }
    const RawImage& getImage() const { return _img;}
    virtual void slideX( const int& );
    virtual void slideY( const int& );
    void slide( const int&, const int& );
    virtual double getValue() const = 0;
protected:
    virtual void addPixel( const int& , const int&) {}
    virtual void removePixel( const int&, const int&) {}
    void clearPixels();
    const RawImage& _img;
    const int _halfWidth;
    const int _halfHeight;
private:
    int _current_x;
    int _current_y;
};

#endif
