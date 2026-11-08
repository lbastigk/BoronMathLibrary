#pragma once

#include "BoronMath/BoronMath.h"

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