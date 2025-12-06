#pragma once
#include <vector>
#include <memory>
#include "SymbolTable.hpp"

class SymbolTableStack {
private:
    std::vector<std::unique_ptr<SymbolTable>> stack;

public:
    // Crea nuevo ámbito
    void pushScope();

    // Sale de un ámbito
    void popScope();

    //Sale el ámbito y retorna la referencia a la tabla de símbolos en la cima
    SymbolTable* popSymbolTable();

    // Insertar solo en tope
    bool insertTop(const SymbolEntry &entry);

    // Insertar solo en la base (ámbito global)
    bool insertBase(const SymbolEntry &entry) ;

    // Buscar solo en tope
    // aqui puse const en la firma 
    const SymbolEntry* lookupTop(const std::string &id);

    // Buscar solo en la base
    // aqui puse const en la firma 
    const SymbolEntry* lookupBase(const std::string &id);

    // Depuración
    SymbolTable* currentScope() {
        if (stack.empty()) return nullptr;
        return stack.back().get();
    }

    SymbolTable* globalScope() {
        if (stack.empty()) return nullptr;
        return stack.front().get();
    }

    size_t levels() const { return stack.size(); }
};
