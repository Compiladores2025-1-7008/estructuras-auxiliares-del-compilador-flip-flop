#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>

enum class Category {
    VAR,
    CONST,
    STRUCT,
    FUNCTION,
    PARAM,
    NOTFOUND // valor general que marca no encontrado
};

struct SymbolEntry {
    std::string id;
    int typeId;
    Category category;
    int address;
    std::vector<int> params;
};

class SymbolTable {
private:
    std::unordered_map<std::string, SymbolEntry> table;

public:
    bool insert(const SymbolEntry &entry);
    // -----------------------------------------
    // Consultas individuales simples
    // -----------------------------------------
    int getType(const std::string &id);

    int getAddress(const std::string &id) ;

    Category getCategory(const std::string &id);

    std::vector<int> getParams(const std::string &id);

    // -----------------------------------------
    // Consulta completa (si necesitas todos los datos)
    // -----------------------------------------
    const SymbolEntry* lookup(const std::string &id) const {
        auto it = table.find(id);
        return (it != table.end()) ? &it->second : nullptr;
    }

    // Para imprimir/depurar
    void print() const;
};

