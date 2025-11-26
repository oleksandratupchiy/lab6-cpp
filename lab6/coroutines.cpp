#include "coroutines.h"

using namespace std;

Dialog guess_number(shared_ptr<int> response)
{
    int min = 1;
    int max = 100;
    int guess;

    guess = min + (max - min) / 2;
    co_yield guess;

    while (true)
    {
        int r = *response;

        if (r == 0) break;

        if (r == 1)      min = guess + 1;
        else if (r == -1) max = guess - 1; 

        if (min > max) min = max;

        guess = min + (max - min) / 2;

        co_yield guess;
    }
}