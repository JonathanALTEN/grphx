#include <iostream>
#include <list>
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
             * This function checks if the graph contains a vertex of type `T`. It supports
             * certain built-in types such as `int`, `float`, `double`, `char`, and `std::string`.
             * For other user-defined types, the `operator==` must be overloaded to compare
             * vertices for equality.
             * 
             * @param v The vertex to check for.
             * @return True if the vertex is found in the graph, false otherwise.
             */
            bool contains_vertex(T v) const {
                return std::find_if(m_adjacency_list.begin(), m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                    return pair.first == v;
                }) != m_adjacency_list.end();
            }

            /**
             * @brief Checks if the graph contains an edge between two vertices.
             * 
             * This function checks if the graph contains an edge between the vertices `u` and `v`.
             * It supports certain built-in types such as `int`, `float`, `double`, `char`, and `std::string`.
             * For other user-defined types, the `operator==` must be overloaded to compare vertices for equality.
             * 
             * @param u The source vertex of the edge.
             * @param v The destination vertex of the edge.
             * @return True if an edge exists between vertices `u` and `v`, false otherwise.
             */
            bool contains_edge(T u, T v) const {
                auto it = std::find_if(m_adjacency_list.begin(), m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                    return pair.first == u;
                });

                if (it == m_adjacency_list.end())
                    return false;
                
                return std::find(it->second.begin(), it->second.end(), v) != it->second.end();
            }

            size_t size() const {
                return m_adjacency_list.size();
            }

            bool is_empty() const {
                return m_adjacency_list.empty();
            }

            void clear() {
                m_adjacency_list.clear();
            }

            virtual void add_vertex(T v) = 0;
            virtual void add_edge(T u, T v) = 0;
            virtual void remove_vertex(T v) = 0;
            virtual void remove_edge(T u, T v) = 0;

        protected:
            LinkedList m_adjacency_list;
        };

    } // namespace internal

    template<typename T>
    class directed_graph : public internal::basic_graph<T> {
    public:
        directed_graph() = default;
        virtual ~directed_graph() = default;

        directed_graph(const directed_graph&) = delete;
        directed_graph(directed_graph&&) = delete;
        directed_graph& operator=(const directed_graph&) = delete;
        directed_graph& operator=(directed_graph&&) = delete;

        void add_vertex(T v) override {
            if (!this->contains_vertex(v)) {
                this->m_adjacency_list.emplace_back(v, std::list<T>());
            }
        }

        void add_edge(T u, T v) override {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                return pair.first == u;
            });

            if (it == this->m_adjacency_list.end())
                return;

            if (std::find(it->second.begin(), it->second.end(), v) == it->second.end()) {
                it->second.push_back(v);
            }
        }

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

        void remove_edge(T u, T v) override {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&u](const std::pair<T, std::list<T>>& pair) {
                return pair.first == u;
            });
            
            if (it == this->m_adjacency_list.end())
                return;

            it->second.remove(v);
        }

        size_t in_degree(T v) const {
            size_t count = 0;
            for (const auto& pair : this->m_adjacency_list) {
                count += std::count(pair.second.begin(), pair.second.end(), v);
            }

            return count;
        }

        size_t out_degree(T v) const {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                return pair.first == v;
            });

            return it != this->m_adjacency_list.end() ? it->second.size() : 0;
        }

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

        void add_vertex(T v) override {
            if (!this->contains_vertex(v)) {
                this->m_adjacency_list.emplace_back(v, std::list<T>());
            }
        }

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

            // At this point, it_u and it_v are guaranteed to be valid iterators
            // Add the edge between u and v
            it_u->second.push_back(v);
            it_v->second.push_back(u);
        }

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

        size_t degree(T v) const {
            auto it = std::find_if(this->m_adjacency_list.begin(), this->m_adjacency_list.end(), [&v](const std::pair<T, std::list<T>>& pair) {
                return pair.first == v;
            });

            return it != this->m_adjacency_list.end() ? it->second.size() : 0;
        }

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

} // namespace grphx
   
