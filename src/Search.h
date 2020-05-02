//
// Created by Enrique Piera Serra on 02/05/2020.
//

#pragma once

#include <iostream>
#include <vector>

#include "../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

struct Molecule
{
    const std::string name;
    const double solubility;
    const u_int molecularWeight;
};

class Search
{
    public:
        Search(std::string loadLocation);

        const std::vector<Molecule> GetMolecules() const
        {return m_molecules;};

        template<typename T>
        const std::vector<Molecule> NumericSearch(const u_int parameterNum,
                                                  const T reference,
                                                  const std::function<bool(T, T)> comparison) const
        {
            std::vector<Molecule> result;

            for (const Molecule& molecule : m_molecules)
            {
                T paramValue;
                switch (parameterNum)
                {
                case 0u:
                    paramValue = molecule.solubility;
                    break;
                case 1u:
                    paramValue = molecule.molecularWeight;
                    break;
                default:
                    break;
                }

                if (comparison(paramValue, reference))
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