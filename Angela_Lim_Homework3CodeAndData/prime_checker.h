//Angela Lim
//Function for prime checking refactored out of quadratic and other probing files
#ifndef PRIME_CHECKER_H
#define PRIME_CHECKER_H

namespace
{

// Internal method to test if a positive number is prime.
bool IsPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

// Internal method to return a prime number at least as large as n.
int NextPrime(int n)
{
    if (n % 2 == 0)
        ++n;
    while (!IsPrime(n))
        n += 2;
    return n;
}

} // namespace

#endif // PRIME_CHECKER_H
