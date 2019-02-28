//
// Created by Caleb Choi on 24/02/2019.
//

#include "AvlTree.h"

using data::AvlTree;

/*
 * Special member functions
 * NOTE: no copy & swap, so basic exception guarantee only
 */

template<typename T>
inline AvlTree<T>::AvlTree(const AvlTree<T>& src) :
        head_(new Node(*(src.head_)))
{}

template<typename T>
inline AvlTree<T>::AvlTree(AvlTree<T>&& src) :
        head_(std::move(src.head_))
{}

template<typename T>
inline AvlTree<T>& AvlTree<T>::operator=(const AvlTree<T>& src)
{
    if (this != &src)
    {
        head_ = std::make_unique<Node>(*(src.head_));
    }
    return *this;
}

template<typename T>
inline AvlTree<T>& AvlTree<T>::operator=(AvlTree<T>&& src)
{
    if (this != &src)
    {
        head_ = std::move(src.head_);
    }
    return *this;
}

/*
 * Interface functions
 */

template<typename T>
inline AvlTree<T>::size_type AvlTree<T>::size() const noexcept
{
    return head_ ? head_->tree_size_ : 0;
}

template<typename T>
inline AvlTree<T>::size_type AvlTree<T>::height() const noexcept
{
    return head_ ? head_->tree_height_ : 0;
}

template<typename T>
inline bool AvlTree<T>::contains(const T& val) const
{
    return Node::contains(head_);
}

template<typename T>
inline bool AvlTree<T>::empty() const noexcept
{
    return !head_;
}

template<typename T>
inline void AvlTree<T>::remove(const T& val)
{
    head_ = std::make_unique<Node>(*Node::remove(val, head_.release()));
}

template<typename T>
inline void AvlTree<T>::remove(T&& val)
{
    head_ = std::make_unique<Node>(*Node::remove(std::move(val), head_.release()));
}

template<typename T>
inline void AvlTree<T>::insert(const T& val)
{
    head_ = std::make_unique<Node>(*Node::insert<T>(val, head_.release()));
}

template<typename T>
inline void AvlTree<T>::insert(T&& val)
{
    head_ = std::make_unique<Node>(*Node::insert<T>(std::move(val), head_.release()));
}

// Emplace construction happens early on here due to the need to compare it immediately
template<typename T, typename...Args>
inline void AvlTree<T>::emplace(Args&&... args)
{
    T val(std::forward(args)...);
    // TODO: check movability and branch cases
    head_ = std::make_unique<Node>(*Node::insert<T>(std::move(val), head_.release()));
}

/*
 * Special member functions (Node)
 */

/*
 * AVL functions
 */
