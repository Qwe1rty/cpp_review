//
// Created by Caleb Choi on 02/03/2019.
//

#include <iostream>
#include "AvlTree.h"

int main()
{
    data::AvlTree<int> tree;
    auto print_stats = [&tree]()
    {
        std::cout << tree.empty() << ' ' << tree.height() << ' ' << tree.size() << '\n';
    };
    auto print_tree = [&tree]()
    {
        std::cout << tree << '\n';
    };

    print_stats();
    tree.insert(50);
    print_tree();

    print_stats();
    tree.insert(40);
    print_tree();

    print_stats();
    tree.insert(30);
    print_tree();

    print_stats();
    tree.insert(20);
    print_tree();

    print_stats();
    tree.insert(10);
    print_tree();
}