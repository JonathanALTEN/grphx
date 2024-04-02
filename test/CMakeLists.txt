if (BUILD_TESTING)
    # Set up testing
    enable_testing()

    # Add test subdirectories
    add_subdirectory(directed_graph)
    add_subdirectory(undirected_graph)
endif()