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
START_TEST(whenRPNConverterCountOperatorsFunctionIsPassedRPNReturnNumberOfOperators)
{   
    ck_assert_int_eq(rpnconverter_countoperators("ab+cd*-"), 3);
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
START_TEST(whenRPNConverterInfix2RPNGetOperatorArrayFunctionIsPassedInfixWithoutParenthesesReturnAllUsedOperatorsInProperOrder)
{   
    char * test = rpnconverter_infix2rpn_getoperatorarray("a*b^c+d/e-f^g");
    ck_assert_str_eq(test, "^^*/+-");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNGetOperatorArrayFunctionIsPassedInfixWithParenthesesReturnAllUsedOperatorsInProperOrder)
{   
    char * test = rpnconverter_infix2rpn_getoperatorarray("(a*b^((c+d)/(e-f))^g)");
    ck_assert_str_eq(test, "+-/^^*");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNOrderOfOperationFunctionIsPassedInfixWithParenthesesReturnAllUsedOperatorsInProperOrder)
{   
    char * test = rpnconverter_infix2rpn_orderofoperation(0,13,"a*b^c+d/e-f^g");
    ck_assert_str_eq(test, "^^*/+-");
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
START_TEST(whenRPNConverterInfix2RPNGetOperatorArrayFunctionIsPassedEmptyInputReturnError)
{   
    char * test = rpnconverter_infix2rpn_getoperatorarray("");
    ck_assert_str_eq(test, "Error: Algorithm Size");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNOrderOfOperationCheckParenthesesFunctionIsPassedInfixWithParenthesesReturnNumberOfOpenParentheses)
{   
    ck_assert_int_eq(rpnconverter_infix2rpn_orderofoperation_checkparentheses("(a*b^((c+d)/(e-f))^g)"), 5);
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
    ck_assert_str_eq(test, "Error: Algorithm Size");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterIsValidOperatorFunctionIsPassedOperatorReturnTheNumberOne)
{   
    ck_assert_int_eq(rpnconverter_isvalidoperator('+'), 1);
}
END_TEST
START_TEST(whenRPNConverterIsValidOperatorFunctionIsPassedNonOperatorReturnTheNumberZero)
{   
    ck_assert_int_eq(rpnconverter_isvalidoperator('a'), 0);
}
END_TEST   
START_TEST(whenRPNConverterInfix2RPNOrderOfOperationFunctionIsPassedEmptyInputReturnError)
{   
    char * test = rpnconverter_infix2rpn_orderofoperation(0,5,"");
    ck_assert_str_eq(test, "Error: Algorithm Size");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixGetOperatorsFunctionIsPassedEmptyInputReturnError)
{   
    char * test = rpnconverter_rpn2infix_getoperators("");
    ck_assert_str_eq(test, "Error: Algorithm Size");
    free(test);
}
END_TEST  
START_TEST(whenRPNConverterInfix2RPNStripFunctionIsPassedEmptyInputReturnError)
{   
    char * test = rpnconverter_infix2rpn_strip("");
    ck_assert_str_eq(test, "Error: Algorithm Size");
    free(test);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixSpanFunctionIsPassedEmptyInputReturnError)
{   
    ck_assert_int_eq(rpnconverter_rpn2infix_span(0,0,""), 0);
}
END_TEST
START_TEST(whenRPNConverterCountOperatorsFunctionIsPassedEmptyInputReturnError)
{   
    ck_assert_int_eq(rpnconverter_countoperators(""), 0);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNOrderOfOperationCheckParenthesesFunctionIsPassedEmptyInputReturnError)
{   
    ck_assert_int_eq(rpnconverter_infix2rpn_orderofoperation_checkparentheses(""), 0);
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
    tcase_add_test(tc_core, whenRPNConverterCountOperatorsFunctionIsPassedRPNReturnNumberOfOperators);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixSpanFunctionIsPassedSpanAndRPNReturnSpan);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedRPNReturnIdentifierForRPN);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedInfixReturnIdentifierForInfix);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNGetOperatorArrayFunctionIsPassedInfixWithoutParenthesesReturnAllUsedOperatorsInProperOrder);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNGetOperatorArrayFunctionIsPassedInfixWithParenthesesReturnAllUsedOperatorsInProperOrder);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNOrderOfOperationFunctionIsPassedInfixWithParenthesesReturnAllUsedOperatorsInProperOrder);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNOrderOfOperationCheckParenthesesFunctionIsPassedInfixWithParenthesesReturnNumberOfOpenParentheses);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNGetOperatorArrayFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterMainFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterIsValidOperatorFunctionIsPassedOperatorReturnTheNumberOne);
    tcase_add_test(tc_core, whenRPNConverterIsValidOperatorFunctionIsPassedNonOperatorReturnTheNumberZero);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNOrderOfOperationFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixGetOperatorsFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNStripFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixSpanFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterCountOperatorsFunctionIsPassedEmptyInputReturnError);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNOrderOfOperationCheckParenthesesFunctionIsPassedEmptyInputReturnError);
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