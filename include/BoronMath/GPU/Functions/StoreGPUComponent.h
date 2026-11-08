#pragma once

//----------------------------------------
// Includes

// BoronMath
#include "BoronMath/GPU/GPUVector2/GPUVector2.h"
#include "BoronMath/GPU/GPUVector3/GPUVector3.h"
#include "BoronMath/GPU/GPUVector4/GPUVector4.h"

//----------------------------------------
inline void StoreVector3(GPUVector3* dest, GPUVector4 const& src) {
    if (!dest) return;
    dest->x = src.x;
    dest->y = src.y;
    dest->z = src.z;
}

inline void StoreVector2(GPUVector2* dest, GPUVector3 const& src) {
    if (!dest) return;
    dest->x = src.x;
    dest->y = src.y;
}