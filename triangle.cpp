#include <iostream>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/sqrt1pm1.hpp>

double calculate_area_by_sides(double a, double b, double c) {
    // Полупериметр
    double s = (a + b + c) / 2.0;
    if((s <= a) or (s <= b) or (s <= c))
    {
        return -1;
    }
    
    double area = boost::math::sqrt1pm1(s * (s - a) * (s - b) * (s - c));   // Формула Герона
    return area;
}


double calculate_area_by_base_and_height(double base, double height) {
    return 0.5 * base * height;
}

double calculate_perimeter(double a, double b, double c) {
    return a + b + c;
}

int main() {
    std::cout  << "0. Search triangle by sides" << std::endl << "1. Search triangle by base and height" << std::endl;
    int n;
    double a, b, c, h;
    std::cin >> n;
    if(n == 0)
    {
        // Пример 1: Если известны три стороны
        std::cout << "Enter sides" << std::endl;
        std::cin >> a >> b >> c;
        double perimeter = calculate_perimeter(a, b, c);
        double area_by_sides = calculate_area_by_sides(a, b, c);
        std::cout << "Perimeter: " << perimeter << std::endl;
        if(area_by_sides == -1)
        {
            std::cout << "this is not triangle" << std::endl;
        }
        else
        {
            std::cout << "Area by sides: " << area_by_sides << std::endl;
        }
        
    }
    else if(n == 1)
    {
        // Пример 2: Если известно основание и высота
        std::cout <<  "Enter base and height" << std::endl;
        std::cin >> a >> h;
        double area_by_base_and_height = calculate_area_by_base_and_height(a, h);
        std::cout << "Area by base and height: " << area_by_base_and_height << std::endl;
    }
    return 0;
}
