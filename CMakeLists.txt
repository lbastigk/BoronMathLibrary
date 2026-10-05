cmake_minimum_required (VERSION 3.10)

include(FetchContent)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("BoronMathLibrary")

FetchContent_Declare(
    BoronTest
    GIT_REPOSITORY https://github.com/Kahviz/BoronTest.git
    GIT_TAG 0.0.4
)

FetchContent_MakeAvailable(BoronTest)

add_executable(BoronMathLibrary
    src/BoronMathTests/BoronMathLibrary.cpp
    src/BoronMathTests/Tests.cpp
)

target_link_libraries(BoronMathLibrary PRIVATE BoronTest)

target_include_directories(BoronMathLibrary PRIVATE 
	include/
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BoronMathLibrary PROPERTY CXX_STANDARD 20)
endif()
