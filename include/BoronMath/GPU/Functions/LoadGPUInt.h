#pragma once

#include "BoronMath/GPU/GPUVector4/GPUVector4.h"
#include "BoronMath/GPU/GPUInt3/GPUInt3.h"

inline GPUVector4 LoadInt3(GPUInt3 a) {
	return GPUVector4(
		static_cast<float>(a.x),
		static_cast<float>(a.y),
		static_cast<float>(a.z),
		0.0f
	);
}