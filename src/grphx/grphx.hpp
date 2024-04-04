#include <iostream>
#include <list>
#include <queue>
#include <algorithm>

namespace grphx {

    namespace internal {

        template<typename T>
        class basic_graph {
        public:
            using LinkedList = std::list<std::pair<T, std::list<T>>>;
            
            /**
             * @brief Checks if the graph contains a vertex.
             * 
             * @param v The vertex to check for.
             * @return True if the vertex is found in the graph, false otherwise.
             */
            bool contains_vertex(T v) const {
                return std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                    return pair.first == v;
                }) != this->m_adjacency_list.end();
            }

            /**
             * @brief Returns the number of vertices in the graph.
             * 
             * @return The number of vertices in the graph.
             */
            size_t size() const {
                return this->m_adjacency_list.size();
            }

            /**
             * @brief Checks if the graph is empty.
             * 
             * @return True if the graph is empty, false otherwise.
             */
            bool is_empty() const {
                return this->m_adjacency_list.empty();
            }

            /**
             * @brief Clears the graph, removing all vertices and edges.
             */
            void clear() {
                this->m_adjacency_list.clear();
            }

            /**
             * @brief Breadth-First Search (BFS) algorithm.
             * 
             * @param start The starting vertex for BFS traversal.
             * @return A vector containing the vertices visited during BFS traversal.
             */
            std::vector<T> bfs(T start) const {
                std::vector<T> visited;
                std::queue<T> queue;
                std::unordered_set<T> seen;
                
                queue.push(start);
                seen.insert(start);
                
                while (!queue.empty()) {
                    T current = queue.front();
                    queue.pop();
                    visited.push_back(current);
                    
                    for (const auto& neighbor : this->successors(current)) {
                        if (seen.find(neighbor) == seen.end()) {
                            queue.push(neighbor);
                            seen.insert(neighbor);
                        }
                    }
                }
                
                return visited;
            }

            /**
             * @brief Depth-First Search (DFS) algorithm.
             * 
             * @param start The starting vertex for DFS traversal.
             * @return A vector containing the vertices visited during DFS traversal.
             */
            std::vector<T> dfs(T start) const {
                std::vector<T> visited;
                std::stack<T> stack;
                std::unordered_set<T> seen;
                
                stack.push(start);
                
                while (!stack.empty()) {
                    T current = stack.top();
                    stack.pop();
                    
                    if (seen.find(current) == seen.end()) {
                        visited.push_back(current);
                        seen.insert(current);
                        
                        for (const auto& neighbor : this->successors(current)) {
                            if (seen.find(neighbor) == seen.end()) {
                                stack.push(neighbor);
                            }
                        }
                    }
                }
                
                return visited;
            }

            virtual void add_vertex(T v) = 0;
            virtual void add_edge(T u, T v) = 0;
            virtual void remove_vertex(T v) = 0;
            virtual void remove_edge(T u, T v) = 0;
            virtual bool contains_edge(T u, T v) const = 0;

        protected:
            LinkedList m_adjacency_list;
        };

    } // end of namespace internal

    template<typename T>
    class directed_graph : public internal::basic_graph<T> {
    public:
        directed_graph() = default;
        virtual ~directed_graph() = default;

        directed_graph(const directed_graph&) = delete;
        directed_graph(directed_graph&&) = delete;
        directed_graph& operator=(const directed_graph&) = delete;
        directed_graph& operator=(directed_graph&&) = delete;

        /**
         * @brief Adds a new vertex to the graph.
         * 
         * If the vertex already exists in the graph, it will not be added again.
         * 
         * @param v The vertex to add to the graph.
         */
        void add_vertex(T v) override {
            if (!this->contains_vertex(v)) {
                this->m_adjacency_list.emplace_back(v, std::list<T>());
            }
        }

        /**
         * @brief Adds a new directed edge from vertex `u` to vertex `v` in the graph.
         * 
         * If either of the vertices does not exist in the graph, it will be added.
         * 
         * @param u The source vertex of the directed edge.
         * @param v The destination vertex of the directed edge.
         * @note This function adds a directed edge from vertex `u` to vertex `v`.
         */
        void add_edge(T u, T v) override {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                return pair.first == u;
            });

            if (it == this->m_adjacency_list.end())
                return; // vertex u not found in graph

            // Add edge from u to v
            if (std::find(it->second.begin(), it->second.end(), v) == it->second.end()) {
                it->second.push_back(v);
            }
        }

        /**
         * @brief Removes a vertex from the graph.
         * 
         * If the vertex does not exist in the graph, this function has no effect.
         * 
         * @param v The vertex to remove from the graph.
         */
        void remove_vertex(T v) override {
            auto it = std::remove_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(),
                                     [&v](const std::pair<T, std::list<T>>& pair) {
                                         return pair.first == v;
                                     });
            this->m_adjacency_list.erase(it, this->m_adjacency_list.end());

            for (auto& pair : this->m_adjacency_list) {
                pair.second.remove(v);
            }
        }

        /**
         * @brief Removes a directed edge from vertex `u` to vertex `v` in the graph.
         * 
         * If the directed edge does not exist in the graph, this function has no effect.
         * 
         * @param u The source vertex of the directed edge to remove.
         * @param v The destination vertex of the directed edge to remove.
         * @note This function removes the directed edge from vertex `u` to vertex `v`.
         */
        void remove_edge(T u, T v) override {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                return pair.first == u;
            });
            
            if (it == this->m_adjacency_list.end())
                return;

            it->second.remove(v);
        }

        /**
         * @brief Checks if the graph contains a directed edge from vertex `u` to vertex `v`.
         * 
         * @param u The source vertex of the edge.
         * @param v The destination vertex of the edge.
         * @return True if a directed edge exists from vertex `u` to vertex `v`, false otherwise.
         */
        bool contains_edge(T u, T v) const override {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                return pair.first == u;
            });

            if (it == this->m_adjacency_list.end())
                return false;
            
            return std::find(it->second.begin(), it->second.end(), v) != it->second.end();
        }

        /**
         * @brief Calculates the in-degree of a vertex in the directed graph.
         * 
         * @param v The vertex for which to calculate the in-degree.
         * @return The in-degree of the vertex.
         */
        size_t in_degree(T v) const {
            size_t count{ 0 };
            for (const auto& pair : this->m_adjacency_list) {
                count += std::count(pair.second.begin(), pair.second.end(), v);
            }

            return count;
        }

        /**
         * @brief Calculates the out-degree of a vertex in the directed graph.
         * 
         * @param v The vertex for which to calculate the out-degree.
         * @return The out-degree of the vertex.
         */
        size_t out_degree(T v) const {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                return pair.first == v;
            });

            return it != this->m_adjacency_list.end() ? it->second.size() : 0;
        }

        /**
         * @brief Returns the list of successors of a vertex in the directed graph.
         * 
         * @param v The vertex for which to find the successors.
         * @return The list of successors of the vertex.
         */
        std::list<T> successors(T v) const {
            std::list<T> successors;
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                return pair.first == v;
            });

            if (it != this->m_adjacency_list.end()) {
                successors = it->second;
            }

            return successors;
        }

        /**
         * @brief Returns the list of predecessors of a vertex in the directed graph.
         * 
         * @param v The vertex for which to find the predecessors.
         * @return The list of predecessors of the vertex.
         */
        std::list<T> predecessors(T v) const {
            std::list<T> predecessors;
            for (const auto& pair : this->m_adjacency_list) {
                if (std::find(pair.second.begin(), pair.second.end(), v) != pair.second.end()) {
                    predecessors.push_back(pair.first);
                }
            }

            return predecessors;
        }
    };

    template<typename T>
    class undirected_graph : public internal::basic_graph<T> {
    public:
        undirected_graph() = default;
        virtual ~undirected_graph() = default;

        undirected_graph(const undirected_graph&) = delete;
        undirected_graph(undirected_graph&&) = delete;
        undirected_graph& operator=(const undirected_graph&) = delete;
        undirected_graph& operator=(undirected_graph&&) = delete;

        /**
         * @brief Adds a new vertex to the graph.
         * 
         * If the vertex already exists in the graph, it will not be added again.
         * 
         * @param v The vertex to add to the graph.
         */
        void add_vertex(T v) override {
            if (!this->contains_vertex(v)) {
                this->m_adjacency_list.emplace_back(v, std::list<T>());
            }
        }

        /**
         * @brief Adds a new directed edge between two vertices in the graph.
         * 
         * If either of the vertices does not exist in the graph, it will be added.
         * 
         * @param u The source vertex of the edge.
         * @param v The destination vertex of the edge.
         */
        void add_edge(T u, T v) override {
            auto it_u = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                return pair.first == u;
            });

            if (it_u == this->m_adjacency_list.end()) {
                // Vertex u not found, add it to the adjacency list
                this->add_vertex(u);
                it_u = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                    return pair.first == u;
                });
            }

            auto it_v = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                return pair.first == v;
            });

            if (it_v == this->m_adjacency_list.end()) {
                // Vertex v not found, add it to the adjacency list
                this->add_vertex(v);
                it_v = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                    return pair.first == v;
                });
            }

            it_u->second.push_back(v);
            it_v->second.push_back(u);
        }

        /**
         * @brief Removes a vertex from the graph.
         * 
         * If the vertex does not exist in the graph, this function has no effect.
         * 
         * @param v The vertex to remove from the graph.
         */
        void remove_vertex(T v) override {
            auto it = std::remove_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(),
                                     [&v](const std::pair<T, std::list<T>>& pair) {
                                         return pair.first == v;
                                     });
            this->m_adjacency_list.erase(it, this->m_adjacency_list.end());

            for (auto& pair : this->m_adjacency_list) {
                pair.second.remove(v);
            }
        }

        /**
         * @brief Removes a directed edge between two vertices from the graph.
         * 
         * If the edge does not exist in the graph, this function has no effect.
         * 
         * @param u The source vertex of the edge.
         * @param v The destination vertex of the edge.
         */
        void remove_edge(T u, T v) override {
            auto it_u = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                return pair.first == u;
            });

            if (it_u == this->m_adjacency_list.end())
                return;

            auto it_v = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                return pair.first == v;
            });
            
            if (it_v == this->m_adjacency_list.end())
                return;

            it_u->second.remove(v);
            it_v->second.remove(u);
        }

        /**
         * @brief Checks if the graph contains an edge between two vertices.
         * 
         * @param u The source vertex of the edge.
         * @param v The destination vertex of the edge.
         * @return True if an edge exists between vertices `u` and `v`, false otherwise.
         */
        bool contains_edge(T u, T v) const override {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                return pair.first == u;
            });

            if (it == this->m_adjacency_list.end())
                return false;
            
            return std::find(it->second.begin(), it->second.end(), v) != it->second.end();
        }

        /**
         * @brief Calculates the degree of a vertex in the undirected graph.
         * 
         * @param v The vertex for which to calculate the degree.
         * @return The degree of the vertex.
         */
        size_t degree(T v) const {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                return pair.first == v;
            });

            return it != this->m_adjacency_list.end() ? it->second.size() : 0;
        }

        /**
         * @brief Returns the list of neighbors of a vertex in the undirected graph.
         * 
         * @param v The vertex for which to find the neighbors.
         * @return The list of neighbors of the vertex.
         */
        std::list<T> neighbors(T v) const {
            std::list<T> neighbors;
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                return pair.first == v;
            });

            if (it != this->m_adjacency_list.end()) {
                neighbors = it->second;
            }

            return neighbors;
        }
    }; 

} // end of namespace grphx
   
