if (BUILD_TESTING)
    # Set up testing
    enable_testing()

    # Add test subdirectories
    add_subdirectory(directed_graph_tests)
    add_subdirectory(undirected_graph_tests)
endif()