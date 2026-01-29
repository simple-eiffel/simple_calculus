/*
 * Code for class INTEGRAL_CALCULATOR
 */

#include "eif_eiffel.h"
#include "../E1/estructure.h"


#ifdef __cplusplus
extern "C" {
#endif

extern void F26_520(EIF_REFERENCE);
extern EIF_TYPED_VALUE F26_521(EIF_REFERENCE);
extern EIF_TYPED_VALUE F26_522(EIF_REFERENCE);
extern EIF_TYPED_VALUE F26_523(EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE);
extern EIF_TYPED_VALUE F26_524(EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE);
extern EIF_TYPED_VALUE F26_525(EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE);
extern void EIF_Minit26(void);

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

/* {INTEGRAL_CALCULATOR}.make */
void F26_520 (EIF_REFERENCE Current)
{
	GTCX
	char *l_feature_name = "make";
	RTEX;
	EIF_INTEGER_32 ti4_1;
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	RTLI(1);
	RTLR(0,Current);
	RTLIU(1);
	RTLU (SK_VOID, NULL);
	RTLU (SK_REF, &Current);
	
	RTEAA(l_feature_name, 25, Current, 0, 0, 521);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(25, Current, 521);
	RTIV(Current, RTAL);
	RTHOOK(1);
	RTDBGAA(Current, dtype, 518, 0x10000000, 1); /* max_iterations */
	*(EIF_INTEGER_32 *)(Current + RTWA(518, dtype)) = (EIF_INTEGER_32) ((EIF_INTEGER_32) 100L);
	if (RTAL & CK_ENSURE) {
		RTHOOK(2);
		RTCT("max_iterations_set", EX_POST);
		ti4_1 = *(EIF_INTEGER_32 *)(Current + RTWA(518, dtype));
		if ((EIF_BOOLEAN)(ti4_1 == ((EIF_INTEGER_32) 100L))) {
			RTCK;
		} else {
			RTCF;
		}
	}
	RTVI(Current, RTAL);
	RTRS;
	RTHOOK(3);
	RTDBGLE;
	RTMD(0);
	RTLE;
	RTLO(2);
	RTEE;
}

/* {INTEGRAL_CALCULATOR}.integration_tolerance */
EIF_TYPED_VALUE F26_521 (EIF_REFERENCE Current)
{
	EIF_TYPED_VALUE r;
	r.type = SK_REAL64;
	r.it_r8 = (EIF_REAL_64) 1.0000000000000001e-05;
	return r;
}

/* {INTEGRAL_CALCULATOR}.max_iterations */
EIF_TYPED_VALUE F26_522 (EIF_REFERENCE Current)
{
	EIF_TYPED_VALUE r;
	r.type = SK_INT32;
	r.it_i4 = *(EIF_INTEGER_32 *)(Current + RTWA(518,Dtype(Current)));
	return r;
}


/* {INTEGRAL_CALCULATOR}.trapezoidal */
EIF_TYPED_VALUE F26_523 (EIF_REFERENCE Current, EIF_TYPED_VALUE arg1x, EIF_TYPED_VALUE arg2x, EIF_TYPED_VALUE arg3x, EIF_TYPED_VALUE arg4x)
{
	GTCX
	char *l_feature_name = "trapezoidal";
	RTEX;
	EIF_REAL_64 loc1 = (EIF_REAL_64) 0;
	EIF_REAL_64 loc2 = (EIF_REAL_64) 0;
	EIF_INTEGER_32 loc3 = (EIF_INTEGER_32) 0;
	EIF_REAL_64 loc4 = (EIF_REAL_64) 0;
#define arg1 arg1x.it_r
#define arg2 arg2x.it_r8
#define arg3 arg3x.it_r8
#define arg4 arg4x.it_i4
	EIF_TYPED_VALUE ur1x = {{0}, SK_REF};
#define ur1 ur1x.it_r
	EIF_REFERENCE tr1 = NULL;
	EIF_REAL_64 tr8_1;
	EIF_REAL_64 tr8_2;
	EIF_BOOLEAN tb1;
	EIF_REAL_64 Result = ((EIF_REAL_64) 0);
	
	RTCFDT;
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	if ((arg4x.type & SK_HEAD) == SK_REF) arg4x.it_i4 = * (EIF_INTEGER_32 *) arg4x.it_r;
	if ((arg3x.type & SK_HEAD) == SK_REF) arg3x.it_r8 = * (EIF_REAL_64 *) arg3x.it_r;
	if ((arg2x.type & SK_HEAD) == SK_REF) arg2x.it_r8 = * (EIF_REAL_64 *) arg2x.it_r;
	
	RTLI(4);
	RTLR(0,arg1);
	RTLR(1,Current);
	RTLR(2,tr1);
	RTLR(3,ur1);
	RTLIU(4);
	RTLU (SK_REAL64, &Result);
	RTLU(SK_REF,&arg1);
	RTLU(SK_REAL64,&arg2);
	RTLU(SK_REAL64,&arg3);
	RTLU(SK_INT32,&arg4);
	RTLU (SK_REF, &Current);
	RTLU(SK_REAL64, &loc1);
	RTLU(SK_REAL64, &loc2);
	RTLU(SK_INT32, &loc3);
	RTLU(SK_REAL64, &loc4);
	
	RTEAA(l_feature_name, 25, Current, 4, 4, 524);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(25, Current, 524);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,645,0xFF01,0xFFF9,1,222,251,251,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		RTCC(arg1, 25, l_feature_name, 1, typres0, 0x01);
	}
	RTIV(Current, RTAL);
	if ((RTAL & CK_REQUIRE) || RTAC) {
		RTHOOK(1);
		RTCT("f_not_void", EX_PRE);
		RTTE((EIF_BOOLEAN)(arg1 != NULL), label_1);
		RTCK;
		RTHOOK(2);
		RTCT("a_less_b", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg2 < arg3), label_1);
		RTCK;
		RTHOOK(3);
		RTCT("a_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg2);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTHOOK(4);
		RTCT("b_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg3);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTHOOK(5);
		RTCT("intervals_positive", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg4 > ((EIF_INTEGER_32) 0L)), label_1);
		RTCK;
		RTJB;
label_1:
		RTCF;
	}
body:;
	RTHOOK(6);
	RTDBGAL(1, 0x20000000, 1, 0); /* loc1 */
	tr8_1 = (EIF_REAL_64) (arg4);
	loc1 = (EIF_REAL_64) (EIF_REAL_64) ((EIF_REAL_64) ((EIF_REAL_64) (arg3 - arg2)) /  (EIF_REAL_64) (tr8_1));
	RTHOOK(7);
	RTDBGAL(2, 0x20000000, 1, 0); /* loc2 */
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,0xFFF9,1,222,251,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 1);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r8 = arg2;
	ur1 = RTCCL(tr1);
	tr8_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4683, "item", arg1))(arg1, ur1x)).it_r8);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,0xFFF9,1,222,251,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 1);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r8 = arg3;
	ur1 = RTCCL(tr1);
	tr8_2 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4683, "item", arg1))(arg1, ur1x)).it_r8);
	loc2 = (EIF_REAL_64) (EIF_REAL_64) ((EIF_REAL_64) ((EIF_REAL_64) (tr8_1 + tr8_2)) /  (EIF_REAL_64) ((EIF_REAL_64) 2.0));
	RTHOOK(8);
	RTDBGAL(3, 0x10000000, 1, 0); /* loc3 */
	loc3 = (EIF_INTEGER_32) ((EIF_INTEGER_32) 1L);
	for (;;) {
		RTHOOK(9);
		if ((EIF_BOOLEAN) (loc3 >= arg4)) break;
		RTHOOK(10);
		RTDBGAL(4, 0x20000000, 1, 0); /* loc4 */
		tr8_1 = (EIF_REAL_64) (loc3);
		loc4 = (EIF_REAL_64) (EIF_REAL_64) (arg2 + (EIF_REAL_64) (tr8_1 * loc1));
		RTHOOK(11);
		RTDBGAL(2, 0x20000000, 1, 0); /* loc2 */
		{
			static EIF_TYPE_INDEX typarr0[] = {0xFF01,0xFFF9,1,222,251,0xFFFF};
			EIF_TYPE typres0;
			static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
			
			typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
			tr1 = RTLNTS(typres0.id, 2, 1);
		}
		((EIF_TYPED_VALUE *)tr1+1)->it_r8 = loc4;
		ur1 = RTCCL(tr1);
		tr8_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4683, "item", arg1))(arg1, ur1x)).it_r8);
		loc2 += tr8_1;
		RTHOOK(12);
		RTDBGAL(3, 0x10000000, 1, 0); /* loc3 */
		loc3++;
	}
	RTHOOK(13);
	RTDBGAL(0, 0x20000000, 1,0); /* Result */
	Result = (EIF_REAL_64) (EIF_REAL_64) (loc1 * loc2);
	if (RTAL & CK_ENSURE) {
		RTHOOK(14);
		RTCT("result_not_nan", EX_POST);
		tb1 = eif_is_nan_real_64 (Result);
		if ((EIF_BOOLEAN) !tb1) {
			RTCK;
		} else {
			RTCF;
		}
	}
	RTVI(Current, RTAL);
	RTRS;
	RTHOOK(15);
	RTDBGLE;
	RTMD(0);
	RTLE;
	RTLO(10);
	RTEE;
	{ EIF_TYPED_VALUE r; r.type = SK_REAL64; r.it_r8 = Result; return r; }
#undef ur1
#undef arg4
#undef arg3
#undef arg2
#undef arg1
}

/* {INTEGRAL_CALCULATOR}.simpson */
EIF_TYPED_VALUE F26_524 (EIF_REFERENCE Current, EIF_TYPED_VALUE arg1x, EIF_TYPED_VALUE arg2x, EIF_TYPED_VALUE arg3x, EIF_TYPED_VALUE arg4x)
{
	GTCX
	char *l_feature_name = "simpson";
	RTEX;
	EIF_REAL_64 loc1 = (EIF_REAL_64) 0;
	EIF_REAL_64 loc2 = (EIF_REAL_64) 0;
	EIF_INTEGER_32 loc3 = (EIF_INTEGER_32) 0;
	EIF_REAL_64 loc4 = (EIF_REAL_64) 0;
#define arg1 arg1x.it_r
#define arg2 arg2x.it_r8
#define arg3 arg3x.it_r8
#define arg4 arg4x.it_i4
	EIF_TYPED_VALUE ur1x = {{0}, SK_REF};
#define ur1 ur1x.it_r
	EIF_REFERENCE tr1 = NULL;
	EIF_REAL_64 tr8_1;
	EIF_REAL_64 tr8_2;
	EIF_BOOLEAN tb1;
	EIF_REAL_64 Result = ((EIF_REAL_64) 0);
	
	RTCFDT;
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	if ((arg4x.type & SK_HEAD) == SK_REF) arg4x.it_i4 = * (EIF_INTEGER_32 *) arg4x.it_r;
	if ((arg3x.type & SK_HEAD) == SK_REF) arg3x.it_r8 = * (EIF_REAL_64 *) arg3x.it_r;
	if ((arg2x.type & SK_HEAD) == SK_REF) arg2x.it_r8 = * (EIF_REAL_64 *) arg2x.it_r;
	
	RTLI(4);
	RTLR(0,arg1);
	RTLR(1,Current);
	RTLR(2,tr1);
	RTLR(3,ur1);
	RTLIU(4);
	RTLU (SK_REAL64, &Result);
	RTLU(SK_REF,&arg1);
	RTLU(SK_REAL64,&arg2);
	RTLU(SK_REAL64,&arg3);
	RTLU(SK_INT32,&arg4);
	RTLU (SK_REF, &Current);
	RTLU(SK_REAL64, &loc1);
	RTLU(SK_REAL64, &loc2);
	RTLU(SK_INT32, &loc3);
	RTLU(SK_REAL64, &loc4);
	
	RTEAA(l_feature_name, 25, Current, 4, 4, 525);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(25, Current, 525);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,645,0xFF01,0xFFF9,1,222,251,251,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		RTCC(arg1, 25, l_feature_name, 1, typres0, 0x01);
	}
	RTIV(Current, RTAL);
	if ((RTAL & CK_REQUIRE) || RTAC) {
		RTHOOK(1);
		RTCT("f_not_void", EX_PRE);
		RTTE((EIF_BOOLEAN)(arg1 != NULL), label_1);
		RTCK;
		RTHOOK(2);
		RTCT("a_less_b", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg2 < arg3), label_1);
		RTCK;
		RTHOOK(3);
		RTCT("a_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg2);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTHOOK(4);
		RTCT("b_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg3);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTHOOK(5);
		RTCT("intervals_even", EX_PRE);
		RTTE((EIF_BOOLEAN) ((EIF_BOOLEAN) (arg4 > ((EIF_INTEGER_32) 0L)) && (EIF_BOOLEAN)((EIF_INTEGER_32) (arg4 % ((EIF_INTEGER_32) 2L)) == ((EIF_INTEGER_32) 0L))), label_1);
		RTCK;
		RTJB;
label_1:
		RTCF;
	}
body:;
	RTHOOK(6);
	RTDBGAL(1, 0x20000000, 1, 0); /* loc1 */
	tr8_1 = (EIF_REAL_64) (arg4);
	loc1 = (EIF_REAL_64) (EIF_REAL_64) ((EIF_REAL_64) ((EIF_REAL_64) (arg3 - arg2)) /  (EIF_REAL_64) (tr8_1));
	RTHOOK(7);
	RTDBGAL(2, 0x20000000, 1, 0); /* loc2 */
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,0xFFF9,1,222,251,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 1);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r8 = arg2;
	ur1 = RTCCL(tr1);
	tr8_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4683, "item", arg1))(arg1, ur1x)).it_r8);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,0xFFF9,1,222,251,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 1);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r8 = arg3;
	ur1 = RTCCL(tr1);
	tr8_2 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4683, "item", arg1))(arg1, ur1x)).it_r8);
	loc2 = (EIF_REAL_64) (EIF_REAL_64) (tr8_1 + tr8_2);
	RTHOOK(8);
	RTDBGAL(3, 0x10000000, 1, 0); /* loc3 */
	loc3 = (EIF_INTEGER_32) ((EIF_INTEGER_32) 1L);
	for (;;) {
		RTHOOK(9);
		if ((EIF_BOOLEAN) (loc3 >= arg4)) break;
		RTHOOK(10);
		RTDBGAL(4, 0x20000000, 1, 0); /* loc4 */
		tr8_1 = (EIF_REAL_64) (loc3);
		loc4 = (EIF_REAL_64) (EIF_REAL_64) (arg2 + (EIF_REAL_64) (tr8_1 * loc1));
		RTHOOK(11);
		RTDBGAL(2, 0x20000000, 1, 0); /* loc2 */
		{
			static EIF_TYPE_INDEX typarr0[] = {0xFF01,0xFFF9,1,222,251,0xFFFF};
			EIF_TYPE typres0;
			static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
			
			typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
			tr1 = RTLNTS(typres0.id, 2, 1);
		}
		((EIF_TYPED_VALUE *)tr1+1)->it_r8 = loc4;
		ur1 = RTCCL(tr1);
		tr8_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4683, "item", arg1))(arg1, ur1x)).it_r8);
		loc2 += (EIF_REAL_64) ((EIF_REAL_64) 4.0 * tr8_1);
		RTHOOK(12);
		RTDBGAL(3, 0x10000000, 1, 0); /* loc3 */
		loc3 += ((EIF_INTEGER_32) 2L);
	}
	RTHOOK(13);
	RTDBGAL(3, 0x10000000, 1, 0); /* loc3 */
	loc3 = (EIF_INTEGER_32) ((EIF_INTEGER_32) 2L);
	for (;;) {
		RTHOOK(14);
		if ((EIF_BOOLEAN) (loc3 >= arg4)) break;
		RTHOOK(15);
		RTDBGAL(4, 0x20000000, 1, 0); /* loc4 */
		tr8_1 = (EIF_REAL_64) (loc3);
		loc4 = (EIF_REAL_64) (EIF_REAL_64) (arg2 + (EIF_REAL_64) (tr8_1 * loc1));
		RTHOOK(16);
		RTDBGAL(2, 0x20000000, 1, 0); /* loc2 */
		{
			static EIF_TYPE_INDEX typarr0[] = {0xFF01,0xFFF9,1,222,251,0xFFFF};
			EIF_TYPE typres0;
			static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
			
			typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
			tr1 = RTLNTS(typres0.id, 2, 1);
		}
		((EIF_TYPED_VALUE *)tr1+1)->it_r8 = loc4;
		ur1 = RTCCL(tr1);
		tr8_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4683, "item", arg1))(arg1, ur1x)).it_r8);
		loc2 += (EIF_REAL_64) ((EIF_REAL_64) 2.0 * tr8_1);
		RTHOOK(17);
		RTDBGAL(3, 0x10000000, 1, 0); /* loc3 */
		loc3 += ((EIF_INTEGER_32) 2L);
	}
	RTHOOK(18);
	RTDBGAL(0, 0x20000000, 1,0); /* Result */
	Result = (EIF_REAL_64) (EIF_REAL_64) ((EIF_REAL_64) ((EIF_REAL_64) (loc1) /  (EIF_REAL_64) ((EIF_REAL_64) 3.0)) * loc2);
	if (RTAL & CK_ENSURE) {
		RTHOOK(19);
		RTCT("result_not_nan", EX_POST);
		tb1 = eif_is_nan_real_64 (Result);
		if ((EIF_BOOLEAN) !tb1) {
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
	{ EIF_TYPED_VALUE r; r.type = SK_REAL64; r.it_r8 = Result; return r; }
#undef ur1
#undef arg4
#undef arg3
#undef arg2
#undef arg1
}

/* {INTEGRAL_CALCULATOR}.compute_adaptive */
EIF_TYPED_VALUE F26_525 (EIF_REFERENCE Current, EIF_TYPED_VALUE arg1x, EIF_TYPED_VALUE arg2x, EIF_TYPED_VALUE arg3x, EIF_TYPED_VALUE arg4x)
{
	GTCX
	char *l_feature_name = "compute_adaptive";
	RTEX;
	EIF_REAL_64 loc1 = (EIF_REAL_64) 0;
	EIF_REAL_64 loc2 = (EIF_REAL_64) 0;
	EIF_INTEGER_32 loc3 = (EIF_INTEGER_32) 0;
	EIF_INTEGER_32 loc4 = (EIF_INTEGER_32) 0;
	EIF_REAL_64 loc5 = (EIF_REAL_64) 0;
#define arg1 arg1x.it_r
#define arg2 arg2x.it_r8
#define arg3 arg3x.it_r8
#define arg4 arg4x.it_r8
	EIF_TYPED_VALUE ur1x = {{0}, SK_REF};
#define ur1 ur1x.it_r
	EIF_TYPED_VALUE ur8_1x = {{0}, SK_REAL64};
#define ur8_1 ur8_1x.it_r8
	EIF_TYPED_VALUE ur8_2x = {{0}, SK_REAL64};
#define ur8_2 ur8_2x.it_r8
	EIF_TYPED_VALUE ui4_1x = {{0}, SK_INT32};
#define ui4_1 ui4_1x.it_i4
	EIF_REFERENCE tr1 = NULL;
	EIF_REAL_64 tr8_1;
	EIF_INTEGER_32 ti4_1;
	EIF_INTEGER_32 ti4_2;
	EIF_BOOLEAN tb1;
	EIF_REFERENCE Result = ((EIF_REFERENCE) 0);
	
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	if ((arg4x.type & SK_HEAD) == SK_REF) arg4x.it_r8 = * (EIF_REAL_64 *) arg4x.it_r;
	if ((arg3x.type & SK_HEAD) == SK_REF) arg3x.it_r8 = * (EIF_REAL_64 *) arg3x.it_r;
	if ((arg2x.type & SK_HEAD) == SK_REF) arg2x.it_r8 = * (EIF_REAL_64 *) arg2x.it_r;
	
	RTLI(5);
	RTLR(0,arg1);
	RTLR(1,ur1);
	RTLR(2,Current);
	RTLR(3,tr1);
	RTLR(4,Result);
	RTLIU(5);
	RTLU (SK_REF, &Result);
	RTLU(SK_REF,&arg1);
	RTLU(SK_REAL64,&arg2);
	RTLU(SK_REAL64,&arg3);
	RTLU(SK_REAL64,&arg4);
	RTLU (SK_REF, &Current);
	RTLU(SK_REAL64, &loc1);
	RTLU(SK_REAL64, &loc2);
	RTLU(SK_INT32, &loc3);
	RTLU(SK_INT32, &loc4);
	RTLU(SK_REAL64, &loc5);
	
	RTEAA(l_feature_name, 25, Current, 5, 4, 526);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(25, Current, 526);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,645,0xFF01,0xFFF9,1,222,251,251,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(Dftype(Current), typarr0)));
		RTCC(arg1, 25, l_feature_name, 1, typres0, 0x01);
	}
	RTIV(Current, RTAL);
	if ((RTAL & CK_REQUIRE) || RTAC) {
		RTHOOK(1);
		RTCT("f_not_void", EX_PRE);
		RTTE((EIF_BOOLEAN)(arg1 != NULL), label_1);
		RTCK;
		RTHOOK(2);
		RTCT("a_less_b", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg2 < arg3), label_1);
		RTCK;
		RTHOOK(3);
		RTCT("a_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg2);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTHOOK(4);
		RTCT("b_valid", EX_PRE);
		tb1 = eif_is_nan_real_64 (arg3);
		RTTE((EIF_BOOLEAN) !tb1, label_1);
		RTCK;
		RTHOOK(5);
		RTCT("tolerance_positive", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg4 > (EIF_REAL_64) 0.0), label_1);
		RTCK;
		RTJB;
label_1:
		RTCF;
	}
body:;
	RTHOOK(6);
	RTDBGAL(4, 0x10000000, 1, 0); /* loc4 */
	loc4 = (EIF_INTEGER_32) ((EIF_INTEGER_32) 4L);
	RTHOOK(7);
	RTDBGAL(1, 0x20000000, 1, 0); /* loc1 */
	ur1 = RTCCL(arg1);
	ur8_1 = arg2;
	ur8_2 = arg3;
	ui4_1 = loc4;
	tr8_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(520, dtype))(Current, ur1x, ur8_1x, ur8_2x, ui4_1x)).it_r8);
	loc1 = (EIF_REAL_64) tr8_1;
	RTHOOK(8);
	RTDBGAL(3, 0x10000000, 1, 0); /* loc3 */
	loc3 = (EIF_INTEGER_32) ((EIF_INTEGER_32) 0L);
	RTHOOK(9);
	RTDBGAL(5, 0x20000000, 1, 0); /* loc5 */
	loc5 = (EIF_REAL_64) (EIF_REAL_64) 0.0;
	RTHOOK(10);
	RTDBGAL(2, 0x20000000, 1, 0); /* loc2 */
	loc2 = (EIF_REAL_64) (EIF_REAL_64) (arg4 + (EIF_REAL_64) 1.0);
	for (;;) {
		RTHOOK(11);
		ti4_1 = *(EIF_INTEGER_32 *)(Current + RTWA(518, dtype));
		if ((EIF_BOOLEAN) ((EIF_BOOLEAN) (loc2 < arg4) || (EIF_BOOLEAN) (loc3 >= ti4_1))) break;
		RTHOOK(12);
		RTDBGAL(5, 0x20000000, 1, 0); /* loc5 */
		loc5 = (EIF_REAL_64) loc1;
		RTHOOK(13);
		RTDBGAL(4, 0x10000000, 1, 0); /* loc4 */
		loc4 *= ((EIF_INTEGER_32) 2L);
		RTHOOK(14);
		RTDBGAL(1, 0x20000000, 1, 0); /* loc1 */
		ur1 = RTCCL(arg1);
		ur8_1 = arg2;
		ur8_2 = arg3;
		ui4_1 = loc4;
		tr8_1 = (((FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(520, dtype))(Current, ur1x, ur8_1x, ur8_2x, ui4_1x)).it_r8);
		loc1 = (EIF_REAL_64) tr8_1;
		RTHOOK(15);
		RTDBGAL(2, 0x20000000, 1, 0); /* loc2 */
		tr8_1 = eif_abs_real64 ((EIF_REAL_64) (loc1 - loc5));
		loc2 = (EIF_REAL_64) tr8_1;
		RTHOOK(16);
		RTDBGAL(3, 0x10000000, 1, 0); /* loc3 */
		loc3++;
	}
	RTHOOK(17);
	RTDBGAL(0, 0xF800001C, 0,0); /* Result */
	tr1 = RTLN(eif_new_type(28, 0x01).id);
	ur8_1 = loc1;
	ur8_2 = loc2;
	ui4_1 = loc3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWC(527, Dtype(tr1)))(tr1, ur8_1x, ur8_2x, ui4_1x);
	RTNHOOK(17,1);
	Result = (EIF_REFERENCE) RTCCL(tr1);
	if (RTAL & CK_ENSURE) {
		RTHOOK(18);
		RTCT("result_not_void", EX_POST);
		if ((EIF_BOOLEAN)(Result != NULL)) {
			RTCK;
		} else {
			RTCF;
		}
		RTHOOK(19);
		RTCT("result_valid", EX_POST);
		tr8_1 = *(EIF_REAL_64 *)(Result + RTVA(528, "value", Result));
		tb1 = eif_is_nan_real_64 (tr8_1);
		if ((EIF_BOOLEAN) !tb1) {
			RTCK;
		} else {
			RTCF;
		}
		RTHOOK(20);
		RTCT("error_non_negative", EX_POST);
		tr8_1 = *(EIF_REAL_64 *)(Result + RTVA(529, "error_bound", Result));
		if ((EIF_BOOLEAN) (tr8_1 >= (EIF_REAL_64) 0.0)) {
			RTCK;
		} else {
			RTCF;
		}
		RTHOOK(21);
		RTCT("iterations_non_negative", EX_POST);
		ti4_2 = *(EIF_INTEGER_32 *)(Result + RTVA(530, "iterations", Result));
		if ((EIF_BOOLEAN) (ti4_2 >= ((EIF_INTEGER_32) 0L))) {
			RTCK;
		} else {
			RTCF;
		}
	}
	RTVI(Current, RTAL);
	RTRS;
	RTHOOK(22);
	RTDBGLE;
	RTMD(0);
	RTLE;
	RTLO(11);
	RTEE;
	{ EIF_TYPED_VALUE r; r.type = SK_REF; r.it_r = Result; return r; }
#undef ur1
#undef ur8_1
#undef ur8_2
#undef ui4_1
#undef arg4
#undef arg3
#undef arg2
#undef arg1
}

void EIF_Minit26 (void)
{
	GTCX
}


#ifdef __cplusplus
}
#endif
