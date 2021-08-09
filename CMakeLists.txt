CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
# here is name of project
PROJECT(TestOpenFx CXX)
include(FindOpenGL REQUIRED)

set (CMAKE_CXX_STANDARD 11)
SET(OPENFX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/openfx)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/SupportExt)
INCLUDE_DIRECTORIES(${OPENFX_PATH}/include)
INCLUDE_DIRECTORIES(${OPENFX_PATH}/Support/include)
INCLUDE_DIRECTORIES(${OPENFX_PATH}/Support/Plugins/include)

set(OFX_SUPPORT_HEADER_DIR "${OPENFX_PATH}/Support/include")
set(OFX_SUPPORT_LIBRARY_DIR "${OPENFX_PATH}/Support/Library")


FILE(GLOB SUPPORT_SOURCES
        "${OFX_SUPPORT_HEADER_DIR}/*.h"

        "${OFX_SUPPORT_LIBRARY_DIR}/ofxsCore.cpp"
        "${OFX_SUPPORT_LIBRARY_DIR}/ofxsImageEffect.cpp"
        "${OFX_SUPPORT_LIBRARY_DIR}/ofxsInteract.cpp"
        "${OFX_SUPPORT_LIBRARY_DIR}/ofxsLog.cpp"
        "${OFX_SUPPORT_LIBRARY_DIR}/ofxsMultiThread.cpp"
        "${OFX_SUPPORT_LIBRARY_DIR}/ofxsParams.cpp"
        "${OFX_SUPPORT_LIBRARY_DIR}/ofxsProperty.cpp"
        "${OFX_SUPPORT_LIBRARY_DIR}/ofxsPropertyValidation.cpp"
        "${OFX_SUPPORT_LIBRARY_DIR}/*.h"
        )

add_executable(TestOpenFX ./src/basic.cpp)