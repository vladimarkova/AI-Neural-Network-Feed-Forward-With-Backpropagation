#include <iostream>
#include "neuron.h"
using namespace std;

const int NUMBER_OF_ENTRIES = 4;
const int NUMBER_OF_NEURONS_IN_INPUT_LAYER = 2; // equals number of attributes for a single entry 
const int MAX_NUMBER_OF_NEURONS_IN_HIDDEN_LAYER = 12; // exact number is a paramater for the system
const int DEFAULT_NUMBER_OF_NEURONS_IN_HIDDEN_LAYER = 4;
const int NUMBER_OF_NEURONS_IN_OUTPUT_LAYER = 1; // equals number of classes for the task 
const int MAX_NUMBER_OF_EPOCHS = 100000; // to be made 50 000 
const double MIN_ERROR = 0.01; // to be made 0.001
const double MAX_ERROR = 1;
const double LEARNING_RATE = 0.1;
const double MULTIPLY_CONST = 0.5;
const double BIAS_VALUE = 1;
const double BIAS_INITIAL_WEIGHT = 1.5;
// const double BIAS_VALUE_AND = 1;
// const double BIAS_WEIGHT_AND = 1.5;
// const double BIAS_VALUE_OR = 1;
// const double BIAS_WEIGHT_OR = 0.5;
// const double BIAS_VALUE_XOR = 1;
// const double BIAS_WEIGHT_XOR = 0.5;

class Neural_Network{
private:
    Vector<Neuron> input_layer;
    Vector<Neuron> hidden_layer;
    Vector<Neuron> output_layer;
    Neuron bias_neuron;

    int task_number = 0;        // 0 - AND, 1 - OR, 2 - XOR 
 
public:
    void initialize(int input_neurons_number, int hidden_nuerons_number, int output_neurons_number) {
        input_layer.add_empty_elements(input_neurons_number);
        hidden_layer.add_empty_elements(hidden_nuerons_number);
        output_layer.add_empty_elements(output_neurons_number);

        if (hidden_layer.size() == 0) {
            for (int i = 0; i < output_layer.size(); i++) {
                output_layer[i].add_left_neurons(input_layer);
            }
        }

        else {
            for (int i = 0; i < hidden_layer.size(); i++) {
                hidden_layer[i].add_left_neurons(input_layer);
            }

            for (int i = 0; i < output_layer.size(); i++) {
                output_layer[i].add_left_neurons(hidden_layer);
            }
        }
    }

    void set_input_values(const Vector<double>& input_values) {
        for (int i = 0; i < input_layer.size() - 1; i++) { // excludng the bias neuron value to be set 
            input_layer[i].set_value(input_values[i]);
        }
    }
    
    void arrange_bias() {
        bias_neuron.set_value(BIAS_VALUE);

        input_layer.add_empty_elements(1);
        int index_of_bias_in_input_layer = input_layer.size();
        input_layer[index_of_bias_in_input_layer] = bias_neuron;

        if (hidden_layer.size() == 0) {
            for (int i = 0; i < output_layer.size(); i++) {
                output_layer[i].add_bias_as_left_neuron(bias_neuron);
            }
        }
        else {
            hidden_layer.add_empty_elements(1);
            int index_of_bias_in_hidden_layer = hidden_layer.size();
            hidden_layer[index_of_bias_in_hidden_layer] = bias_neuron;

            for (int i = 0; i < hidden_layer.size(); i++) {
                hidden_layer[i].add_bias_as_left_neuron(bias_neuron);
            }

            for (int i = 0; i < output_layer.size(); i++) {
                output_layer[i].add_bias_as_left_neuron(bias_neuron);
            }
        }
    }

    void set_task_number(int _task_number) {
        task_number = _task_number;
    }

    void activate_neurons() {
        for (int i = 0; i < hidden_layer.size() - 1; i++) { // excluding the bias neuron value to be set 
            double new_value = hidden_layer[i].calculate_value();
            hidden_layer[i].set_value(new_value);
        }

        for (int i = 0; i < output_layer.size(); i++) {
            double new_value = output_layer[i].calculate_value();
            output_layer[i].set_value(new_value);
        }
    }

    void apply_backpropagation(double expected_output_for_entry) {
        for (int i = 0; i < output_layer.size(); i++) {
            double output_neuron_value = output_layer[i].get_value();
            for (int j = 0; j < output_layer[i].number_of_left_connected_neurons(); j++) {        
                double left_neuron_value = output_layer[i].get_left_connected_neuron(j)->get_value();
                double partial_derivative = -output_neuron_value
                                          * (1 - output_neuron_value) 
                                          * left_neuron_value
                                          * (expected_output_for_entry - output_neuron_value);
                double delta_weight = -LEARNING_RATE * partial_derivative;
                double current_weight = output_layer[i].get_weight(j);
                double new_weight = current_weight + delta_weight;
                output_layer[i].set_weight(j, new_weight);
            }

            for (int i = 0; i < hidden_layer.size(); i++) {
                double hidden_neuron_value = hidden_layer[i].get_value();
                for (int j = 0; j < hidden_layer[i].number_of_left_connected_neurons(); j++) {
                    double left_neuron_value = hidden_layer[i].get_left_connected_neuron(j)->get_value();
                    
                    double sum_outputs = 0;

                    for (int k = 0; k < output_layer.size(); k++) {
                        double weight = output_layer[k].get_weight(i);
                        double output_neuron_value = output_layer[k].get_value();
                        sum_outputs += (-(expected_output_for_entry - output_neuron_value)) 
                                     * output_neuron_value
                                     * (1 - output_neuron_value)
                                     * weight;  
                    }
                    double partial_derivative = hidden_neuron_value
                                          * (1 - hidden_neuron_value) 
                                          * left_neuron_value
                                          * sum_outputs; 
                    double delta_weight = -LEARNING_RATE * partial_derivative;
                    double current_weight = hidden_layer[i].get_weight(j);
                    double new_weight = current_weight + delta_weight;
                    hidden_layer[i].set_weight(j, new_weight);
                }
            }
        }
    }

    void educate(const Vector<Vector<double>>& all_entries, const Vector<Vector<double>>& expected_outputs) {
        int current_epoch = 0;
        double error = MAX_ERROR;
        while (current_epoch < MAX_NUMBER_OF_EPOCHS && error > MIN_ERROR) {
            // cout << "CURRENT EPOCH: " << current_epoch << endl;
            error = 0;
            for (int i = 0; i < all_entries.size(); i++) {

                double current_output = classify_entry(all_entries[i]);

                double err = MULTIPLY_CONST * (expected_outputs[task_number][i] - current_output) * (expected_outputs[task_number][i] - current_output);

                error += err;

                apply_backpropagation(expected_outputs[task_number][i]);
            }
            current_epoch++;
        }

        cout << endl << "TOTAL NUMBER OF LEARNING EPOCHS MADE: " << current_epoch << endl;
        cout << "MAX NUMBER OF LEARNING EPOCHS: " << MAX_NUMBER_OF_EPOCHS << endl << endl;
    }

    double classify_entry(const Vector<double>& entry) {
        set_input_values(entry);

        activate_neurons();

        return output_layer[0].get_value();
    }

    bool is_multilayered() const {
        return task_number == 2;
    }

    int get_task_number() const {
        return task_number; 
    }

    double estimate_error_of_entry_classification(const Vector<double>& entry, double expected_output_for_entry) {
        double result_from_classification = output_layer[0].get_value();
        double error = abs(expected_output_for_entry - result_from_classification);
        return error;
    }

    void print_result_for_single_entry_classification(const Vector<double>& entry, double expected_output_for_entry) const {
        double result_from_classification = output_layer[0].get_value();
        double error = abs(expected_output_for_entry - result_from_classification);
        cout << "INPUT: {" 
         << entry[0] 
         << ", " 
         << entry[1] 
         << "}          EXPECTED OUTPUT: " 
         << expected_output_for_entry
         << "           REAL OUTPUT: " 
         << result_from_classification 
         << "         CALCULATED ERROR: "
         << error
         << endl << endl;
    }

    void print_weights() {
        cout << "WEIGHTS FOR CONNECTIONS BETWEEN: ";
        if (hidden_layer.size() != 0) {
            cout << "HIDDEN AND INPUT LAYERS " << endl << endl;
            for (int i = 0; i < hidden_layer.size(); i++) {
                cout << "FOR NEURON " << i << " IN HIDDEN LAYER: " << endl;
                for (int j = 0; j < hidden_layer[i].number_of_left_connected_neurons(); j++) {
                    double weight = hidden_layer[i].get_weight(j);
                    cout << "WEIGHT " << j << ": " << weight << endl;
                }
                cout << endl;
            }

            cout << endl;

            cout << "OUTPUT AND HIDDEN LAYERS" << endl << endl;
            for (int i = 0; i < output_layer.size(); i++) {
                cout << "FOR NEURON " << i << " IN OUTPUT LAYER: " << endl;
                for (int j = 0; j < output_layer[i].number_of_left_connected_neurons(); j++) {
                    double weight = output_layer[i].get_weight(j);
                    cout << "WEIGHT " << j << ": " << weight << endl;
                }
                cout << endl;
            }
        } 
        else {
            cout << "OUTPUT AND INPUT LAYERS" << endl << endl;
            for (int i = 0; i < output_layer.size(); i++) {
                cout << "FOR NEURON " << i << " IN OUTPUT LAYER: " << endl;
                for (int j = 0; j < output_layer[i].number_of_left_connected_neurons(); j++) {
                    double weight = output_layer[i].get_weight(j);
                    cout << "WEIGHT " << j << ": " << weight << endl;
                }
                cout << endl;
            }
        }
    }

    void print() const {
        cout << endl;
        cout << "NEURAL NETWORK: INPUT LAYER: NUMBER OF NEURONS: " << input_layer.size() << endl << endl;
        for (int i = 0; i < input_layer.size(); i++) {
            cout << "NEURON " << i << ':' << endl << endl;
            input_layer[i].print();
            cout << endl << endl;
        }
        cout << endl << endl;

        cout << "NEURAL NETWORK: HIDDEN LAYER: NUMBER OF NEURONS: " << hidden_layer.size() << endl << endl;
        for (int i = 0; i < hidden_layer.size();i++) {
            cout << "NEURON " << i << ':' << endl << endl;
            hidden_layer[i].print();
            cout << endl << endl;
        }
        cout << endl << endl;

        cout << "NEURAL NETWORK: OUTPUT LAYER: NUMBER OF NEURONS: " << output_layer.size() << endl << endl;
        for (int i = 0; i < output_layer.size(); i++) {
            cout << "NEURON " << i << ':' << endl << endl;
            output_layer[i].print();
            cout << endl << endl;
        }
        cout << endl << endl;
    }
};