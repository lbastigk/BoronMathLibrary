#pragma once
#include <iostream>

struct GPUVector2
{
    float x;
    float y;

    GPUVector2& operator+=(GPUVector2 const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    GPUVector2& operator-=(GPUVector2 const& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

inline std::ostream& operator<<(std::ostream& os, GPUVector2 const& v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}

inline GPUVector2 operator+(GPUVector2 const& a, GPUVector2 const& b)
{
    return GPUVector2{
        .x=a.x + b.x,
        .y=a.y + b.y
    };
}

inline GPUVector2 operator-(GPUVector2 const& a, GPUVector2 const& b)
{
    return GPUVector2{
        .x=a.x - b.x,
        .y=a.y - b.y
    };
}

inline GPUVector2 operator*(GPUVector2 const& a, float const scalar)
{
    return GPUVector2{
        .x=a.x * scalar,
        .y=a.y * scalar
    };
}

inline GPUVector2 operator/(GPUVector2 const& a, float const scalar)
{
    auto const scalarInv = 1.0f / scalar;
    return GPUVector2{
        .x=a.x * scalarInv,
        .y=a.y * scalarInv
    };
}

inline float dot(GPUVector2 const& a, GPUVector2 const& b)
{
    return a.x * b.x + a.y * b.y;
}

inline float MagnitudeGPUVector2(GPUVector2 const& a, GPUVector2 const& b) {
    auto const dx = std::fabs(a.x - b.x);
    auto const dy = std::fabs(a.y - b.y);

    return dx + dy;
}