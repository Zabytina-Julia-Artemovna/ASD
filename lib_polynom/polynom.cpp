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
    double result = 0.0;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        result += (*it).calculate(x, y, z);
    }
    return result;
}
std::ostream& operator<<(std::ostream& out, const Polynom& polynom) {
    if (polynom.is_zero()) {
        out << "0";
        return out;
    }
    auto it = polynom._polynom.begin();
    out << *it;
    for (++it; it != polynom._polynom.end(); it++) {
        double coef = (*it).get_coefficient();

        if (coef > 0) {
            out << " + " << *it;
        }
        else {
            out << " - " << -(*it);
        }
    }
    return out;
}
std::istream& operator>>(std::istream& input, Polynom& polynom) {
    polynom = Polynom();
    char c;
    bool positive = true;
    std::string monom_str;
    while (input.get(c)) {
        if (c == '+' || c == '-') {
            if (!monom_str.empty()) {
                try {
                    Monom m;
                    std::istringstream iss(monom_str);
                    iss >> m;
                    if (!positive) {
                        m = -m;
                    }
                    polynom._polynom.push_back(m);
                }
                catch (std::exception ex) {
                    input.setstate(std::ios::failbit);
                    return input;
                }
                monom_str.clear();
            }
            positive = (c == '+');
        }
        else if (!isspace(c)) {
            monom_str += c;
        }
    }
    if (!monom_str.empty()) {
        try {
            Monom m;
            std::istringstream iss(monom_str);
            iss >> m;
            if (!positive) {
                m = -m;
            }
            polynom._polynom.push_back(m);
        }
        catch (std::exception ex) {
            input.setstate(std::ios::failbit);
            return input;
        }
    }
    polynom.sort();
    polynom.simplify();

    return input;
}
void Polynom::sort() {
    size_t n = _polynom.get_size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            auto it_i = _polynom.begin();
            for (size_t k = 0; k < i; ++k) ++it_i;

            auto it_j = _polynom.begin();
            for (size_t k = 0; k < j; ++k) ++it_j;
            if (!(*it_i > *it_j)) {
                Monom temp = *it_i;
                *it_i = *it_j;
                *it_j = temp;
            }
        }
    }
}
void Polynom::simplify() {
    sort();
    size_t i = 0;
    while (i + 1 < _polynom.get_size()) {
        auto it1 = _polynom.begin();
        for (size_t k = 0; k < i; ++k) ++it1;
        auto it2 = it1;
        ++it2;
        if ((*it1) == (*it2)) {
            double new_coef = (*it1).get_coefficient() + (*it2).get_coefficient();
            (*it1).set_coefficient(new_coef);
            _polynom.erase(i + 1);
        }
        else {
            ++i;
        }
    }
    i = 0;
    while (i < _polynom.get_size()) {
        auto it = _polynom.begin();
        for (size_t k = 0; k < i; ++k) ++it;
        if (std::abs((*it).get_coefficient()) < EPSILON) {
            _polynom.erase(i);
        }
        else {
            ++i;
        }
    }
}
