//
// Created by Enrique Piera Serra on 02/05/2020.
//

#include <iostream>
#include "Search.h"

void DisplayResults(const std::vector<Molecule>& molecules)
{
    cout << "RESULTS:" << endl;
    cout << "NAME:\t\t" << "SOLUBILITY:\t" << "MOLECULAR WEIGHT:" << endl;

    for (const auto& molecule : molecules)
    {
        cout << molecule.name << "\t" << molecule.solubility << "\t\t" << molecule.molecularWeight << endl;
    }
}

bool isNumber(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

u_int SelectParameter()
{
    while (true){
        cout << "Please select a parameter to compare from the following:" << endl;
        cout << "1. Molecule name" << endl;
        cout << "2. Solubility" << endl;
        cout << "3. Molecular Weight" << endl;

        string input;
        cin >> input;

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

u_int SelectOperation(const u_int& parameter)
{
    while (true){
        u_int maxOperation = 5u;

        cout << "Please select an operation:" << endl;
        cout << "1. Less than" << endl;
        cout << "2. Less than or equal to" << endl;
        cout << "3. Equal to" << endl;
        cout << "4. Greater than or equal to" << endl;
        cout << "5. Greater than" << endl;
        if (parameter == 1u) {
            cout << "6. Name contains substring" << endl;
            maxOperation = 6u;
        }

        string input;
        cin >> input;

        if (isNumber(input))
        {
            u_int operation = std::stoi(input);

            if (operation >= 1u && operation <= maxOperation)
            {
                return operation;
            }
        }
    }

    return 0u;
}

vector<Molecule> RunOperation(const Search& search, const u_int& parameter, const u_int& operation)
{
    string moleculeName;
    double solubility;
    u_int molecularWeight;
    bool validInput = false;

    do {
        cout << "Please give a value to run the operation:" << endl;

        string input;
        cin >> input;

        if (parameter == 1u)
        {
            moleculeName = input;
            validInput = true;
        }
        else if (parameter == 2u && std::sscanf(input.c_str(), "%lg", &solubility) == 1)
        {
            validInput = true;
        }
        else if (parameter == 3 && isNumber(input))
        {
            molecularWeight = std::stoi(input);
            validInput = true;
        }

    } while (!validInput);

    switch (operation)
    {
    case 1:
        switch (parameter)
        {
            case 1:
                return search.ParameterSearch<string>(moleculeName, std::less<string>());
            case 2:
                return search.ParameterSearch<double>(solubility, std::less<double>());
            case 3:
                return search.ParameterSearch<u_int>(molecularWeight, std::less<u_int>());
            default:
                cout << "ERROR: INVALID OPERATION!" << endl;
                break;
        }
        break;
    case 2:
        switch (parameter)
        {
            case 1:
                return search.ParameterSearch<string>(moleculeName, std::less_equal<string>());
            case 2:
                return search.ParameterSearch<double>(solubility, std::less_equal<double>());
            case 3:
                return search.ParameterSearch<u_int>(molecularWeight, std::less_equal<u_int>());
            default:
                cout << "ERROR: INVALID OPERATION!" << endl;
                break;
        }
        break;
    case 3:
        switch (parameter)
        {
            case 1:
                return search.ParameterSearch<string>(moleculeName, std::equal_to<string>());
            case 2:
                return search.ParameterSearch<double>(solubility, std::equal_to<double>());
            case 3:
                return search.ParameterSearch<u_int>(molecularWeight, std::equal_to<u_int>());
            default:
                cout << "ERROR: INVALID OPERATION!" << endl;
                break;
        }
        break;
    case 4:
        switch (parameter)
        {
            case 1:
                return search.ParameterSearch<string>(moleculeName, std::greater_equal<string>());
            case 2:
                return search.ParameterSearch<double>(solubility, std::greater_equal<double>());
            case 3:
                return search.ParameterSearch<u_int>(molecularWeight, std::greater_equal<u_int>());
            default:
                cout << "ERROR: INVALID OPERATION!" << endl;
                break;
        }
        break;
    case 5:
        switch (parameter)
        {
            case 1:
                return search.ParameterSearch<string>(moleculeName, std::greater<string>());
            case 2:
                return search.ParameterSearch<double>(solubility, std::greater<double>());
            case 3:
                return search.ParameterSearch<u_int>(molecularWeight, std::greater<u_int>());
            default:
                cout << "ERROR: INVALID OPERATION!" << endl;
                break;
        }
        break;
    case 6:
        switch (parameter)
        {
            case 1:
                return search.SubStringSearch(moleculeName);
            default:
                cout << "ERROR: INVALID OPERATION!" << endl;
                break;
        }
        break;
    default:
        cout << "ERROR: INVALID OPERATION!" << endl;
        break;
    }

    return vector<Molecule>{};
}



int main ()
{
    string filePath = "../molecules.json";
    cout << "Welcome to the MOLECULE SELECTOR!" << endl;
    cout << "Please input a file path with molecules. (Press Enter for default)" << endl;
    string input;
    getline (cin, input);

    if (input != "")
    {
        filePath = input;
    }

    Search search(filePath);

    if (search.GetMolecules().empty())
    {
        return 1;
    }

    //do {
    u_int parameter = SelectParameter();
    u_int operation = SelectOperation(parameter);
    const auto molecules = RunOperation(search, parameter, operation);
    DisplayResults(molecules);

    //} while ();

/*
    std::vector<Molecule> v_intersection;

    std::set_symmetric_difference(molecules.begin(), molecules.end(),
                   molecules2.begin(), molecules2.end(),
                   std::back_inserter(v_intersection));

    DisplayResults(v_intersection);
*/
    return 0;
}
