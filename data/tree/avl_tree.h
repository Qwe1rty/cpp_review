//
// Created by Caleb Choi on 24/02/2019.
//

#ifndef CLION_AVL_TREE_H
#define CLION_AVL_TREE_H

#include <memory>
#include "avl_tree.cpp"

namespace data
{
    template<typename T>
    class avl_tree final
    {
    public:

        /* Aliases */
        using value_type        = T;
        using reference         = T&;
        using const_reference   = const T&;
        using size_type         = int; // https://www.aristeia.com/Papers/C++ReportColumns/sep95.pdf

        /* Special member functions */
        avl_tree() = default;
        ~avl_tree() = default;
        avl_tree(const avl_tree<T>& src);
        avl_tree(avl_tree<T>&& src) noexcept;
        avl_tree<T>& operator= (const avl_tree<T>& src);
        avl_tree<T>& operator= (avl_tree<T>&& src);

        /* Interface functions */
        bool empty() const noexcept;
        bool contains(const value_type& val) const;
        size_type size() const noexcept;
        size_type height() const noexcept;
        void remove(const value_type& val);
        void remove(value_type&& val);
        void insert(const value_type& val);
        void insert(value_type&& val);
        template<typename...Args> void emplace(Args&&... args);

        /* Friend functions */
        template<typename T>
        friend bool operator== (const avl_tree<T>& lhs, const avl_tree<T>& rhs) const;
        template<typename T>
        friend bool operator!= (const avl_tree<T>& lhs, const avl_tree<T>& rhs) const;

    private:

        struct node
        {
            ~node();
            node(const node& src);
            node(node&& src) noexcept;

            value_type value;
            std::unique_ptr<node> left;
            std::unique_ptr<node> right;
            size_type node_height = 0;
        };

        size_type tree_size = 0;
        size_type tree_height = 0;
        std::unique_ptr<node> head;
    };
}

#endif //CLION_AVL_TREE_H
