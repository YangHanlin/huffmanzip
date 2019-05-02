// BinaryTree.h
// This file contains declarations for a linked binary tree with limited functions.

#ifndef BINARYTREE_H

template <class T> class Node;
template <class T> class BinaryTree;
template <class T> class BinaryTreeIterator;

template <class T>
class Node {
private:
    T content;
    Node<T> *lchild, *rchild;
public:
    Node();
    Node(const T &content, Node<T> *lchild, Node<T> *rchild);
    friend class BinaryTree<T>;
};

template <class T>
class BinaryTree {
private:
    Node<T> *anchor;
public:
    typedef BinaryTreeIterator<T> Iterator;
    BinaryTree();
    BinaryTree(const BinaryTree &rhs);
    BinaryTree(const T &content);
    ~BinaryTree();
    Iterator root();
    Iterator root(lchild)
};

#endif
