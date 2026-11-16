#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

const double a = 0;
const double b = 1;

/**
 * Approximates S(x) = sum of (-1)^n * x^n / (n!)^2, n = 0..inf.
 * The summation stops after the first term whose absolute value <= eps.
 * Preconditions: x belongs to [a; b], eps > 0 (not checked here).
 */
double s(double x, double eps)
{
    const double negX = -x;
    double term = 1;
    double sum = term;
    double n = 0;
    while (term > eps || term < -eps)
    {
        n += 1;
        term *= negX / (n * n);
        sum += term;
    }
    return sum;
}

void printAuthorAndTask()
{
    std::cout << "Author: Viktor Filimonchuk, group ITK-11\n"
              << "Lab 2, variant 181\n"
              << "Task: compute the sum of the power series S(x)\n"
              << "at a given point x in [" << a << "; " << b << "]\n"
              << "with a given accuracy eps > 0.\n\n";
}

/**
 * Reads a whole input line and interprets it as exactly one real number.
 * Throws std::invalid_argument if the line holds anything else.
 */
double readReal(const char* name)
{
    std::string line;
    std::getline(std::cin, line);
    std::istringstream lineStream(line);
    double value = 0;
    std::string extra;
    if (!(lineStream >> value) || (lineStream >> extra))
        throw std::invalid_argument(
            std::string("Input error: ") + name + " is not a real number.");
    return value;
}

double readX()
{
    std::cout << "Enter x (real number from [" << a << "; " << b << "]): ";
    const double x = readReal("x");
    if (x < a || x > b)
        throw std::domain_error("Invalid x: it is outside [a; b].");
    return x;
}

double readEps()
{
    std::cout << "Enter eps (real number greater than 0): ";
    const double eps = readReal("eps");
    if (eps <= 0)
        throw std::domain_error("Invalid eps: it must be greater than 0.");
    return eps;
}

void printReport(double x, double eps, double result)
{
    std::cout << std::scientific << std::setprecision(7)
              << "for x = " << x << '\n'
              << std::setprecision(9)
              << "for eps = " << eps << '\n'
              << std::fixed << std::setprecision(8)
              << "result = " << result << '\n';
}

int main()
{
    printAuthorAndTask();
    try
    {
        const double x = readX();
        const double eps = readEps();
        std::cout << "***** do calculations ...";
        const double result = s(x, eps);
        std::cout << " done\n";
        printReport(x, eps, result);
    }
    catch (const std::exception& error)
    {
        std::cout << "***** error\n" << error.what() << '\n'
                  << "Calculation is impossible.\n";
    }
}
