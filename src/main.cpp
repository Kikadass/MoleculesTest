//
// Created by Enrique Piera Serra on 02/05/2020.
//

#include <iostream>
#include "Search.h"

int main ()
{
    Search search("../molecules.json");
    //const auto molecules = search.NumericSearch<double>(0u, 4.97, std::less_equal<double>());
    const auto molecules = search.NumericSearch<u_int>(290, std::greater<u_int>());
    const auto molecules2 = search.NumericSearch<string>("Paracetamol", std::greater<string>());

    search.DisplayResults(molecules);
    search.DisplayResults(molecules2);

    std::vector<Molecule> v_intersection;
/*
    std::set_union(molecules.begin(), molecules.end(),
                   molecules2.begin(), molecules2.end(),
                   std::back_inserter(v_intersection));
*/

    std::set_intersection(molecules.begin(), molecules.end(),
                molecules2.begin(), molecules2.end(),
                std::back_inserter(v_intersection));

    search.DisplayResults(v_intersection);

    return 0;
}
