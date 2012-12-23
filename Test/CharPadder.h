#pragma once
#include <ostream>

using namespace std;
class CharPadder
{
    int myWidth;
    char fill;
public:
    CharPadder( int width, char fill = '0' ) : myWidth( width ), fill(fill) {}

    friend std::ostream& operator<<(
        std::ostream& stream, CharPadder const& manip )
    {
        stream.fill( manip.fill );
        stream.width( manip.myWidth );
        return stream;
    }
};
