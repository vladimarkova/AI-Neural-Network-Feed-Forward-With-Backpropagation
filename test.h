#include <iostream>
#include <ratio>
#include <chrono>
#include "neural_network.h"
using namespace std;

void choose_task_number(int& task_number) {
    cout << endl;
    cout << "Enter task (0 for AND, 1 for OR, 2 for XOR)" << endl << endl;
    cin >> task_number;
}

void choose_number_of_neurons_in_hidden_layer(int& number_of_neurons_in_hidden_layer) {
    cout << endl;
    cout << "Enter number of neurons in hidden layer: " << endl << endl;
    cin >> number_of_neurons_in_hidden_layer;
}

void fill_all_entries(Vector<Vector<double>>& all_entries) {
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

// 0 - AND, 1 - OR, 2 - XOR
void fill_all_expected_outputs(Vector<Vector<double>>& expected_outputs) {
    expected_outputs[0][0] = 0;
    expected_outputs[0][1] = 0;
    expected_outputs[0][2] = 0;
    expected_outputs[0][3] = 1;
    
    expected_outputs[1][0] = 0;
    expected_outputs[1][1] = 1;
    expected_outputs[1][2] = 1;
    expected_outputs[1][3] = 1;
    
    expected_outputs[2][0] = 0;
    expected_outputs[2][1] = 1;
    expected_outputs[2][2] = 1;
    expected_outputs[2][3] = 0;
}

void show_task_type(int task_number, int number_of_neurons_in_hidden_layer) {
    if (task_number == 0) {
        cout << "TASK TYPE: 'AND'" << endl;
    }

    if (task_number == 1) {
        cout << "TASK TYPE: 'OR'" << endl;
    }
    
    if (task_number == 2) {
        cout << "TASK TYPE: 'XOR'" << endl;
    }

    cout << "INPUT LAYER: NUMBER OF NEURONS IN INPUT LAYER: " << NUMBER_OF_NEURONS_IN_INPUT_LAYER << endl;

    if (task_number == 2) {
        if (number_of_neurons_in_hidden_layer != 0) {
            cout << "HIDDEN LAYERS: 1, NUMBER OF NEURONS IN HIDDEN LAYER: " << number_of_neurons_in_hidden_layer << endl;
        }
    }

    cout << "OUTPUT LAYER: NUMBER OF NEURONS IN OUTPUT LAYER: " << NUMBER_OF_NEURONS_IN_OUTPUT_LAYER << endl;

    cout << endl << "ADMISSIBLE ERROR <= " << MIN_ERROR << endl;

    cout << endl;
} 

void test() {
    Vector<Vector<double>> all_entries;
    Vector<Vector<double>> expected_outputs;
    fill_all_entries(all_entries);
    fill_all_expected_outputs(expected_outputs);

    char response = '1';

    while(response != '0')
    {
        using namespace std::chrono;
        high_resolution_clock::time_point t1 = high_resolution_clock::now(); 

        int number_of_neurons_in_hidden_layer = 0;

        int task_number = 0;
        choose_task_number(task_number);

        if (task_number == 2) {
            choose_number_of_neurons_in_hidden_layer(number_of_neurons_in_hidden_layer);
        } 

        Neural_Network neural_network;
        neural_network.set_task_number(task_number);

        neural_network.initialize(
            NUMBER_OF_NEURONS_IN_INPUT_LAYER,
            number_of_neurons_in_hidden_layer,
            NUMBER_OF_NEURONS_IN_OUTPUT_LAYER
        );

        // cout << "RESULT FROM CLASSIFICATION: " << neural_network.classify_entry(all_entries[3]) << endl;

        // neural_network.apply_backpropagation(expected_outputs[task_number][3]);

        // cout << "RESULT FROM CLASSIFICATION AFTER APPLYING BACKPROPAGATION: " << neural_network.classify_entry(all_entries[3]) << endl;
        
        // neural_network.print_result_for_single_entry_classification(all_entries[3], expected_outputs[task_number][3]);
        
        // cout << endl << "NOW PRINTING: " << endl;

        // neural_network.print();

        neural_network.educate(all_entries, expected_outputs);

        show_task_type(task_number, number_of_neurons_in_hidden_layer);

        double error_of_all_entries_classification = 0;
        for (int i = 0; i < all_entries.size(); i++) {
            neural_network.classify_entry(all_entries[i]);

            error_of_all_entries_classification += neural_network.estimate_error_of_entry_classification(all_entries[i], expected_outputs[task_number][i]);

            neural_network.print_result_for_single_entry_classification(all_entries[i], expected_outputs[task_number][i]);
        }

        cout << "ESTIMATED TOTAL ERROR FOR ALL ENTRIES: " << error_of_all_entries_classification << endl << endl;

        // neural_network.classify_entry(all_entries[1]);

        // neural_network.apply_backpropagation(expected_outputs[task_number][1]);

        // cout << "NOW PRINTING NEURAL NETWORK FOR INPUT {0, 1}..." << endl << endl;

        // neural_network.print();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::milli> time_span = t2 - t1; 

        cout << "Time in miliseconds for classification with the neural network was: " << time_span.count() << " milliseconds." << endl << endl;
        
        cout << "Enter 0 to stop tests or 1 to continue: " << endl << endl;
        cin >> response;
    }
}