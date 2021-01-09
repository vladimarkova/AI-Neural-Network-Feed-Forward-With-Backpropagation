#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "Vector.h"
using namespace std;

const double MIN_WEIGHT = -0.05;
const double MAX_WEIGHT= 0.05;

class Neuron {
private:
    Vector<Neuron*> leftconnected_neurons; 
    Vector<double> weights;
    double value = 0;

public:
    void add_left_neurons(const Vector<Neuron*>& new_left_neurons) {
        for (int i = 0; i < leftconnected_neurons.size(); i++) {
            leftconnected_neurons.push_back(new_left_neurons[i]);
            weights.push_back(random_double(MIN_WEIGHT, MAX_WEIGHT));
        }
    }

    double calculate_value() const {
        double sum = 0;
        for (int i = 0; i < leftconnected_neurons.size(); i++) {
            sum += (leftconnected_neurons[i]->value * weights[i]);
        }
        return activation(sum);
    }

    double activation(double sum) const {
        return sigmoid(sum);
    }

    double sigmoid(double sum) const {
        return 1.0 / (1.0 + exp(-sum));
    }

    void print() const {
        cout << "VALUE: " << value <<endl;
        cout << "LEFT CONNECTED NEURONS: " << endl;
        cout << "NUMBER: " << leftconnected_neurons.size() << endl;
        for (int i = 0; i < leftconnected_neurons.size(); i++) {
            cout << "NEURON " << i << ": " << "VALUE: " << 
            leftconnected_neurons[i]->value << "WEIGHT: " << weights[i] << endl << endl;
        }
    }

    void set_value(double new_value) {
        value = new_value;
    }

    void set_weight(int index_of_weight, double new_weight) {
        weights[index_of_weight] = new_weight;
    }

    double get_value() const {
        return value;
    }

    double get_weight(int index_of_weight) const {
        return weights[index_of_weight];
    }

    Neuron* get_left_connected_neuron(int index_of_neuron) const {
        return leftconnected_neurons[index_of_neuron];
    }

    int number_of_left_connected_neurons() const {
        return leftconnected_neurons.size();
    }

    double random_double(double min_number, double max_number) {
        double number = (double)rand() / RAND_MAX;
        return min_number + number * (max_number - min_number);
    }
};