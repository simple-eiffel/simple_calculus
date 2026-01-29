/*
 * Code for class CONVERGENCE_ANALYZER
 */

#include "eif_eiffel.h"
#include "../E1/estructure.h"


#ifdef __cplusplus
extern "C" {
#endif

extern EIF_TYPED_VALUE F27_526(EIF_REFERENCE);
extern EIF_TYPED_VALUE F27_527(EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE);
extern void EIF_Minit27(void);

#ifdef __cplusplus
}
#endif

#include "eif_helpers.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C" {
#endif

/* {CONVERGENCE_ANALYZER}.default_tolerance */
EIF_TYPED_VALUE F27_526 (EIF_REFERENCE Current)
{
	EIF_TYPED_VALUE r;
	r.type = SK_REAL64;
	r.it_r8 = (EIF_REAL_64) 9.9999999999999995e-07;
	return r;
}

/* {CONVERGENCE_ANALYZER}.analyze */
EIF_TYPED_VALUE F27_527 (EIF_REFERENCE Current, EIF_TYPED_VALUE arg1x, EIF_TYPED_VALUE arg2x, EIF_TYPED_VALUE arg3x, EIF_TYPED_VALUE arg4x)
{
	GTCX
	char *l_feature_name = "analyze";
	RTEX;
	EIF_REAL_64 loc1 = (EIF_REAL_64) 0;
	EIF_REAL_64 loc2 = (EIF_REAL_64) 0;
	EIF_REAL_64 loc3 = (EIF_REAL_64) 0;
	EIF_INTEGER_32 loc4 = (EIF_INTEGER_32) 0;
#define arg1 arg1x.it_r8
#define arg2 arg2x.it_r8
#define arg3 arg3x.it_r8
#define arg4 arg4x.it_r8
	EIF_TYPED_VALUE ur8_1x = {{0}, SK_REAL64};
#define ur8_1 ur8_1x.it_r8
	EIF_TYPED_VALUE ui4_1x = {{0}, SK_INT32};
#define ui4_1 ui4_1x.it_i4
	EIF_REFERENCE tr1 = NULL;
	EIF_REAL_64 tr8_1;
	EIF_INTEGER_32 ti4_1;
	EIF_INTEGER_32 ti4_2;
	EIF_BOOLEAN tb1;
	EIF_BOOLEAN tb2;
	EIF_REFERENCE Result = ((EIF_REFERENCE) 0);
	
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	if ((arg4x.type & SK_HEAD) == SK_REF) arg4x.it_r8 = * (EIF_REAL_64 *) arg4x.it_r;
	if ((arg3x.type & SK_HEAD) == SK_REF) arg3x.it_r8 = * (EIF_REAL_64 *) arg3x.it_r;
	if ((arg2x.type & SK_HEAD) == SK_REF) arg2x.it_r8 = * (EIF_REAL_64 *) arg2x.it_r;
	if ((arg1x.type & SK_HEAD) == SK_REF) arg1x.it_r8 = * (EIF_REAL_64 *) arg1x.it_r;
	
	RTLI(3);
	RTLR(0,Current);
	RTLR(1,tr1);
	RTLR(2,Result);
	RTLIU(3);
	RTLU (SK_REF, &Result);
	RTLU(SK_REAL64,&arg1);
	RTLU(SK_REAL64,&arg2);
	RTLU(SK_REAL64,&arg3);
	RTLU(SK_REAL64,&arg4);
	RTLU (SK_REF, &Current);
	RTLU(SK_REAL64, &loc1);
	RTLU(SK_REAL64, &loc2);
	RTLU(SK_REAL64, &loc3);
	RTLU(SK_INT32, &loc4);
	
	RTEAA(l_feature_name, 26, Current, 4, 4, 527);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(26, Current, 527);
	RTIV(Current, RTAL);
	if ((RTAL & CK_REQUIRE) || RTAC) {
		RTHOOK(1);
		RTCT("tolerance_positive", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg4 > (EIF_REAL_64) 0.0), label_1);
		RTCK;
		RTHOOK(2);
		RTCT("tolerance_reasonable", EX_PRE);
		RTTE((EIF_BOOLEAN) ((EIF_BOOLEAN) (arg4 >= (EIF_REAL_64) 1.0e-12) && (EIF_BOOLEAN) (arg4 <= (EIF_REAL_64) 1.0e-3)), label_1);
		RTCK;
		RTHOOK(3);
		RTCT("forward_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg1);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTHOOK(4);
		RTCT("backward_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg2);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTHOOK(5);
		RTCT("central_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg3);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTJB;
label_1:
		RTCF;
	}
body:;
	RTHOOK(6);
	RTDBGAL(1, 0x20000000, 1, 0); /* loc1 */
	tr8_1 = eif_abs_real64 ((EIF_REAL_64) (arg1 - arg3));
	loc1 = (EIF_REAL_64) tr8_1;
	RTHOOK(7);
	RTDBGAL(2, 0x20000000, 1, 0); /* loc2 */
	tr8_1 = eif_abs_real64 ((EIF_REAL_64) (arg2 - arg3));
	loc2 = (EIF_REAL_64) tr8_1;
	RTHOOK(8);
	if ((EIF_BOOLEAN) (loc1 >= loc2)) {
		RTHOOK(9);
		RTDBGAL(3, 0x20000000, 1, 0); /* loc3 */
		loc3 = (EIF_REAL_64) loc1;
	} else {
		RTHOOK(10);
		RTDBGAL(3, 0x20000000, 1, 0); /* loc3 */
		loc3 = (EIF_REAL_64) loc2;
	}
	RTHOOK(11);
	if ((EIF_BOOLEAN) ((EIF_BOOLEAN) (loc1 < arg4) && (EIF_BOOLEAN) (loc2 < arg4))) {
		RTHOOK(12);
		RTDBGAL(4, 0x10000000, 1, 0); /* loc4 */
		ti4_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE)) RTWF(532, 29))(Current)).it_i4);
		loc4 = (EIF_INTEGER_32) ti4_1;
	} else {
		RTHOOK(13);
		if ((EIF_BOOLEAN) ((EIF_BOOLEAN) (loc1 < arg4) || (EIF_BOOLEAN) (loc2 < arg4))) {
			RTHOOK(14);
			RTDBGAL(4, 0x10000000, 1, 0); /* loc4 */
			ti4_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE)) RTWF(533, 29))(Current)).it_i4);
			loc4 = (EIF_INTEGER_32) ti4_1;
		} else {
			RTHOOK(15);
			RTDBGAL(4, 0x10000000, 1, 0); /* loc4 */
			ti4_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE)) RTWF(534, 29))(Current)).it_i4);
			loc4 = (EIF_INTEGER_32) ti4_1;
		}
	}
	RTHOOK(16);
	RTDBGAL(0, 0xF800001B, 0,0); /* Result */
	tr1 = RTLN(eif_new_type(27, 0x01).id);
	ur8_1 = loc3;
	ui4_1 = loc4;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWC(524, Dtype(tr1)))(tr1, ur8_1x, ui4_1x);
	RTNHOOK(16,1);
	Result = (EIF_REFERENCE) RTCCL(tr1);
	if (RTAL & CK_ENSURE) {
		RTHOOK(17);
		RTCT("result_not_void", EX_POST);
		if ((EIF_BOOLEAN)(Result != NULL)) {
			RTCK;
		} else {
			RTCF;
		}
		RTHOOK(18);
		RTCT("error_non_negative", EX_POST);
		tr8_1 = *(EIF_REAL_64 *)(Result + RTVA(525, "error_bound", Result));
		if ((EIF_BOOLEAN) (tr8_1 >= (EIF_REAL_64) 0.0)) {
			RTCK;
		} else {
			RTCF;
		}
		RTHOOK(19);
		RTCT("status_valid", EX_POST);
		tb1 = '\01';
		tb2 = '\01';
		ti4_1 = *(EIF_INTEGER_32 *)(Result + RTVA(526, "status", Result));
		ti4_2 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE)) RTWF(532, 29))(Current)).it_i4);
		if (!(EIF_BOOLEAN)(ti4_1 == ti4_2)) {
			ti4_1 = *(EIF_INTEGER_32 *)(Result + RTVA(526, "status", Result));
			ti4_2 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE)) RTWF(533, 29))(Current)).it_i4);
			tb2 = (EIF_BOOLEAN)(ti4_1 == ti4_2);
		}
		if (!tb2) {
			ti4_1 = *(EIF_INTEGER_32 *)(Result + RTVA(526, "status", Result));
			ti4_2 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE)) RTWF(534, 29))(Current)).it_i4);
			tb1 = (EIF_BOOLEAN)(ti4_1 == ti4_2);
		}
		if (tb1) {
			RTCK;
		} else {
			RTCF;
		}
	}
	RTVI(Current, RTAL);
	RTRS;
	RTHOOK(20);
	RTDBGLE;
	RTMD(0);
	RTLE;
	RTLO(10);
	RTEE;
	{ EIF_TYPED_VALUE r; r.type = SK_REF; r.it_r = Result; return r; }
#undef ur8_1
#undef ui4_1
#undef arg4
#undef arg3
#undef arg2
#undef arg1
}

void EIF_Minit27 (void)
{
	GTCX
}


#ifdef __cplusplus
}
#endif
