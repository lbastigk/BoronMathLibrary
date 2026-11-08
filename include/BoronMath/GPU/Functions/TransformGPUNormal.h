#pragma once

//----------------------------------------
// Includes

// BoronMath
#include "BoronMath/GPU/GPUMatrix4x4/GPUMatrix4x4.h"
#include "BoronMath/GPU/GPUVector3/GPUVector3.h"
#include "BoronMath/GPU/GPUVector4/GPUVector4.h"

//----------------------------------------
inline GPUVector4 TransformGPUNormal(GPUVector4 const& v, GPUMatrix4x4 const& m)
{
    return GPUVector4{
        .x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x,
        .y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y,
        .z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z,
        .w = 0.0f
    };
}

inline GPUVector3 TransformGPUNormal(GPUVector3 const& v, GPUMatrix4x4 const& m)
{
    return GPUVector3{
        .x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x,
        .y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y,
        .z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z
    };
}