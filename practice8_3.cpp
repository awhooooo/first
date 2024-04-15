#include "practice8.h"


using namespace MATRIX;

int main()
{
    // SquareMatrix macOS(3);
    // SquareMatrix iOS(3);
    // SquareMatrix visionOS(4);
    // macOS.show_matrix();
    // std::cin >> macOS;
    // std::cin >> iOS;
    // std::cin >> visionOS;
    // macOS *= 3 ;

    // macOS.show_matrix();
    // tvOS.show_matrix(); 
    // visionOS.show_matrix();
    // std::cout << "Determinant ==> " << macOS.det() << std::endl;
    // std::cout << "Trace ==>" << macOS.trace() << std::endl;
    // macOS.transpose();
    // macOS.show_matrix();

    int R, C;
    std::cin >> R >> C;
    TextMatrix tvOS(R, C);
    std::cin >> tvOS;
    std::cout << std::endl;
    std::cout << tvOS;
    // tvOS.show_matrix();
    
    return 0;
}


