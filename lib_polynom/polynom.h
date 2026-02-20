#include "../lib_monom/monom.h"
#include "../lib_list/List.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>  
#include <stdexcept>
class Polynom {
private:
    List<Monom> _polynom;
    static constexpr double EPSILON = 1e-10;
    void simplify();
    void sort();
    Monom parseMonom(const std::string& token) const;
public:
    Polynom() : _polynom() {} //
    Polynom(const Monom& monom) {
        _polynom.push_back(monom);
    } //
    Polynom(const std::string& string);
    Polynom(const char* str) {
        if (!str) {
            throw std::invalid_argument("Null string pointer");
        }
        // Преобразуем C-строку в std::string и вызываем другой конструктор
        *this = Polynom(std::string(str));
    }
    Polynom(const Polynom& other) {
        _polynom = other._polynom;  
    } //
    Polynom& operator=(const Polynom& other); //

    Polynom operator +(const Polynom& other_polynom) const;
    Polynom operator -(const Polynom& other_polynom) const;
    Polynom operator *(const Polynom& other_polynom) const;

    Polynom& operator +=(const Polynom& other_polynom);
    Polynom& operator -=(const Polynom& other_polynom);
    Polynom& operator *=(const Polynom& other_polynom);

    Polynom operator +(const Monom& other_monom) const;
    Polynom operator -(const Monom& other_monom) const;

    Polynom& operator +=(const Monom& other_monom);
    Polynom& operator -=(const Monom& other_monom);

    Polynom operator-() const;

    double calculate(double x, double y, double z) const;
    bool is_zero() const noexcept { 
        return _polynom.is_empty(); 
    }
    size_t size() const noexcept { 
        return _polynom.get_size();
    }
    friend std::ostream& operator<<(std::ostream& out, const Polynom& polynom);
    friend std::istream& operator>>(std::istream& input, Polynom& polynom);
};
