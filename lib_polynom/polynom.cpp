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
Polynom Polynom::operator *(const Polynom& other_polynom) const { // x^2, y   // y^2, z
    Polynom result;
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); it1++) {
        for (auto it2 = other_polynom._polynom.begin(); it2 != other_polynom._polynom.end(); it2++) {
            result += (*it1) * (*it2);
        }
    }
    return result; 
}
