//
// Created by Enrique Piera Serra on 02/05/2020.
//

#pragma once

#include <iostream>
#include "Search.h"

enum SetOperations
{
    SET_UNION = 1u,
    SET_DIFFERENCE = 2u,
    SET_SYMETRIC_DIFFERENCE = 3u,
    SET_INTERSECTION = 4u
};

enum SearchOperations
{
    LESS_THAN = 1u,
    LESS_EQUAL = 2u,
    EQUAL_TO = 3u,
    GREATER_EQUAL = 4u,
    GREATER_THAN = 5u,
    SUBSTRING = 6u
};

enum Parameter
{
    MOLECULE_NAME = 1u,
    SOLUBILITY = 2u,
    MOLECULAR_WEIGHT = 3u
};

void DisplayResults(const std::vector<Molecule>& molecules)
{
    std::cout << std::endl << "NAME:\t\t" << "SOLUBILITY:\t" << "MOLECULAR WEIGHT:" << std::endl;

    for (const auto& molecule : molecules)
    {
        std::cout << molecule.name << "\t" << molecule.solubility << "\t\t" << molecule.molecularWeight << std::endl;
    }
}

bool isNumber(const std::string& s)
{
    // Check that all characters are digits
    return !s.empty()
            && std::find_if(s.begin(),
                            s.end(),
                            [](unsigned char c) { return !std::isdigit(c); })
                == s.end();
}

u_int SelectParameter()
{
    // Loop until a valid input gets entered
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Please select a parameter to compare from the following:" << std::endl;
        std::cout << "1. Molecule name" << std::endl;
        std::cout << "2. Solubility" << std::endl;
        std::cout << "3. Molecular Weight" << std::endl;

        std::string input;
        std::cin >> input;

        if (isNumber(input))
        {
            u_int parameter = std::stoi(input);

            if (parameter >= 1u && parameter <= 3u)
            {
                return parameter;
            }
        }
    }

    return 0u;
}

u_int SelectSearchOperation(const u_int& parameter)
{
    while (true)
    {
        u_int maxOperation = SearchOperations::GREATER_THAN;

        std::cout << std::endl;
        std::cout << "Please select an operation:" << std::endl;
        std::cout << "1. Less than" << std::endl;
        std::cout << "2. Less than or equal to" << std::endl;
        std::cout << "3. Equal to" << std::endl;
        std::cout << "4. Greater than or equal to" << std::endl;
        std::cout << "5. Greater than" << std::endl;
        if (parameter == 1u) {
            std::cout << "6. Name contains substring" << std::endl;
            maxOperation = SearchOperations::SUBSTRING;
        }

        std::string input;
        std::cin >> input;

        if (isNumber(input))
        {
            u_int operation = std::stoi(input);

            if (operation >= SearchOperations::LESS_THAN && operation <= maxOperation)
            {
                return operation;
            }
        }
    }

    return 0u;
}

template<typename T>
std::vector<std::function<bool(T, T)>> GetSearchOperations()
{
    // Save template functions into vector for easy access
    std::vector<std::function<bool(T, T)>> operations;
    operations.push_back(std::less<T>());
    operations.push_back(std::less_equal<T>());
    operations.push_back(std::equal_to<T>());
    operations.push_back(std::greater_equal<T>());
    operations.push_back(std::greater<T>());

    return operations;
}

std::vector<Molecule> RunSearchOperation(const Search& search, const u_int& parameter, const u_int& operation)
{
    std::string moleculeName;
    double solubility;
    u_int molecularWeight;

    // Save template functions into vectors for easy access. Avoids creating nested if or switch statements
    std::vector<std::function<bool(std::string, std::string)>> stringOps = GetSearchOperations<std::string>();
    std::vector<std::function<bool(double, double)>> doubleOps = GetSearchOperations<double>();
    std::vector<std::function<bool(u_int, u_int)>> intOps = GetSearchOperations<u_int>();

    // Loop runs until valid input is entered
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Please give a value to run the operation:" << std::endl;

        std::string input;
        std::cin >> input;

        if (parameter == Parameter::MOLECULE_NAME)
        {
            moleculeName = input;
            break;
        }
        else if (parameter == Parameter::SOLUBILITY && std::sscanf(input.c_str(), "%lg", &solubility) == 1)  // If parameter is Solubility, check input is a double. If so, store it in variable
        {
            break;
        }
        else if (parameter == Parameter::MOLECULAR_WEIGHT && isNumber(input))
        {
            molecularWeight = std::stoi(input);
            break;
        }
    };

    switch(parameter)
    {
        case Parameter::MOLECULE_NAME:
            if (operation == SearchOperations::SUBSTRING)
                return search.SubStringSearch(moleculeName);

            return search.ParameterSearch<std::string>(moleculeName, stringOps[operation - 1]);
            break;
        case Parameter::SOLUBILITY:
            return search.ParameterSearch<double>(solubility, doubleOps[operation - 1]);
            break;
        case Parameter::MOLECULAR_WEIGHT:
            return search.ParameterSearch<u_int>(molecularWeight, intOps[operation - 1]);
            break;
        default:
            std::cout << "ERROR: INVALID OPERATION!" << std::endl;
            break;
    }

    return std::vector<Molecule>{};
}

u_int SelectSetOperation()
{
    // Loop runs until valid input is entered
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Please select a set operation to do with the previous two tables:" << std::endl;
        std::cout << "1. Union" << std::endl;
        std::cout << "2. Difference" << std::endl;
        std::cout << "3. Symmetric Difference" << std::endl;
        std::cout << "4. Intersection" << std::endl;

        std::string input;
        std::cin >> input;

        if (isNumber(input))
        {
            u_int operation = std::stoi(input);

            if (operation >= 1u && operation <= 5u)
            {
                return operation;
            }
        }
    }
}

std::vector<Molecule> RunSetOperation(const std::vector<Molecule>& table1, const std::vector<Molecule>& table2)
{
    std::vector<Molecule> result;

    u_int setOperation = SelectSetOperation();

    std::cout << std::endl << std::endl << "Table 1:" << std::endl;
    DisplayResults(table1);

    switch (setOperation)
    {
    case SetOperations::SET_UNION:
        std::cout << std::endl << "UNION" << std::endl;
        std::set_union(table1.begin(), table1.end(),
                       table2.begin(), table2.end(),
                       std::back_inserter(result));
        break;
    case SetOperations::SET_DIFFERENCE:
        std::cout << std::endl << "DIFFERENCE" << std::endl;
        std::set_difference(table1.begin(), table1.end(),
                            table2.begin(), table2.end(),
                            std::back_inserter(result));
        break;
    case SetOperations::SET_SYMETRIC_DIFFERENCE:
        std::cout << std::endl << "SYMETRIC DIFFERENCE" << std::endl;
        std::set_symmetric_difference(table1.begin(), table1.end(),
                                      table2.begin(), table2.end(),
                                      std::back_inserter(result));
        break;
    case SetOperations::SET_INTERSECTION:
        std::cout << std::endl << "INTERSECTION" << std::endl;
        std::set_intersection(table1.begin(), table1.end(),
                              table2.begin(), table2.end(),
                              std::back_inserter(result));
        break;
    default:
        std::cout << "ERROR: INVALID OPERATION!" << std::endl;
        result = table1;
        break;
    }

    std::cout << std::endl << "Table 2:" << std::endl;
    DisplayResults(table2);

    std::cout << "================================================" << std::endl;
    DisplayResults(result);

    return result;
}


std::vector<Molecule> CreateTable(const Search& search)
{
    u_int parameter = SelectParameter();
    u_int operation = SelectSearchOperation(parameter);
    const auto table = RunSearchOperation(search, parameter, operation);
    DisplayResults(table);

    return table;
}