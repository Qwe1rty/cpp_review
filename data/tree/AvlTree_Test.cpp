//
// Created by Caleb Choi on 02/03/2019.
//

#include <iostream>
#include "AvlTree.h"

namespace
{
    struct Movable
    {
        Movable(int);
        Movable(const Movable&);
        Movable(Movable&&);

        friend bool operator== (const Movable&, const Movable&);
        friend bool operator!= (const Movable&, const Movable&);
        friend bool operator<  (const Movable&, const Movable&);
        friend bool operator<= (const Movable&, const Movable&);
        friend bool operator>  (const Movable&, const Movable&);
        friend bool operator>= (const Movable&, const Movable&);
        friend std::ostream& operator<< (std::ostream&, const Movable&);

        std::unique_ptr<int> val_;
    };

    Movable::Movable(int i) : val_(std::make_unique<int>(i)) {}
    Movable::Movable(const Movable& src) : val_(std::make_unique<int>(*src.val_))
    { std::cout << "Movable copied: " << *val_ << '\n'; }
    Movable::Movable(Movable&& src) : val_(std::move(src.val_))
    { std::cout << "Movable moved: " << *val_ << '\n'; }

    bool operator== (const Movable& lhs, const Movable& rhs) { return *lhs.val_ == *rhs.val_; }
    bool operator!= (const Movable& lhs, const Movable& rhs) { return !(lhs == rhs); }
    bool operator<  (const Movable& lhs, const Movable& rhs) { return *lhs.val_ < *rhs.val_; }
    bool operator<= (const Movable& lhs, const Movable& rhs) { return (lhs < rhs) || (lhs == rhs); }
    bool operator>  (const Movable& lhs, const Movable& rhs) { return !(lhs <= rhs); }
    bool operator>= (const Movable& lhs, const Movable& rhs) { return !(lhs < rhs); }
    std::ostream& operator<< (std::ostream& os, const Movable& rhs)
    {
        os << *rhs.val_;
        return os;
    }
}

template<typename T>
void print_stats(const data::AvlTree<T>& tree)
{ std::cout << tree.empty() << ' ' << tree.height() << ' ' << tree.size() << '\n'; }

template<typename T>
void print_tree(const data::AvlTree<T>& tree)
{ std::cout << tree << '\n'; }

int main()
{
    data::AvlTree<int> int_tree;
    data::AvlTree<Movable> mov_tree;

    auto insert_int = [&int_tree](int val)
    {
        int_tree.insert(val);
        print_stats<int>(int_tree);
        print_tree<int>(int_tree);
    };
    auto insert_mov = [&mov_tree](int val)
    {
        mov_tree.insert(Movable(val));
        print_stats<Movable>(mov_tree);
        print_tree<Movable>(mov_tree);
    };

    print_stats(int_tree);
    insert_int(50);
    insert_int(40);
    insert_int(30); // Causes right rotation at root
    insert_int(20);
    insert_int(10); // Causes right rotation at depth 2
    insert_int(35); // Causes right-left rotation at depth 2
    insert_int(70);
    insert_int(80); // Causes left rotation at depth 3
    insert_int(60); // Causes right-left rotation at depth 2
    insert_int(15); // Causes left-right rotation at depth 2
    insert_int(15); // Should do nothing

    std::cout << '\n';

    print_stats(mov_tree);
    insert_mov(10);
}