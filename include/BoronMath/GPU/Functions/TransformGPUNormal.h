#pragma once

#include "BoronMath/GPU/GPUVector4/GPUVector4.h"
#include "BoronMath/GPU/GPUMatrix4x4/GPUMatrix4x4.h"
#include "BoronMath/GPU/GPUVector3/GPUVector3.h"

inline GPUVector4 TransformGPUNormal(GPUVector4 const& v, GPUMatrix4x4 const& m)
{
    GPUVector4 result;
    result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
    result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
    result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;
    result.w = 0.0f;
    return result;
}

inline GPUVector3 TransformGPUNormal(GPUVector3 const& v, GPUMatrix4x4 const& m)
{
    GPUVector3 result;
    result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
    result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
    result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;
    return result;
}