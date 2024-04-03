`GrphX` is a tiny and easy to use, header-only, library written in **C++17**.<br/>

# Table of Contents

* [Introduction](#introduction)
  * [Motivation](#motivation)
  * [Code Example](#code-example)
* [Integration](#integration)
  * [Requirements](#requirements)
  * [How to use](#How-to-use)
* [Documentation](#documentation)
* [Tests](#tests)

# Introduction

## Motivation
`GrphX` strives to offer a lightweight and user-friendly solution for graph-related tasks within C++ projects. The library currently provides essential functionalities for both directed and undirected graphs. It's worth noting that this project originated as a hobby endeavor, primarily aimed at gaining familiarity with some functions and algorithms in the C++ standard library, but also how to use Google Test framework. 
I advise you not to use this is any commercial product, it's not fully tested and might produce errors. However, the library is free to use and modify as you like to fit your particular needs. 

### Code Example
Example 1: Basic Usage of Directed Graph.
```cpp
#include <grphx/grphx.hpp>

int main() {
  // Create a directed graph
  grphx::directed_graph<int> graph;

  // Add vertices
  graph.add_vertex(1);
  graph.add_vertex(2);
  graph.add_vertex(3);

  // Add edges
  graph.add_edge(1, 3);
  graph.add_edge(2, 3);

  // Get predecessors of vertex 3
  const auto predecessors = graph.predecessors(3);

  // Output the predecessors of vertex 3
  std::cout << "Predecessors of vertex 3: ";
  for (const auto& predecessor : predecessors) {
    std::cout << predecessor << " ";
  }
  std::cout << std::endl;

  return 0;
}
```

Example 2: Using Custom Data Types with an Undirected Graph.
```cpp
#include <grphx/grphx.hpp>

struct CustomType {
    int value;

    // Overload the equality operator
    bool operator==(const CustomType& other) const {
      return value == other.value;
    }
};

int main() {
    // Create an undirected graph with custom data type
    grphx::undirected_graph<CustomType> graph;

    // Define some vertices
    CustomType vertex1{1};
    CustomType vertex2{2};
    CustomType vertex3{3};

    // Add vertices to the graph
    graph.add_vertex(vertex1);
    graph.add_vertex(vertex2);
    graph.add_vertex(vertex3);

    // Add edges between vertices
    graph.add_edge(vertex1, vertex2);
    graph.add_edge(vertex2, vertex3);

    // Perform graph operations using custom data types
    bool hasEdge12 = graph.contains_edge(vertex1, vertex2); // true
    bool hasEdge23 = graph.contains_edge(vertex2, vertex3); // true
    bool hasEdge13 = graph.contains_edge(vertex1, vertex3); // false

    // Output the results
    std::cout << "Edge between vertex1 and vertex2: " << std::boolalpha << hasEdge12 << std::endl;
    std::cout << "Edge between vertex2 and vertex3: " << std::boolalpha << hasEdge23 << std::endl;
    std::cout << "Edge between vertex1 and vertex3: " << std::boolalpha << hasEdge13 << std::endl;

    return 0;
}
```

Example 3: Demonstrates Breadth-First Search (BFS) and Depth-First Search (DFS) in an Undirected Graph.
```cpp
#include <grphx/grphx.hpp>

int main() {
  // Create an undirected graph
  grphx::undirected_graph<int> graph;

  // Add vertices to the graph
  graph.add_vertex(1);
  graph.add_vertex(2);
  graph.add_vertex(3);
  graph.add_vertex(4);
  graph.add_vertex(5);

  // Add edges between vertices
  graph.add_edge(1, 2);
  graph.add_edge(1, 3);
  graph.add_edge(2, 4);
  graph.add_edge(3, 5);

  std::cout << "BFS traversal: ";
  for (int vertex : graph.bfs(1)) {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;

  std::cout << "DFS traversal: ";
  for (int vertex : graph.dfs(1)) {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;

  return 0;
}
```

# Integration

### Requirements
`GrphX` requires a C++17-compliant compiler and the C++ standard library.

### How to use
To use `GrphX`, simply include the `grphx.hpp` header file in your project:

```cpp
#include <grphx/grphx.hpp>
```

# CMake

### Building with CMake
To build the `GrphX` project, follow these steps:

1. Clone or Download: Obtain the `GrphX` project by either cloning the repository or downloading the source code archive.

2. Install CMake: Ensure that CMake is installed on your system. You can download and install CMake from the official website: https://cmake.org/download/.

3. Build the Project:

- Open a terminal or command prompt and navigate to the root directory of the `GrphX` project.

- Run the following commands in the terminal:
```ps1 
cmake -S . -B build
cmake --build build
```

# Documentation
Comprehensive documentation for `GrphX` is available in the documentation directory. Open `index.html` in `docs/html/`.

# Tests
To run all tests for the `GrphX` library; first build the project, then execute the `run_tests.ps1` script located in the script folder. This script will automatically execute all test cases and provide the test results.

