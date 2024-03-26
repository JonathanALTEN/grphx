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
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    ASSERT_TRUE(graph.contains_edge(1, 2));
    ASSERT_TRUE(graph.contains_edge(2, 1)); // Undirected graph, so edge should exist in both directions
}

TEST_F(AddEdgeTest, AddMultipleEdges_AddedCorrectly) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 1);
    ASSERT_TRUE(graph.contains_edge(1, 2));
    ASSERT_TRUE(graph.contains_edge(2, 3));
    ASSERT_TRUE(graph.contains_edge(3, 1));
    ASSERT_TRUE(graph.contains_edge(2, 1));
    ASSERT_TRUE(graph.contains_edge(3, 2));
    ASSERT_TRUE(graph.contains_edge(1, 3));
}

TEST_F(AddEdgeTest, AddDuplicateEdgeTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    graph.add_edge(1, 2); // Adding duplicate edge
    ASSERT_TRUE(graph.contains_edge(1, 2)); // Edge should still exist
    ASSERT_TRUE(graph.contains_edge(2, 1)); // Undirected graph, so edge should exist in both directions
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
