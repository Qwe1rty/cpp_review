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
        Base(int);

        Base(const Base&)                = delete;
        Base(Base&&) noexcept            = delete;
        Base& operator=(const Base&)     = delete;
        Base& operator=(Base&&) noexcept = delete;

        virtual void something()              const;
        virtual std::unique_ptr<Base> clone() const;
        virtual std::unique_ptr<Base> move()  noexcept;

        int get_int() const;

    private:
        int int_resource_ = 111;
    };

    class Derived : public Base
    {
    public:
        Derived()           = default;
        ~Derived() override = default;
        Derived(std::string, int = 222);

        Derived(const Derived&)                = delete;
        Derived(Derived&&) noexcept            = delete;
        Derived& operator=(const Derived&)     = delete;
        Derived& operator=(Derived&&) noexcept = delete;

        void something()                const override;
        std::unique_ptr<Base> clone()   const override;
        std::unique_ptr<Base> move() noexcept override;

        std::string get_string() const;

    private:
        std::string string_resource_;
    };
};

#endif //CLION_BASIC_H