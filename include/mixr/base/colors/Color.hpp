#pragma once

#include "mixr/base/Object.hpp"
#include "mixr/base/types.hpp"

namespace mixr::base {

class Color : public Object
{
    DECLARE_SUBCLASS(Color, Object)

public:
    // Components of RGB color
    enum : t_index { RED = 0, GREEN = 1, BLUE = 2, ALPHA = 3 };

public:
    Color() = default;

    operator const t_Vec3*() const;
    operator const t_Vec4*() const;

    double red() const;
    double green() const;
    double blue() const;
    double alpha() const;

    virtual bool setRed(const double r);
    virtual bool setGreen(const double g);
    virtual bool setBlue(const double b);
    virtual bool setAlpha(const double a);

    const t_Vec3* getRGB() const;
    const t_Vec4* getRGBA() const;

    static double getDefaultAlpha();
    static void setDefaultAlpha(const double alpha);

protected:
    t_Vec4 m_values{0.0, 0.0, 0.0, s_default_alpha}; // RGBA color vector

    constinit static double s_default_alpha;
};

}
