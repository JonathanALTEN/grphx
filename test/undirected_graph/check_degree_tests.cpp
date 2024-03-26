#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class DegreeTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

// Test case to verify the degree function
TEST_F(DegreeTest, ZeroDegreeTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);

    ASSERT_EQ(graph.degree(1), 0);
}

TEST_F(DegreeTest, OneDegreeTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    ASSERT_EQ(graph.degree(1), 1);
    ASSERT_EQ(graph.degree(2), 1);
}

TEST_F(DegreeTest, MultipleDegreeTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    ASSERT_EQ(graph.degree(1), 1);
    ASSERT_EQ(graph.degree(2), 2);
    ASSERT_EQ(graph.degree(3), 1);
}

TEST_F(DegreeTest, LoopDegreeTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    graph.add_edge(2, 1);

    ASSERT_EQ(graph.degree(1), 2);
    ASSERT_EQ(graph.degree(2), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}