if (BUILD_TESTING)
    # Define the test executables
    add_executable(dir_add_vertex_test dir_add_vertex_tests.cpp)
    add_executable(dir_add_edge_test dir_add_edge_tests.cpp)
    add_executable(dir_contains_vertex_test dir_contains_vertex_tests.cpp)
    add_executable(dir_contains_edge_test dir_contains_edge_tests.cpp)
    add_executable(dir_remove_edge_test dir_remove_edge_tests.cpp)
    add_executable(dir_remove_vertex_test dir_remove_vertex_tests.cpp)
    add_executable(dir_in_degree_test dir_in_degree_tests.cpp)
    add_executable(dir_out_degree_test dir_out_degree_tests.cpp)
    add_executable(dir_successors_test dir_successors_tests.cpp)
    add_executable(dir_predecessors_test dir_predecessors_tests.cpp)


    # Link each test executable with Google Test and your library
    target_link_libraries(dir_add_vertex_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_add_edge_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_contains_vertex_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_contains_edge_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_remove_edge_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_remove_vertex_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_in_degree_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_out_degree_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_successors_test PRIVATE grphx gtest_main)
    target_link_libraries(dir_predecessors_test PRIVATE grphx gtest_main)


    # Define the tests
    include(GoogleTest)
    gtest_discover_tests(dir_add_vertex_test)
    gtest_discover_tests(dir_add_edge_test)
    gtest_discover_tests(dir_contains_vertex_test)
    gtest_discover_tests(dir_contains_edge_test)
    gtest_discover_tests(dir_remove_edge_test)
    gtest_discover_tests(dir_remove_vertex_test)
    gtest_discover_tests(dir_out_degree_test)
    gtest_discover_tests(dir_successors_test)
    gtest_discover_tests(dir_predecessors_test)
endif()