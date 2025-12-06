#include "SymbolTable.hpp"
#include <iostream>


bool SymbolTable::insert(const SymbolEntry &entry) {
    // verificamos que no exista ya el símbolo en la tabla
    auto it = table.find(entry.id);
    // si no existe lo insertamos e indicamos exito, sino indicamos fallo
    if (it == table.end()){   
        table.insert({entry.id, entry});
        return true;
    }
    return false;
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

// auxiliar para imprimir  categoria en la función imprimir
std::ostream& operator<<(std::ostream& os, const Category Symbol) {
    switch(Symbol) {
        case Category::VAR:
            os << "Variable";
            break;
        case Category::CONST:
            os << "Constante";
            break;
        case Category::STRUCT:
            os << "Estructura";
            break;
        case Category::FUNCTION:
            os << "Función";
            break;
        case Category::PARAM:
            os << "Parámetro";
            break;
        case Category::NOTFOUND:
            // Este no debería pasar
            break;
    }
    return os;
}

void SymbolTable::print() const{
    // iteramos sobre la tabla e imprimos el id de la entrada (primero) y el simbolo correspondiente (segundo)
    for(auto it = table.begin(); it != table.end(); it++) {
        std::cout << "Entrada: " << it->first << std::endl;
        std::cout << "ID: " << it->second.id << std::endl;
        std::cout << "ID de Tipo: " << it->second.typeId << std::endl;
        std::cout << "Categoría: " << it->second.category << std::endl;
        std::cout << "Dirección: " << it->second.address << std::endl;
        if (it->second.params.size() == 0) {
            std::cout << "Parámetros: {}" << std::endl;
        } else {
            for (auto vecit = it->second.params.begin(); vecit != it->second.params.end(); vecit++) {
                std::cout << "Parámetro: " << *vecit << std::endl;
            }
        }
    }
}