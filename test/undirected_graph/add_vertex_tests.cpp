#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class AddVertexTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(AddVertexTest, AddSingleVertexTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    ASSERT_TRUE(graph.contains_vertex(1));
}

TEST_F(AddVertexTest, AddMultipleVertices_AddedCorrectly) {
    grphx::undirected_graph<int> graph;
    constexpr int NUM_VERTICES = 5;
    constexpr int START_INDEX = 0;

    // Add vertices to the graph
    for (int i = START_INDEX; i < START_INDEX + NUM_VERTICES; ++i) {
        graph.add_vertex(i);
    }

    // Check that vertices have been added correctly
    for (int i = START_INDEX; i < START_INDEX + NUM_VERTICES; ++i) {
        ASSERT_TRUE(graph.contains_vertex(i));
    }
}

TEST_F(AddVertexTest, AddSingleDuplicateVertexTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(1);
    ASSERT_TRUE(graph.contains_vertex(1));
}

TEST_F(AddVertexTest, AddMultipleDuplicateVertexTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(1);

    graph.add_vertex(2);
    graph.add_vertex(2);

    ASSERT_TRUE(graph.contains_vertex(1));
    ASSERT_TRUE(graph.contains_vertex(2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
