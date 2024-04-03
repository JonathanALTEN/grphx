#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class PredecessorsTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

// Test case to verify the predecessors function
TEST_F(PredecessorsTest, ZeroPredecessorsTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);

    auto predecessors = graph.predecessors(1);
    ASSERT_EQ(predecessors.size(), 0);
}

TEST_F(PredecessorsTest, SinglePredecessorsTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    auto predecessors = graph.predecessors(2);
    ASSERT_EQ(predecessors.size(), 1);

    ASSERT_TRUE(std::find(predecessors.begin(), predecessors.end(), 1) != predecessors.end());
    ASSERT_FALSE(std::find(predecessors.begin(), predecessors.end(), 3) != predecessors.end());
}

TEST_F(PredecessorsTest, MultiplePredecessorsTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(3, 2);

    auto predecessors = graph.predecessors(2);
    ASSERT_EQ(predecessors.size(), 2);
    ASSERT_TRUE(std::find(predecessors.begin(), predecessors.end(), 1) != predecessors.end());
    ASSERT_TRUE(std::find(predecessors.begin(), predecessors.end(), 3) != predecessors.end());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
