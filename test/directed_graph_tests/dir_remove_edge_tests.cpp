#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class RemoveEdgeTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

// Test case to verify the remove_edge function
TEST_F(RemoveEdgeTest, RemoveSingleEdgeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);
    graph.remove_edge(2, 3);

    ASSERT_TRUE(graph.contains_edge(1, 2));
    ASSERT_FALSE(graph.contains_edge(2, 3));
    ASSERT_TRUE(graph.contains_edge(3, 4));
}

TEST_F(RemoveEdgeTest, RemoveMultipleEdgeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);
    graph.remove_edge(1, 2);
    graph.remove_edge(2, 3);
    graph.remove_edge(3, 4);

    ASSERT_FALSE(graph.contains_edge(1, 2));
    ASSERT_FALSE(graph.contains_edge(2, 3));
    ASSERT_FALSE(graph.contains_edge(3, 4));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}