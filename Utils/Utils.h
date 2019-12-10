#ifndef UTILS_H
#define UTILS_H
#include <cmath>

class Utils
{
public:
    static bool Equal(double d1, double d2)  {
        return abs(d1 - d2) <= 1e-9;
    }

    static int binomialCoeff(int n, int k)
    {
        // Base Cases
        if (k == 0 || k == n)
            return 1;

        // Recur
        return binomialCoeff(n - 1, k - 1) +
                    binomialCoeff(n - 1, k);
    }


};

#endif // UTILS_H
