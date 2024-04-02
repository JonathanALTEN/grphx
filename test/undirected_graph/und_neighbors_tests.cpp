#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class NeighborsTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

// Test case to verify the neighbors function
TEST_F(NeighborsTest, ZeroNeighbors) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);

    std::list<int> neighbors_of_1 = graph.neighbors(1);

    ASSERT_EQ(neighbors_of_1.size(), 0);
    ASSERT_TRUE(std::find(neighbors_of_1.begin(), neighbors_of_1.end(), 1) == neighbors_of_1.end());
}

TEST_F(NeighborsTest, OneNeighbor) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    std::list<int> neighbors_of_1 = graph.neighbors(1);

    ASSERT_EQ(neighbors_of_1.size(), 1);
    ASSERT_TRUE(std::find(neighbors_of_1.begin(), neighbors_of_1.end(), 1) == neighbors_of_1.end());
}

TEST_F(NeighborsTest, MultipleNeighbors) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    std::list<int> neighbors_of_1 = graph.neighbors(1);
    std::list<int> neighbors_of_2 = graph.neighbors(2);
    std::list<int> neighbors_of_3 = graph.neighbors(3);

    ASSERT_EQ(neighbors_of_1.size(), 1);
    ASSERT_TRUE(std::find(neighbors_of_1.begin(), neighbors_of_1.end(), 2) != neighbors_of_1.end());

    ASSERT_EQ(neighbors_of_2.size(), 2);
    ASSERT_TRUE(std::find(neighbors_of_2.begin(), neighbors_of_2.end(), 1) != neighbors_of_2.end());
    ASSERT_TRUE(std::find(neighbors_of_2.begin(), neighbors_of_2.end(), 3) != neighbors_of_2.end());

    ASSERT_EQ(neighbors_of_3.size(), 1);
    ASSERT_TRUE(std::find(neighbors_of_3.begin(), neighbors_of_3.end(), 2) != neighbors_of_3.end());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}