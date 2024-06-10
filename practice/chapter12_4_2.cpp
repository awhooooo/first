#include "chapter12_4.h"
#include <cmath>
using namespace SPHERICAL_COOR;

int main()
{
    Spherical v1(5, 0, 0);
    Spherical v2(5, M_PI/2.0, M_PI/2.0);
    v1.show_coor();
    v2.show_coor();
    v1.convert_to_cartesian();
    v2.convert_to_cartesian();
    Spherical v3;
    while (std::cin >> v3)
    {
        v3.show_coor();
        v3.convert_to_cartesian();
        std::cout << "v1 + v2 + v3 = " << (v1 + v2 + v3) << std::endl;
        std::cout << "v1 - v2 - v3 = " << (v1 - v2 - v3) << std::endl;
        std::cout << "2 * v3 = " << (2 * v3) << std::endl;
        std::cout << "v3 * 2 = " << (v3 * 2) << std::endl;
        std::cout << "v1 * v3 = " << (v1 * v3) << std::endl;
        std::cout << "Enter a spherical coordinate (q to quit):\n";
    }
    std::cout << "TERMINATING...\n";
    return 0;
}
