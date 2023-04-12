cmake_minimum_required(VERSION 3.24)
project(chosu C)

set(CMAKE_C_STANDARD 23)

include(FetchContent)

FetchContent_Declare(CSFML
        URL https://www.sfml-dev.org/files/CSFML-2.5.1-sources.zip
)

FetchContent_GetProperties(CSFML)
if (NOT CSFML_POPULATED)
    FetchContent_Populate(CSFML)
    add_library(CSFML INTERFACE)
    target_include_directories(CSFML INTERFACE ${csfml_SOURCE_DIR}/include)
    include_directories(${csfml_SOURCE_DIR}/include)
endif ()

FetchContent_Declare(Ruby
        URL https://cache.ruby-lang.org/pub/ruby/3.0/ruby-3.0.0.tar.gz
        )

FetchContent_GetProperties(Ruby)
if (NOT Ruby_POPULATED)
    FetchContent_Populate(Ruby)
    add_library(Ruby INTERFACE)
    include_directories(${ruby_SOURCE_DIR}/include)
endif ()

include_directories(ext/src)
include_directories(ext/include)

add_library(chosu ext/src/ext.c)
target_link_libraries(chosu PRIVATE Ruby csfml-graphics csfml-audio csfml-network csfml-window csfml-system)