`GrphX` is a tiny and easy to use, header-only, library written in **C++17**.<br/>

# Table of Contents

* [Introduction](#introduction)
  * [Motivation](#motivation)
  * [Code Example](#code-example)
* [Integration](#integration)
  * [Requirements](#requirements)
  * [How to use](#How to use)
* [Documentation](#documentation)
* [Tests](#tests)
* [GrphX in Action](#grphx-in-action)

# Introduction

### Motivation

`GrphX` aims to provide a lightweight and easy-to-use solution for graph-related operations in C++ projects. It currently offers some common operations for directed and undirected graphs.

### Code Example

```cpp
#include <iostream>
#include <grphx/directed_graph.hpp>

int main() {
    // Create a directed graph
    grphx::directed_graph<int> graph;

    // Add vertices
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);

    // Add edges
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    // Perform graph operations...
    const auto neighbours = graph.neighbours(2);

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

# Documentation
Comprehensive documentation for `GrphX` is available in the documentation directory. It includes detailed explanations of the library's features, usage examples, and API reference.

# Tests
To run all tests for the `GrphX` library; first build the project, then execute the `run_tests.ps1` script located in the script folder. This script will automatically execute all test cases and provide the test results.

# GrphX in Action
Examples of GrphX in action can be found in the examples directory. These examples demonstrate various use cases and scenarios where `GrphX` can be applied effectively.
