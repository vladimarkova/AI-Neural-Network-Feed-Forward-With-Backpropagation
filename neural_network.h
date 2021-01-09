#include <iostream>
#include "neuron.h"
using namespace std;

const int NUMBER_OF_ENTRIES = 4;
const int NUMBER_OF_NEURONS_IN_INPUT_LAYER = 2; // equals number of attributes for a single entry 
const int MAX_NUMBER_OF_NEURONS_IN_HIDDEN_LAYER = 12; // exact number is a paramater for the system
const int DEFAULT_NUMBER_OF_NEURONS_IN_HIDDEN_LAYER = 4;
const int NUMBER_OF_NEURONS_IN_OUTPUT_LAYER = 1; // equals number of classes for the task 
const int MAX_NUMBER_OF_EPOCHS = 1000;
const double LEARNING_RATE = 0.01;

void set_entries(Vector<Vector<double>>& all_entries) {
    Vector<double> first_entry;
    first_entry[0] = 0;
    first_entry[1] = 0;
    all_entries.push_back(first_entry);

    Vector<double> second_entry;
    second_entry[0] = 0;
    second_entry[1] = 1;
    all_entries.push_back(second_entry);

    Vector<double> third_entry;
    third_entry[0] = 1;
    third_entry[1] = 0;
    all_entries.push_back(third_entry);

    Vector<double> forth_entry;
    forth_entry[0] = 1;
    forth_entry[1] = 1;
    all_entries.push_back(forth_entry);
}

class Neural_Network{
private:
 
public:
    void set_number_of_neurons_in_hidden_layer(int number_of_neurons_in_hidden_layer) {

    }

    void classify_entry(const Vector<double>& entry) {

    }

    void print_result() const {

    }
};