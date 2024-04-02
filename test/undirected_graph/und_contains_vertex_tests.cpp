#include <gtest/gtest.h>
#include "grphx/grphx.hpp"

// Define a test fixture for the graph
class ContainsVertexTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(ContainsVertexTest, ContainsSingleVertexTest) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    ASSERT_TRUE(graph.contains_vertex(1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
