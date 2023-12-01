#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class BinaryTree {
private:
    int _depth;
    T _defaultValue;
    std::vector<std::vector<T>> _tree;

public:

    // Default constructor
    BinaryTree() : _depth(0), _defaultValue(T()) {
        // Initialize with depth 0, which means no elements
        _tree.resize(1);
        _tree[0].resize(1, _defaultValue); // Use _defaultValue for the type T
    }


    // Constructor for initializing with a specific depth
    BinaryTree(int depth) : _depth(depth), _defaultValue(T()) {
        _tree.resize(depth + 1);
        for (int i = 0; i <= depth; ++i) {
            _tree[i].resize(i + 1, _defaultValue); // Use _defaultValue for type T
        }
    }

    // Constructor for initializing with a specific depth and default value
    BinaryTree(int depth, T defaultValue) : _depth(depth), _defaultValue(defaultValue) {
        _tree.resize(depth + 1);
        for (int i = 0; i <= depth; ++i) {
            _tree[i].resize(i + 1, _defaultValue);
        }
    }

    // Setter method for _depth
    void setDepth(int newDepth) {
        if (newDepth < 0) {
            throw std::invalid_argument("Depth cannot be negative.");
        }
        else {
            _depth = newDepth;
            _tree.resize(_depth + 1); // Resize _tree (initial size 0) with a depth+1 size [depth0 is include]
            for (int i = 0; i <= _depth; ++i) {
                _tree[i].resize(i + 1);
            }
        }
    }

    void setNode(int i, int j, const T value) {
        if (i<0 || j<0 || i>_depth || j>i) { // j>i because size of vector[i] cannot be more than i
            throw std::invalid_argument("Invalid indices.");
        }
        else {
            _tree[i][j] = value;
        }
    }

    T getNode(int i, int j) const {
        if (i < 0 || j < 0 || i > _depth || j > i) {
            throw std::invalid_argument("Invalid indices.");
        }
        return _tree[i][j];
    }

    void display() const {
        for (int i = 0; i < _tree.size(); ++i) {
            for (int j = 0; j < _tree[i].size(); ++j) {
                std::cout << _tree[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif
