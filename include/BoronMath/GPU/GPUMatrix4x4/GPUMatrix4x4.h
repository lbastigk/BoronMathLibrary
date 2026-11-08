#pragma once

//----------------------------------------
// Includes

// Standard library
#include <cmath>
#include <iostream>
#include <stdexcept>

// BoronMath
#include "BoronMath/GPU/GPUVector4/GPUVector4.h"

//----------------------------------------
struct GPUMatrix4x4
{
    GPUVector4 x;
    GPUVector4 y;
    GPUVector4 z;
    GPUVector4 w;
};

inline std::ostream& operator<<(std::ostream& os, GPUMatrix4x4 const& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}

inline GPUMatrix4x4 operator+(GPUMatrix4x4 const& a, GPUMatrix4x4 const& b)
{
    return GPUMatrix4x4{
        .x=a.x + b.x,
        .y=a.y + b.y,
        .z=a.z + b.z,
        .w=a.w + b.w
    };
}

inline GPUMatrix4x4 operator-(GPUMatrix4x4 const& a, GPUMatrix4x4 const& b)
{
    return GPUMatrix4x4{
        .x=a.x - b.x,
        .y=a.y - b.y,
        .z=a.z - b.z,
        .w=a.w - b.w
    };
}

inline GPUMatrix4x4 operator*(GPUMatrix4x4 const& a, float const scalar)
{
    return GPUMatrix4x4{
        .x=a.x * scalar,
        .y=a.y * scalar,
        .z=a.z * scalar,
        .w=a.w * scalar
    };
}

inline GPUMatrix4x4 operator/(GPUMatrix4x4 const& a, float const scalar)
{
    return GPUMatrix4x4{
        .x=a.x / scalar,
        .y=a.y / scalar,
        .z=a.z / scalar,
        .w=a.w / scalar
    };
}

inline GPUMatrix4x4 GPUMatrix4x4RotationRollPitchYaw(float const pitch, float const yaw, float const roll) {
    auto const cp = std::cosf(pitch);
    auto const sp = std::sinf(pitch);
    auto const cy = std::cosf(yaw);
    auto const sy = std::sinf(yaw);
    auto const cr = std::cosf(roll);
    auto const sr = std::sinf(roll);
    return GPUMatrix4x4{
        .x = GPUVector4(cr * cy + sr * sp * sy, sr * cp, -cr * sy + sr * sp * cy, 0),
        .y = GPUVector4(-sr * cy + cr * sp * sy, cr * cp, sr * sy + cr * sp * cy, 0),
        .z = GPUVector4(cp * sy, -sp, cp * cy, 0),
        .w = GPUVector4(0, 0, 0, 1),
    };
}

inline GPUMatrix4x4 GPUMatrix4x4PerspectiveFovLH(float const fovRadians, float const aspect, float const nearZ, float const farZ) {
    auto const f = 1.0f / std::tanf(fovRadians / 2.0f);
    return GPUMatrix4x4{
        .x ={ .x = f / aspect, .y = 0, .z = 0, .w = 0 },
        .y = { .x = 0, .y = f, .z = 0, .w = 0 },
        .z = { .x = 0, .y = 0, .z = farZ / (farZ - nearZ), .w = 1 },
        .w = { .x = 0, .y = 0, .z = -nearZ * farZ / (farZ - nearZ), .w = 0 },
    };
}

inline GPUMatrix4x4 IdentityGPUMatrix4x4() {
    return GPUMatrix4x4{
        .x={.x = 1, .y = 0, .z = 0, .w = 0},
        .y={.x = 0, .y = 1, .z = 0, .w = 0},
        .z={.x = 0, .y = 0, .z = 1, .w = 0},
        .w={.x = 0, .y = 0, .z = 0, .w = 1}
    };
}

inline float Determinant3x3(
    float const a1, float const a2, float const a3,
    float const b1, float const b2, float const b3,
    float const c1, float const c2, float const c3)
{
    return a1 * (b2 * c3 - b3 * c2) - a2 * (b1 * c3 - b3 * c1) + a3 * (b1 * c2 - b2 * c1);
}

inline GPUMatrix4x4 InverseGPUMatrix4x4(GPUMatrix4x4 const& m) {
    GPUMatrix4x4 inv{};

    // Käytä rowX, rowY, rowZ, rowW ja Vector4:n jäseniä x,y,z,w
    inv.x.x = Determinant3x3(m.y.y, m.y.z, m.y.w, m.z.y, m.z.z, m.z.w, m.w.y, m.w.z, m.w.w);
    inv.x.y = -Determinant3x3(m.y.x, m.y.z, m.y.w, m.z.x, m.z.z, m.z.w, m.w.x, m.w.z, m.w.w);
    inv.x.z = Determinant3x3(m.y.x, m.y.y, m.y.w, m.z.x, m.z.y, m.z.w, m.w.x, m.w.y, m.w.w);
    inv.x.w = -Determinant3x3(m.y.x, m.y.y, m.y.z, m.z.x, m.z.y, m.z.z, m.w.x, m.w.y, m.w.z);

    inv.y.x = -Determinant3x3(m.x.y, m.x.z, m.x.w, m.z.y, m.z.z, m.z.w, m.w.y, m.w.z, m.w.w);
    inv.y.y = Determinant3x3(m.x.x, m.x.z, m.x.w, m.z.x, m.z.z, m.z.w, m.w.x, m.w.z, m.w.w);
    inv.y.z = -Determinant3x3(m.x.x, m.x.y, m.x.w, m.z.x, m.z.y, m.z.w, m.w.x, m.w.y, m.w.w);
    inv.y.w = Determinant3x3(m.x.x, m.x.y, m.x.z, m.z.x, m.z.y, m.z.z, m.w.x, m.w.y, m.w.z);

    inv.z.x = Determinant3x3(m.x.y, m.x.z, m.x.w, m.y.y, m.y.z, m.y.w, m.w.y, m.w.z, m.w.w);
    inv.z.y = -Determinant3x3(m.x.x, m.x.z, m.x.w, m.y.x, m.y.z, m.y.w, m.w.x, m.w.z, m.w.w);
    inv.z.z = Determinant3x3(m.x.x, m.x.y, m.x.w, m.y.x, m.y.y, m.y.w, m.w.x, m.w.y, m.w.w);
    inv.z.w = -Determinant3x3(m.x.x, m.x.y, m.x.z, m.y.x, m.y.y, m.y.z, m.w.x, m.w.y, m.w.z);

    inv.w.x = -Determinant3x3(m.x.y, m.x.z, m.x.w, m.y.y, m.y.z, m.y.w, m.z.y, m.z.z, m.z.w);
    inv.w.y = Determinant3x3(m.x.x, m.x.z, m.x.w, m.y.x, m.y.z, m.y.w, m.z.x, m.z.z, m.z.w);
    inv.w.z = -Determinant3x3(m.x.x, m.x.y, m.x.w, m.y.x, m.y.y, m.y.w, m.z.x, m.z.y, m.z.w);
    inv.w.w = Determinant3x3(m.x.x, m.x.y, m.x.z, m.y.x, m.y.y, m.y.z, m.z.x, m.z.y, m.z.z);

    auto const det = m.x.x * inv.x.x + m.x.y * inv.y.x + m.x.z * inv.z.x + m.x.w * inv.w.x;
    if (std::fabs(det) < 1e-6f) throw std::runtime_error("Matrix not invertible!");

    auto const invDet = 1.0f / det;
    inv.x.x *= invDet; inv.x.y *= invDet; inv.x.z *= invDet; inv.x.w *= invDet;
    inv.y.x *= invDet; inv.y.y *= invDet; inv.y.z *= invDet; inv.y.w *= invDet;
    inv.z.x *= invDet; inv.z.y *= invDet; inv.z.z *= invDet; inv.z.w *= invDet;
    inv.w.x *= invDet; inv.w.y *= invDet; inv.w.z *= invDet; inv.w.w *= invDet;

    return inv;
}