cmake_minimum_required(VERSION 3.24)

project(market_reader)

include(FetchContent)

# ---- Core library ----
add_library(reader_core
    ohlcv_1m.h
    mmap_reader.cpp
)
target_include_directories(reader_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ---- Vendor: Databento ----
FetchContent_Declare(
  databento
  GIT_REPOSITORY https://github.com/databento/databento-cpp
  GIT_TAG HEAD
)
FetchContent_MakeAvailable(databento)

add_executable(databento_reader bento_reader.cpp)
target_link_libraries(databento_reader PRIVATE reader_core databento::databento)

