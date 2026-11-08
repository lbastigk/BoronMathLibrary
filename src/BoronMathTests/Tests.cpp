//----------------------------------------
// Includes

// BoronMath
#include "BoronMath/GPU/GPUInt3/GPUInt3.h"
#include "BoronMathTests/Tests.h"

//----------------------------------------
// BoronTest
#include "expects.h"

//----------------------------------------
void Tests::doTests() {
    //Variables
    GPUInt3 constexpr gpuInt3A{.x=1,.y=2,.z=3};
    GPUInt3 constexpr gpuInt3B{.x=2,.y=2,.z=2};

    //GPU
    EXPECTVALUE(gpuInt3A.x, 1);
    EXPECTVALUE(gpuInt3A.y, 2);
    EXPECTVALUE(gpuInt3A.z, 3);

    EXPECTVALUE(gpuInt3A.x + gpuInt3B.x, 3);
    EXPECTVALUE(gpuInt3A.y + gpuInt3B.y, 4);
    EXPECTVALUE(gpuInt3A.z + gpuInt3B.z, 5);
}