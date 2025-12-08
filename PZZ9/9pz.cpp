#include <iostream>
#include <cmath>
#include <typeinfo>
#include <stdexcept>
#include <vector>

template<typename T>
class MyArray {
private:
    std::vector<T> data;
    
public:
    // Конструкторы
    MyArray() = default;
    MyArray(size_t size) : data(size) {}
    MyArray(std::initializer_list<T> init) : data(init) {}
    
    // Доступ к элементам
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    // Размер массива
    size_t size() const {
        return data.size();
    }
    
    // Сеттер с проверкой для числовых типов
    template<typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value, void>::type
    setChecked(size_t index, U value) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }
    
    // Сеттер без проверки для нечисловых типов
    template<typename U = T>
    typename std::enable_if<!std::is_arithmetic<U>::value, void>::type
    setChecked(size_t index, U value) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }
    
    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const MyArray<T>& arr) {
        os << "[";
        for (size_t i = 0; i < arr.data.size(); ++i) {
            os << arr.data[i];
            if (i != arr.data.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
    
    // Расстояние между массивами (только для числовых типов)
    template<typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value, double>::type
    distance(const MyArray<T>& other) const {
        if (typeid(T) != typeid(other[0])) {
            throw std::bad_typeid();
        }
        
        if (data.size() != other.data.size()) {
            throw std::invalid_argument("Arrays must have the same size");
        }
        
        double sum = 0.0;
        for (size_t i = 0; i < data.size(); ++i) {
            double diff = static_cast<double>(data[i]) - static_cast<double>(other.data[i]);
            sum += diff * diff;
        }
        
        return std::sqrt(sum);
    }
    
    // Перегрузка для нечисловых типов
    template<typename U = T>
    typename std::enable_if<!std::is_arithmetic<U>::value, double>::type
    distance(const MyArray<T>& other) const {
        throw std::bad_typeid();
    }
};

// Пример использования
int main() {
    try {
        // Тест с целыми числами
        MyArray<int> arr1 = {1, 2, 3, 4, 5};
        MyArray<int> arr2 = {5, 4, 3, 2, 1};
        
        std::cout << "arr1: " << arr1 << std::endl;
        std::cout << "arr2: " << arr2 << std::endl;
        
        // Используем сеттер с проверкой
        arr1.setChecked(0, 10);
        std::cout << "After setChecked: " << arr1 << std::endl;
        
        // Вычисляем расстояние
        double dist = arr1.distance(arr2);
        std::cout << "Distance between arr1 and arr2: " << dist << std::endl;
        
        // Тест с вещественными числами
        MyArray<double> arr3 = {1.5, 2.5, 3.5};
        MyArray<double> arr4 = {0.5, 1.5, 2.5};
        
        std::cout << "\narr3: " << arr3 << std::endl;
        std::cout << "arr4: " << arr4 << std::endl;
        std::cout << "Distance between arr3 and arr4: " << arr3.distance(arr4) << std::endl;
        
        // Тест с нечисловым типом (должна быть ошибка при вычислении расстояния)
        MyArray<std::string> arr5 = {"hello", "mam"};
        MyArray<std::string> arr6 = {"by", "dad"};
        
        std::cout << "\narr5: " << arr5 << std::endl;
        
        try {
            double bad_dist = arr5.distance(arr6);
            std::cout << "Distance: " << bad_dist << std::endl;
        } catch (const std::bad_typeid& e) {
            std::cout << "Correctly caught bad_typeid for string arrays" << std::endl;
        }
        
        // Тест с разными размерами
        MyArray<int> arr7 = {1, 2, 3};
        MyArray<int> arr8 = {1, 2};
        
        try {
            double invalid_dist = arr7.distance(arr8);
            std::cout << "Distance: " << invalid_dist << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Correctly caught invalid_argument for different sizes: " 
                     << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}