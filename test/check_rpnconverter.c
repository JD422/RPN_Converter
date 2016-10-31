#include <check.h>
#include "../src/rpnconverter.h"

START_TEST(whenRPNConverterMainFunctionIsPassedEitherRPNorInfixReturnConvertedAlg)
{   
    ck_assert_str_eq(rpnconverter("ab+"), "(a+b)");
    ck_assert_str_eq(rpnconverter("a+b"), "ab+");
}
END_TEST
START_TEST(whenRPNConverterInfix2RPNFunctionIsPassedInfixReturnItInRPN)
{   
    ck_assert_str_eq(rpnconverter_infix2rpn("a+b"), "ab+");
    ck_assert_str_eq(rpnconverter_infix2rpn("a+b-c*d"), "ab+cd*-");
    ck_assert_str_eq(rpnconverter_infix2rpn("a/b+c^d+f"), "ab/cd^+f+");
    ck_assert_str_eq(rpnconverter_infix2rpn("(a*b^((c+d)/(e-f))^g)"), "abcd+^*ef-/g^");
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedRPNReturnItInInfix)
{   
    ck_assert_str_eq(rpnconverter_rpn2infix("ab+"), "(a+b)");
    ck_assert_str_eq(rpnconverter_rpn2infix("ab+cd*-"), "((a+b)-(c*d))");
    ck_assert_str_eq(rpnconverter_rpn2infix("ab/cd^+f+"), "(((a/b)+(c^d))+f)");
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedRPNReturnItInInfixAdvanced)
{   
    ck_assert_str_eq(rpnconverter_rpn2infix("ag+ba-c+cedf^*+^*"), "((a+g)*(((b-a)+c)^(c+(e*(d^f)))))");
}
END_TEST
START_TEST(whenRPNConverterAutoselectFunctionIsPassedInfixReturnIdentifierForInfix)
{   
    ck_assert_int_eq(rpnconverter_autoselect("a+b"), 2);
}
END_TEST
START_TEST(whenRPNConverterAutoselectFunctionIsPassedRPNReturnIdentifierForRPN)
{   
    ck_assert_int_eq(rpnconverter_autoselect("ab+"), 1);
}
END_TEST
START_TEST(whenRPNConverterOrderOfOperationFunctionIsPassedAlgorithmReturnAllUsedOperatorsInProperOrder)
{   
    ck_assert_str_eq(rpnconverter_orderOfOperation("a*b^c+d/e-f^g"), "^^*/+-");
    ck_assert_str_eq(rpnconverter_orderOfOperation("(a*b^((c+d)/(e-f))^g)"), "+-/^^*");
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
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedRPNReturnItInInfixAdvanced);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedInfixReturnIdentifierForInfix);
    tcase_add_test(tc_core, whenRPNConverterAutoselectFunctionIsPassedRPNReturnIdentifierForRPN);
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