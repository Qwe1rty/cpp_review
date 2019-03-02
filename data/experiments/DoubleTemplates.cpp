//
// Created by Caleb Choi on 26/02/2019.
//

#include <iostream>

struct Thing {
    Thing()                       { std::cout << "Thing init constructor called\n"; }
    Thing(const Thing& thing)     { std::cout << "Thing copy constructor called\n"; }
    Thing(Thing&& thing) noexcept { std::cout << "Thing move constructor called\n"; }
    ~Thing()                      = default;
};

struct CopyOnlyThing {
    CopyOnlyThing()                           { std::cout << "CopyOnlyThing init constructor called\n"; }
    CopyOnlyThing(const CopyOnlyThing& thing) { std::cout << "CopyOnlyThing copy constructor called\n"; }
    ~CopyOnlyThing()                          = default;
};

struct MoveOnlyThing {
    MoveOnlyThing()                               { std::cout << "MoveOnlyThing init constructor called\n"; }
    MoveOnlyThing(MoveOnlyThing&& thing) noexcept { std::cout << "MoveOnlyThing move constructor called\n"; }
    ~MoveOnlyThing()                              = default;
};

template<typename T>
struct Ping {
    void set(const T& val);
    void set(T&& val);
private:
    struct Pong {
        template<typename C>
        static void set(C&& val);
    };
};

template<typename T>
void Ping<T>::set(const T& val) { Pong::set(val); }

template<typename T>
void Ping<T>::set(T&& val) { Pong::set(std::move(val)); }

template<typename T>
template<typename C>
void Ping<T>::Pong::set(C&& val) {
    std::cout << "entering pong::set\n";
    T(std::forward<C>(val));
    std::cout << "exiting pong::set\n";
}

int main() {
    Ping<Thing> p1;
    Ping<CopyOnlyThing> p2;
    Ping<MoveOnlyThing> p3;

    Thing t;
    p1.set(t);
    std::cout << '\n';
    
    p1.set(Thing());
    std::cout << '\n';
    
    CopyOnlyThing c;
    p2.set(c);
    std::cout << '\n';

    p2.set(CopyOnlyThing());
    std::cout << '\n';

    // Error: calls Ping<MoveOnlyThing>::set(const MoveOnlyThing& val) but errors
    //        on construction due to lack of copy constructor
//    MoveOnlyThing m;
//    p3.set(m);
//    std::cout << '\n';

    p3.set(MoveOnlyThing());
    std::cout << '\n';
}

// Program output:
/*
Thing init constructor called
entering pong::set
Thing copy constructor called
exiting pong::set

Thing init constructor called
entering pong::set
Thing move constructor called
exiting pong::set

CopyOnlyThing init constructor called
entering pong::set
CopyOnlyThing copy constructor called
exiting pong::set

CopyOnlyThing init constructor called
entering pong::set
CopyOnlyThing copy constructor called
exiting pong::set

MoveOnlyThing init constructor called
entering pong::set
MoveOnlyThing move constructor called
exiting pong::set
*/
