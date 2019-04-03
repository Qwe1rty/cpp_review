//
// Created by Caleb Choi on 31/03/2019.
//

#ifndef CLION_CAS_H
#define CLION_CAS_H

namespace Data
{
    class CaS
    {
    public:
        explicit CaS(int);
        CaS(const CaS&);
        CaS(CaS&&) noexcept;
        ~CaS();
        CaS& operator= (CaS);

        friend void swap(CaS&, CaS&) noexcept;

    private:
        int size_;
        int* array_;
    };
}

#endif //CLION_CAS_H
