#include <check.h>
#include "../src/rpnconverter.h"

START_TEST(whenRPNConverterIsPassedOperatorsInInfixItReturnsOperatorsInRPN)
{   
    ck_assert_str_eq(rpnconverter_infix2rpn("a+b"), "ab+");
}
END_TEST
START_TEST(whenRPNConverterIsPassedInfixNotationReturnIdentifierForInfixNotation)
{   
    ck_assert_int_eq(rpnconverter_autoselect("a+b"), 2);
}
END_TEST
START_TEST(whenRPNConverterIsPassedRPNReturnIdentifierForRPN)
{   
    ck_assert_int_eq(rpnconverter_autoselect("ab+"), 1);
}
END_TEST
START_TEST(whenRPNConverterRPN2InfixFunctionIsPassedRPNReturnItInInfix)
{   
    ck_assert_str_eq(rpnconverter_rpn2infix("ab+"), "a+b");
}
END_TEST
    
Suite * rpn_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RPNConverter");
    
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, whenRPNConverterIsPassedOperatorsInInfixItReturnsOperatorsInRPN);
    tcase_add_test(tc_core, whenRPNConverterIsPassedInfixNotationReturnIdentifierForInfixNotation);
    tcase_add_test(tc_core, whenRPNConverterIsPassedRPNReturnIdentifierForRPN);
    tcase_add_test(tc_core, whenRPNConverterRPN2InfixFunctionIsPassedRPNReturnItInInfix);
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