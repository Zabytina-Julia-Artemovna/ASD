#include <iostream>
#include <stdexcept> 
#include <cmath>
class Monom {
private:
    static constexpr size_t VAR_COUNT = 3; //ƒл€ всех объектов класса Monom существует неизменна€ константа (вычисл€етс€ во врем€ компил€ции)
    double _coefficient; 
    int _powers[VAR_COUNT];
public:
    double get_coefficient() const noexcept {
        return _coefficient;
    }
    int powerX() const noexcept {
        return _powers[0]; 
    }
    int powerY() const noexcept {
        return _powers[1]; 
    }
    int powerZ() const noexcept {
        return _powers[2]; 
    }
    void set_coefficient(double value) {
        _coefficient = value;
    }
    void set_powers(int value1, int value2, int value3) {
        _powers[0] = value1;
        _powers[1] = value2;
        _powers[2] = value3;
    }
    Monom(double coefficient = 0.0): _coefficient(coefficient) {
        for (size_t i = 0; i < VAR_COUNT; i++) {
            _powers[i] = 0;
        }
    }
    Monom(double coefficient, int x_power, int y_power, int z_power)
        : _coefficient(coefficient)
        , _powers{ x_power, y_power, z_power } {
        if (x_power < 0 || y_power < 0 || z_power < 0) {
            throw std::invalid_argument("Powers cannot be negative");
        }
    }
    Monom(const Monom& other) = default; 
    bool operator ==(const Monom& other_monom) const;
    bool operator !=(const Monom& other_monom) const; 
    bool operator >(const Monom& other_monom) const;
    bool operator <(const Monom& other_monom) const;

    Monom& operator=(const Monom& other) = default;

    Monom operator +(const Monom& other_monom) const;
    Monom operator -(const Monom& other_monom) const;
    Monom operator *(const Monom& other_monom) const;
    Monom operator *(double value) const;
    Monom operator /(const Monom& other_monom) const;
    Monom operator /(double value) const;

    Monom& operator +=(const Monom& other_monom);
    Monom& operator -=(const Monom& other_monom);
    Monom& operator *=(const Monom& other_monom);
    Monom& operator *=(double value);
    Monom& operator /=(const Monom& other_monom);
    Monom& operator /=(double value);

    Monom operator -() const {
        return Monom(_coefficient * (-1), _powers[0], _powers[1], _powers[2]);
    }
    double calculate(double x, double y, double z) const;
    friend std::ostream& operator<<(std::ostream& out, const Monom& monom);
    friend std::istream& operator>>(std::istream& input, Monom& monom);
};
