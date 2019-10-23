cmake_minimum_required (VERSION 2.6)
project (chromevfx)

include_directories(${CMAKE_SOURCE_DIR})

set(CHROMEVFX_SRC
  mlt/service_manager.h
  mlt/service_manager.cpp
  webvfx/logger.h
  webvfx/effects.h
  webvfx/effects.cpp
  webvfx/effects_impl.h
  webvfx/effects_impl.cpp
  webvfx/webvfx.h
  webvfx/webvfx.cpp
  )

add_library(chromevfx ${CHROMEVFX_SRC})
