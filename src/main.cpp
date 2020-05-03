//
// Created by Enrique Piera Serra on 02/05/2020.
//

#include <iostream>
#include "Search.h"
#include "Utils.cpp"

int main ()
{
    std::string filePath = "../molecules.json";
    std::cout << "Welcome to the MOLECULE SELECTOR!" << std::endl;
    std::cout << "Please input a file path with molecules. (Press Enter for default)" << std::endl;
    std::string input;
    getline (std::cin, input);

    // The input is empty (pressed Enter) use the default file, so do not override with input
    if (input != "")
    {
        filePath = input;
    }

    // Load file
    Search search(filePath);

    // Check that the molecules have been loaded
    if (search.GetMolecules().empty())
    {
        return 1;
    }

    std::vector<Molecule> table1 = CreateTable(search);

    while (true)
    {
        std::cout << std::endl;
        std::cout << "Do you want to do another operation? (Yes / No)" << std::endl;
        std::cin >> input;

        // Only exit if user writes "No" or "no"
        if (input == "No" || input == "no")
        {
            return 0;
        }

        std::vector<Molecule> table2 = CreateTable(search);
        table1 = RunSetOperation(table1, table2);
    }

    return 0;
}
