//
// Created by Enrique Piera Serra on 02/05/2020.
//

#pragma once

#include <iostream>
#include "Molecule.h"

template<typename T> class AssertHelper : public std::false_type {};

// Base trait class
template<typename T>
class search_param
{
    public:
        static_assert(AssertHelper<T>::value, "A search_param specialization is required for this type");

        static T param (const Molecule&);
};

// search_param specialization for std::string (name searches)
template<>
class search_param<std::string>
{
    public:
        static std::string param (const Molecule& m)
        {
            return m.name;
        }
};

// search_param specialization for double (Solubility searches)
template<>
class search_param<double>
{
    public:
        static double param (const Molecule& m)
        {
            return m.solubility;
        }
};

// search_param specialization for u_int (molecular weight searches)
template<>
class search_param<u_int>
{
    public:
        static u_int param (const Molecule& m)
        {
            return m.molecularWeight;
        }
};
