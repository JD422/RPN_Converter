#include <check.h>
#include "../src/rpnconverter.h"

START_TEST(whenRPNConverterMainFunctionIsPassedEitherRPNorInfixReturnConvertedAlg)
{   
    char * testOne = rpnconverter("ab+");
    ck_assert_str_eq(testOne, "(a+b)");
    free(testOne);
    char * testTwo = rpnconverter("a+b");
    ck_assert_str_eq(testTwo, "ab+");
    free(testTwo);
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNFunctionIsPassedInfixReturnItInRPN)
{   
    char * testOne = rpnconverter_infix2rpn("a+b");
    ck_assert_str_eq(testOne, "ab+");
    free(testOne);
    char * testTwo = rpnconverter_infix2rpn("a+b-c*d");
    ck_assert_str_eq(testTwo, "ab+cd*-");
    free(testTwo);
    char * testThree = rpnconverter_infix2rpn("a/b+c^d+f");
    ck_assert_str_eq(testThree, "ab/cd^+f+");
    free(testThree);
    char * testFour = rpnconverter_infix2rpn("(a*b^((c+d)/(e-f))^g)");
    ck_assert_str_eq(testFour, "abcd+^*ef-/g^");
    free(testFour);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedRPNReturnItInInfix)
{   
    char * testOne = rpnconverter_rpn2infix("ab+");
    ck_assert_str_eq(testOne, "(a+b)");
    free(testOne);
    char * testTwo = rpnconverter_rpn2infix("ab+cd*-");
    ck_assert_str_eq(testTwo, "((a+b)-(c*d))");
    free(testTwo);
    char * testThree = rpnconverter_rpn2infix("ab/cd^+f+");
    ck_assert_str_eq(testThree, "(((a/b)+(c^d))+f)");
    free(testThree);
    char * testFour = rpnconverter_rpn2infix("ag+ba-c+cedf^*+^*");
    ck_assert_str_eq(testFour, "((a+g)*(((b-a)+c)^(c+(e*(d^f)))))");
    free(testFour);
}
END_TEST
START_TEST(whenRPNConverterAutoselectFunctionIsPassedAlgorithmReturnIdentifierForCorrectAlgorithm)
{   
    ck_assert_int_eq(rpnconverter_autoselect("ab+"), 1);
    ck_assert_int_eq(rpnconverter_autoselect("a+b"), 2);
}
END_TEST
START_TEST(whenRPNConverterOrderOfOperationFunctionIsPassedAlgorithmReturnAllUsedOperatorsInProperOrder)
{   
    char * testOne = rpnconverter_orderOfOperation("a*b^c+d/e-f^g");
    ck_assert_str_eq(testOne, "^^*/+-");
    free(testOne);
    char * testTwo = rpnconverter_orderOfOperation("(a*b^((c+d)/(e-f))^g)");
    ck_assert_str_eq(testTwo, "+-/^^*");
    free(testTwo);
}
END_TEST

    
Suite * rpn_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RPNConverter");
    
    tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, whenRPNConverterMainFunctionIsPassedEitherRPNorInfixReturnConvertedAlg);
    tcase_add_test(tc_core, whenRPNConverterInfix2RPNFunctionIsPassedInfixReturnItInRPN);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedRPNReturnItInInfix);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedAlgorithmReturnIdentifierForCorrectAlgorithm);
    tcase_add_test(tc_core, whenRPNConverterOrderOfOperationFunctionIsPassedAlgorithmReturnAllUsedOperatorsInProperOrder);
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