//
// Created by Caleb Choi on 24/02/2019.
//

#ifndef CLION_AVL_TREE_H
#define CLION_AVL_TREE_H

#include <memory>
#include <ostream>

namespace data
{
    template<typename T> class AvlTree;
    template<typename T> std::ostream& operator<< (std::ostream&, const AvlTree<T>&);

    template<typename T>
    class AvlTree final
    {
    public:

        /* Aliases */
        using value_type        = T;
        using pointer           = value_type*;
        using reference         = value_type&;
        using const_reference   = const value_type&;
        using move_reference    = value_type&&;
        using size_type         = int; // https://www.aristeia.com/Papers/C++ReportColumns/sep95.pdf

        /* Special member functions */
        AvlTree()  = default;
        ~AvlTree() = default;
        AvlTree(const AvlTree<T>& src);
        AvlTree(AvlTree<T>&& src) noexcept;
        AvlTree<T>& operator= (const AvlTree<T>& src);
        AvlTree<T>& operator= (AvlTree<T>&& src) noexcept;

        /* Interface functions */
        size_type size() const noexcept;
        size_type height() const noexcept;
        bool contains(const T& val) const noexcept;
        bool empty() const noexcept;
        void remove(const T& val);
        void remove(T&& val);
        void insert(const T& val);
        void insert(T&& val);
        template<typename...Args> void emplace(Args&&... args);

        /* Relational operator overloads */
        template<typename U>
        friend bool operator== (const AvlTree<U>&, const AvlTree<U>&);
        template<typename U>
        friend bool operator!= (const AvlTree<U>&, const AvlTree<U>&);
        template<typename U>
        friend bool operator<  (const AvlTree<U>&, const AvlTree<U>&);
        template<typename U>
        friend bool operator<= (const AvlTree<U>&, const AvlTree<U>&);
        template<typename U>
        friend bool operator>  (const AvlTree<U>&, const AvlTree<U>&);
        template<typename U>
        friend bool operator>= (const AvlTree<U>&, const AvlTree<U>&);

        /* Other operator overloads */
        friend std::ostream& operator<< <T>(std::ostream&, const AvlTree<T>&);

    private:

        /* Node struct */
        class Node
        {
        public:

            /* Special member functions (Node) */
            Node() = delete;
            ~Node() = default;
            Node(const Node& src);
            Node(Node&& src) noexcept;
            explicit Node(const T& src);
            explicit Node(T&& src);

            /* AVL functions */
            static Node* rotate_left(Node* node);
            static Node* rotate_right(Node* node);
            static Node* find(const T& val) noexcept;
            static bool contains(const T& val) noexcept;
            template<typename V>
            static Node* insert(V&& val, Node* node);
            template<typename V>
            static Node* remove(V&& val, Node* node);

            /* Bookkeeping functions */
            static void update_stats(Node* node);
            static int delta(const Node* node) noexcept;
            static size_type get_size(const Node* node) noexcept;
            static size_type get_height(const Node* node) noexcept;
            static void print(std::ostream& os, const Node* node, const int depth = 0);

        private:

            /* Fields (Node) */
            Node* parent_ = nullptr;
            std::unique_ptr<Node> left_;
            std::unique_ptr<Node> right_;
            std::unique_ptr<T> val_;
            size_type size_ = 1;
            size_type height_ = 1;
        };

        /* Fields */
        std::unique_ptr<Node> head_;
    };
}

#include "AvlTree.tpp"

#endif //CLION_AVL_TREE_H
