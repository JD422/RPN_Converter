#include <check.h>
#include "../src/rpnconverter.h"

START_TEST(whenRPNConverterMainFunctionIsPassedRPNReturnInfix)
{   
    char * test = rpnconverter("ab+");
    ck_assert_str_eq(test, "(a+b)");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterMainFunctionIsPassedInfixReturnRPN)
{   
    char * test = rpnconverter("a+b");
    ck_assert_str_eq(test, "ab+");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNFunctionIsPassedBasicInfixReturnItInRPN)
{   
    char * test = rpnconverter_infix2rpn("a+b");
    ck_assert_str_eq(test, "ab+");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNFunctionIsPassedInfixWithBasicOrderOfOperationChallengeReturnItInRPN)
{   
    char * test = rpnconverter_infix2rpn("a+b-c*d");
    ck_assert_str_eq(test, "ab+cd*-");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNFunctionIsPassedInfixWithIntermediateOrderOfOperationChallengeReturnItInRPN)
{   
    char * test = rpnconverter_infix2rpn("a/b+c^d+f");
    ck_assert_str_eq(test, "ab/cd^+f+");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNFunctionIsPassedInfixWithAdvancedOrderOfOperationChallengeReturnItInRPN)
{   
    char * test = rpnconverter_infix2rpn("(a*b^((c+d)/(e-f))^g)");
    ck_assert_str_eq(test, "abcd+^*ef-/g^");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNStripFunctionIsPassedInfixWithParenthesesReturnInfixWithoutParentheses)
{   
    char * test = rpnconverter_infix2rpn_strip("(c+d)/(e-f)");
    ck_assert_str_eq(test, "c+d/e-f");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedBasicRPNReturnItInInfix)
{   
    char * test = rpnconverter_rpn2infix("ab+");
    ck_assert_str_eq(test, "(a+b)");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedRPNWithBasicOrderOfOperationChallengeReturnItInInfix)
{   
    char * test = rpnconverter_rpn2infix("ab+cd*-");
    ck_assert_str_eq(test, "((a+b)-(c*d))");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedRPNWithIntermediateOrderOfOperationChallengeReturnItInInfix)
{   
    char * test = rpnconverter_rpn2infix("ab/cd^+f+");
    ck_assert_str_eq(test, "(((a/b)+(c^d))+f)");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedRPNWithAdvancedOrderOfOperationChallengeReturnItInInfix)
{   
    char * test = rpnconverter_rpn2infix("ag+ba-c+cedf^*+^*");
    ck_assert_str_eq(test, "((a+g)*(((b-a)+c)^(c+(e*(d^f)))))");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixGetOperatorsFunctionIsPassedRPNReturnOperatorsInCorrectOrder)
{   
    char * test = rpnconverter_rpn2infix_getoperators("ag+ba-c+cedf^*+^*");
    ck_assert_str_eq(test, "+-+^*+^*");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixCountOperatorsFunctionIsPassedRPNReturnNumberOfOperators)
{   
    ck_assert_int_eq(rpnconverter_rpn2infix_countoperators("ab+cd*-"), 3);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixSpanFunctionIsPassedSpanAndRPNReturnSpan)
{   
    ck_assert_int_eq(rpnconverter_rpn2infix_span(14,2,"((a/b)+(c^d))f+"), 14);
}
END_TEST
START_TEST(whenRPNConverterAutoselectFunctionIsPassedRPNReturnIdentifierForRPN)
{   
    ck_assert_int_eq(rpnconverter_autoselect("ab+"), 1);
}
END_TEST
START_TEST(whenRPNConverterAutoselectFunctionIsPassedInfixReturnIdentifierForInfix)
{   
    ck_assert_int_eq(rpnconverter_autoselect("a+b"), 2);
}
END_TEST
START_TEST(whenRPNConverterOrderOfOperationFunctionIsPassedInfixWithoutParenthesesReturnAllUsedOperatorsInProperOrder)
{   
    char * test = rpnconverter_orderOfOperation("a*b^c+d/e-f^g");
    ck_assert_str_eq(test, "^^*/+-");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterOrderOfOperationFunctionIsPassedInfixWithParenthesesReturnAllUsedOperatorsInProperOrder)
{   
    char * test = rpnconverter_orderOfOperation("(a*b^((c+d)/(e-f))^g)");
    ck_assert_str_eq(test, "+-/^^*");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNFunctionIsPassedEmptyInputReturnError)
{   
    char * test = rpnconverter_infix2rpn("");
    ck_assert_str_eq(test, "Error: Algorithm Size");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedEmptyInputReturnError)
{   
    char * test = rpnconverter_rpn2infix("");
    ck_assert_str_eq(test, "Error: Algorithm Size");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterOrderOfOperationFunctionIsPassedEmptyInputReturnError)
{   
    char * test = rpnconverter_orderOfOperation("");
    ck_assert_str_eq(test, "Error: Algorithm Size");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterOrderOfOperationCheckParenthesesFunctionIsPassedInfixWithParenthesesReturnNumberOfOpenParentheses)
{   
    ck_assert_int_eq(rpnconverter_orderOfOperation_checkParentheses("(a*b^((c+d)/(e-f))^g)"), 4);
}
END_TEST
START_TEST(whenRPNConverterAutoselectFunctionIsPassedEmptyInputReturnError)
{   
    ck_assert_int_eq(rpnconverter_autoselect(""), 0);
}
END_TEST
START_TEST(whenRPNConverterMainFunctionIsPassedEmptyInputReturnError)
{   
    char * test = rpnconverter("");
    ck_assert_str_eq(test, "Error: Algorithm is NULL");
    free(test);
}
END_TEST
    
Suite * rpn_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RPNConverter");
    
    tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, whenRPNConverterMainFunctionIsPassedRPNReturnInfix);
    tcase_add_test(tc_core, whenRPNConverterMainFunctionIsPassedInfixReturnRPN);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNFunctionIsPassedBasicInfixReturnItInRPN);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNFunctionIsPassedInfixWithBasicOrderOfOperationChallengeReturnItInRPN);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNFunctionIsPassedInfixWithIntermediateOrderOfOperationChallengeReturnItInRPN);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNFunctionIsPassedInfixWithAdvancedOrderOfOperationChallengeReturnItInRPN);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNStripFunctionIsPassedInfixWithParenthesesReturnInfixWithoutParentheses);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedBasicRPNReturnItInInfix);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedRPNWithBasicOrderOfOperationChallengeReturnItInInfix);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedRPNWithIntermediateOrderOfOperationChallengeReturnItInInfix);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedRPNWithAdvancedOrderOfOperationChallengeReturnItInInfix);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixGetOperatorsFunctionIsPassedRPNReturnOperatorsInCorrectOrder);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixCountOperatorsFunctionIsPassedRPNReturnNumberOfOperators);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixSpanFunctionIsPassedSpanAndRPNReturnSpan);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedRPNReturnIdentifierForRPN);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedInfixReturnIdentifierForInfix);
    tcase_add_test(tc_core, whenRPNConverterOrderOfOperationFunctionIsPassedInfixWithoutParenthesesReturnAllUsedOperatorsInProperOrder);
    tcase_add_test(tc_core, whenRPNConverterOrderOfOperationFunctionIsPassedInfixWithParenthesesReturnAllUsedOperatorsInProperOrder);
    tcase_add_test(tc_core, whenRPNConverterOrderOfOperationCheckParenthesesFunctionIsPassedInfixWithParenthesesReturnNumberOfOpenParentheses);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterOrderOfOperationFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterMainFunctionIsPassedEmptyInputReturnError);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = rpn_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}