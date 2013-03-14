#ifndef __VEC2H__
#define __VEC2H__


/**
 *
 *  @file Vec2.h
 *
 *  @brief
 *
 *  @author Ren DING
 *  @date 07/10/12.
 *
 */

#include <math.h>
#include <assert.h>

// Vec2 Class

class Vec2
{
public:

    // Constructors
    Vec2();
    Vec2(float u, float v);   // [u,v]

    float        &operator [] (int i);
    const float  &operator [] (int i) const;

protected:

    float elt[2];
};


inline Vec2::Vec2()
{
    elt[0] = 0;
    elt[1] = 0;
}

inline Vec2::Vec2(float u, float v)
{
    elt[0] = u;
    elt[1] = v;
}

inline float &Vec2::operator [] (int i)
{
    assert( i >= 0 && i < 2 );
    return(elt[i]);
}

inline const float &Vec2::operator [] (int i) const
{
    assert( i >= 0 && i < 2 );
    return(elt[i]);
}

#endif // __VEC2H__
