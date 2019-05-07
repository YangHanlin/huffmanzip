// BinaryTree.ipp
// binary tree module - implementation

#ifndef BINARYTREE_IPP

#include "BinaryTree.h"

#include <cstdlib>

template <class T>
Node<T>::Node() : lchild(NULL), rchild(NULL) {}

template <class T>
Node<T>::Node(const T &content, Node<T> *lchild, Node<T> *rchild) : content(content), lchild(lchild), rchild(rchild) {}

template <class T>
BinaryTree<T>::BinaryTree() {
    // ...
}

#endif
