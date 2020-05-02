//
// Created by Enrique Piera Serra on 02/05/2020.
//

#include "Search.h"
#include <fstream>

Search::Search(std::string loadLocation)
{
    json molecules;
    try
    {
        ifstream i(loadLocation);
        i >> molecules;
    }
    catch(exception e)
    {
        cout << "ERROR: File could not be opened or read!" << endl;
        return;
    }

    molecules = molecules.at("Molecules").get<json>();

    for (auto& molecule : molecules)
    {
        const string name = molecule.at("name").get<string>();
        const double solubility = molecule.at("solubility").get<double>();;
        const uint molecularWeight = molecule.at("molecularWeight").get<u_int>();;

        m_molecules.push_back(Molecule{name, solubility, molecularWeight});
    }

    std::sort(m_molecules.begin(), m_molecules.end());

    cout << "Molecules Loaded!" << endl << endl;
}

const std::vector<Molecule> Search::SubStringSearch(const string& str) const
{
    std::vector<Molecule> result;

    for (const Molecule& molecule : m_molecules)
    {
        if (molecule.name.find(str) != std::string::npos)
        {
            result.push_back(molecule);
        }
    }

    return result;
}
