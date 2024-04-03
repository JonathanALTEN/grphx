#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class AddEdgeTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(AddEdgeTest, AddSingleEdgeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    // For a directed graph, edge from 1 to 2 should exist, but not from 2 to 1
    ASSERT_TRUE(graph.contains_edge(1, 2));
    ASSERT_FALSE(graph.contains_edge(2, 1));
}

TEST_F(AddEdgeTest, AddMultipleEdges_AddedCorrectly) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 1);

    ASSERT_TRUE(graph.contains_edge(1, 2));
    ASSERT_TRUE(graph.contains_edge(2, 3));
    ASSERT_TRUE(graph.contains_edge(3, 1));
    ASSERT_FALSE(graph.contains_edge(2, 1));
    ASSERT_FALSE(graph.contains_edge(3, 2));
    ASSERT_FALSE(graph.contains_edge(1, 3));
}

TEST_F(AddEdgeTest, AddDuplicateEdgeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    graph.add_edge(1, 2); // Adding duplicate edge

    ASSERT_TRUE(graph.contains_edge(1, 2)); // Edge should still exist
    ASSERT_FALSE(graph.contains_edge(2, 1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
