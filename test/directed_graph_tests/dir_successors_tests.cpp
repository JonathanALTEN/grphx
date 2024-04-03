#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class SuccessorsTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

// Test case to verify the successors function
TEST_F(SuccessorsTest, SuccessorsTest1) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);

    auto successors = graph.successors(1);
    ASSERT_EQ(successors.size(), 2);
    ASSERT_TRUE(std::find(successors.begin(), successors.end(), 2) != successors.end());
    ASSERT_TRUE(std::find(successors.begin(), successors.end(), 3) != successors.end());
}

TEST_F(SuccessorsTest, SuccessorsTest2) {
    grphx::directed_graph<int> graph;
    graph.add_vertex(1);

    auto successors = graph.successors(1);
    ASSERT_EQ(successors.size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
