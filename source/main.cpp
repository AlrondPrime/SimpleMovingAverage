#include "tests.hpp"

int main()
{
    // Check that function works correctly
    tests::correctnessCheck();
    std::cout << "\n\n";
    // Measure function with different types and window sizes
    tests::performanceCheck();

    return EXIT_SUCCESS;
}
