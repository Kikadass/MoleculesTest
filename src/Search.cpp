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

    cout << "Molecules Loaded!" << endl;
}

void Search::DisplayResults(const std::vector<Molecule>& molecules) const
{
    cout << "RESULTS:" << endl;
    cout << "NAME:\t\t" << "SOLUBILITY:\t" << "MOLECULAR WEIGHT:" << endl;

    for (const auto& molecule : molecules)
    {
        cout << molecule.name << "\t" << molecule.solubility << "\t\t" << molecule.molecularWeight << endl;
    }
}

