#include <iostream>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/sqrt1pm1.hpp>

using namespace std;

double calculate_area_by_sides(double a, double b, double c) {
    // Полупериметр
    double s = (a + b + c) / 2.0;
    
    // Формула Герона: A = sqrt(s * (s - a) * (s - b) * (s - c))
    double area = boost::math::sqrt1pm1(s * (s - a) * (s - b) * (s - c));
    return area;
}


double calculate_area_by_base_and_height(double base, double height) {
    return boost::math::sqrt1pm1(base * height);
}

double calculate_perimeter(double a, double b, double c) {
    return a + b + c;
}

int main() {
    // Пример 1: Если известны три стороны
    double a = 3, b = 4, c = 5;
    double perimeter = calculate_perimeter(a, b, c);
    double area_by_sides = calculate_area_by_sides(a, b, c);
    cout << "Периметр: " << perimeter << endl;
    cout << "Площадь (по сторонам): " << area_by_sides << endl;

    // Пример 2: Если известно основание и высота
    double base = 5, height = 4;
    double area_by_base_and_height = calculate_area_by_base_and_height(base, height);
    cout << "Площадь (по основанию и высоте): " << area_by_base_and_height << endl;

    return 0;
}
