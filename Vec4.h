#ifndef __VEC4H__
#define __VEC4H__


/**
 *
 *  @file Vec4.h
 *
 *  @brief
 *
 *  @author Ren DING
 *  @date 06/10/12.
 *
 */

#include <math.h>
#include <assert.h>

// Vec4 Class

class Vec4
{
public:

    // Constructors
    Vec4();
    Vec4(float x, float y, float z, float a);   // [x, y, z, a]

    float        &operator [] (int i);
    const float  &operator [] (int i) const;

protected:

    float elt[4];
};

inline Vec4::Vec4()
{
    elt[0] = 0;
    elt[1] = 0;
    elt[2] = 0;
    elt[3] = 0;
}

inline Vec4::Vec4(float x, float y, float z, float a)
{
    elt[0] = x;
    elt[1] = y;
    elt[2] = z;
    elt[3] = a;
}

inline float &Vec4::operator [] (int i)
{
    assert( i >= 0 && i < 4 );
    return(elt[i]);
}

inline const float &Vec4::operator [] (int i) const
{
    assert( i >= 0 && i < 4 );
    return(elt[i]);
}

#endif // __VEC4H__
