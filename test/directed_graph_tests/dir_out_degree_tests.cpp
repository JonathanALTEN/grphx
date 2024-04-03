#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class OutDegreeTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

// Test case to verify the out_degree function
TEST_F(OutDegreeTest, ZeroOutDegreeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);

    ASSERT_EQ(graph.out_degree(1), 0);
}

TEST_F(OutDegreeTest, OneOutDegreeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    ASSERT_EQ(graph.out_degree(1), 1);
    ASSERT_EQ(graph.out_degree(2), 0);
}

TEST_F(OutDegreeTest, MultipleOutDegreeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);

    ASSERT_EQ(graph.out_degree(1), 2);
    ASSERT_EQ(graph.out_degree(2), 0);
    ASSERT_EQ(graph.out_degree(3), 0);
}

TEST_F(OutDegreeTest, LoopOutDegreeTest) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    graph.add_edge(2, 1);

    ASSERT_EQ(graph.out_degree(1), 1);
    ASSERT_EQ(graph.out_degree(2), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
