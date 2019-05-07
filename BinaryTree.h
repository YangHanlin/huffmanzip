// BinaryTree.h
// binarytree module - interface

#ifndef LINKEDTREE_H
#define LINKEDTREE_H

#include <cstdlib>

template <class T> class Node;
template <class T> class BinaryTree;
template <class T> class BinaryTreeIterator;

template <class T>
class Node {
public:
    Node();
    Node(const T &content, Node<T> *lchild = NULL, Node<T> *rchild = NULL);
private:
    T content;
    Node<T> *lchild, *rchild;
    friend class BinaryTree<T>;
    friend class BinaryTreeIterator<T>;
};

template <class T>
class BinaryTree {
public:
    typedef BinaryTreeIterator<T> Iterator;
    BinaryTree();
    BinaryTree(const BinaryTree &rhs);
    BinaryTree(const T &src);
    ~BinaryTree();
    T &operator[](int seq);
    const T &operator[](int seq) const;
    Iterator root() const;
    BinaryTree<T> subTree(const Iterator &iter) const;
    void move(const Iterator &iter, BinaryTree<T> &src);
    void clear();
    friend class BinaryTreeIterator<T>;
private:
    Node<T> *anchor;
    void clear(Node<T> *target);
};

template <class T>
class BinaryTreeIterator {
public:
    BinaryTreeIterator(Node<T> *&p);
    T &operator*() const;
    T *operator->() const;
    bool null() const;
    BinaryTreeIterator<T> lchild() const;
    BinaryTreeIterator<T> rchild() const;
    BinaryTreeIterator<T> go(int seq) const;
    friend class BinaryTree<T>;
private:
    Node<T> **p;
};

#include "BinaryTree.ipp"

#endif
