set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp *.cc)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

add_executable(
        ranking_fns_test
        ranking_fns_test.cc
)
target_link_libraries(
        ranking_fns_test
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(ranking_fns_test)