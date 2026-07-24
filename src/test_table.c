#include <check.h>
#include <config.h>
#include <table.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(test_table_init_empty) {
    table_t *t = table_init();
    ck_assert_int_eq(table_size(t), 0);
    table_free(t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

START_TEST(test_table_insert_lookup_remove) {
    table_t *t = table_init();
    table_insert(t, "key1", "value1");
    ck_assert_str_eq(table_lookup(t, "key1"), "value1");
    table_remove(t, "key1");
    ck_assert_ptr_eq(table_lookup(t, "key1"), NULL);
    table_free(t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

START_TEST(test_table_insert_conflict) {
    table_t *t = table_init();
    table_insert(t, "key1", "value1");
    table_insert(t, "key1", "value2");
    ck_assert_str_eq(table_lookup(t, "key1"), "value2");
    table_remove(t, "key1");
    ck_assert_ptr_eq(table_lookup(t, "key1"), NULL);
    table_free(t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

START_TEST(test_table_lookup_nonexistent) {
    table_t *t = table_init();
    ck_assert_ptr_eq(table_lookup(t, "nonexistent"), NULL);
    table_free(t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

Suite *table_suite(void) {
    Suite *s = suite_create("Table");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_table_init_empty);
    tcase_add_test(tc_core, test_table_insert_lookup_remove);
    tcase_add_test(tc_core, test_table_insert_conflict);
    tcase_add_test(tc_core, test_table_lookup_nonexistent);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    SRunner *sr = srunner_create(table_suite());
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}