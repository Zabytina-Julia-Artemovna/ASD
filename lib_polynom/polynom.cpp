#include "polynom.h"
Polynom::Polynom(const std::string& str) {
    if (str.empty()) {
        return;
    }
    std::stringstream ss(str);// превращаем строку в поток
    std::string token;
    char sign = '+';
    while (ss >> token) { //ss >> token будет читать слова, разделенные пробелами
        if (token == "+" || token == "-") {
            sign = token[0];
            continue;
        }
        Monom monom = parseMonom(token);
        if (sign == '-') {
            monom.set_coefficient(-monom.get_coefficient());
        }
        *this += monom;
        sign = '+';
    }
}
Polynom Polynom::operator +(const Polynom& other_polynom) const {
    Polynom result = *this;
    result += other_polynom; 
    return result;
}
Polynom Polynom::operator -(const Polynom& other_polynom) const {
    Polynom result = *this;
    result -= other_polynom;
    return result;
}
Polynom Polynom::operator *(const Polynom& other_polynom) const {
    Polynom result = *this;
    result *= other_polynom;
    return result;
}
Polynom& Polynom::operator+=(const Polynom& other_polynom) {
    for (auto it = other_polynom._polynom.begin(); it != other_polynom._polynom.end(); ++it) {
        *this += *it;  
    }
    return *this;
}
Polynom& Polynom::operator -=(const Polynom& other_polynom) {
    for (auto it = other_polynom._polynom.begin(); it != other_polynom._polynom.end(); ++it) {
        *this -= *it;
    }
    return *this;
}
Polynom& Polynom::operator*=(const Polynom& other_polynom) {
    Polynom result;
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1) { // через result: нельз€ измен€ть коллекцию, по которой итерируешьс€!!!
        // напр, если simplify() удалил элемент, на который указывал it1 - он уничтожен
        for (auto it2 = other_polynom._polynom.begin(); it2 != other_polynom._polynom.end(); ++it2) {
            result += (*it1) * (*it2);
        }
    }
    _polynom.clear();  
    _polynom = result._polynom;
    return *this;
}
Polynom Polynom::operator+(const Monom& other_monom) const {
    Polynom result = *this;
    result += other_monom;
    return result;
}
Polynom Polynom::operator -(const Monom& other_monom) const {
    Polynom result = *this;
    result -= other_monom;
    return result;
}
Polynom& Polynom::operator+=(const Monom& other_monom) {
    if (std::abs(other_monom.get_coefficient()) < EPSILON) {
        return *this;
    }
    if (_polynom.is_empty()) {
        _polynom.push_back(other_monom);
        return *this;
    }
    size_t pos = 0;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it, ++pos) {
        if (other_monom == *it) {
            *it += other_monom;
            if (std::abs(it->get_coefficient()) < EPSILON) {
                _polynom.erase(it);
            }
            return *this;
        }
        if (*it < other_monom) { 
            _polynom.insert(pos, other_monom);
            return *this;
        }
    }
    _polynom.push_back(other_monom);
    return *this;
}
Polynom& Polynom::operator-=(const Monom& other_monom) {
    (*this) += (-other_monom);
    return *this;
}
Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        _polynom.clear();
        for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
            _polynom.push_back(*it);
        }
    }
    return *this;
}
Polynom Polynom::operator-() const {
    Polynom result;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
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
                    polynom += m;
                }
                catch (std::exception& ex) {
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
            polynom += m;
        }
        catch (std::exception& ex) {
            input.setstate(std::ios::failbit);
            return input;
        }
    }

    return input;
}
Monom Polynom::parseMonom(const std::string& token) const { //считываем число - коэфф., перем., затем степень
   if (token.empty()) {
        throw std::invalid_argument("Empty monom token");
    }
        if (token == "0") {
        return Monom(0.0, 0, 0, 0);
    }
    double coefficient = 1.0;
    int powers[3] = { 0, 0, 0 };
    size_t pos = 0;
    if (isdigit(token[pos]) || token[pos] == '.') {
        size_t end;
        coefficient = std::stod(token.substr(pos), &end);
        pos = end;
    }
    while (pos < token.length()) {
        char var = token[pos];
        pos++;

        int var_index = -1;
        if (var == 'x') {
            var_index = 0;
        }
        else if (var == 'y') {
            var_index = 1;
        }
        else if (var == 'z') {
            var_index = 2;
        }
        else {
            throw std::invalid_argument("Invalid variable: " + std::string(1, var));
        }
        int power = 1;
        if (pos < token.length() && token[pos] == '^') {
            pos++;
            size_t end;
            power = std::stoi(token.substr(pos), &end);
            pos += end;
        }
        powers[var_index] = power;
    }
    return Monom(coefficient, powers[0], powers[1], powers[2]);
}
