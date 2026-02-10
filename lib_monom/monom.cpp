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
//bool Monom::operator >(const Monom& other_monom) const {//?
//    if (this->powerX() <= other_monom.powerX()) { 
//        return false;
//    }
//    return true;
//}
//bool Monom::operator <(const Monom& other_monom) const {//?
//    if (this->powerX() >= other_monom.powerX()) {
//        return false;
//    }
//    return true;
//}
Monom Monom::operator +(const Monom& other_monom) const {
    if (*this != other_monom) {
        throw std::logic_error("Monoms must be similar");
    }
    double new_coefficient = this->get_coefficient() + other_monom.get_coefficient();
    return Monom(new_coefficient, this->powerX(), this->powerY(), this->powerZ());
}
Monom Monom::operator -(const Monom& other_monom) const {
    if (*this != other_monom) {
        throw std::logic_error("Monoms must be similar");
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
Monom Monom::operator /(const Monom& other_monom) const {
    if (std::abs(other_monom.get_coefficient()) < EPSILON) {
        throw std::logic_error("Division by zero");
    }

    if (other_monom.powerX() > this->powerX() ||
        other_monom.powerY() > this->powerY() ||
        other_monom.powerZ() > this->powerZ()) {
        throw std::logic_error("Negative power in division");
    }

    double new_coefficient = this->get_coefficient() / other_monom.get_coefficient();
    int new_x = this->powerX() - other_monom.powerX();
    int new_y = this->powerY() - other_monom.powerY();
    int new_z = this->powerZ() - other_monom.powerZ();
    return Monom(new_coefficient, new_x, new_y, new_z);
}
Monom Monom::operator /(double value) const {
    if (std::abs(value) < EPSILON) {
        throw std::logic_error("Division by zero");
    }
    double new_coefficient = this->get_coefficient() / value;
    return Monom(new_coefficient, this->powerX(), this->powerY(), this->powerZ());
}
double Monom::calculate(double x, double y, double z) const {
    return _coefficient *
        std::pow(x, _powers[0]) *
        std::pow(y, _powers[1]) *
        std::pow(z, _powers[2]);
}
