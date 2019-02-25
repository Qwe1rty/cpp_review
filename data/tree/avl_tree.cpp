//
// Created by Caleb Choi on 24/02/2019.
//

#include "avl_tree.h"

// NOTE: no copy & swap, basic exception guarantee only
template<typename T>
inline data::avl_tree<T>::avl_tree(const avl_tree<T>& src) :
        tree_size(src.tree_size),
        tree_height(src.tree_height)
{
    this->head = std::make_unique<T>(*(src.head));
}

template<typename T>
inline data::avl_tree<T>::avl_tree(avl_tree<T>&& src) :
        tree_size(src.tree_size),
        tree_height(src.tree_height),
        head(std::move(src.head))
{}

template<typename T>
inline data::avl_tree<T>& data::avl_tree<T>::operator=(const avl_tree<T> &src)
{
    // TODO
}

template<typename T, typename...Args>
inline void data::avl_tree<T>::emplace(Args&&... args)
{
    
}
