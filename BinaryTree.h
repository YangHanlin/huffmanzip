// BinaryTree.h
// binarytree module - interface

#ifndef LINKEDTREE_H
#define LINKEDTREE_H

#include <cstdlib>

template <class T> class Node;
template <class T> class BinaryTree;
template <class T> class BinaryTreeIterator;
template <class T> class BinaryTreeConstIterator;

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
    friend class BinaryTreeConstIterator<T>;
};

template <class T>
class BinaryTree {
public:
    typedef BinaryTreeIterator<T> Iterator;
    typedef BinaryTreeConstIterator<T> ConstIterator;
    BinaryTree();
    BinaryTree(const BinaryTree &rhs);
    BinaryTree(const T &src);
    ~BinaryTree();
    BinaryTree<T> &operator=(const BinaryTree<T> &rhs);
    T &operator[](int seq);
    const T &operator[](int seq) const;
    Iterator root();
    ConstIterator root() const;
    static void copy(const Iterator &to, const ConstIterator &from);
    static void move(const Iterator &to, const Iterator &from);
    void clear();
    static void clear(const Iterator &iter);
private:
    Node<T> *anchor;
    static void copy(Node<T> *&to, Node<T> * const &from);
    static void clear(Node<T> *&target);
    friend class BinaryTreeIterator<T>;
    friend class BinaryTreeConstIterator<T>;
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
    BinaryTreeIterator<T> &go(int seq, BinaryTreeIterator<T> &res) const;
    Node<T> **p;
};

template <class T>
class BinaryTreeConstIterator {
public:
    BinaryTreeConstIterator(Node<T> * const &p);
    BinaryTreeConstIterator(const BinaryTreeIterator<T> &iter);
    const T &operator*() const;
    const T *operator->() const;
    bool null() const;
    BinaryTreeConstIterator<T> lchild() const;
    BinaryTreeConstIterator<T> rchild() const;
    BinaryTreeConstIterator<T> go(int seq) const;
    friend class BinaryTree<T>;
private:
    BinaryTreeConstIterator<T> &go(int seq, BinaryTreeConstIterator<T> &res) const;
    Node<T> * const *p;
};

#include "BinaryTree.ipp"

#endif
