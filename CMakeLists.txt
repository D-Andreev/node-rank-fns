cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project (node-rank-fns)
include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "src/node_rank_fns.cc")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC} src/ranking_fns/RankingFns.cc src/ranking_fns/RankingFns.h src/utils/Utils.cpp src/utils/Utils.h src/workers/TfIdfWorker.cpp src/workers/TfIdfWorker.h src/workers/BM25Worker.cpp src/workers/BM25Worker.h)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# Include Node-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# define NPI_VERSION
add_compile_definitions(NAPI_VERSION=3)
add_definitions(-DNAPI_VERSION=3)

enable_testing()
add_executable(
        ranking_fns_test
        test/ranking_fns_test.cc
        src/ranking_fns/RankingFns.cc
)
target_link_libraries(
        ranking_fns_test
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(ranking_fns_test)