#include "../src/TypeTable.hpp"
#include <gtest/gtest.h>

TEST(TypeTableTest, InsertAndRetrieveBasicType) {
    TypeTable tt;
    // Usamos addBasicType, no insertType
    int id = tt.addBasicType("int", 4);

    ASSERT_TRUE(tt.exists(id));
    auto t = tt.get(id);

    EXPECT_EQ(t.name, "int");
    EXPECT_EQ(t.size, 4);
    EXPECT_EQ(t.elements, 1); // Usamos elements, no numElements
    EXPECT_EQ(t.baseTypeId, -1);
}

TEST(TypeTableTest, InsertArrayType) {
    TypeTable tt;

    int baseId = tt.addBasicType("float", 8);
    // Usamos addArrayType, no insertArrayType
    int arrId = tt.addArrayType(baseId, 5);

    auto arrType = tt.get(arrId);
    auto baseType = tt.get(baseId);

    EXPECT_EQ(arrType.size, baseType.size * 5);
    EXPECT_EQ(arrType.elements, 5);
    EXPECT_EQ(arrType.baseTypeId, baseId);
    EXPECT_EQ(arrType.name, "float[5]");
}