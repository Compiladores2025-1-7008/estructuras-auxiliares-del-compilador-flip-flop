#include "../../src/TypeTable.hpp"
#include <gtest/gtest.h>

TEST(TypeTableTest, InsertAndRetrieveBasicType) {
    TypeTable tt;

    int id = tt.insertType("int", 4);
    auto t = tt.getType(id);

    EXPECT_EQ(t.name, "int");
    EXPECT_EQ(t.size, 4);
    EXPECT_EQ(t.numElements, 1);
    EXPECT_EQ(t.baseTypeId, -1);
}

TEST(TypeTableTest, InsertArrayType) {
    TypeTable tt;

    int baseId = tt.insertType("float", 8);
    int arrId = tt.insertArrayType("float[]", baseId, 5);

    auto arrType = tt.getType(arrId);
    auto baseType = tt.getType(baseId);

    EXPECT_EQ(arrType.size, baseType.size * 5);
    EXPECT_EQ(arrType.numElements, 5);
    EXPECT_EQ(arrType.baseTypeId, baseId);
}
