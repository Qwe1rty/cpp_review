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
    return Node::get_size(head_);
}

template<typename T>
inline typename AvlTree<T>::size_type AvlTree<T>::height() const noexcept
{
    return Node::get_height(head_);
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
    head_ = Node::remove(val, std::move(head_));
}

template<typename T>
inline void AvlTree<T>::remove(T&& val)
{
    head_ = Node::remove(std::move(val), std::move(head_));
}

template<typename T>
inline void AvlTree<T>::insert(const T& val)
{
    head_ = Node::insert(val, std::move(head_));
}

template<typename T>
inline void AvlTree<T>::insert(T&& val)
{
    head_ = Node::insert(std::move(val), std::move(head_));
}

// Emplace construction happens early on here due to the need to compare it immediately
template<typename T>
template<typename...Args>
inline void AvlTree<T>::emplace(Args&&... args)
{
    insert(T(std::forward<Args>(args)...)); // Unavoidable copy if T is not movable
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
    std::ostream& operator<< (std::ostream& os, const AvlTree<T>& tree)
    {
        AvlTree<T>::Node::print(os, tree.head_);
        return os;
    }
}

/*
 * Special member functions (Node)
 */

template<typename T>
inline AvlTree<T>::Node::Node(const T& src) :
        val_(std::make_unique<T>(src)),
        parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        size_(1),
        height_(1)
{}

template<typename T>
inline AvlTree<T>::Node::Node(T&& src) :
        val_(std::make_unique<T>(std::move(src))),
        parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        size_(1),
        height_(1)
{}

/*
 * AVL functions
 * TODO: see if semi-duplicate left/right code can be reduced
 */

template<typename T>
void AvlTree<T>::Node::print(std::ostream& os, const std::unique_ptr<Node>& node, const int depth)
{
    if (node)
    {
        print(os, node->right_, depth + 1);

        for (int i = 0; i < depth; ++i) { os << "  "; }
        os << *node->val_ << '\n';

        print(os, node->left_, depth + 1);
    }
}

template<typename T>
inline typename AvlTree<T>::size_type AvlTree<T>::Node::get_size(const std::unique_ptr<Node>& node) noexcept
{
    return node ? node->size_ : 0;
}

template<typename T>
inline typename AvlTree<T>::size_type AvlTree<T>::Node::get_height(const std::unique_ptr<Node>& node) noexcept
{
    return node ? node->height_ : 0;
}

template<typename T>
template<typename V>
std::unique_ptr<typename AvlTree<T>::Node> AvlTree<T>::Node::insert(V&& val, std::unique_ptr<Node> node)
{
    if (!node) { return std::make_unique<Node>(std::forward<V>(val)); }

    // Standard BST insertion
    if (*node->val_ > val)
    {
        node->left_ = insert(std::forward<V>(val), std::move(node->left_));
        node->left_->parent_ = node.get();
    }
    else if (*node->val_ < val)
    {
        node->right_ = insert(std::forward<V>(val), std::move(node->right_));
        node->right_->parent_ = node.get();
    }
    update_stats(node.get());

    // Rebalance tree, and return the resulting new head
    std::unique_ptr<Node> head = std::move(node);
    {
        int delta = Node::delta(head);
        if (delta < -1)
        {
            if (Node::delta(head->left_) > 0)
            {
                head->left_ = rotate_left(std::move(head->left_));
                head->left_->parent_ = head.get();
            }
            head = rotate_right(std::move(head));
        }
        else if (delta > 1)
        {
            if (Node::delta(head->right_) < 0)
            {
                head->right_ = rotate_right(std::move(head->right_));
                head->right_->parent_ = head.get();
            }
            head = rotate_left(std::move(head));
        }
    }

    return head;
}

template<typename T>
template<typename V>
std::unique_ptr<typename AvlTree<T>::Node> AvlTree<T>::Node::remove(V&& val, std::unique_ptr<Node> node)
{
    if (!node || *node->val_ == val)
    {
        return node;
    }
    else if (*node->val_ > val)
    {
//        Node* newLeft = remove(std::forward<V>(val), node->left_.get());
//        if (*node->left_.get() == newLeft)
//        {
//
//        }
    }
    return node;
}

/*
 * Bookkeeping functions
 */

template<typename T>
inline std::unique_ptr<typename AvlTree<T>::Node> AvlTree<T>::Node::rotate_left(std::unique_ptr<Node> node)
{
    // Transfer ownership of node->right node to function
    std::unique_ptr<Node> head = std::move(node->right_);

    // Transfer ownership of node->right_->left_ to node
    node->right_ = std::move(head->left_);
    if (node->right_) { node->right_->parent_ = node.get(); }

    // Make "head" actually the new head
    head->left_ = std::move(node);
    head->left_->parent_ = head.get();

    update_stats(node.get());
    update_stats(head.get());
    return head;
}

template<typename T>
inline std::unique_ptr<typename AvlTree<T>::Node> AvlTree<T>::Node::rotate_right(std::unique_ptr<Node> node)
{
    // Transfer ownership of node->left node to function
    std::unique_ptr<Node> head = std::move(node->left_);

    // Transfer ownership of node->left_->right_ to node
    node->left_ = std::move(head->right_);
    if (node->left_) { node->left_->parent_ = node.get(); }

    // Make "head" actually the new head
    head->right_ = std::move(node);
    head->right_->parent_ = head.get();

    update_stats(node.get());
    update_stats(head.get());
    return head;
}

template<typename T>
inline int AvlTree<T>::Node::delta(const std::unique_ptr<Node>& node) noexcept
{
    return get_height(node->right_) - get_height(node->left_);
}

template<typename T>
inline void AvlTree<T>::Node::update_stats(Node* node)
{
    if (node)
    {
        node->size_ = get_size(node->left_) + get_size(node->right_) + 1;
        node->height_ = std::max(get_height(node->left_), get_height(node->right_)) + 1;
    }
}