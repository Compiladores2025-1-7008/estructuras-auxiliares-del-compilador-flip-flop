#include "SymbolTable.hpp"


bool SymbolTable::insert(const SymbolEntry &entry) {
    table.insert({entry.id, entry});
}

int SymbolTable::getType(const std::string &id) {
    // creamos un iterador para la tabla y buscamos la entrada para el id
    auto it = table.find(id); 
    // regresamos el valor si existe, sino regresamos un valor que indica no encontrado
    return (it != table.end()) ? it->second.typeId : -1;
}

int SymbolTable::getAddress(const std::string &id) {
    // creamos un iterador para la tabla y buscamos la entrada para el id
    auto it = table.find(id); 
    // regresamos el valor si existe, sino regresamos un valor que indica no encontrado
    return (it != table.end()) ? it->second.address : -1;
}

Category SymbolTable::getCategory(const std::string &id) {
    // creamos un iterador para la tabla y buscamos la entrada para el id
    auto it = table.find(id); 
    // regres
    return (it != table.end()) ? it->second.category : Category::NOTFOUND;
}

std::vector<int> SymbolTable::getParams(const std::string &id) {
    // creamos un iterador para la tabla y buscamos la entrada para el id
    auto it = table.find(id); 
    // regresamos el valor si existe, sino regresamos un valor que indica no encontrado
    return (it != table.end()) ? it->second.params : std::vector<int>{};
}