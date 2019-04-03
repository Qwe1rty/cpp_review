//
// Created by Caleb Choi on 30/03/2019.
//

#ifndef CLION_BASIC_H
#define CLION_BASIC_H

#include <string>
#include <memory>

namespace dynamic
{
    class Base
    {
    public:
        Base()          = default;
        virtual ~Base() = default;

        Base(const Base&)                = delete;
        Base(Base&&) noexcept            = delete;
        Base& operator=(const Base&)     = delete;
        Base& operator=(Base&&) noexcept = delete;

        virtual void something()              const;
        virtual std::unique_ptr<Base> clone() const;
        virtual std::unique_ptr<Base> move()  noexcept;

    private:
        int int_resource_ = 111;
    };

    class Derived1 : public Base
    {
        Derived1();
        Derived1(std::string);
        ~Derived1() override;

        Derived1(const Derived1&);
        Derived1(Derived1&&) noexcept;
        Derived1& operator=(const Derived1&);
        Derived1& operator=(Derived1&&) noexcept;

        void something()                const override;
        std::unique_ptr<Base> clone()   const override;
        std::unique_ptr<Base> move() noexcept override;

    private:
        std::string string_resource_;
    };

    class Derived2 : public Base
    {

    };
};

#endif //CLION_BASIC_H