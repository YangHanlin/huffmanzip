// BinaryTree.ipp
// binary tree module - implementation

#ifndef BINARYTREE_IPP

#include "BinaryTree.h"

#include <stdexcept>
#include <cstdlib>

using std::out_of_range;

template <class T>
Node<T>::Node() : lchild(NULL), rchild(NULL) {}

template <class T>
Node<T>::Node(const T &content, Node<T> *lchild, Node<T> *rchild) : content(content), lchild(lchild), rchild(rchild) {}

template <class T>
BinaryTree<T>::BinaryTree() : anchor(NULL) {}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree &rhs) : anchor(NULL) {
    copy(anchor, rhs.anchor);
}

template <class T>
BinaryTree<T>::BinaryTree(const T &src) : anchor(new Node<T>(src, NULL, NULL)) {}

template <class T>
BinaryTree<T>::~BinaryTree() {
    clear();
}

template <class T>
T &BinaryTree<T>::operator[](int seq) {
    return *root().go(seq);
}

template <class T>
const T &BinaryTree<T>::operator[](int seq) const {
    return *root().go(seq);
}

template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::root() {
    return Iterator(anchor);
}

template <class T>
typename BinaryTree<T>::ConstIterator BinaryTree<T>::root() const {
    return ConstIterator(anchor);
}

template <class T>
void BinaryTree<T>::copy(const Iterator &to, const ConstIterator &from) {
    if (!to.null())
        clear(to);
    copy(*to.p, *from.p);
}

template <class T>
void BinaryTree<T>::move(const Iterator &to, const Iterator &from) {
    if (!to.null())
        clear(to);
    *to.p = *from.p;
    *from.p = NULL;
}

template <class T>
void BinaryTree<T>::clear() {
    clear(anchor);
}

template <class T>
void BinaryTree<T>::clear(const Iterator &iter) {
    clear(*iter.p);
}

template <class T>
void BinaryTree<T>::copy(Node<T> *&to, const Node<T> *&from) {
    if (from == NULL)
        return;
    to = new Node<T>(from->content, NULL, NULL);
    copy(to->lchild, from->lchild);
    copy(to->rchild, from->rchild);
}


template <class T>
void clear(Node<T> *&target) {
    if (target == NULL)
        return;
    clear(target->lchild);
    clear(target->rchild);
    delete target;
    target = NULL;
}

template <class T>
BinaryTreeIterator<T>::BinaryTreeIterator(Node<T> *&p) : p(&p) {}

template <class T>
T &BinaryTreeIterator<T>::operator*() const {
    return (*p)->content;
}

template <class T>
T *BinaryTreeIterator<T>::operator->() const {
    return &operator*();
}

template <class T>
bool BinaryTreeIterator<T>::null() const {
    return *p == NULL;
}

template <class T>
BinaryTreeIterator<T> BinaryTreeIterator<T>::lchild() const {
    if (null())
        throw out_of_range("Null iterator");
    return BinaryTreeIterator<T>((*p)->lchild);
}

template <class T>
BinaryTreeIterator<T> BinaryTreeIterator<T>::rchild() const {
    if (null())
        throw out_of_range("Null iterator");
    return BinaryTreeIterator<T>((*p)->rchild);
}

template <class T>
BinaryTreeIterator<T> BinaryTreeIterator<T>::go(int seq) const {
    BinaryTreeIterator<T> res = *this;
    return go(seq, res);
}

template <class T>
BinaryTreeIterator<T> &BinaryTreeIterator<T>::go(int seq, BinaryTreeIterator<T> &res) const {
    if (seq == 0 ||  seq == 1)
        return res;
    go(seq / 2, res);
    return res = seq % 2 == 0 ? res.lchild() : res.rchild();
}

template <class T>
BinaryTreeConstIterator<T>::BinaryTreeConstIterator(const Node<T> *&p) : p(&p) {}

template <class T>
BinaryTreeConstIterator<T>::BinaryTreeConstIterator(const BinaryTreeIterator<T> &iter) : p(iter.p) {}

template <class T>
const T &BinaryTreeConstIterator<T>::operator*() const {
    return (*p)->content;
}

template <class T>
const T *BinaryTreeConstIterator<T>::operator->() const {
    return &operator*();
}

template <class T>
bool BinaryTreeConstIterator<T>::null() const {
    return *p == NULL;
}

template <class T>
BinaryTreeConstIterator<T> BinaryTreeConstIterator<T>::lchild() const {
    if (null())
        throw out_of_range("Null iterator");
    return BinaryTreeConstIterator((*p)->lchild);
}

template <class T>
BinaryTreeConstIterator<T> BinaryTreeConstIterator<T>::rchild() const {
    if (null())
        throw out_of_range("Null iterator");
    return BinaryTreeConstIterator((*p)->rchild);
}

template <class T>
BinaryTreeConstIterator<T> BinaryTreeConstIterator<T>::go(int seq) const {
    BinaryTreeConstIterator<T> res = *this;
    return go(seq, res);
}

template <class T>
BinaryTreeConstIterator<T> &BinaryTreeConstIterator<T>::go(int seq, BinaryTreeConstIterator<T> &res) const {
    if (seq == 0 || seq == 1)
        return res;
    go(seq / 2, res);
    return res = seq % 2 == 0 ? res.lchild() : res.rchild();
}

#endif
