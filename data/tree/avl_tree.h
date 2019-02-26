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
        using reference         = value_type&;
        using const_reference   = const value_type&;
        using move_reference    = value_type&&;
        using size_type         = int; // https://www.aristeia.com/Papers/C++ReportColumns/sep95.pdf

        /* Special member functions */
        avl_tree()  = default;
        ~avl_tree() = default;
        avl_tree(const avl_tree<value_type>& src);
        avl_tree(avl_tree<value_type>&& src) noexcept;
        avl_tree<value_type>& operator= (const avl_tree<value_type>& src);
        avl_tree<value_type>& operator= (avl_tree<value_type>&& src);

        /* Interface functions */
        size_type size() const noexcept;
        size_type height() const noexcept;
        bool contains(const_reference val) const;
        bool empty() const noexcept;
        void remove(const_reference val);
        void remove(move_reference  val);
        void insert(const_reference val);
        void insert(move_reference  val);
        template<typename...Args> void emplace(Args&&... args);

        /* Friend functions */
        template<typename T>
        friend bool operator== (const avl_tree<T>& lhs, const avl_tree<T>& rhs) const;
        template<typename T>
        friend bool operator!= (const avl_tree<T>& lhs, const avl_tree<T>& rhs) const;

    private:

        /* Fields */
        std::unique_ptr<node> head;

        /* Node struct */
        struct node
        {
            /* Special member functions (node) */
            node() = delete;
            node(const_reference src);
            node(move_reference  src);
            ~node();
            node(const node& src);
            node(node&& src) noexcept;

            /* AVL functions */

            bool contains(const_reference val) const;
            std::unique_ptr<node> insert(move_reference val);
            std::unique_ptr<node> remove(move_reference val);
            std::unique_ptr<node> rotate_right();
            std::unique_ptr<node> rotate_left();
            int update_stats();

            /* Fields (node) */
            node* parent = nullptr;
            std::unique_ptr<node> left;
            std::unique_ptr<node> right;
            value_type val;
            size_type tree_size = 1;
            size_type tree_height = 1;
        };
    };
}

#endif //CLION_AVL_TREE_H
