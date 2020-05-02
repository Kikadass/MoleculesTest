//
// Created by Enrique Piera Serra on 02/05/2020.
//

#include <iostream>
#include "Search.h"

int main ()
{
    Search search("../molecules.json");
    //const auto molecules = search.NumericSearch<double>(0u, 4.97, std::less_equal<double>());
    const auto molecules = search.NumericSearch<u_int>(1u, 290, std::less_equal<u_int>());

    search.DisplayResults(molecules);

    return 0;
}
