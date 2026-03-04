#include "monom.h"
const double EPSILON = 1e-10;
bool Monom::operator ==(const Monom& other_monom) const {
    return this->powerX() == other_monom.powerX() &&
        this->powerY() == other_monom.powerY() &&
        this->powerZ() == other_monom.powerZ();
}
bool Monom::operator !=(const Monom& other_monom) const {
    return !(*this == other_monom);
}
bool Monom::operator >(const Monom& other_monom) const { 
    int total_degree_this = this->powerX() + this->powerY() + this->powerZ();
    int total_degree_other = other_monom.powerX() + other_monom.powerY() + other_monom.powerZ();

    if (total_degree_this == total_degree_other) {

        int pow_x_this = this->powerX();
        int pow_y_this = this->powerY();
        int pow_z_this = this->powerZ();

        int pow_x_other = other_monom.powerX();
        int pow_y_other = other_monom.powerY();
        int pow_z_other = other_monom.powerZ();

        if (pow_x_this != pow_x_other) {
            return (pow_x_this > pow_x_other);
        }
        if (pow_y_this != pow_y_other) {
            return (pow_y_this > pow_y_other);
        }
        if (pow_z_this != pow_z_other) {
            return (pow_z_this > pow_z_other);
        }
        return false;
    }
    return total_degree_this > total_degree_other;
}
bool Monom::operator<(const Monom& other_monom) const {
    return other_monom > *this;
}
Monom Monom::operator +(const Monom& other_monom) const {
    if (*this != other_monom) {
        throw std::invalid_argument("Monoms must be similar");
    }
    double new_coefficient = this->get_coefficient() + other_monom.get_coefficient();
    return Monom(new_coefficient, this->powerX(), this->powerY(), this->powerZ());
}
Monom Monom::operator -(const Monom& other_monom) const {
    if (*this != other_monom) {
        throw std::invalid_argument("Monoms must be similar");
    }
    double new_coefficient = this->get_coefficient() - other_monom.get_coefficient();
    return Monom(new_coefficient, this->powerX(), this->powerY(), this->powerZ());
}
Monom Monom::operator *(const Monom& other_monom) const {
    double new_coefficient = this->get_coefficient() * other_monom.get_coefficient();
    int new_x = this->powerX() + other_monom.powerX();
    int new_y = this->powerY() + other_monom.powerY();
    int new_z = this->powerZ() + other_monom.powerZ();
    return Monom(new_coefficient, new_x, new_y, new_z);
}
Monom Monom::operator *(double value) const {
    double new_coefficient = value * this->get_coefficient();
    return Monom(new_coefficient, this->powerX(), this->powerY(), this->powerZ());
}
Monom Monom::operator /(const Monom& other_monom) const {
    if (std::abs(other_monom.get_coefficient()) < EPSILON) {
        throw std::invalid_argument("Division by zero");
    }
    if (other_monom.powerX() > this->powerX() ||
        other_monom.powerY() > this->powerY() ||
        other_monom.powerZ() > this->powerZ()) {
        throw std::invalid_argument("Negative power in division");
    }
    double new_coefficient = this->get_coefficient() / other_monom.get_coefficient();
    int new_x = this->powerX() - other_monom.powerX();
    int new_y = this->powerY() - other_monom.powerY();
    int new_z = this->powerZ() - other_monom.powerZ();
    return Monom(new_coefficient, new_x, new_y, new_z);
}
Monom Monom::operator /(double value) const {
    if (std::abs(value) < EPSILON) {
        throw std::invalid_argument("Division by zero");
    }
    double new_coefficient = this->get_coefficient() / value;
    return Monom(new_coefficient, this->powerX(), this->powerY(), this->powerZ());
}
Monom& Monom::operator +=(const Monom& other_monom) {
    if (*this != other_monom) {
        throw std::invalid_argument("Monoms must be similar");
    }
    double new_coefficient = this->get_coefficient() + other_monom.get_coefficient();
    this->set_coefficient(new_coefficient);
    return *this;
}
Monom& Monom::operator -=(const Monom& other_monom) {
    if (*this != other_monom) {
        throw std::invalid_argument("Monoms must be similar");
    }
    double new_coefficient = this->get_coefficient() - other_monom.get_coefficient();
    this->set_coefficient(new_coefficient);
    return *this;
}
Monom& Monom::operator *=(const Monom& other_monom) {
    double new_coefficient = this->get_coefficient() * other_monom.get_coefficient();
    int new_x = this->powerX() + other_monom.powerX();
    int new_y = this->powerY() + other_monom.powerY();
    int new_z = this->powerZ() + other_monom.powerZ();
    this->set_coefficient(new_coefficient);
    this->set_powers(new_x, new_y, new_z);
    return *this;
}
Monom& Monom::operator *=(double value) {
    this->set_coefficient(this->get_coefficient() * value);
    return *this;
}
Monom& Monom::operator /=(const Monom& other_monom) {
    if (std::abs(other_monom.get_coefficient()) < EPSILON) {
        throw std::invalid_argument("Division by zero");
    }
    if (other_monom.powerX() > this->powerX() ||
        other_monom.powerY() > this->powerY() ||
        other_monom.powerZ() > this->powerZ()) {
        throw std::invalid_argument("Negative power in division");
    }
    double new_coefficient = this->get_coefficient() / other_monom.get_coefficient();
    int new_x = this->powerX() - other_monom.powerX();
    int new_y = this->powerY() - other_monom.powerY();
    int new_z = this->powerZ() - other_monom.powerZ();
    this->set_coefficient(new_coefficient);
    this->set_powers(new_x, new_y, new_z);
    return *this;
}
Monom& Monom::operator /=(double value) {
    if (std::abs(value) < EPSILON) {
        throw std::invalid_argument("Division by zero");
    }
    this->set_coefficient(this->get_coefficient() / value);
    return *this;
}
double Monom::calculate(double x, double y, double z) const {
    return _coefficient *
        std::pow(x, _powers[0]) *
        std::pow(y, _powers[1]) *
        std::pow(z, _powers[2]);
}
std::ostream& operator<<(std::ostream& out, const Monom& monom) {
    double coefficient = monom.get_coefficient();
    int power_x = monom.powerX();
    int power_y = monom.powerY();
    int power_z = monom.powerZ();

    if (std::abs(coefficient) < EPSILON) {
        out << "0";
        return out;
    }
    if (std::abs(coefficient - 1.0) > EPSILON ||
        (power_x == 0 && power_y == 0 && power_z == 0)) {
        out << coefficient;
    }
    if (power_x > 0) {
        out << "x";
        if (power_x > 1) {
            out << "^" << power_x;
        }
    }
    if (power_y > 0) {
        out << "y";
        if (power_y > 1) {
            out << "^" << power_y;
        }
    }
    if (power_z > 0) {
        out << "z";
        if (power_z > 1) {
            out << "^" << power_z;
        }
    }
    if (std::abs(coefficient - 1.0) < EPSILON &&
        power_x == 0 && power_y == 0 && power_z == 0) {
        out << "1";
    }
    return out;
}
std::istream& operator>>(std::istream& input, Monom& monom) {
    double coefficient;
    int power_x, power_y, power_z;
    input >> coefficient >> power_x >> power_y >> power_z;
    if (input) {
        if (power_x >= 0 && power_y >= 0 && power_z >= 0) {
            monom.set_coefficient(coefficient);
            monom.set_powers(power_x, power_y, power_z);
        }
        else {
            input.setstate(std::ios::failbit);
        }
    }
    return input;
}
