#include "../lib_monom/monom.h"
#include "../lib_list/List.h"
#include <iostream>
#include <string>
#include <stdexcept>
class Polynom {
private:
    List<Monom> _polynom;

    void simplify();  // удалить нулевые, объединить подобные
    void sort();  // упорядочить
public:
    Polynom() : _polynom() {}
    Polynom(const Monom& monom) {
        _polynom.push_back(monom);
    }
    Polynom(const std::string& string);
    Polynom(const char* str);
    Polynom::Polynom(const Polynom& other) {
        _polynom = other._polynom;  
    }
    Polynom& operator=(const Polynom& other);

    Polynom operator +(const Polynom& other_polynom) const;
    Polynom operator -(const Polynom& other_polynom) const;
    Polynom operator *(const Polynom& other_polynom) const;
    //Polynom operator /(const Polynom& other_polynom) const;

    Polynom& operator +=(const Polynom& other_polynom);
    Polynom& operator -=(const Polynom& other_polynom);
    Polynom& operator *=(const Polynom& other_polynom);
   //Polynom& operator /=(const Polynom& other_polynom);

    Polynom operator +(const Monom& other_monom) const;
    Polynom operator -(const Monom& other_monom) const;
    //Polynom operator /(const Monom& other_monom) const;

    Polynom& operator +=(const Monom& other_monom);
    Polynom& operator -=(const Monom& other_monom);
    //Polynom& operator /=(const Monom& other_monom);

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
