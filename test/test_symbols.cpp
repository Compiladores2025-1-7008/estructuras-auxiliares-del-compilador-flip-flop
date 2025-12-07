#include "../src/SymbolTable.hpp"
#include <gtest/gtest.h>
#include <vector>

TEST(SymbolTableTest, InsertAndRetrieveSymbol) {
    SymbolTable ts;

    // La firma requiere un struct SymbolEntry.
    // Usamos inicialización de lista { ... }
    SymbolEntry entry = {"x", 1, Category::VAR, 100, {}};
    ts.insert(entry);

    // Verificamos usando lookup que retorna un puntero
    const SymbolEntry* sym = ts.lookup("x");

    ASSERT_TRUE(sym != nullptr);
    EXPECT_EQ(sym->typeId, 1);
    EXPECT_EQ(sym->address, 100);
    EXPECT_EQ(sym->category, Category::VAR);
    EXPECT_TRUE(sym->params.empty());
}

TEST(SymbolTableTest, FunctionSymbol) {
    SymbolTable ts;
    // Insertamos función con lista de tipos de parámetros {1, 2} (ej. int, float)
    SymbolEntry entry = {"sum", 3, Category::FUNCTION, 200, {1, 2}};
    ts.insert(entry);

    const SymbolEntry* sym = ts.lookup("sum");
    ASSERT_TRUE(sym != nullptr);
    EXPECT_EQ(sym->category, Category::FUNCTION);
    ASSERT_EQ(sym->params.size(), 2u);
    EXPECT_EQ(sym->params[0], 1);
    EXPECT_EQ(sym->params[1], 2);
}