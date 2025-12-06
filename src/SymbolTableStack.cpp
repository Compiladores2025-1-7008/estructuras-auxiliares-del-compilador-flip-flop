#include "SymbolTableStack.hpp"

void SymbolTableStack::pushScope() {
    // creamos una nueva tabla para el ambito 
    stack.push_back(std::make_unique<SymbolTable>());
    return;
}

void SymbolTableStack::popScope() {
    // si no esta vacio quitamos el tope
    if(!stack.empty())
        stack.pop_back();
    return;
}

SymbolTable* SymbolTableStack::popSymbolTable() {
    // si no está vacío quitamos el tope y lo regresamos 
    if(!stack.empty())
        stack.pop_back();
    // si no regresamos apuntador nulo
    return nullptr;
}

bool SymbolTableStack::insertTop(const SymbolEntry &entry) {
    // si no existen contextos no podemos insertar
    if(SymbolTableStack::levels() == 0)
        return false;
    // insertamos el elemento, tomamos el valor de retorno de insert como el que retornamos aquí
    return stack.front()->insert(entry);
}

bool SymbolTableStack::insertBase(const SymbolEntry &entry) {
    // si no existen contextos no podemos insertar
    if(SymbolTableStack::levels() == 0)
        return false;
    // insertamos el elemento, tomamos el valor de retorno de insert como el que retornamos aquí
    return stack.back()->insert(entry);
}

const SymbolEntry* SymbolTableStack::lookupTop(const std::string &id) {
    // si no existen contextos no puede existir en el tope
    if(SymbolTableStack::levels() == 0)
        return nullptr;
    // insertamos el elemento, tomamos el valor de retorno de insert como el que retornamos aquí
    return stack.front().get()->lookup(id);
}

const SymbolEntry* SymbolTableStack::lookupBase(const std::string &id) {
    // si no existen contextos no puede existir en el tope
    if(SymbolTableStack::levels() == 0)
        return nullptr;
    // insertamos el elemento, tomamos el valor de retorno de insert como el que retornamos aquí
    return stack.back().get()->lookup(id);
}