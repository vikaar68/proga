#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    int* data;
    size_t size;

public:
    // Конструктор
    DynamicArray(size_t arraySize = 0) : size(arraySize) {
        if (size > 0) {
            data = new int[size](); 
        } else {
            data = nullptr;
        }
    }

    // Конструктор копирования (2)
    DynamicArray(const DynamicArray& other) : size(other.size) {
        if (size > 0) {
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    // Деструктор
    ~DynamicArray() {
        delete[] data;
    }

    // Вывод всех значений массива
    void print() const {
        std::cout << "array" << size << ": ";
        if (size == 0) {
            std::cout << "empty";
        } else {
            for (size_t i = 0; i < size; ++i) {
                std::cout << data[i];
                if (i < size - 1) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << std::endl;
    }

    // Сеттер (1)
    void setValue(size_t index, int value) {
        if (index >= size) {
            throw std::out_of_range("index out");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("-100 до 100");
        }
        data[index] = value;
    }

    // Геттер (1)
    int getValue(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("index out");
        }
        return data[index];
    }

    // Получение размера массива
    size_t getSize() const {
        return size;
    }

    // Добавление значения в конец массива (3)
    void pushBack(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("-100 до 100");
        }

        // Новый массив
        int* newData = new int[size + 1];
        
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        
        newData[size] = value;
        
        delete[] data;
        data = newData;
        ++size;
    }

    // Операция сложения массивов (4)
    DynamicArray add(const DynamicArray& other) const {
        size_t maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            int sum = val1 + val2;
            
            // Проверка результата
            if (sum < -100) sum = -100;
            if (sum > 100) sum = 100;
            
            result.data[i] = sum;
        }
        return result;
    }

    // Операция вычитания массивов (4)
    DynamicArray subtract(const DynamicArray& other) const {
        size_t maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            int diff = val1 - val2;
            
            // Проверка результатов
            if (diff < -100) diff = -100;
            if (diff > 100) diff = 100;
            
            result.data[i] = diff;
        }
        return result;
    }

    // Присваивание
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            if (size > 0) {
                data = new int[size];
                for (size_t i = 0; i < size; ++i) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }
};

// Демонстрация работы класса pypy
int main() {
    try {
        std::cout << "Task 1: " << std::endl;
        DynamicArray arr1(3);
        arr1.setValue(0, 10);
        arr1.setValue(1, -50);
        arr1.setValue(2, 100);
        arr1.print();

        std::cout << "index 1: " << arr1.getValue(1) << std::endl;

        std::cout << "\nTask 2: " << std::endl;
        DynamicArray arr2 = arr1; // Используется конструктор копирования
        arr2.print();

        std::cout << "\nTask 3: " << std::endl;
        arr1.pushBack(25);
        arr1.pushBack(-75);
        arr1.print();

        std::cout << "\nTask 4: " << std::endl;
        DynamicArray A(3);
        A.setValue(0, 10);
        A.setValue(1, 20);
        A.setValue(2, 30);

        DynamicArray B(2);
        B.setValue(0, 5);
        B.setValue(1, 15);

        std::cout << "A: ";
        A.print();
        std::cout << "B: ";
        B.print();

        DynamicArray sumResult = A.add(B);
        std::cout << "A + B: ";
        sumResult.print();

        DynamicArray diffResult = A.subtract(B);
        std::cout << "A - B: ";
        diffResult.print();

        // Тест с разными размерами массивов
        std::cout << "\nTest" << std::endl;
        DynamicArray C(1);
        C.setValue(0, 50);

        DynamicArray D(4);
        D.setValue(0, 10);
        D.setValue(1, 20);
        D.setValue(2, 30);
        D.setValue(3, 40);

        std::cout << "C: ";
        C.print();
        std::cout << "D: ";
        D.print();

        DynamicArray sumCD = C.add(D);
        std::cout << "C + D: ";
        sumCD.print();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}