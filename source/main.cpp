#include <iostream>
#include <vector>
#include <random>

struct PointF
{
    float x{}, y{};
};

struct PointD
{
    double x{}, y{};
};

float getRandomF()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(std::numeric_limits<float>::min(),std::numeric_limits<float>::max());

    return dist(gen);
}

double getRandomD()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(std::numeric_limits<double>::min(),std::numeric_limits<double>::max());

    return dist(gen);
}

int main() {

    return EXIT_SUCCESS;
}
