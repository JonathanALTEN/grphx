#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class InDegreeTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

// Test case to verify the in_degree function
TEST_F(InDegreeTest, ZeroInDegreeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);

    ASSERT_EQ(graph.in_degree(1), 0);
}

TEST_F(InDegreeTest, OneInDegreeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    ASSERT_EQ(graph.in_degree(1), 0);
    ASSERT_EQ(graph.in_degree(2), 1);
}

TEST_F(InDegreeTest, MultipleInDegreeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(1, 3);

    ASSERT_EQ(graph.in_degree(1), 0);
    ASSERT_EQ(graph.in_degree(2), 1);
    ASSERT_EQ(graph.in_degree(3), 2);
}

TEST_F(InDegreeTest, LoopInDegreeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    graph.add_edge(2, 1);

    ASSERT_EQ(graph.in_degree(1), 1);
    ASSERT_EQ(graph.in_degree(2), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
