#include "TypeTable.hpp"
#include "SymbolTable.hpp"
#include <stdexcept>
#include <iostream>

int TypeTable::addBasicType(const std::string& name, int size) {
    int id = types.size();
    types.push_back({id, TypeKind::BASIC, name, size});
    return id;
}

int TypeTable::addArrayType(int baseTypeId, int elements) {
    if (baseTypeId < 0 || baseTypeId >= static_cast<int>(types.size())) {
        throw std::runtime_error("ID de tipo base invalido");
    }

    int id = types.size();
    const auto& base = types[baseTypeId];
    int totalSize = base.size * elements;

    // Nombre sugerido: int[10]
    std::string arrName = base.name + "[" + std::to_string(elements) + "]";

    types.push_back({id, TypeKind::ARRAY, arrName, totalSize, elements, baseTypeId});
    return id;
}

int TypeTable::addStructType(const std::string &name, SymbolTable* fields) {
    int id = types.size();
    int structSize = 0;

    // Calculamos el tamaño sumando los campos
    if (fields) {
        for (const auto& pair : fields->getEntries()) {
            int fieldTypeId = pair.second.typeId;
            if (exists(fieldTypeId)) {
                structSize += get(fieldTypeId).size;
            }
        }
    }
}

const TypeEntry& TypeTable::get(int id) const {
    if (id < 0 || id >= static_cast<int>(types.size())) {
        throw std::out_of_range("Type ID fuera de rango: " + std::to_string(id));
    }
    return types[id];
}

bool TypeTable::exists(int id) const {
    return id >= 0 && id < static_cast<int>(types.size());
}

std::string TypeTable::getName(int id) const {
    return get(id).name;
}

void TypeTable::print() const {
    std::cout << "--- TABLA DE TIPOS ---\n";
    for (const auto& t : types) {
        std::cout << "ID: " << t.id << " | Name: " << t.name
                  << " | Size: " << t.size << "\n";
    }
}
