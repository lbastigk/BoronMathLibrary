#pragma once

//----------------------------------------
// Includes

// Standard library
#include "BoronMath/GPU/GPUMatrix4x4/GPUMatrix4x4.h"

// BoronMath
#include <cmath>
#include <iostream>

//----------------------------------------

struct GPUVector3
{
    float x;
    float y;
    float z;
};

inline std::ostream& operator<<(std::ostream& os, GPUVector3 const& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

inline GPUVector3 operator+(GPUVector3 const& a, GPUVector3 const& b)
{
    return GPUVector3{
        .x=a.x + b.x,
        .y=a.y + b.y,
        .z=a.z + b.z
    };
}

inline GPUVector3 operator-(GPUVector3 const& a, GPUVector3 const& b)
{
    return GPUVector3{
        .x=a.x - b.x,
        .y=a.y - b.y,
        .z=a.z - b.z
    };
}

inline GPUVector3 operator*(GPUVector3 const& a, float const scalar)
{
    return GPUVector3{
        .x=a.x * scalar,
        .y=a.y * scalar,
        .z=a.z * scalar
    };
}

inline GPUVector3 operator/(GPUVector3 const& a, float const scalar)
{
    auto const scalarInv = 1.0f / scalar;
    return GPUVector3{
        .x=a.x * scalarInv,
        .y=a.y * scalarInv,
        .z=a.z * scalarInv
    };
}

inline float dot(GPUVector3 const& a, GPUVector3 const& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline GPUVector3 Cross(GPUVector3 const& a, GPUVector3 const& b) {
    return GPUVector3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

inline float Length(GPUVector3 const& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline GPUVector3 Normalize(GPUVector3 const& v) {
    float const len = Length(v);
    if (len == 0.0f) return GPUVector3(0, 0, 0);
    return v / len;
}

inline GPUVector3 GPUVector3TransformCoord(GPUVector3 const& v, GPUMatrix4x4 const& m) {
    float x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + m.w.x;
    float y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + m.w.y;
    float z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + m.w.z;
    if (float const w = v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + m.w.w; w != 0.0f) {
        x /= w;
        y /= w;
        z /= w;
    }
    return GPUVector3{
        .x=x,
        .y=y,
        .z=z
    };
}

inline GPUVector3 VectorSet(float const x, float const y, float const z) {
    return GPUVector3(x, y, z);
}