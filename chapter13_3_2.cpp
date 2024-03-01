#include "chapter13_3.h"
#include <iostream>
#include <new>

int main()
{
    POLAR_COOR::Polar3 aaa(4, M_PI/4, 0);
    aaa.view_coor();
    aaa.view_cartesian_coor();
    POLAR_COOR::Polar3 bbb(sqrt(2), M_PI/4, 0);
    bbb.view_coor();
    bbb.view_cartesian_coor();
    std::cout << "==>" << &aaa << std::endl;
    std::cout << "==>" << &bbb << std::endl;
    bbb.operator=(aaa);
    bbb.view_coor();
    bbb.view_cartesian_coor();
    POLAR_COOR::Polar4 ccc(sqrt(2), M_PI/4, "segregated witness", "bech32m");
    ccc.view_coor();
    POLAR_COOR::Polar4 ddd(sqrt(8), M_PI/4, "strategy became the provenace of conservatives and neoconservatives", "america once again finds itself at war");
    ddd.view_coor();
    ccc.operator=(ddd);
    ccc.view_coor();
    return 0;
}