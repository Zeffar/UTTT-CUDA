#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include "bitset.hpp"
template <size_t M, size_t N>
class Node {
public:
    bitset2D<M, N> gameState; 
    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children; 
    int wins; 
    int visits; 

    // Factory method for creating a new Node with shared_ptr
    static std::shared_ptr<Node<M, N>> create(const bitset2D<M, N>& state, std::shared_ptr<Node<M, N>> parent = nullptr) 
        {return std::shared_ptr<Node<M, N>>(new Node<M, N>(state, parent));}
    void addChild(const bitset2D<M, N>& state) {children.push_back(std::make_shared<Node>(state, this));}
    bool isLeaf() const {return children.empty();}
    
private:
    // Constructor
    Node(const bitset2D<M, N>& state, std::shared_ptr<Node<M, N>> parent = nullptr):gameState(state), parent(parent), wins(0), visits(0) {}

    // Friend declaration
    friend class std::enable_shared_from_this<Node<M, N>>;

};
#endif