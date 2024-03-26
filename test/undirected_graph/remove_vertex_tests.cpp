#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

// Test case to verify the remove_vertex function
TEST_F(GraphTest, RemoveVertexTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.remove_vertex(2);
    ASSERT_TRUE(graph.contains_vertex(1));
    ASSERT_FALSE(graph.contains_vertex(2));
    ASSERT_TRUE(graph.contains_vertex(3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}