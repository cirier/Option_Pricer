#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <stdexcept>

// Template class BinaryTree
template <typename T>
class BinaryTree {
private:
    int _depth;
    std::vector<std::vector<T>> _tree;

public:
    BinaryTree(int depth) : _depth(depth) {
        _tree.resize(depth + 1);
        for (int i = 0; i <= depth; ++i) {
            _tree[i].resize(i + 1);
        }
    }

    void setDepth(int newDepth) {
        if (newDepth < 0) {
            throw std::invalid_argument("Depth cannot be negative.");
        }

        _depth = newDepth;
        _tree.resize(_depth + 1);
        for (int i = 0; i <= _depth; ++i) {
            _tree[i].resize(i + 1);
        }
    }

    void setNode(int i, int j, const T value) {
        if (i < 0 || j < 0 || i > _depth || j > i) {
            throw std::invalid_argument("Invalid indices.");
        }
        _tree[i][j] = value;
    }

    T getNode(int i, int j) const {
        if (i < 0 || j < 0 || i > _depth || j > i) {
            throw std::invalid_argument("Invalid indices.");
        }
        return _tree[i][j];
    }

    void display() const {
        for (int i = 0; i <= _depth; ++i) {
            for (int j = 0; j <= i; ++j) {
                std::cout << _tree[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};


#include "BinaryTree.cpp"  // Inclusion des définitions de template

#endif // BINARYTREE_H
