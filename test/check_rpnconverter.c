#include <check.h>
#include "../src/rpnconverter.h"

START_TEST(whenRPNConverterIsPassedOperatorsInInfixItReturnsOperatorsInRPN)
{   
    ck_assert_str_eq(rpnconverter_infix2rpn("a+b"), "ab+");
}
END_TEST
    
Suite * rpn_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RPNConverter");
    
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, whenRPNConverterIsPassedOperatorsInInfixItReturnsOperatorsInRPN);
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