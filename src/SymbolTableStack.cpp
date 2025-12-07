#include "SymbolTableStack.hpp"

void SymbolTableStack::pushScope() {
    // Añadimos una nueva tabla al final del vector (tope de la pila)
    stack.push_back(std::make_unique<SymbolTable>());
}

void SymbolTableStack::popScope() {
    if(!stack.empty()) {
        stack.pop_back(); // El unique_ptr se encarga de liberar la memoria
    }
}

SymbolTable* SymbolTableStack::popSymbolTable() {
    if(stack.empty()) return nullptr;

    // release() libera la propiedad del puntero del unique_ptr para que
    // no se borre al hacer pop_back(). El llamador es responsable de borrarlo.
    SymbolTable* table = stack.back().release();
    stack.pop_back();
    return table;
}

bool SymbolTableStack::insertTop(const SymbolEntry &entry) {
    if(stack.empty()) return false;
    // El tope es back()
    return stack.back()->insert(entry);
}

bool SymbolTableStack::insertBase(const SymbolEntry &entry) {
    if(stack.empty()) return false;
    // La base es front()
    return stack.front()->insert(entry);
}

const SymbolEntry* SymbolTableStack::lookupTop(const std::string &id) {
    if(stack.empty()) return nullptr;
    return stack.back()->lookup(id);
}

const SymbolEntry* SymbolTableStack::lookupBase(const std::string &id) {
    if(stack.empty()) return nullptr;
    return stack.front()->lookup(id);
}