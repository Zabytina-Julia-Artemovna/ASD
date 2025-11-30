#include "../lib_vector/vector.h"
#include "lexem.h"
class Expression {
private:
    List<Lexem> _lexems;
public:
    Expression(std::string expression);
    Expression(const List<Lexem>& list);
};