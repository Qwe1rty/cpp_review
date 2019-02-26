//
// Created by Caleb Choi on 24/02/2019.
//

#include "avl_tree.h"

using data::avl_tree;

/*
 * Special member functions
 * NOTE: no copy & swap, so basic exception guarantee only
 */

template<typename T>
inline avl_tree::avl_tree(const avl_tree<T>& src) :
        head(new avl_tree::node(*(src.head)))
{}

template<typename T>
inline avl_tree::avl_tree(avl_tree<T>&& src) :
        head(std::move(src.head))
{}

template<typename T>
inline avl_tree<T>& avl_tree::operator=(const avl_tree<T>& src)
{
    if (this != &src)
    {
        head = std::make_unique<avl_tree::node>(*(src.head));
    }
    return *this;
}

template<typename T>
inline avl_tree<T>& avl_tree::operator=(avl_tree<T>&& src)
{
    if (this != &src)
    {
        head = std::move(src.head);
    }
    return *this;
}

/*
 * Interface functions
 */

template<typename T>
inline avl_tree::size_type avl_tree::size() const noexcept
{
    return head ? head->tree_size : 0;
}

template<typename T>
inline avl_tree::size_type avl_tree::height() const noexcept
{
    return head ? head->tree_height : 0;
}

template<typename T>
inline bool avl_tree::contains(const T& val) const
{
    return head && head->contains(val);
}

template<typename T>
inline bool avl_tree::empty() const noexcept
{
    return !head;
}

template<typename T>
inline void avl_tree::remove(const T& val)
{
    if (head) { head = head->remove(val); }
}

template<typename T>
inline void avl_tree::remove(T&& val)
{
    if (head) { head = head->remove(std::move(val)); }
}

template<typename T>
inline void avl_tree::insert(const T& val)
{
    emplace(val);
}

template<typename T>
inline void avl_tree::insert(T&& val)
{
    emplace(std::move(val));
}

// Emplace construction happens early on here due to the need to compare it immediately
template<typename T, typename...Args>
inline void avl_tree::emplace(Args&&... args)
{
    T value(std::forward(args)...);
    head = (head ? head->insert(std::move(value)) : std::make_unique<T>(std::move(value)));
}

/*
 * Special member functions (node)
 */

/*
 * AVL functions
 */

//template<typename T>
//avl_tree::node avl_tree::node::find(const T& val) const
//{
//    if (&(this->val) == &val || this->val == val) return true;
//    else if (val < this->val && this->left) return this->left->contains(val);
//    else if (this->right) return this->right->contains(val);
//    return false;
//}
