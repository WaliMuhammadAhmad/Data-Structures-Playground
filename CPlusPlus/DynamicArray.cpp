#include <iostream>
using namespace std;

class DynamicArray
{
private:
    int *array;
    int size;
    int capacity;

public:
    // Constructor
    DynamicArray(int initialCapacity)
    {
        capacity = initialCapacity;
        size = 0;
        array = new int[capacity];
    }

    // Destructor
    ~DynamicArray()
    {
        delete[] array;
    }

    // Function to add an element to the end of the array
    void pushBack(int element)
    {
        if (size == capacity)
        {
            // If the array is full, double its capacity
            capacity *= 2;
            int *newArray = new int[capacity];
            for (int i = 0; i < size; i++)
            {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
        }
        array[size++] = element;
    }

    // Function to remove an element from the end of the array
    void popBack()
    {
        if (size > 0)
        {
            size--;
        }
    }

    // Function to get the element at a specific index
    int getElementAt(int index)
    {
        if (index >= 0 && index < size)
        {
            return array[index];
        }
        // Return an error value (you can customize this)
        return -1;
    }

    // Function to get the current size of the array
    int getSize()
    {
        return size;
    }

    // Function to get the current capacity of the array
    int getCapacity()
    {
        return capacity;
    }
};

int main()
{
    // Create a dynamic array with an initial capacity of 5
    DynamicArray arr(5);

    // Push elements to the dynamic array
    for (int i = 1; i <= 10; i++)
    {
        arr.pushBack(i * (rand() % 10 + 1));
    }

    // Print the elements in the array
    for (int i = 0; i < arr.getSize(); i++)
    {
        cout << arr.getElementAt(i) << " ";
    }

    // Deallocate memory when done
    return 0;
}
