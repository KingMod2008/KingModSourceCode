
cmake_minimum_required(VERSION 3.15)
project(KernelInjector CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(KernelInjector
    KernelInjector.cpp
)

target_include_directories(KernelInjector PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Components/Components
)

if(WIN32)
    target_compile_definitions(KernelInjector PRIVATE
        _UNICODE
        UNICODE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
    
    target_link_libraries(KernelInjector
        ntdll.lib
    )
    
    set_property(TARGET KernelInjector PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
endif()

set_target_properties(KernelInjector PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/Release"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/Debug"
)

message(STATUS "KernelInjector configured successfully")
message(STATUS "Build with: cmake --build . --config Release")
