#pragma once

#include <cmath>
#include <iostream>

struct GPUVector4
{
    float x;
    float y;
    float z;
    float w;
};

inline std::ostream& operator<<(std::ostream& os, GPUVector4 const& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}

inline GPUVector4 operator+(GPUVector4 const& a, GPUVector4 const& b)
{
    return GPUVector4{
        .x=a.x + b.x,
        .y=a.y + b.y,
        .z=a.z + b.z,
        .w=a.w + b.w
    };
}

inline GPUVector4 operator-(GPUVector4 const& a, GPUVector4 const& b)
{
    return GPUVector4{
        .x=a.x - b.x,
        .y=a.y - b.y,
        .z=a.z - b.z,
        .w=a.w - b.w
    };
}

inline GPUVector4 operator*(GPUVector4 const& a, float const scalar)
{
    return GPUVector4{
        .x=a.x * scalar,
        .y=a.y * scalar,
        .z=a.z * scalar,
        .w=a.w * scalar
    };
}

inline GPUVector4 operator/(GPUVector4 const& a, float const scalar)
{
    float const scalarInv = 1.0f / scalar;
    return GPUVector4{
        .x=a.x * scalarInv,
        .y=a.y * scalarInv,
        .z=a.z * scalarInv,
        .w=a.w * scalarInv
    };
}

inline float dot(GPUVector4 const& a, GPUVector4 const& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}


inline GPUVector4 VectorSet(float const x, float const y, float const z, float const w) {
    return GPUVector4(x, y, z, w);
}

inline GPUVector4 Normalize(GPUVector4 const& v) {
    float const len = std::hypot(std::hypot(v.x, v.y), std::hypot(v.z, v.w));
    if (len == 0.0f) return GPUVector4(0.0f, 0.0f, 0.0f, 0.0f);
    return GPUVector4(v.x / len, v.y / len, v.z / len, v.w / len);
}