#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <ctime>

class DynamicArray {
protected:
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
    virtual ~DynamicArray() {
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

    // Сеттер
    void setValue(size_t index, int value) {
        if (index >= size) {
            throw std::out_of_range("index out");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("-100 до 100");
        }
        data[index] = value;
    }

    // Геттер
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

    // Добавление значения в конец массива
    void pushBack(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("-100 до 100");
        }

        int* newData = new int[size + 1];
        
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        
        newData[size] = value;
        
        delete[] data;
        data = newData;
        ++size;
    }

    virtual DynamicArray* add(const DynamicArray& other) const = 0;
    virtual DynamicArray* subtract(const DynamicArray& other) const = 0;

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

    // Метод для вывода в файл
    virtual void saveToFile() const = 0;

protected:
    // Метод для получения текущего времени
    std::string getCurrentDateTime() const {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);
        return buf;
    }
};

// Класс для записи в TXT файл
class ArrTxt : public DynamicArray {
public:
    // Конструкторы
    ArrTxt(size_t arraySize = 0) : DynamicArray(arraySize) {}
    ArrTxt(const DynamicArray& other) : DynamicArray(other) {}

    // Реализация метода для записи в TXT
    void saveToFile() const override {
        std::string filename = getCurrentDateTime() + ".txt";
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        file << "DynamicArray (TXT format)\n";
        file << "Size: " << size << "\n";
        file << "Elements: ";
        
        if (size == 0) {
            file << "empty";
        } else {
            for (size_t i = 0; i < size; ++i) {
                file << data[i];
                if (i < size - 1) {
                    file << ", ";
                }
            }
        }
        file << "\n";
        
        file.close();
        std::cout << "Array saved to: " << filename << std::endl;
    }

    // Операция сложения
    DynamicArray* add(const DynamicArray& other) const override {
        size_t maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrTxt* result = new ArrTxt(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.getSize()) ? other.getValue(i) : 0;
            int sum = val1 + val2;
            
            if (sum < -100) sum = -100;
            if (sum > 100) sum = 100;
            
            result->data[i] = sum;
        }
        return result;
    }

    // Операция вычитания
    DynamicArray* subtract(const DynamicArray& other) const override {
        size_t maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrTxt* result = new ArrTxt(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.getSize()) ? other.getValue(i) : 0;
            int diff = val1 - val2;
            
            if (diff < -100) diff = -100;
            if (diff > 100) diff = 100;
            
            result->data[i] = diff;
        }
        return result;
    }
};

// Класс для записи в CSV файл
class ArrCSV : public DynamicArray {
public:
    // Конструкторы
    ArrCSV(size_t arraySize = 0) : DynamicArray(arraySize) {}
    ArrCSV(const DynamicArray& other) : DynamicArray(other) {}

    // Метода для записи в CSV
    void saveToFile() const override {
        std::string filename = getCurrentDateTime() + ".csv";
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        // Заголовок CSV
        file << "Index,Value\n";
        
        // Данные
        for (size_t i = 0; i < size; ++i) {
            file << i << "," << data[i] << "\n";
        }
        
        file.close();
        std::cout << "Array saved to: " << filename << std::endl;
    }

    // Операция сложения
    DynamicArray* add(const DynamicArray& other) const override {
        size_t maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrCSV* result = new ArrCSV(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.getSize()) ? other.getValue(i) : 0;
            int sum = val1 + val2;
            
            if (sum < -100) sum = -100;
            if (sum > 100) sum = 100;
            
            result->data[i] = sum;
        }
        return result;
    }

    // Операция вычитания
    DynamicArray* subtract(const DynamicArray& other) const override {
        size_t maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrCSV* result = new ArrCSV(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.getSize()) ? other.getValue(i) : 0;
            int diff = val1 - val2;
            
            if (diff < -100) diff = -100;
            if (diff > 100) diff = 100;
            
            result->data[i] = diff;
        }
        return result;
    }
};

// Демонстрация работы классов
int main() {
    try {
        std::cout << "Testing ArrTxt class" << std::endl;
        ArrTxt txtArray(4);
        txtArray.setValue(0, 10);
        txtArray.setValue(1, -50);
        txtArray.setValue(2, 75);
        txtArray.setValue(3, 100);
        txtArray.print();
        txtArray.saveToFile();
        
        std::cout << "\nTesting ArrCSV class" << std::endl;
        ArrCSV csvArray(3);
        csvArray.setValue(0, 25);
        csvArray.setValue(1, -75);
        csvArray.setValue(2, 50);
        csvArray.print();
        csvArray.saveToFile();
        
        std::cout << "\nTesting operations" << std::endl;
        ArrTxt A(3);
        A.setValue(0, 10);
        A.setValue(1, 20);
        A.setValue(2, 30);

        ArrCSV B(2);
        B.setValue(0, 5);
        B.setValue(1, 15);

        std::cout << "A: ";
        A.print();
        std::cout << "B: ";
        B.print();

        // Тестирование операций с использованием указателей
        DynamicArray* sumResult = A.add(B);
        std::cout << "A + B: ";
        sumResult->print();
        sumResult->saveToFile();
        delete sumResult;

        DynamicArray* diffResult = B.subtract(A);
        std::cout << "B - A: ";
        diffResult->print();
        diffResult->saveToFile();
        delete diffResult;
        
        std::cout << "\nTesting polymorphism" << std::endl;
        DynamicArray* arrays[2];
        
        arrays[0] = new ArrTxt(2);
        arrays[0]->setValue(0, 5);
        arrays[0]->setValue(1, -25);
        
        arrays[1] = new ArrCSV(3);
        arrays[1]->setValue(0, 15);
        arrays[1]->setValue(1, 35);
        arrays[1]->setValue(2, -45);
        
        // Демонстрация полиморфизма
        for (int i = 0; i < 2; i++) {
            arrays[i]->print();
            arrays[i]->saveToFile();
            delete arrays[i];
        }
        
        std::cout << "\nTesting copy functionality" << std::endl;
        ArrTxt original(2);
        original.setValue(0, 99);
        original.setValue(1, -99);
        
        ArrTxt copy = original;
        copy.print();
        copy.saveToFile();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}