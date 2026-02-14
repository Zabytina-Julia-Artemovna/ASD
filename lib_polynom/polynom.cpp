#include "polynom.h"
const double EPSILON = 1e-10;

Polynom Polynom::operator +(const Polynom& other_polynom) const {
    Polynom result = *this;
    for (auto it = other_polynom._polynom.begin(); it != other_polynom._polynom.end(); it++) {
        result += *it;
    }
    return result;
}
Polynom Polynom::operator -(const Polynom& other_polynom) const {
    Polynom result = *this;
    for (auto it = other_polynom._polynom.begin(); it != other_polynom._polynom.end(); it++) {
        result -= *it;
    }
    return result;
}
Polynom Polynom::operator *(const Polynom& other_polynom) const { 
    Polynom result;
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); it1++) {
        for (auto it2 = other_polynom._polynom.begin(); it2 != other_polynom._polynom.end(); it2++) {
            result += (*it1) * (*it2);
        }
    }
    return result; 
}
Polynom& Polynom::operator +=(const Polynom& other_polynom) {
    *this = *this + other_polynom;
    return *this;
}
Polynom& Polynom::operator -=(const Polynom& other_polynom) {
    *this = *this - other_polynom;
    return *this;
}
Polynom& Polynom::operator *=(const Polynom& other_polynom) {
    *this = *this * other_polynom;
    return *this;
}
Polynom Polynom::operator +(const Monom& other_monom) const {
    Polynom result = *this;
    result += other_monom;
    result.simplify();
    result.sort();
    return result;
}
Polynom Polynom::operator -(const Monom& other_monom) const {
    Polynom result = *this;
    result -= other_monom;
    result.simplify();
    result.sort();
    return result;
}

Polynom& Polynom::operator +=(const Monom& other_monom) {
    *this = *this + other_monom;
    return *this;
}
Polynom& Polynom::operator -=(const Monom& other_monom) {
    *this = *this - other_monom;
    return *this;
}
Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        _polynom = other._polynom;
    }
    return *this;
}
Polynom Polynom::operator-() const {
    Polynom result;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        result += -(*it);
    }
    return result;
}
double Polynom::calculate(double x, double y, double z) const {
    double result;

}
