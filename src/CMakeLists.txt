# CMakeLists.txt in src/grphx

# Define the library target
add_library(grphx INTERFACE)

# Include the directory containing the header file
target_include_directories(grphx INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/grphx)
