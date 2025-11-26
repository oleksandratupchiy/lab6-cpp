#include <iostream>
#include <memory>
#include <limits>
#include "coroutines.h"

using namespace std;

void demo_guess();

int main()
{
    demo_guess();
    return 0;
}

void demo_guess()
{
    cout << "=== Guess the Number ===" << endl;
    cout << "Think of a number between 1 and 100." << endl;
    cout << "Controls:" << endl;
    cout << " 1  : My number is BIGGER than yours." << endl;
    cout << " -1 : My number is SMALLER than yours." << endl;
    cout << " 0  : CORRECT! You guessed it." << endl;
    cout << "--------------------------------------" << endl;

    auto response_ptr = make_shared<int>(0);
    auto game = guess_number(response_ptr);

    int guess = game.ask(0);
    int user_response = -2;
    int steps = 1;

    while (true)
    {
        cout << "Step " << steps << ". Is it " << guess << "? > ";

        while (!(cin >> user_response) || (user_response != -1 && user_response != 0 && user_response != 1)) {
            cout << "Invalid input. Please enter -1, 0, or 1: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (user_response == 0)
        {
            cout << "Yay! The number was " << guess << "." << endl;
            game.ask(0);
            break;
        }

        guess = game.ask(user_response);
        steps++;
    }
    cout << "Game finished in " << steps << " steps." << endl;
}