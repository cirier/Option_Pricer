#pragma once
#include <vector>
#include <iostream>

/*
We gonna create a template class.
It is a class that allows the programmer to operate with generic data types
*/

template<typename T> //Declaration of the template class following by its parameters
class BinaryTree
{
private:
	int _depth;
	std::vector<std::vector<T>> _tree; // Initialization of a vector of vector of data of type T

public:
	// Constructor 
	BinaryTree() : _depth(0) {
		_tree.resize(1);
	}

	BinaryTree(int depth) : _depth(depth) { // Initialization of _depth with the value of depth
		_tree.resize(depth + 1); // Resize _tree (initial size 0) with a depth+1 size [depth0 is include]
		for (int i = 0; i <= depth; ++i) {
			_tree[i].resize(i + 1);
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

	// Implementation of setNode
	/*
	* int i : Position of the node in the "big" vector
	* int j : Position of the node in the "small" vector (vector[i])
	* const T value : value of type T / const -> cannot modify accidentaly the value of value
	*/
	void setNode(int i, int j, const T value) {
		if (i<0 || j<0 || i>_depth || j>i) { // j>i because size of vector[i] cannot be more than i
			throw std::invalid_argument("Invalid indices.");
		}
		else {
			_tree[i][j] = value;
		}
	}

	//Implementation of getNode
/*
* int i : Position of the node in the "big" vector
* int j : Position of the node in the "small" vector (vector[i])
* const -> Indicates that the function cannot modify the object on which it is called.
*/
	T getNode(int i, int j) const {
		if (i<0 || j<0 || i>_depth || j>i) { // j>i because size of vector[i] cannot be more than i
			throw std::invalid_argument("Invalid indices.");
		}

		return _tree[i][j];
		/*
		while (i<0 || j<0 || i>_depth || j>i) { // j>i because size of vector[i] cannot be more than i
			std::cout << "Invalid indices."<<std::endl;
			if (i<0 || i>_depth) {
				std::cout << "Enter a value for i between 0 and the depth of your tree :"<<std::endl;
				std::cin >> i;
			}
			if (j<0 || j>i) {
				std::cout << "Enter a value for j between 0 and "<<i<<" :"<<std::endl;
				std::cin >> j;
			}

		}
		return _tree[i][j];*/
	}

	// Implementation of the display method
	void display() const {
		for (int i = 0; i < _tree.size();++i) {
			for (int j = 0; j < _tree[i].size();++j) {
				std::cout << _tree[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

};