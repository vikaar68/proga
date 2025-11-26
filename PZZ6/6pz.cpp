#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    int* data;      
    size_t size;    

public:
    DynamicArray(size_t arraySize = 0) : size(arraySize) {
        if (size > 0) {
            data = new int[size]();
        } else {
            data = nullptr; 
        }
    }

    // Конструктор копирования 
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

    void print() const {
        std::cout << "array" << size << ": ";
        if (size == 0) {
            std::cout << "empty"; // Пустой массив
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

    // Установка значения
    void setValue(size_t index, int value) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Value must be between -100 and 100");
        }
        data[index] = value;
    }

    int getValue(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    void pushBack(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Value must be between -100 and 100");
        }

        int* newData = new int[size + 1];
        
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        
        // Добавляем новый элемент
        newData[size] = value;
        
        delete[] data;
        data = newData;
        ++size; 
    }

    // Сложение двух массивов
    DynamicArray add(const DynamicArray& other) const {
        size_t maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            // Если индекс выходит за границы массива, используем 0
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            int sum = val1 + val2;
            
            if (sum < -100) sum = -100;
            if (sum > 100) sum = 100;
            
            result.data[i] = sum;
        }
        return result;
    }

    // Вычитание двух массивов
    DynamicArray subtract(const DynamicArray& other) const {
        size_t maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            int diff = val1 - val2;
            
            if (diff < -100) diff = -100;
            if (diff > 100) diff = 100;
            
            result.data[i] = diff;
        }
        return result;
    }

    // Оператор присваивания
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

// Тестирование функциональности класса
int main() {
    try {
        std::cout << "Task 1: Basic functionality" << std::endl;
        DynamicArray arr1(3);
        arr1.setValue(0, 10);
        arr1.setValue(1, -50);
        arr1.setValue(2, 100);
        arr1.print(); 

        std::cout << "Value at index 1: " << arr1.getValue(1) << std::endl; 

        std::cout << "\nTask 2: Copy constructor" << std::endl;
        DynamicArray arr2 = arr1; 
        arr2.print(); 

        std::cout << "\nTask 3: Push back" << std::endl;
        arr1.pushBack(25);
        arr1.pushBack(-75);
        arr1.print(); 

        std::cout << "\nTask 4: Array operations" << std::endl;
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

        // Сложение массивов разной длины
        DynamicArray sumResult = A.add(B);
        std::cout << "A + B: ";
        sumResult.print(); // array3: 15, 35, 30

        // Вычитание массивов разной длины
        DynamicArray diffResult = A.subtract(B);
        std::cout << "A - B: ";
        diffResult.print(); // array3: 5, 5, 30

        // Тест с массивами разного размера
        std::cout << "\nTest with different sizes:" << std::endl;
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

        // Тестирование исключений
        std::cout << "\nTesting exceptions:" << std::endl;
        try {
            arr1.setValue(10, 50); 
        } catch (const std::out_of_range& e) {
            std::cout << "Caught out_of_range: " << e.what() << std::endl;
        }

        try {
            arr1.setValue(0, 150);
        } catch (const std::invalid_argument& e) {
            std::cout << "Caught invalid_argument: " << e.what() << std::endl;
        }

        try {
            arr1.getValue(10); // Неверный индекс
        } catch (const std::out_of_range& e) {
            std::cout << "Caught out_of_range: " << e.what() << std::endl;
        }

        try {
            arr1.pushBack(150); // Значение вне диапазона
        } catch (const std::invalid_argument& e) {
            std::cout << "Caught invalid_argument: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    return 0;
}