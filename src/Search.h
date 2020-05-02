//
// Created by Enrique Piera Serra on 02/05/2020.
//

#pragma once

#include <iostream>
#include <vector>

#include "Molecule.h"
#include "SearchParam.h"
#include "../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Search
{
    public:
        Search(std::string loadLocation);

        const std::vector<Molecule> GetMolecules() const
        {return m_molecules;};

        template<typename T>
        const std::vector<Molecule> NumericSearch(const T reference,
                                                  const std::function<bool(T, T)> comparison) const
        {
            std::vector<Molecule> result;

            for (const Molecule& molecule : m_molecules)
            {
                auto value = search_param<T>::param(molecule);
                if (comparison(value, reference))
                {
                    result.push_back(molecule);
                }
            }

            return result;
        }

        void DisplayResults(const std::vector<Molecule>& molecules) const;

    private:
        std::vector<Molecule> m_molecules;
};