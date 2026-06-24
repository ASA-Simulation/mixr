#include "mixr/base/colors/Color.hpp"

namespace mixr {
namespace base {

IMPLEMENT_SUBCLASS(Color, "Color")
EMPTY_SLOTTABLE(Color)
EMPTY_DELETEDATA(Color)

constinit double Color::s_default_alpha = 1.0;

//------------------------------------------------------------------------------
// data access functions
//------------------------------------------------------------------------------
Color::operator const t_Vec3*() const
{
    return reinterpret_cast<const t_Vec3*>( &m_values );
}

Color::operator const t_Vec4*() const
{
    return &m_values;
}

// Return the color vector of color array index PF_RED
double Color::red() const
{
    return m_values[RED];
}

// Return the color vector of color array index PF_GREEN
double Color::green() const
{
    return m_values[GREEN];
}

// Return the color vector of color array index PF_BLUE
double Color::blue() const
{
    return m_values[BLUE];
}

// Return the color vector of color array index PF_ALPHA
double Color::alpha() const
{
    return m_values[ALPHA];
}

// Get the address of the color vector array(3)
const t_Vec3* Color::getRGB() const
{
    // Note: Color is a Vec4, which is just a four element array [ r g b a ], and
    // we're reinterpreting it as a Vec3, which is a three element array [ r g b ].
    return reinterpret_cast<const t_Vec3*>( &m_values );
}

// Get the address of the color vector array(4)
const t_Vec4* Color::getRGBA() const
{
    return &m_values;
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------

bool Color::setRed(const double value)
{
    bool ok{value >= 0 && value <= 1};
    if (ok) m_values[Color::RED] = value;
    return ok;
}

bool Color::setGreen(const double value)
{
    bool ok{value >= 0 && value <= 1};
    if (ok) m_values[Color::GREEN] = value;
    return ok;
}

bool Color::setBlue(const double value)
{
    bool ok{value >= 0 && value <= 1};
    if (ok) m_values[Color::BLUE] = value;
    return ok;
}

bool Color::setAlpha(const double value)
{
    bool ok{value >= 0 && value <= 1};
    if (ok) m_values[Color::ALPHA] = value;
    return ok;
}

//------------------------------------------------------------------------------
// Comparison operators: == and !=
//------------------------------------------------------------------------------
bool operator==(const Color& c1, const Color& c2)
{
    return (c1.getRGBA() == c2.getRGBA());
}

bool operator!=(const Color& c1, const Color& c2)
{
    return (c1.getRGBA() != c2.getRGBA());
}

//------------------------------------------------------------------------------
// getDefaultAlpha() -- returns the default alpha value
//------------------------------------------------------------------------------
double Color::getDefaultAlpha()
{
   return s_default_alpha;
}

//------------------------------------------------------------------------------
// setDefaultAlpha()
//------------------------------------------------------------------------------
void Color::setDefaultAlpha(const double alpha)
{
    s_default_alpha = alpha;
}

}
}
