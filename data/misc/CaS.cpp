//
// Created by Caleb Choi on 31/03/2019.
//

#include <algorithm>

#include "CaS.h"

Data::CaS::CaS(int size) :
    size_(size),
    array_(size_ ? new int[size_]() : nullptr)
{}

Data::CaS::CaS(const CaS& src) :
    CaS(src.size_)
{
    std::copy(src.array_, src.array_ + size_, array_);
}

Data::CaS::CaS(CaS&& src) noexcept :
    CaS()
{
    swap(*this, src);
}

Data::CaS::~CaS()
{
    delete array_;
}

Data::CaS& Data::CaS::operator= (CaS src)
    {
    swap(*this, src);
    return *this;
}

void Data::swap(Data::CaS& a, Data::CaS& b) noexcept
{
    using std::swap;
    swap(a.size_, b.size_);
    swap(a.array_, b.array_);
}