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
        // Load File
        std::ifstream i(loadLocation);
        // Pass file contents to json object: molecules
        i >> molecules;
    }
    catch(std::exception e)
    {
        std::cout << "ERROR: File could not be opened or read!" << std::endl;
        return;
    }

    try
    {
        molecules = molecules.at("Molecules").get<json>();

        // Parse json molecules into a vector of Molecule structs
        for (auto& molecule : molecules)
        {
            const std::string name = molecule.at("name").get<std::string>();
            const double solubility = molecule.at("solubility").get<double>();;
            const uint molecularWeight = molecule.at("molecularWeight").get<u_int>();;

            m_molecules.push_back(Molecule{name, solubility, molecularWeight});
        }
    }
    catch(std::exception e)
    {
        std::cout << "ERROR: Some parameter was missing!" << std::endl;
        std::cout << "JSON file example:" << std::endl;
        std::cout << "{" << std::endl;
        std::cout << "\t\"Molecules\": [" << std::endl;
        std::cout << "\t\t{" << std::endl;
        std::cout << "\t\t\t\"name\": \"Paracetamol\"," << std::endl;
        std::cout << "\t\t\t\"solubility\": 4.97," << std::endl;
        std::cout << "\t\t\t\"molecularWeight\": 151," << std::endl;
        std::cout << "\t\t}" << std::endl;
        std::cout << "\t]" << std::endl;
        std::cout << "}" << std::endl;
    }

    std::sort(m_molecules.begin(), m_molecules.end());
    std::cout << "Molecules Loaded!" << std::endl << std::endl;
}

const std::vector<Molecule> Search::SubStringSearch(const std::string& str) const
{
    std::vector<Molecule> result;

    for (const Molecule& molecule : m_molecules)
    {
        // If the molecule's name contains str in it, add the molecule to result.
        if (molecule.name.find(str) != std::string::npos)
        {
            result.push_back(molecule);
        }
    }

    return result;
}
