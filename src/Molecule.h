//
// Created by Enrique Piera Serra on 02/05/2020.
//

#pragma once

#include <iostream>

struct Molecule
{
    std::string name;
    double solubility;
    u_int molecularWeight;

    bool operator== (const Molecule& m) const
    {
        return name == m.name
                && solubility == m.solubility
                && molecularWeight == m.molecularWeight;
    }

    bool operator> (const Molecule& m) const
    {
        return name > m.name;
    }

    bool operator< (const Molecule& m) const
    {
        return name < m.name;
    }

    friend void swap(Molecule& a, Molecule& b)
    {
        std::swap(a.name, b.name);
        std::swap(a.solubility, b.solubility);
        std::swap(a.molecularWeight, b.molecularWeight);
    }
};
