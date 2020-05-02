//
// Created by Enrique Piera Serra on 02/05/2020.
//

#pragma once

#include <iostream>

struct Molecule
{
    const std::string name;
    const double solubility;
    const u_int molecularWeight;

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
};