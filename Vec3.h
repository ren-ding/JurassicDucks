/**
 *
 *  @file Vec3.h
 *
 *  @brief
 *
 *  @author Ren DING
 *  @date 05/08/12.
 *
 */

#ifndef __Vec3__
#define __Vec3__

#include <math.h>
#include <assert.h>

#define SELF (*this)    // A syntactic convenience.

// Vec3 Class

class Vec3
{
public:

    // Constructors

                Vec3();
                Vec3(float x, float y, float z);   // [x, y, z]
                Vec3(const Vec3 &v);            // Copy constructor

    // Accessor functions

    int         Elts() const { return(3); };

    float        &operator [] (int i);
    const float  &operator [] (int i) const;

    float        *Ref() const;                   // Return pointer to data

    // Assignment operators

    Vec3        &operator =  (const Vec3 &a);
    Vec3        &operator += (const Vec3 &a);
    Vec3        &operator -= (const Vec3 &a);
    Vec3        &operator *= (const Vec3 &a);
    Vec3        &operator *= (float s);
    Vec3        &operator /= (const Vec3 &a);
    Vec3        &operator /= (float s);

    // Comparison operators

    bool        operator == (const Vec3 &a) const;  // v == a?
    bool        operator != (const Vec3 &a) const;  // v != a?
    bool        operator <  (const Vec3 &a) const; // v <  a?
    bool        operator >= (const Vec3 &a) const; // v >= a?

    // Arithmetic operators

    Vec3        operator + (const Vec3 &a) const;   // v + a
    Vec3        operator - (const Vec3 &a) const;   // v - a
    Vec3        operator - () const;                // -v
    Vec3        operator * (const Vec3 &a) const;   // v * a (vx * ax, ...)
    Vec3        operator * (float s) const;          // v * s
    Vec3        operator / (const Vec3 &a) const;   // v / a (vx / ax, ...)
    Vec3        operator / (float s) const;          // v / s

    Vec3        &Normalise();                       // normalise vector
    float      magnitude();                        // get the magnitude
    float      dotProduct(Vec3 dotV);              // dotProduct
    // Private...

protected:

    float elt[3];
};


//  Vec operators

inline Vec3     operator * (float s, const Vec3 &v); // s * v
inline float     dot(const Vec3 &a, const Vec3 &b);  // v . a
inline float     len(const Vec3 &v);                 // || v ||
inline float     sqrlen(const Vec3 &v);              // v . v
inline Vec3     norm(const Vec3 &v);                // v / || v ||
inline void     normalise(Vec3 &v);                 // v = norm(v)
inline Vec3     cross(const Vec3 &a, const Vec3 &b);// a x b

// --- Inlines 

inline float &Vec3::operator [] (int i)
{
    assert( i >= 0 && i < 3 );
    return(elt[i]);
}

inline const float &Vec3::operator [] (int i) const
{
    assert( i >= 0 && i < 3 );
    return(elt[i]);
}

inline Vec3::Vec3()
{
}

inline Vec3::Vec3(float x, float y, float z)
{
    elt[0] = x;
    elt[1] = y;
    elt[2] = z;
}

inline Vec3::Vec3(const Vec3 &v)
{
    elt[0] = v[0];
    elt[1] = v[1];
    elt[2] = v[2];
}


inline float *Vec3::Ref() const
{
    return((float *) elt);
}

inline Vec3 &Vec3::operator = (const Vec3 &v)
{
    elt[0] = v[0];
    elt[1] = v[1];
    elt[2] = v[2];

    return(SELF);
}

inline Vec3 &Vec3::operator += (const Vec3 &v)
{
    elt[0] += v[0];
    elt[1] += v[1];
    elt[2] += v[2];

    return(SELF);
}

inline Vec3 &Vec3::operator -= (const Vec3 &v)
{
    elt[0] -= v[0];
    elt[1] -= v[1];
    elt[2] -= v[2];

    return(SELF);
}

inline Vec3 &Vec3::operator *= (const Vec3 &a)
{
    elt[0] *= a[0];
    elt[1] *= a[1];
    elt[2] *= a[2];

    return(SELF);
}

inline Vec3 &Vec3::operator *= (float s)
{
    elt[0] *= s;
    elt[1] *= s;
    elt[2] *= s;

    return(SELF);
}

inline Vec3 &Vec3::operator /= (const Vec3 &a)
{
    elt[0] /= a[0];
    elt[1] /= a[1];
    elt[2] /= a[2];

    return(SELF);
}

inline Vec3 &Vec3::operator /= (float s)
{
    elt[0] /= s;
    elt[1] /= s;
    elt[2] /= s;

    return(SELF);
}

inline Vec3 Vec3::operator + (const Vec3 &a) const
{
    Vec3 result;

    result[0] = elt[0] + a[0];
    result[1] = elt[1] + a[1];
    result[2] = elt[2] + a[2];

    return(result);
}

inline Vec3 Vec3::operator - (const Vec3 &a) const
{
    Vec3 result;

    result[0] = elt[0] - a[0];
    result[1] = elt[1] - a[1];
    result[2] = elt[2] - a[2];

    return(result);
}

inline Vec3 Vec3::operator - () const
{
    Vec3 result;

    result[0] = -elt[0];
    result[1] = -elt[1];
    result[2] = -elt[2];

    return(result);
}

inline Vec3 Vec3::operator * (const Vec3 &a) const
{
    Vec3 result;

    result[0] = elt[0] * a[0];
    result[1] = elt[1] * a[1];
    result[2] = elt[2] * a[2];

    return(result);
}

inline Vec3 Vec3::operator * (float s) const
{
    Vec3 result;

    result[0] = elt[0] * s;
    result[1] = elt[1] * s;
    result[2] = elt[2] * s;

    return(result);
}

inline Vec3 Vec3::operator / (const Vec3 &a) const
{
    Vec3 result;

    result[0] = elt[0] / a[0];
    result[1] = elt[1] / a[1];
    result[2] = elt[2] / a[2];

    return(result);
}

inline Vec3 Vec3::operator / (float s) const
{
    Vec3 result;

    result[0] = elt[0] / s;
    result[1] = elt[1] / s;
    result[2] = elt[2] / s;

    return(result);
}

inline Vec3 operator * (float s, const Vec3 &v)
{
    return(v * s);
}

inline Vec3 &Vec3::Normalise()
{
    if(sqrlen(SELF) > 0.0) {
    SELF /= len(SELF);
}
    return(SELF);
}


inline bool Vec3::operator == (const Vec3 &a) const
{
    return(elt[0] == a[0] && elt[1] == a[1] && elt[2] == a[2]);
}

inline bool Vec3::operator != (const Vec3 &a) const
{
    return(elt[0] != a[0] || elt[1] != a[1] || elt[2] != a[2]);
}

inline bool Vec3::operator < (const Vec3 &a) const
{
    return(elt[0] < a[0] && elt[1] < a[1] && elt[2] < a[2]);
}

inline bool Vec3::operator >= (const Vec3 &a) const
{
    return(elt[0] >= a[0] && elt[1] >= a[1] && elt[2] >= a[2]);
}


inline float dot(const Vec3 &a, const Vec3 &b)
{
    return(a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

inline float len(const Vec3 &v)
{
    return(sqrt(dot(v, v)));
}

inline float sqrlen(const Vec3 &v)
{
    return(dot(v, v));
}

inline Vec3 norm(const Vec3 &v)
{
    assert(sqrlen(v) > 0.0);
    return(v / len(v));
}

inline void normalise(Vec3 &v)
{
    v /= len(v);
}

inline float Vec3::magnitude()
{
    return (float) sqrt(elt[0]*elt[0] + elt[1]*elt[1] + elt[2]*elt[2]);
}

inline float Vec3::dotProduct (Vec3 dotV)
{
    return elt[0]*dotV.elt[0] + elt[1]*dotV.elt[1] + elt[2]*dotV.elt[2];
}

inline Vec3 cross(const Vec3 &a, const Vec3 &b)
{
    Vec3 result;

    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];

    return(result);
}


#endif
