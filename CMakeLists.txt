cmake_minimum_required(VERSION 3.8)  # using the latest version atm

project(Connect)
set(LIB_NAME lib_${PROJECT_NAME})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -g -no-pie")
    elseif (MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")
    endif()
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "-DNDEBUG -O4 -s")
    elseif (MSVC)
        set(CMAKE_CXX_FLAGS "/Ox /Ob2 /Oi /Ot /Oy /MT")
    endif()
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath,/usr/local/lib")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/include  # includes for the project
)

# fetching all .cpp
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.c
)
list(REMOVE_ITEM SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/main.c")

add_library(${LIB_NAME} ${SOURCE_FILES})
set_property(TARGET ${LIB_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.c)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_NAME})