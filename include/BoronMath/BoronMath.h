#pragma once

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#define BORONMATHversion 0.07

#include "BoronMath/SIMD/Vector2/Vector2.h"
#include "BoronMath/SIMD/Vector3/Vector3.h"
#include "BoronMath/SIMD/Vector4/Vector4.h"

#include "BoronMath/SIMD/Int3/Int3.h"
#include "BoronMath/SIMD/Int2/Int2.h"

#include "BoronMath/SIMD/Color255/Color255.h"

#include "BoronMath/SIMD/Matrix4x4/Matrix4x4.h"

#include "BoronMath/SIMD/Functions/Matrix4x4Functions.h"
#include "BoronMath/SIMD/Functions/StoreComponent.h"
#include "BoronMath/SIMD/Functions/LoadInt.h"
#include "BoronMath/SIMD/Functions/LoadVector.h"
#include "BoronMath/SIMD/Functions/Utils.h"
#include "BoronMath/SIMD/Functions/TransformNormal.h"
#include "BoronMath/SIMD/Functions/TransformVector.h"

#include "BoronMath/Variables.h"

//16 byte (GPU Compatable, Not SIMD)
#include "BoronMath/GPU/GPUVector2/GPUVector2.h"
#include "BoronMath/GPU/GPUVector3/GPUVector3.h"
#include "BoronMath/GPU/GPUVector4/GPUVector4.h"

#include "BoronMath/GPU/GPUInt3/GPUInt3.h"

#include "BoronMath/GPU/GPUMatrix4x4/GPUMatrix4x4.h"

#include "BoronMath/GPU/Functions/LoadGPUInt.h"
#include "BoronMath/GPU/Functions/StoreGPUComponent.h"
#include "BoronMath/GPU/Functions/TransformGPUNormal.h"

//Structs
struct Transform {
    BML::Vector3 Position{ 0,0,0 };
    BML::Vector3 Orientation{ 0,0,0 };
    BML::Vector3 Size{ 1,1,1 };
};