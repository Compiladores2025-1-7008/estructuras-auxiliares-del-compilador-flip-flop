#include "../src/TypeManager.hpp"
#include "../src/TypeTable.hpp"
#include <gtest/gtest.h>

// Fixture para configurar la tabla antes de cada test
class TypeManagerTest : public ::testing::Test {
protected:
    TypeTable tt;
    int tVoid, tBool, tInt, tFloat, tDouble;

    void SetUp() override {
        // Registramos los tipos según la jerarquía del PDF
        tVoid   = tt.addBasicType("void", 0);
        tBool   = tt.addBasicType("bool", 1);
        tt.addBasicType("char", 1); // dummy
        tInt    = tt.addBasicType("int", 4);
        tFloat  = tt.addBasicType("float", 4);
        tDouble = tt.addBasicType("double", 8);
    }
};

TEST_F(TypeManagerTest, MaxType) {
    // float vs int -> gana float
    EXPECT_EQ(TypeManager::max(tt, tFloat, tInt), tFloat);
    // int vs int -> int
    EXPECT_EQ(TypeManager::max(tt, tInt, tInt), tInt);
    // double vs int -> double
    EXPECT_EQ(TypeManager::max(tt, tDouble, tInt), tDouble);
}

TEST_F(TypeManagerTest, MinType) {
    // float vs int -> menor es int
    EXPECT_EQ(TypeManager::min(tt, tFloat, tInt), tInt);
    // bool vs int -> menor es bool
    EXPECT_EQ(TypeManager::min(tt, tBool, tInt), tBool);
}

TEST_F(TypeManagerTest, Ampliar) {
    // Int se puede ampliar a Float (promoción implícita)
    int res = TypeManager::ampliar(0, tInt, tFloat, tt);
    EXPECT_EQ(res, tFloat);

    // Float NO se debe ampliar automáticamente a Int (pérdida de datos)
    // Según la lógica estándar, ampliar solo sube en jerarquía.
    int invalid = TypeManager::ampliar(0, tFloat, tInt, tt);
    EXPECT_EQ(invalid, -1);
}

TEST_F(TypeManagerTest, Reducir) {
    // Float se puede reducir explícitamente a Int (cast)
    int res = TypeManager::reducir(0, tFloat, tInt, tt);
    EXPECT_EQ(res, tInt);
}