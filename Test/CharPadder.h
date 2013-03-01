#pragma once
#include <ostream>

using namespace std;
class CharPadder
{
    int _width;
    char _fill;
public:
    CharPadder( int width, char fill = '0' ) : _width( width ), _fill(fill) {}

    friend std::ostream& operator<<(
        std::ostream& stream, CharPadder const& manip )
    {
        stream.fill( manip._fill );
        stream.width( manip._width );
        return stream;
    }
};
