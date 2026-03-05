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
        _polynom.push_back(monom);
        sign = '+';
    }
    simplify();  
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
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1) { // через result: нельзя изменять коллекцию, по которой итерируешься!!!
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
    _polynom.push_back(other_monom);
    simplify();
    return *this;
}
Polynom& Polynom::operator-=(const Monom& other_monom) {
    _polynom.push_back(-other_monom);
    simplify();
    return *this;
}
Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        while (!_polynom.is_empty()) {
            _polynom.pop_back();
        }
        for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
            _polynom.push_back(*it);
        }
        
        simplify();
    }
    return *this;
}
Polynom Polynom::operator-() const {
    Polynom result;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        result._polynom.push_back(-(*it));
    }
    result.simplify();
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
            polynom._polynom.push_back(m);
        }
        catch (std::exception& ex) {
            input.setstate(std::ios::failbit);
            return input;
        }
    }
    polynom.sort();
    polynom.simplify();

    return input;
}
void Polynom::sort() {
    if (_polynom.get_size() <= 1) {
        return;
    }
    std::vector<Monom> temp;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        temp.push_back(*it);
    }
    std::sort(temp.begin(), temp.end(),
        [](const Monom& a, const Monom& b) { return a > b; }); //лямбда-функция (анонимная функция), которая сравнивает два монома a и b (сортировка по убыв. степ.)
    while (!_polynom.is_empty()) {
        _polynom.pop_back();
    }
    for (const auto& m : temp) {
        _polynom.push_back(m);
    }
}
void Polynom::simplify() {
    if (_polynom.get_size() <= 1) {
        return;
    }
    sort();
    std::vector<Monom> monoms;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        monoms.push_back(*it);
    }
    while (!_polynom.is_empty()) {
        _polynom.pop_back();
    }
    size_t i = 0;
    while (i + 1 < monoms.size()) {
        if (monoms[i] == monoms[i + 1]) {
            double new_coef = monoms[i].get_coefficient() + monoms[i + 1].get_coefficient(); //складываем подобные
            monoms[i].set_coefficient(new_coef);
            monoms.erase(monoms.begin() + i + 1);
        }
        else {
            ++i;
        }
    }
    i = 0;
    while (i < monoms.size()) {
        if (std::abs(monoms[i].get_coefficient()) < EPSILON) {
            monoms.erase(monoms.begin() + i); //удаляем нулевые
        }
        else {
            ++i;
        }
    }
    for (const auto& m : monoms) {
        _polynom.push_back(m);
    }
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
