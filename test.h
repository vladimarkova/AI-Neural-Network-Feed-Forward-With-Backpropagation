#include <iostream>
#include <ratio>
#include <chrono>
#include "neural_network.h"
using namespace std;

void test() {
    char response = '1';

    while(response != '0')
    {
        using namespace std::chrono;
        high_resolution_clock::time_point t1 = high_resolution_clock::now(); 

        // isolated_tests();
        Neural_Network();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::milli> time_span = t2 - t1; 

        cout << "Time in miliseconds for classification with the neural network was: " << time_span.count() << " milliseconds." << endl;
        
        cout << "Enter 0 to stop tests or 1 to continue: " << endl << endl;
        cin >> response;
    }
}