#include "eif_eiffel.h"
#include "eif_rout_obj.h"
#include "eaddress.h"

#ifdef __cplusplus
extern "C" {
#endif

	/* SIMPLE_SORTER [REAL_64] compare_by_keys */
EIF_TYPED_VALUE _A968_66_2_3 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTVF(72, "compare_by_keys", closed [1].it_r))(closed [1].it_r, open [1], open [2], closed [2], closed [3]);
}

	/* SIMPLE_STATISTICS real_identity */
EIF_TYPED_VALUE _A3_63_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(134, "real_identity", closed [1].it_r))(closed [1].it_r, open [1]);
}

	/* EQA_SYSTEM_PATH extend */
void _A10_43_2 ( void(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(247, "extend", closed [1].it_r))(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS test_derivative_simple */
void _A59_51 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1043, "test_derivative_simple", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_integrate_simple */
void _A59_52 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1044, "test_integrate_simple", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_partial_derivative_simple */
void _A59_53 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1045, "test_partial_derivative_simple", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_derivative_with_options */
void _A59_54 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1046, "test_derivative_with_options", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_integrate_with_options */
void _A59_55 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1047, "test_integrate_with_options", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_gradient */
void _A59_56 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1048, "test_gradient", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_derivative_calculator_creation */
void _A59_57 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1049, "test_derivative_calculator_creation", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_integral_calculator_creation */
void _A59_58 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1050, "test_integral_calculator_creation", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_convergence_status_converged */
void _A59_59 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1051, "test_convergence_status_converged", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_convergence_status_warning */
void _A59_60 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1052, "test_convergence_status_warning", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_convergence_status_failed */
void _A59_61 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1053, "test_convergence_status_failed", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_derivative_accuracy_across_scales */
void _A59_62 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1054, "test_derivative_accuracy_across_scales", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_integration_error_bounds */
void _A59_63 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1055, "test_integration_error_bounds", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_derivative_near_zero */
void _A59_64 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1056, "test_derivative_near_zero", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_derivative_very_large_x */
void _A59_65 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1057, "test_derivative_very_large_x", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_integrate_very_small_interval */
void _A59_66 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1058, "test_integrate_very_small_interval", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_integrate_very_large_interval */
void _A59_67 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1059, "test_integrate_very_large_interval", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_derivative_with_discontinuous_function */
void _A59_68 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1060, "test_derivative_with_discontinuous_function", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_derivative_with_nearly_zero_slope */
void _A59_69 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1061, "test_derivative_with_nearly_zero_slope", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_stress_many_consecutive_derivatives */
void _A59_70 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1062, "test_stress_many_consecutive_derivatives", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_stress_many_consecutive_integrals */
void _A59_71 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1063, "test_stress_many_consecutive_integrals", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_partial_derivative_single_dimension */
void _A59_72 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1064, "test_partial_derivative_single_dimension", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS test_partial_derivative_high_dimensions */
void _A59_73 ( void(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(1065, "test_partial_derivative_high_dimensions", closed [1].it_r))(closed [1].it_r);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_partial_derivative_high_dimensions */
EIF_TYPED_VALUE _A59_74_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7033)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_partial_derivative_single_dimension */
EIF_TYPED_VALUE _A59_75_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7034)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_stress_many_consecutive_integrals */
EIF_TYPED_VALUE _A59_76_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7035)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_stress_many_consecutive_derivatives */
EIF_TYPED_VALUE _A59_77_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7036)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_derivative_with_nearly_zero_slope */
EIF_TYPED_VALUE _A59_78_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7037)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_derivative_with_discontinuous_function */
EIF_TYPED_VALUE _A59_79_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7038)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_integrate_very_large_interval */
EIF_TYPED_VALUE _A59_80_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7039)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_integrate_very_small_interval */
EIF_TYPED_VALUE _A59_81_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7040)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_derivative_very_large_x */
EIF_TYPED_VALUE _A59_82_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7041)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_derivative_near_zero */
EIF_TYPED_VALUE _A59_83_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7042)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_integration_error_bounds */
EIF_TYPED_VALUE _A59_84_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7043)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_derivative_accuracy_across_scales */
EIF_TYPED_VALUE _A59_85_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7044)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_integral_calculator_creation */
EIF_TYPED_VALUE _A59_86_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7045)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_derivative_calculator_creation */
EIF_TYPED_VALUE _A59_87_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7046)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_gradient */
EIF_TYPED_VALUE _A59_88_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7047)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_integrate_with_options */
EIF_TYPED_VALUE _A59_89_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7048)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_derivative_with_options */
EIF_TYPED_VALUE _A59_90_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7049)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_partial_derivative_simple */
EIF_TYPED_VALUE _A59_91_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7050)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_integrate_simple */
EIF_TYPED_VALUE _A59_92_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7051)(closed [1].it_r, open [1]);
}

	/* TEST_SIMPLE_CALCULUS inline-agent#1 of test_derivative_simple */
EIF_TYPED_VALUE _A59_93_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) F59_7052)(closed [1].it_r, open [1]);
}

	/* MML_SET [REAL_64] has */
EIF_TYPED_VALUE _A740_35_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(1748, "has", closed [1].it_r))(closed [1].it_r, open [1]);
}

	/* MML_SET [G#1] has */
EIF_TYPED_VALUE _A967_35_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(1748, "has", closed [1].it_r))(closed [1].it_r, open [1]);
}

	/* MML_SET [INTEGER_32] has */
EIF_TYPED_VALUE _A991_35_2 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(1748, "has", closed [1].it_r))(closed [1].it_r, open [1]);
}

	/* EQA_TEST_EVALUATOR [G#1] inline-agent#1 of execute */
EIF_TYPED_VALUE _A979_271 ( EIF_TYPED_VALUE(*f_ptr) (EIF_REFERENCE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	return (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE)) F979_7077)(closed [1].it_r);
}

	/* PROCEDURE [G#1] call */
void _A311_140 ( void(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4658, "call", closed [1].it_r))(closed [1].it_r, closed [2]);
}

	/* EQA_TEST_SET clean */
void _A58_39 ( void(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(1031, "clean", closed [1].it_r))(closed [1].it_r, closed [2]);
}

	/* EQA_EVALUATOR invoke_routine */
void _A194_208_2 ( void(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTVF(1689, "invoke_routine", closed [1].it_r))(closed [1].it_r, open [1], closed [2]);
}

	/* RT_DBG_CALL_RECORD inline-agent#1 of record_fields */
void _A209_159_2 ( void(*f_ptr) (EIF_REFERENCE, EIF_TYPED_VALUE), EIF_TYPED_VALUE * closed, EIF_TYPED_VALUE * open)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) F209_7101)(closed [1].it_r, open [1]);
}

	/* MISMATCH_INFORMATION wipe_out */
void A219_98 (EIF_REFERENCE Current)
{
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTVF(3107, "wipe_out", Current))(Current);
}

	/* MISMATCH_INFORMATION internal_put */
void A219_162 (EIF_REFERENCE Current, EIF_REFERENCE arg1, EIF_POINTER arg2)
{
	EIF_TYPED_VALUE u [2];
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTVF(3813, "internal_put", Current))(Current, ((u [0].type = SK_REF), (u [0].it_r = arg1), u [0]), ((u [1].type = SK_POINTER), (u [1].it_p = arg2), u [1]));
}

	/* MISMATCH_INFORMATION set_string_versions */
void A219_163 (EIF_REFERENCE Current, EIF_POINTER arg1, EIF_POINTER arg2)
{
	EIF_TYPED_VALUE u [2];
	GTCX
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTVF(3814, "set_string_versions", Current))(Current, ((u [0].type = SK_POINTER), (u [0].it_p = arg1), u [0]), ((u [1].type = SK_POINTER), (u [1].it_p = arg2), u [1]));
}


static fnptr feif_address_table[] = {
(fnptr)0,
(fnptr)A219_98,
(fnptr)A219_162,
(fnptr)A219_163,
};

fnptr *egc_address_table_init = feif_address_table;



#ifdef __cplusplus
}
#endif
