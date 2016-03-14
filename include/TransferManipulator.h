#include "Manipulator.h"

#ifndef TRANSFER_MANIPULATOR
#define TRANSFER_MANIPULATER

class TransferManipulator : public Manipulator {
public:
    TransferManipulator() { clear();}
    TransferManipulator( const TransferManipulator& );
    void manipulate( RawImage& ) ;
    virtual void clear();
    const unsigned char& operator[](const unsigned char& ) const;
    unsigned char& operator[](const unsigned char& ); 
    void setAsPowerLaw(double p );
    void setAsLog(double a );
    void setAsInverseLog(double a );
    void setAsInverse();
    void setAsReverse();
private:
    unsigned char _transfer[256];
};
#endif
