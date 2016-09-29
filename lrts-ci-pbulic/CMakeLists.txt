cmake_minimum_required(VERSION 2.8)

if ( NOT PROJECT_SOURCE_DIR)
    PROJECT(public)
    MESSAGE(STATUS "## Making project " ${CMAKE_PROJECT_NAME})
    
    SET(ROOTPATH ${CMAKE_SOURCE_DIR})
    INCLUDE(${ROOTPATH}/cm/global.cmake)
    INCLUDE(${ROOTPATH}/cm/pclint.cmake)
    GET_GPATH (${ROOTPATH})
    SET_USE_FOLDER()
endif()

add_subdirectory(src/lrts/ci/public)
