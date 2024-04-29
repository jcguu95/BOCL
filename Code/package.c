#include "object.h"
#include "package.h"
#include "symbol.h"
#include "character.h"
#include "string.h"
#include "cons.h"

/* DEBUG */
#include <stdio.h>
#include "print.h"
#include "stream.h"

DEFINE_CLASS(class_package);

object package_common_lisp;
object package_keyword;
object package_common_lisp_user;
object current_package;

static int package_initialized_p = 0;
static int package_initialized_2_p = 0;

typedef struct package_rack *package_rack;

struct package_rack
{
  struct rack prefix;
  object name;
  object nicknames;
  object used_packages;
  object internal_symbols;
  object external_symbols;
};

static int package_rack_size = sizeof(struct package_rack);

void
set_package_name(object package, object string)
{
  package_rack r = (package_rack) rack_of(package);
  r -> name = string;
}

void
set_package_nicknames(object package, object list)
{
  package_rack r = (package_rack) rack_of(package);
  r -> nicknames = list;
}

void
make_common_lisp_package()
{
  /* NOTE This is almost the same as the subroutine of the function
     make_package. We had to do this because the symbol CL:NIL (symbol_nil) is
     used to represent the empty list, which is used when the CL package is
     constructed.*/
  object package = make_object();
  package_rack r = (package_rack) malloc(package_rack_size);

  /* NOTE Global definition of symbol_nil. */
  symbol_nil = cfun_symbol_to_symbol("NIL", package);
  /* FIXME How to write it in a better style? */

  set_class_of(package, class_package);
  set_rack_of(package, (rack) r);
  r -> used_packages = symbol_nil;
  r -> internal_symbols = symbol_nil;
  r -> external_symbols = symbol_nil;
  set_package_name(package, cfun_string_to_string("COMMON-LISP"));
  set_package_nicknames(package, cfun_cons(cfun_string_to_string("CL"), symbol_nil));
  package_common_lisp = package;
}

object
make_package()
{
  /* NOTE Do you use this to make the COMMON-LISP package. */
  object package = make_object();
  package_rack r = (package_rack) malloc(package_rack_size);
  r -> used_packages = symbol_nil;
  r -> internal_symbols = symbol_nil;
  r -> external_symbols = symbol_nil;
  set_class_of(package, class_package);
  set_rack_of(package, (rack) r);
  return package;
}

void
make_keyword_package()
{
  package_keyword = make_package();
  set_package_name(package_keyword, cfun_string_to_string("KEYWORD"));
}

void
make_common_lisp_user_package()
{
  package_common_lisp_user = make_package();
  set_package_name(package_common_lisp_user, cfun_string_to_string("COMMON-LISP-USER"));
  set_package_nicknames(package_common_lisp_user, cfun_cons(cfun_string_to_string("CL-USER"), symbol_nil));
}

void
ensure_package_initialized(void)
{
  if (package_initialized_p) {
    return;
  } 
  make_common_lisp_package();
  make_keyword_package();
  make_common_lisp_user_package();
  current_package = package_common_lisp;
  package_initialized_p = 1;
}

object
cfun_packagep(object maybe_package)
{
  return class_of(maybe_package) == class_package ? symbol_t : symbol_nil;
}

object
cfun_package_name(object maybe_package)
{
  assert(cfun_packagep(maybe_package) == symbol_t);
  return ((package_rack) rack_of(maybe_package)) -> name;
}

object
cfun_package_nicknames(object maybe_package)
{
  assert(cfun_packagep(maybe_package) == symbol_t);
  return ((package_rack) rack_of(maybe_package)) -> nicknames;
}

object
cfun_package_external_symbols(object package)
{
  package_rack r = (package_rack) rack_of(package);
  return r -> external_symbols;
}

object
cfun_package_internal_symbols(object package)
{
  package_rack r = (package_rack) rack_of(package);
  return r -> internal_symbols;
}

extern void
package_add_external_symbol(object package, object symbol)
{
  package_rack r = (package_rack) rack_of(package);
  r -> external_symbols = cfun_cons(symbol, r -> external_symbols);
}

extern void
package_add_internal_symbol(object package, object symbol)
{
  package_rack r = (package_rack) rack_of(package);
  r -> internal_symbols = cfun_cons(symbol, r -> internal_symbols);
}

void
ensure_package_initialized_2(void)
{
  if (package_initialized_2_p) {
    return;
  }
  ensure_symbol_initialized();
  object symbols[] = {
    symbol_abort, symbol_abs, symbol_acons, symbol_acos, symbol_acosh, symbol_add_method, symbol_adjoin, symbol_adjust_array, symbol_adjustable_array_p, symbol_allocate_instance, 
    symbol_alpha_char_p, symbol_alphanumericp, symbol_and, symbol_append, symbol_apply, symbol_apropos, symbol_apropos_list, symbol_aref, symbol_arithmetic_error, symbol_arithmetic_error_operands, 
    symbol_arithmetic_error_operation, symbol_array, symbol_array_dimension, symbol_array_dimension_limit, symbol_array_dimensons, symbol_array_displacement, symbol_array_element_type, symbol_array_has_fill_pointer_p, symbol_array_in_bounds_p, symbol_array_rank, 
    symbol_array_rank_limit, symbol_array_row_major_index, symbol_array_total_size, symbol_array_total_size_limit, symbol_arrayp, symbol_ash, symbol_asin, symbol_asinh, symbol_assert, symbol_assoc, 
    symbol_assoc_if, symbol_assoc_if_not, symbol_atan, symbol_atanh, symbol_atom, symbol_base_char, symbol_base_string, symbol_bignum, symbol_bit, symbol_bit_and, 
    symbol_bit_andc1, symbol_bit_andc2, symbol_bit_eqv, symbol_bit_ior, symbol_bit_nand, symbol_bit_nor, symbol_bit_not, symbol_bit_orc1, symbol_bit_orc2, symbol_bit_vector, 
    symbol_bit_vector_p, symbol_bit_xor, symbol_block, symbol_boole, symbol_boole_1, symbol_boole_2, symbol_boole_and, symbol_boole_andc1, symbol_boole_andc2, symbol_boole_c1, 
    symbol_boole_c2, symbol_boole_clr, symbol_boole_eqv, symbol_boole_ior, symbol_boole_nand, symbol_boole_nor, symbol_boole_orc1, symbol_boole_orc2, symbol_boole_set, symbol_boole_xor, 
    symbol_boolean, symbol_both_case_p, symbol_boundp, symbol_break, symbol_broadcast_stream, symbol_broadcast_stream_streams, symbol_built_in_class, symbol_butlast, symbol_byte, symbol_byte_position, 
    symbol_byte_size, symbol_caaaar, symbol_caaadr, symbol_caaar, symbol_caadar, symbol_caaddr, symbol_caadr, symbol_caar, symbol_cadaar, symbol_cadadr, 
    symbol_cadar, symbol_caddar, symbol_cadddr, symbol_caddr, symbol_cadr, symbol_call_arguments_limit, symbol_call_method, symbol_call_next_method, symbol_car, symbol_case, 
    symbol_catch, symbol_ccase, symbol_cdaaar, symbol_cdaadr, symbol_cdaar, symbol_cdadar, symbol_cdaddr, symbol_cdadr, symbol_cdar, symbol_cddaar, 
    symbol_cddadr, symbol_cddar, symbol_cdddar, symbol_cddddr, symbol_cdddr, symbol_cddr, symbol_cdr, symbol_ceiling, symbol_cell_error, symbol_cell_error_name, 
    symbol_cerror, symbol_change_class, symbol_char, symbol_char_code, symbol_char_code_limit, symbol_char_downcase, symbol_char_equal, symbol_char_greaterp, symbol_char_int, symbol_char_lessp, 
    symbol_char_name, symbol_char_not_equal, symbol_char_not_greaterp, symbol_char_not_lessp, symbol_char_upcase, symbol_char_not_equal_sign, symbol_char_less_sign, symbol_char_less_or_equal_sign, symbol_char_equal_sign, symbol_char_greater_sign, 
    symbol_char_greater_or_equal_sign, symbol_character, symbol_characterp, symbol_check_type, symbol_cis, symbol_class, symbol_class_name, symbol_class_of, symbol_clear_input, symbol_clear_output, 
    symbol_close, symbol_clrhash, symbol_code_char, symbol_coerce, symbol_compilation_speed, symbol_compile, symbol_compile_file, symbol_compile_file_pathname, symbol_compiled_function, symbol_compiled_function_p, 
    symbol_compiler_macro, symbol_compiler_macro_function, symbol_complement, symbol_complex, symbol_complexp, symbol_compute_applicable_methods, symbol_compute_restarts, symbol_concatenate, symbol_concatenated_stream, symbol_concatenated_stream_streams, 
    symbol_cond, symbol_condition, symbol_conjugate, symbol_cons, symbol_consp, symbol_constantly, symbol_constantp, symbol_continue, symbol_control_error, symbol_copy_alist, 
    symbol_copy_list, symbol_copy_pprint_dispatch, symbol_copy_readtable, symbol_copy_seq, symbol_copy_structure, symbol_copy_symbol, symbol_copy_tree, symbol_cos, symbol_cosh, symbol_count, 
    symbol_count_if, symbol_count_if_not, symbol_ctypecase, symbol_debug, symbol_decf, symbol_declaim, symbol_declaration, symbol_declare, symbol_decode_float, symbol_decode_universal_time, 
    symbol_defclass, symbol_defconstant, symbol_defgeneric, symbol_define_compiler_macro, symbol_define_condition, symbol_define_method_combination, symbol_define_modify_macro, symbol_define_setf_expander, symbol_define_symbol_macro, symbol_defmacro, 
    symbol_defmethod, symbol_defpackage, symbol_defparameter, symbol_defsetf, symbol_defstruct, symbol_deftype, symbol_defun, symbol_defvar, symbol_delete, symbol_delete_duplicates, 
    symbol_delete_file, symbol_delete_if, symbol_delete_if_not, symbol_delete_package, symbol_denominator, symbol_deposit_field, symbol_describe, symbol_describe_object, symbol_destructuring_bind, symbol_digit_char, 
    symbol_digit_char_p, symbol_directory, symbol_directory_namestring, symbol_disassemble, symbol_division_by_zero, symbol_do, symbol_do_star, symbol_do_all_symbols, symbol_do_external_symbols, symbol_do_symbols, 
    symbol_documentation, symbol_dolist, symbol_dotimes, symbol_double_float, symbol_double_float_epsilon, symbol_double_float_negative_epsilon, symbol_dpb, symbol_dribble, symbol_dynamic_extent, symbol_ecase, 
    symbol_echo_stream, symbol_echo_stream_input_stream, symbol_echo_stream_output_stream, symbol_ed, symbol_eighth, symbol_elt, symbol_encode_universal_time, symbol_end_of_file, symbol_endp, symbol_enough_namestring, 
    symbol_ensure_directories_exist, symbol_ensure_generic_function, symbol_eq, symbol_eql, symbol_equal, symbol_equalp, symbol_error, symbol_etypecase, symbol_eval, symbol_eval_when, 
    symbol_evenp, symbol_every, symbol_exp, symbol_export, symbol_expt, symbol_extended_char, symbol_fboundp, symbol_fceiling, symbol_fdefinition, symbol_ffloor, 
    symbol_fifth, symbol_file_author, symbol_file_error, symbol_file_error_pathname, symbol_file_length, symbol_file_namestring, symbol_file_position, symbol_file_stream, symbol_file_string_length, symbol_file_write_date, 
    symbol_fill, symbol_fill_pointer, symbol_find, symbol_find_all_symbols, symbol_find_class, symbol_find_if, symbol_find_if_not, symbol_find_method, symbol_find_package, symbol_find_restart, 
    symbol_find_symbol, symbol_finish_output, symbol_first, symbol_fixnum, symbol_flet, symbol_float, symbol_float_digits, symbol_float_precision, symbol_float_radix, symbol_float_sign, 
    symbol_floating_point_inexact, symbol_floating_point_invalid_operation, symbol_floating_point_overflow, symbol_floating_point_underflow, symbol_floatp, symbol_floor, symbol_fmakunbound, symbol_force_output, symbol_format, symbol_formatter, 
    symbol_fourth, symbol_fresh_line, symbol_fround, symbol_ftruncate, symbol_ftype, symbol_funcall, symbol_function, symbol_function_keywords, symbol_function_lambda_expression, symbol_functionp, 
    symbol_gcd, symbol_generic_function, symbol_gensym, symbol_gentemp, symbol_get, symbol_get_decoded_time, symbol_get_dispatch_macro_character, symbol_get_internal_real_time, symbol_get_internal_run_time, symbol_get_macro_character, 
    symbol_get_output_stream_string, symbol_get_properties, symbol_get_setf_expansion, symbol_get_universal_time, symbol_getf, symbol_gethash, symbol_go, symbol_graphic_char_p, symbol_handler_bind, symbol_handler_case, 
    symbol_hash_table, symbol_hash_table_count, symbol_hash_table_p, symbol_hash_table_rehash_size, symbol_hash_table_rehash_threshold, symbol_hash_table_size, symbol_hash_table_test, symbol_host_namestring, symbol_identity, symbol_if, 
    symbol_ignorable, symbol_ignore, symbol_ignore_errors, symbol_imagpart, symbol_import, symbol_in_package, symbol_incf, symbol_initialize_instance, symbol_inline, symbol_input_stream_p, 
    symbol_inspect, symbol_integer, symbol_integer_decode_float, symbol_integer_length, symbol_integerp, symbol_interactive_stream_p, symbol_intern, symbol_internal_time_units_per_second, symbol_intersection, symbol_invalid_method_error, 
    symbol_invoke_debugger, symbol_invoke_restart, symbol_invoke_restart_interactively, symbol_isqrt, symbol_keyword, symbol_keywordp, symbol_labels, symbol_lambda, symbol_lambda_list_keywords, symbol_lambda_parameters_limit, 
    symbol_last, symbol_lcm, symbol_ldb, symbol_ldb_test, symbol_ldiff, symbol_least_negative_double_float, symbol_least_negative_long_float, symbol_least_negative_normalized_double_float, symbol_least_negative_normalized_long_float, symbol_least_negative_normalized_short_float, 
    symbol_least_negative_normalized_single_float, symbol_least_negative_short_float, symbol_least_negative_single_float, symbol_least_positive_double_float, symbol_least_positive_long_float, symbol_least_positive_normalized_double_float, symbol_least_positive_normalized_long_float, symbol_least_positive_normalized_short_float, symbol_least_positive_normalized_single_float, symbol_least_positive_short_float, 
    symbol_least_positive_single_float, symbol_length, symbol_let, symbol_let_star, symbol_lisp_implementation_type, symbol_lisp_implementation_version, symbol_list, symbol_list_star, symbol_list_all_packages, symbol_list_length, 
    symbol_listen, symbol_listp, symbol_load, symbol_load_logical_pathname_translations, symbol_load_time_value, symbol_locally, symbol_log, symbol_logand, symbol_logandc1, symbol_logandc2, 
    symbol_logbitp, symbol_logcount, symbol_logeqv, symbol_logical_pathname, symbol_logical_pathname_translations, symbol_logior, symbol_lognand, symbol_lognor, symbol_lognot, symbol_logorc1, 
    symbol_logorc2, symbol_logtest, symbol_logxor, symbol_long_float, symbol_long_float_epsilon, symbol_long_float_negative_epsilon, symbol_long_site_name, symbol_loop, symbol_loop_finish, symbol_lower_case_p, 
    symbol_machine_instance, symbol_machine_type, symbol_machine_version, symbol_macro_function, symbol_macroexpand, symbol_macroexpand_1, symbol_macrolet, symbol_make_array, symbol_make_broadcast_stream, symbol_make_concatenated_stream, 
    symbol_make_condition, symbol_make_dispatch_macro_character, symbol_make_echo_stream, symbol_make_hash_table, symbol_make_instance, symbol_make_instances_obsolete, symbol_make_list, symbol_make_load_form, symbol_make_load_form_saving_slots, symbol_make_method, 
    symbol_make_package, symbol_make_pathname, symbol_make_random_state, symbol_make_sequence, symbol_make_string, symbol_make_string_input_stream, symbol_make_string_output_stream, symbol_make_symbol, symbol_make_synonym_stream, symbol_make_two_way_stream, 
    symbol_makunbound, symbol_map, symbol_map_into, symbol_mapc, symbol_mapcan, symbol_mapcar, symbol_mapcon, symbol_maphash, symbol_mapl, symbol_maplist, 
    symbol_mask_field, symbol_max, symbol_member, symbol_member_if, symbol_member_if_not, symbol_merge, symbol_merge_pathnames, symbol_method, symbol_method_combination, symbol_method_combination_error, 
    symbol_method_qualifiers, symbol_min, symbol_minusp, symbol_mismatch, symbol_mod, symbol_most_negative_double_float, symbol_most_negative_fixnum, symbol_most_negative_long_float, symbol_most_negative_short_float, symbol_most_negative_single_float, 
    symbol_most_positive_double_float, symbol_most_positive_fixnum, symbol_most_positive_long_float, symbol_most_positive_short_float, symbol_most_positive_single_float, symbol_muffle_warning, symbol_multiple_value_bind, symbol_multiple_value_call, symbol_multiple_value_list, symbol_multiple_value_prog1, 
    symbol_multiple_value_setq, symbol_multiple_values_limit, symbol_name_char, symbol_namestring, symbol_nbutlast, symbol_nconc, symbol_next_method_p, symbol_nil, symbol_nintersection, symbol_ninth, 
    symbol_no_applicable_method, symbol_no_next_method, symbol_not, symbol_notany, symbol_notevery, symbol_notinline, symbol_nreconc, symbol_nreverse, symbol_nset_difference, symbol_nset_exclusive_or, 
    symbol_nstring_capitalize, symbol_nstring_downcase, symbol_nstring_upcase, symbol_nsublis, symbol_nsubst, symbol_nsubst_if, symbol_nsubst_if_not, symbol_nsubstitute, symbol_nsubstitute_if, symbol_nsubstitute_if_not, 
    symbol_nth, symbol_nth_value, symbol_nthcdr, symbol_null, symbol_number, symbol_numberp, symbol_numerator, symbol_nunion, symbol_oddp, symbol_open, 
    symbol_open_stream_p, symbol_optimize, symbol_or, symbol_otherwise, symbol_output_stream_p, symbol_package, symbol_package_error, symbol_package_error_package, symbol_package_name, symbol_package_nicknames, 
    symbol_package_shadowing_symbols, symbol_package_use_list, symbol_package_used_by_list, symbol_packagep, symbol_pairlis, symbol_parse_error, symbol_parse_integer, symbol_parse_namestring, symbol_pathname, symbol_pathname_device, 
    symbol_pathname_directory, symbol_pathname_host, symbol_pathname_match_p, symbol_pathname_name, symbol_pathname_type, symbol_pathname_version, symbol_pathnamep, symbol_peek_char, symbol_phase, symbol_pi, 
    symbol_plusp, symbol_pop, symbol_position, symbol_position_if, symbol_position_if_not, symbol_pprint, symbol_pprint_dispatch, symbol_pprint_exit_if_list_exhausted, symbol_pprint_fill, symbol_pprint_indent, 
    symbol_pprint_linear, symbol_pprint_logical_block, symbol_pprint_newline, symbol_pprint_pop, symbol_pprint_tab, symbol_pprint_tabular, symbol_prin1, symbol_prin1_to_string, symbol_princ, symbol_princ_to_string, 
    symbol_print, symbol_print_not_readable, symbol_print_not_readable_object, symbol_print_object, symbol_print_unreadable_object, symbol_probe_file, symbol_proclaim, symbol_prog, symbol_prog_star, symbol_prog1, 
    symbol_prog2, symbol_progn, symbol_program_error, symbol_progv, symbol_provide, symbol_psetf, symbol_psetq, symbol_push, symbol_pushnew, symbol_quote, 
    symbol_random, symbol_random_state, symbol_random_state_p, symbol_rassoc, symbol_rassoc_if, symbol_rassoc_if_not, symbol_ratio, symbol_rational, symbol_rationalize, symbol_rationalp, 
    symbol_read, symbol_read_byte, symbol_read_char, symbol_read_char_no_hang, symbol_read_delimited_list, symbol_read_from_string, symbol_read_line, symbol_read_preserving_whitespace, symbol_read_sequence, symbol_reader_error, 
    symbol_readtable, symbol_readtable_case, symbol_readtablep, symbol_real, symbol_realp, symbol_realpart, symbol_reduce, symbol_reinitialize_instance, symbol_rem, symbol_remf, 
    symbol_remhash, symbol_remove, symbol_remove_duplicates, symbol_remove_if, symbol_remove_if_not, symbol_remove_method, symbol_remprop, symbol_rename_file, symbol_rename_package, symbol_replace, 
    symbol_require, symbol_rest, symbol_restart, symbol_restart_bind, symbol_restart_case, symbol_restart_name, symbol_return, symbol_return_from, symbol_revappend, symbol_reverse, 
    symbol_room, symbol_rotatef, symbol_round, symbol_row_major_aref, symbol_rplaca, symbol_rplacd, symbol_safety, symbol_satisfies, symbol_sbit, symbol_scale_float, 
    symbol_schar, symbol_search, symbol_second, symbol_sequence, symbol_serious_condition, symbol_set, symbol_set_difference, symbol_set_dispatch_macro_character, symbol_set_exclusive_or, symbol_set_macro_character, 
    symbol_set_pprint_dispatch, symbol_set_syntax_from_char, symbol_setf, symbol_setq, symbol_seventh, symbol_shadow, symbol_shadowing_import, symbol_shared_initialize, symbol_shiftf, symbol_short_float, 
    symbol_short_float_epsilon, symbol_short_float_negative_epsilon, symbol_short_site_name, symbol_signal, symbol_signed_byte, symbol_signum, symbol_simple_array, symbol_simple_base_string, symbol_simple_bit_vector, symbol_simple_bit_vector_p, 
    symbol_simple_condition, symbol_simple_condition_format_arguments, symbol_simple_condition_format_control, symbol_simple_error, symbol_simple_string, symbol_simple_string_p, symbol_simple_type_error, symbol_simple_vector, symbol_simple_vector_p, symbol_simple_warning, 
    symbol_sin, symbol_single_float, symbol_single_float_epsilon, symbol_single_float_negative_epsilon, symbol_sinh, symbol_sixth, symbol_sleep, symbol_slot_boundp, symbol_slot_exists_p, symbol_slot_makunbound, 
    symbol_slot_missing, symbol_slot_unbound, symbol_slot_value, symbol_software_type, symbol_software_version, symbol_some, symbol_sort, symbol_space, symbol_special, symbol_special_operator_p, 
    symbol_speed, symbol_sqrt, symbol_stable_sort, symbol_standard, symbol_standard_char, symbol_standard_char_p, symbol_standard_class, symbol_standard_generic_function, symbol_standard_method, symbol_standard_object, 
    symbol_step, symbol_storage_condition, symbol_store_value, symbol_stream, symbol_stream_element_type, symbol_stream_error, symbol_stream_error_stream, symbol_stream_external_format, symbol_streamp, symbol_string, 
    symbol_string_capitalize, symbol_string_downcase, symbol_string_equal, symbol_string_greaterp, symbol_string_left_trim, symbol_string_lessp, symbol_string_not_equal, symbol_string_not_greaterp, symbol_string_not_lessp, symbol_string_right_trim, 
    symbol_string_stream, symbol_string_trim, symbol_string_upcase, symbol_string_slash_equal, symbol_string_less_than_sign, symbol_string_less_than_or_equal_sign, symbol_string_equal_sign, symbol_string_greater_than_sign, symbol_string_greater_than_or_equal_sign, symbol_stringp, 
    symbol_structure, symbol_structure_class, symbol_structure_object, symbol_style_warning, symbol_sublis, symbol_subseq, symbol_subsetp, symbol_subst, symbol_subst_if, symbol_subst_if_not, 
    symbol_substitute, symbol_substitute_if, symbol_substitute_if_not, symbol_subtypep, symbol_svref, symbol_sxhash, symbol_symbol, symbol_symbol_function, symbol_symbol_macrolet, symbol_symbol_name, 
    symbol_symbol_package, symbol_symbol_plist, symbol_symbol_value, symbol_symbolp, symbol_synonym_stream, symbol_synonym_stream_symbol, symbol_t, symbol_tagbody, symbol_tailp, symbol_tan, 
    symbol_tanh, symbol_tenth, symbol_terpri, symbol_the, symbol_third, symbol_throw, symbol_time, symbol_trace, symbol_translate_logical_pathname, symbol_translate_pathname, 
    symbol_tree_equal, symbol_truename, symbol_truncate, symbol_two_way_stream, symbol_two_way_stream_input_stream, symbol_two_way_stream_output_stream, symbol_type, symbol_type_error, symbol_type_error_datum, symbol_type_error_expected_type, 
    symbol_type_of, symbol_typecase, symbol_typep, symbol_unbound_slot, symbol_unbound_slot_instance, symbol_unbound_variable, symbol_undefined_function, symbol_unexport, symbol_unintern, symbol_union, 
    symbol_unless, symbol_unread_char, symbol_unsigned_byte, symbol_untrace, symbol_unuse_package, symbol_unwind_protect, symbol_update_instance_for_different_class, symbol_update_instance_for_redefined_class, symbol_upgraded_array_element_type, symbol_upgraded_complex_part_type, 
    symbol_upper_case_p, symbol_use_package, symbol_use_value, symbol_user_homedir_pathname, symbol_values, symbol_values_list, symbol_variable, symbol_vector, symbol_vector_pop, symbol_vector_push, 
    symbol_vector_push_extend, symbol_vectorp, symbol_warn, symbol_warning, symbol_when, symbol_wild_pathname_p, symbol_with_accessors, symbol_with_compilation_unit, symbol_with_condition_restarts, symbol_with_hash_table_iterator, 
    symbol_with_input_from_string, symbol_with_open_file, symbol_with_open_stream, symbol_with_output_to_string, symbol_with_package_iterator, symbol_with_simple_restart, symbol_with_slots, symbol_with_standard_io_syntax, symbol_write, symbol_write_byte, 
    symbol_write_char, symbol_write_line, symbol_write_sequence, symbol_write_string, symbol_write_to_string, symbol_y_or_n_p, symbol_yes_or_no_p, symbol_zerop, symbol_ampersand_allow_other_keys, symbol_ampersand_aux, 
    symbol_ampersand_body, symbol_ampersand_environment, symbol_ampersand_key, symbol_ampersand_optional, symbol_ampersand_rest, symbol_ampersand_whole, symbol_star, symbol_star_star, symbol_star_star_star, symbol_star_break_on_signals_star, 
    symbol_star_compile_file_pathname_star, symbol_star_compile_file_truename_star, symbol_star_compile_print_star, symbol_star_compile_verbose_star, symbol_star_debug_io_star, symbol_star_debugger_hook_star, symbol_star_default_pathname_defaults_star, symbol_star_error_output_star, symbol_star_features_star, symbol_star_gensym_counter_star, 
    symbol_star_load_pathname_star, symbol_star_load_print_star, symbol_star_load_truename_star, symbol_star_load_verbose_star, symbol_star_macroexpand_hook_star, symbol_star_modules_star, symbol_star_package_star, symbol_star_print_array_star, symbol_star_print_base_star, symbol_star_print_case_star, 
    symbol_star_print_circle_star, symbol_star_print_escape_star, symbol_star_print_gensym_star, symbol_star_print_length_star, symbol_star_print_level_star, symbol_star_print_lines_star, symbol_star_print_miser_width_star, symbol_star_print_pprint_dispatch_star, symbol_star_print_pretty_star, symbol_star_print_radix_star, 
    symbol_star_print_readably_star, symbol_star_print_right_margin_star, symbol_star_query_io_star, symbol_star_random_state_star, symbol_star_read_base_star, symbol_star_read_default_float_format_star, symbol_star_read_eval_star, symbol_star_read_suppress_star, symbol_star_readtable_star, symbol_star_standard_input_star, 
    symbol_star_standard_output_star, symbol_star_terminal_io_star, symbol_star_trace_output_star, symbol_plus, symbol_plus_plus, symbol_plus_plus_plus, symbol_minus, symbol_slash, symbol_slash_slash, symbol_slash_slash_slash, 
    symbol_slash_equal, symbol_one_plus, symbol_one_minus, symbol_less_than_sign, symbol_less_than_or_equal_sign, symbol_equal_sign, symbol_greater_than_sign, symbol_greater_than_or_equal_sign, 
  };
  int size = sizeof(symbols) / sizeof(symbols[0]);
  for (int i = 0; i < size; i++) {
    object symbol = symbols[i];
    object name = cfun_symbol_name(symbol);
    object result = cfun_find_symbol_in_package(name, package_common_lisp);
    if (result == 0) {
      package_add_external_symbol(package_common_lisp, symbol);
    } 
  }
  package_initialized_2_p = 1;
}

object
cfun_find_symbol_in_list(object string, object list)
{
  assert(cfun_stringp(string));
  assert(cfun_listp(list));
  for (object rest = list; rest != symbol_nil; rest = cfun_cdr(rest)) {
    object symbol = cfun_car(rest);
    object name = cfun_symbol_name(symbol);
    if (cfun_string_equal_sign(name, string) == symbol_t) {
      return symbol;
    }
  }
  return 0;
}

object
cfun_find_symbol_in_package(object string, object package)
{
  package_rack r = (package_rack) rack_of(package);
  object symbol;
  symbol = cfun_find_symbol_in_list(string, r -> external_symbols);
  if (symbol != 0) {
    return symbol;
  }
  symbol = cfun_find_symbol_in_list(string, r -> internal_symbols);
  if (symbol != 0) {
    return symbol;
  }
  for (object restp = r -> used_packages;
       restp != symbol_nil;
       restp = cfun_cdr(restp)) {
    object p = cfun_car(restp);
    package_rack r = (package_rack) rack_of(p);
    symbol = cfun_find_symbol_in_list(string, r -> external_symbols);
    if (symbol != 0) {
      return symbol;
    }
  }
  return 0;
}

object
cfun_intern(object string, object package)
{
  object symbol = cfun_find_symbol_in_package(string, package);
  if (symbol != 0) {
    return symbol;
  } else {
    symbol = cfun_make_symbol(string, package);
    package_add_internal_symbol(package, symbol);
    return symbol;
  }
}

