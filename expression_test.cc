//Author: Adam Princiotta
#include "gtest/gtest.h"
#include "expression.h"


TEST(prefix, one) {
    Expression e("2");
    EXPECT_EQ("2", e.getPrefix());
}

TEST(prefix, two) {
    Expression e("2+3+4");
    EXPECT_EQ("++234", e.getPrefix());
}

TEST(prefix, three) {
    Expression e("2+3+4+3*4");
    EXPECT_EQ("+++234*34", e.getPrefix());
}

TEST(prefix, four) {
    Expression e("2+3*4+5*6/2");
    EXPECT_EQ("+2+*34/*562", e.getPrefix());
}

TEST(prefix, five) {
    Expression e("(2)");
    EXPECT_EQ("2", e.getPrefix());
}

TEST(prefix, six) {
    Expression e("(1+3)*(2+4)");
    EXPECT_EQ("*+13+24", e.getPrefix());
}

TEST(prefix, seven) {
    Expression e("3*((2+4)*(1+1)+7)/(2*5+9)");
    EXPECT_EQ("/*3+*+24+117+*259", e.getPrefix());
}

TEST(prefix, eight) {
    Expression e("7+4*(2+4*(7-2)*(5*(4-2))/(5*4*5))");
    EXPECT_EQ("+7*4+2/**4-72*5-42**545", e.getPrefix());
}

TEST(prefix, nine) {
    Expression e("(((2)))");
    EXPECT_EQ("2", e.getPrefix());
}

TEST(postfix, two) {
    Expression e("2");
    EXPECT_EQ("2", e.getPostfix());
}

TEST(postfix, someParens) {
    Expression e("(1+3)*(2+4)");
    EXPECT_EQ("13+24+*", e.getPostfix());
}

TEST(evaluate, two) {
    Expression e("2");
    EXPECT_EQ(2, e.getValue());
}

TEST(evaluate, someParens) {
    Expression e("(1+3)*(2+4)");
    EXPECT_EQ(24, e.getValue());
}

TEST(evaluate, NumTwo) {
    Expression e("2+3+4");
    EXPECT_EQ(9, e.getValue());
}

TEST(evaluate, three) {
    Expression e("2+3+4+3*4");
    EXPECT_EQ(21, e.getValue());
}

TEST(evaluate, four) {
    Expression e("2+3*4+5*6/2");
    EXPECT_EQ(29, e.getValue());
}

TEST(evaluate, five) {
    Expression e("(2)");
    EXPECT_EQ(2, e.getValue());
}

TEST(evaluate, six) {
    Expression e("(1+3)*(2+4)");
    EXPECT_EQ(24, e.getValue());
}

TEST(evaluate, seven) {
    Expression e("3*((2+4)*(1+1)+7)/(2*5+9)");
    EXPECT_EQ(3, e.getValue());
}

TEST(evaluate, eight) {
    Expression e("7+4*(2+4*(7-2)*(5*(4-2))/(5*4*5))");
    EXPECT_EQ(23, e.getValue());
}

TEST(evaluate, nine) {
    Expression e("(((2)))");
    EXPECT_EQ(2, e.getValue());
}

// Comment out tests for options you don't do.
/*TEST(postfixError, empty) {
    // test that invalid empty expression causes syntax error
    try {
        Expression e("");
        e.getPostfix();
        FAIL() << "Didn't throw the expected exception.";
    } catch(SyntaxError e) {
        EXPECT_EQ(0, e.getPosition());
        EXPECT_EQ("Operand expected", e.getDescription());
    }
}

TEST(postfixError, plus) {
    try {
        Expression e("+");
        e.getPostfix();
        FAIL() << "Didn't throw the expected exception.";
    } catch(SyntaxError e) {
        EXPECT_EQ(0, e.getPosition());
        EXPECT_EQ("Operand expected", e.getDescription());
    }
}

TEST(postfixError, missingOp) {
    try {
        Expression e("1+23");
        e.getPostfix();
        FAIL() << "Didn't throw the expected exception.";
    } catch(SyntaxError e) {
        EXPECT_EQ(3, e.getPosition());
        EXPECT_EQ("Operator expected", e.getDescription());
    }
}*/


