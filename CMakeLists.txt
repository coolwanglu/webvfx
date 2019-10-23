cmake_minimum_required (VERSION 2.6)
project (mltchromevfx)

set (mltchromevfx_VERSION_MAJOR 1)
set (mltchromevfx_VERSION_MINOR 0)

include_directories(${CMAKE_SOURCE_DIR})

set(CHROMEVFX_SRC
  mlt/factory.h
  mlt/factory.cpp
  mlt/service_locker.h
  mlt/service_locker.cpp
  mlt/service_manager.h
  mlt/service_manager.cpp
  mlt/webvfx_filter.cpp
  webvfx/logger.h
  webvfx/effects.h
  webvfx/effects.cpp
  webvfx/effects_impl.h
  webvfx/effects_impl.cpp
  webvfx/parameters.h
  webvfx/parameters.cpp
  webvfx/webvfx.h
  webvfx/webvfx.cpp
  )

add_library(mltchromevfx SHARED ${CHROMEVFX_SRC})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIC")

execute_process(COMMAND pkg-config --variable=libdir mlt-framework OUTPUT_VARIABLE INSTALL_BASE_DIR)
string(REGEX REPLACE "\n$" "" INSTALL_BASE_DIR "${INSTALL_BASE_DIR}")
install(TARGETS mltchromevfx LIBRARY DESTINATION "${INSTALL_BASE_DIR}/mlt")
