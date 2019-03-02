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
        head_(new Node(*src.head_))
{}

template<typename T>
inline AvlTree<T>::AvlTree(AvlTree<T>&& src) noexcept :
        head_(std::move(src.head_))
{}

template<typename T>
inline AvlTree<T>& AvlTree<T>::operator=(const AvlTree<T>& src)
{
    if (this != &src)
    {
        head_ = std::make_unique<Node>(*src.head_);
    }
    return *this;
}

template<typename T>
inline AvlTree<T>& AvlTree<T>::operator=(AvlTree<T>&& src) noexcept
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
inline typename AvlTree<T>::size_type AvlTree<T>::size() const noexcept
{
    return Node::get_size(head_.get());
}

template<typename T>
inline typename AvlTree<T>::size_type AvlTree<T>::height() const noexcept
{
    return Node::get_height(head_.get());
}

template<typename T>
inline bool AvlTree<T>::contains(const T& val) const noexcept
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
//    head_ = std::make_unique<Node>(*Node::insert(val, head_.release()));
    head_.reset(Node::insert(val, head_.release()));
}

template<typename T>
inline void AvlTree<T>::insert(T&& val)
{
//    head_ = std::make_unique<Node>(*Node::insert(std::move(val), head_.release()));
    head_.reset(Node::insert(std::move(val), head_.release()));
}

// Emplace construction happens early on here due to the need to compare it immediately
template<typename T>
template<typename...Args>
inline void AvlTree<T>::emplace(Args&&... args)
{
    insert(T(std::forward(args)...)); // Unavoidable copy if T is not movable
}

/*
 * Other operator overloads
 */

// operator<< defined in data namespace, or else C++ thinks that the one defined in the header
// file and the one here are two different functions - leading to ambiguous overload
//
// https://stackoverflow.com/questions/38082022/operator-overloading-namespaces-and-templates
namespace data {
    template<typename T>
    std::ostream& operator<< (std::ostream& os, const data::AvlTree<T>& tree)
    {
        data::AvlTree<T>::Node::print(os, tree.head_.get());
        return os;
    }
}

/*
 * Special member functions (Node)
 */

template<typename T>
inline data::AvlTree<T>::Node::Node(const T& src, Node* parent, Node* left, Node* right) :
        val_(std::make_unique<T>(src)),
        parent_(parent),
        left_(std::unique_ptr<Node>(left)),
        right_(std::unique_ptr<Node>(right)),
        size_(1),
        height_(1)
{}

/*
 * AVL functions
 * TODO: see if semi-duplicate left/right code can be reduced
 */

template<typename T>
typename data::AvlTree<T>::Node* data::AvlTree<T>::Node::rotate_left(Node* node)
{
    Node* newHead = node->right_.release();

    // Transfer ownership of node->right_->left_ to node
    node->right_ = std::move(newHead->left_);
    if (node->right_)
    {
        node->right_->parent_ = node;
    }

    // Made newHead the new head
    node->parent_ = newHead;
    newHead->left_.reset(node);

    update_stats(node);
    update_stats(newHead);
    return newHead;
}

template<typename T>
typename data::AvlTree<T>::Node* data::AvlTree<T>::Node::rotate_right(Node* node)
{
    Node *newHead = node->left_.release();

    // Transfer ownership of node->left_->right_ to node
    node->left_ = std::move(newHead->right_);
    if (node->left_)
    {
        node->left_->parent_ = node;
    }

    // Made newHead the new head
    node->parent_ = newHead;
    newHead->right_.reset(node);

    update_stats(node);
    update_stats(newHead);
    return newHead;
}

// TODO: see if all the 3-line process-parent-reset can be correctly reduced to 2 lines
template<typename T>
template<typename V>
typename data::AvlTree<T>::Node* data::AvlTree<T>::Node::insert(V&& val, Node* node)
{
    if (node == nullptr) { return new Node(val, nullptr, nullptr, nullptr); }

    // Standard BST insertion
    if (*node->val_ > val)
    {
        Node* newLeft = insert(std::move(val), node->left_.release());
        newLeft->parent_ = node;
        node->left_.reset(newLeft);
    }
    else if (*node->val_ < val)
    {
        Node* newRight = insert(std::move(val), node->right_.release());
        newRight->parent_ = node;
        node->right_.reset(newRight);
    }
    Node::update_stats(node);

    // Rebalance tree, and return the resulting new head
    Node* newHead = node;
    {
        int delta = Node::delta(node);
        if (delta < -1)
        {
            if (Node::delta(node->left_.get()) > 0)
            {
                Node* newLeft = Node::rotate_left(node->left_.release());
                newLeft->parent_ = node;
                node->left_.reset(newLeft);
            }
            newHead = Node::rotate_right(node);
        }
        else if (delta > 1)
        {
            if (Node::delta(node->right_.get()) < 0)
            {
                Node* newRight = Node::rotate_right(node->right_.release());
                newRight->parent_ = node;
                node->right_.reset(newRight);
            }
            newHead = Node::rotate_left(node);
        }
    }

    return newHead;
}

/*
 * Bookkeeping functions
 */

template<typename T>
inline void data::AvlTree<T>::Node::update_stats(Node* node)
{
    if (node)
    {
        node->size_ = get_size(node->left_.get()) + get_size(node->right_.get()) + 1;
        node->height_ = std::max(get_height(node->left_.get()), get_height(node->right_.get())) + 1;
    }
}

template<typename T>
inline int data::AvlTree<T>::Node::delta(const Node *node) noexcept
{
    return get_height(node->right_.get()) - get_height(node->left_.get());
}

template<typename T>
inline typename data::AvlTree<T>::size_type data::AvlTree<T>::Node::get_size(const Node *node) noexcept
{
    return node ? node->size_ : 0;
}

template<typename T>
inline typename data::AvlTree<T>::size_type data::AvlTree<T>::Node::get_height(const Node *node) noexcept
{
    return node ? node->height_ : 0;
}

template<typename T>
void data::AvlTree<T>::Node::print(std::ostream& os, const Node* node, const int depth)
{
    if (node)
    {
        print(os, node->right_.get(), depth + 1);

        for (int i = 0; i < depth; ++i) { os << "  "; }
        os << *node->val_ << '\n';

        print(os, node->left_.get(), depth + 1);
    }
}