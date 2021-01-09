#include <iostream>
using namespace std;

const int MAX_ELEMENTS = 100;

template <typename T>
class Vector{
private:
    T arr[MAX_ELEMENTS];
    int arr_size = 0;
public:
    void push_back(const T& element) {
        if (arr_size < MAX_ELEMENTS) {
            arr[arr_size] = element;
            arr_size++;
        } else {
            cout << "MAX_ELEMENTS IN VECTOR: " << MAX_ELEMENTS << endl;
        }
    }

    const T& operator[](int index_of_element) const {
        return arr[index_of_element];
    }

    T& operator[](int index_of_element) {
        return arr[index_of_element];
    }

    int size() const {
        return arr_size;
    }
};