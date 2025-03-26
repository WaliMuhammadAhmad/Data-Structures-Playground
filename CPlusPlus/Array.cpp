#include <iostream>
using namespace std;

const int SIZE = 5;

int main()
{
    // Define Method 1
    // int arr[SIZE];

    // Define Method 2 - brace-enclosed initializer
    // int arr[] = {1, 2, 3, 4, 5};

    // for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    // {
    //     cout << arr[i] << endl;
    // }

    // Define Method 3 - dynamic memeory allocation
    int size = 0;
    cout << "Enter the size of array:";
    cin >> size;
    int *arr = new int[size];

    // add elements to array
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10 + 1; // Assign random values to array elements
    }

    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    delete[] arr; // Free dynamically allocated memory

    return 0;
}