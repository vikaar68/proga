#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>

class DynamicArray {
private:
    int* data;
    size_t size;

public:
    DynamicArray(size_t arraySize = 0) : size(arraySize) {
        data = (size > 0) ? new int[size]() : nullptr;
    }

    DynamicArray(const DynamicArray& other) : size(other.size) {
        data = (size > 0) ? new int[size] : nullptr;
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    void print() const {
        std::cout << "Array: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void setValue(size_t index, int value) {
        if (index >= size) throw std::out_of_range("Index out of range");
        if (value < -100 || value > 100) throw std::invalid_argument("Value must be between -100 and 100");
        data[index] = value;
    }

    int getValue(size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t getSize() const { return size; }

    void pushBack(int value) {
        if (value < -100 || value > 100) throw std::invalid_argument("Value must be between -100 and 100");
        
        int* newData = new int[size + 1];
        for (size_t i = 0; i < size; ++i) newData[i] = data[i];
        newData[size] = value;
        
        delete[] data;
        data = newData;
        ++size;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = (size > 0) ? new int[size] : nullptr;
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
        }
        return *this;
    }
};

class ExtendedArray : public DynamicArray {
public:
    ExtendedArray(size_t arraySize = 0) : DynamicArray(arraySize) {}
    
    double calculateAverage() const {
        if (getSize() == 0) throw std::runtime_error("Array is empty");
        double sum = 0;
        for (size_t i = 0; i < getSize(); ++i) sum += getValue(i);
        return sum / getSize();
    }

    double calculateMedian() {
        if (getSize() == 0) throw std::runtime_error("Array is empty");
        
        std::vector<int> temp;
        for (size_t i = 0; i < getSize(); ++i) temp.push_back(getValue(i));
        std::sort(temp.begin(), temp.end());
        
        size_t mid = getSize() / 2;
        return (getSize() % 2 == 0) ? (temp[mid-1] + temp[mid]) / 2.0 : temp[mid];
    }

    int findMin() const {
        if (getSize() == 0) throw std::runtime_error("Array is empty");
        int minVal = getValue(0);
        for (size_t i = 1; i < getSize(); ++i) {
            if (getValue(i) < minVal) minVal = getValue(i);
        }
        return minVal;
    }

    int findMax() const {
        if (getSize() == 0) throw std::runtime_error("Array is empty");
        int maxVal = getValue(0);
        for (size_t i = 1; i < getSize(); ++i) {
            if (getValue(i) > maxVal) maxVal = getValue(i);
        }
        return maxVal;
    }
};

int main() {
    ExtendedArray arr(5);
    arr.setValue(0, 10);
    arr.setValue(1, -5);
    arr.setValue(2, 25);
    arr.setValue(3, -15);
    arr.setValue(4, 30);
    
    arr.print();
    std::cout << "Average: " << arr.calculateAverage() << std::endl;
    std::cout << "Median: " << arr.calculateMedian() << std::endl;
    std::cout << "Min: " << arr.findMin() << std::endl;
    std::cout << "Max: " << arr.findMax() << std::endl;
    
    return 0;
}