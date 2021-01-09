#include <iostream>
#include <ratio>
#include <chrono>
#include "neural_network.h"
using namespace std;

const int NUMBER_OF_ENTRIES = 4;

// Vector<Vector<double>> all_entries;
// set_entries(all_entries);

void test() {
    char response = '1';

    while(response != '0')
    {
        using namespace std::chrono;
        high_resolution_clock::time_point t1 = high_resolution_clock::now(); 

        // isolated_tests();
        int number_of_neurons_in_hidden_layer = DEFAULT_NUMBER_OF_NEURONS_IN_HIDDEN_LAYER;
        cout << "Enter number of neurons in hidden layer: " << endl;
        cin >> number_of_neurons_in_hidden_layer;

        Neural_Network neural_network;

        neural_network.set_number_of_neurons_in_hidden_layer(number_of_neurons_in_hidden_layer);

        for (int i = 0; i < all_entries.size(); i++) {
            neural_network.classify_entry(all_entries[i]);
            neural_network.print_result();
        }

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::milli> time_span = t2 - t1; 

        cout << "Time in miliseconds for classification with the neural network was: " << time_span.count() << " milliseconds." << endl;
        
        cout << "Enter 0 to stop tests or 1 to continue: " << endl << endl;
        cin >> response;
    }
}