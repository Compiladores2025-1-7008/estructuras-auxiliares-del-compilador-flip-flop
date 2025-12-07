#include "../src/CodeGenerator.hpp"
#include <gtest/gtest.h>

TEST(CodeGeneratorTest, GenerateNewTemporary) {
    CodeGenerator cg;
    // Debe empezar en 0
    EXPECT_EQ(cg.newTemp(), "t0");
    EXPECT_EQ(cg.newTemp(), "t1");
    EXPECT_EQ(cg.newTemp(), "t2");
}

TEST(CodeGeneratorTest, GenerateNewLabel) {
    CodeGenerator cg;
    // Debe empezar en 0
    EXPECT_EQ(cg.newLabel(), "L0");
    EXPECT_EQ(cg.newLabel(), "L1");
    EXPECT_EQ(cg.newLabel(), "L2");
}

TEST(CodeGeneratorTest, Reset) {
    CodeGenerator cg;
    cg.newTemp(); // t0
    cg.reset();
    EXPECT_EQ(cg.newTemp(), "t0"); // Debe volver a t0
}