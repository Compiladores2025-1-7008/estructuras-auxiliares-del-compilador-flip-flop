#include "CodeGenerator.hpp"
#include <string>

std::string CodeGenerator::newTemp() {
    // Retorna t0, t1, t2... y luego incrementa
    return "t" + std::to_string(nextTemp++);
}

std::string CodeGenerator::newLabel() {
    // Retorna L0, L1, L2... y luego incrementa
    return "L" + std::to_string(nextLabel++);
}

void CodeGenerator::reset() {
    nextTemp = 0;
    nextLabel = 0;
}
