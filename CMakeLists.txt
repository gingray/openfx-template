cmake_minimum_required(VERSION 3.1)
set(PLUGIN_NAME TestOpenFX)
project(${PLUGIN_NAME} LANGUAGES C CXX)
include(FindOpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(OPENFX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/openfx)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SupportExt)
include_directories(${OPENFX_PATH}/include)
include_directories(${OPENFX_PATH}/Support/include)
include_directories(${OPENFX_PATH}/Support/Plugins/include)

set(OFX_SUPPORT_HEADER_DIR "${OPENFX_PATH}/Support/include")
set(OFX_SUPPORT_LIBRARY_DIR "${OPENFX_PATH}/Support/Library")
add_compile_options(-Wall -Wextra)



file(GLOB SUPPORT_SOURCES
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
file(GLOB SOURCES
        "src/basic.cpp"
        "src/basic.h"
        )

add_library(${PLUGIN_NAME} SHARED ${SOURCES} ${SUPPORT_SOURCES})

set_target_properties(${PLUGIN_NAME} PROPERTIES PREFIX "")
set_target_properties(${PLUGIN_NAME} PROPERTIES SUFFIX ".ofx")
set_target_properties(${PLUGIN_NAME} PROPERTIES LINK_FLAGS "-fvisibility=hidden -exported_symbols_list,${OFX_SUPPORT_HEADER_DIR}/osxSymbols")
target_link_libraries(${PLUGIN_NAME})
set(OFX_ARCH "MacOS")
set(OFX_ARCH_NAME ${OFX_ARCH} CACHE STRING "OpenFX target OS and architecture")
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

install(TARGETS ${PLUGIN_NAME}
        RUNTIME DESTINATION ${PLUGIN_NAME}.ofx.bundle/Contents/${OFX_ARCH_NAME}
        LIBRARY DESTINATION ${PLUGIN_NAME}.ofx.bundle/Contents/${OFX_ARCH_NAME}
        )

install(FILES Info.plist
        DESTINATION ${PLUGIN_NAME}.ofx.bundle/Contents
        )

install(TARGETS ${PLUGIN_NAME}
        RUNTIME DESTINATION ${PLUGIN_NAME}.ofx.bundle/Contents/${OFX_ARCH_NAME}
        LIBRARY DESTINATION ${PLUGIN_NAME}.ofx.bundle/Contents/${OFX_ARCH_NAME}
        )
