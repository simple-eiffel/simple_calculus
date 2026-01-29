/*
 * Code for class INTEGRAL_RESULT
 */

#include "eif_eiffel.h"
#include "../E1/estructure.h"


#ifdef __cplusplus
extern "C" {
#endif

extern void F29_531(EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE, EIF_TYPED_VALUE);
extern EIF_TYPED_VALUE F29_532(EIF_REFERENCE);
extern EIF_TYPED_VALUE F29_533(EIF_REFERENCE);
extern EIF_TYPED_VALUE F29_534(EIF_REFERENCE);
extern EIF_TYPED_VALUE F29_535(EIF_REFERENCE);
extern void EIF_Minit29(void);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C" {
#endif

/* {INTEGRAL_RESULT}.make */
void F29_531 (EIF_REFERENCE Current, EIF_TYPED_VALUE arg1x, EIF_TYPED_VALUE arg2x, EIF_TYPED_VALUE arg3x)
{
	GTCX
	char *l_feature_name = "make";
	RTEX;
#define arg1 arg1x.it_r8
#define arg2 arg2x.it_r8
#define arg3 arg3x.it_i4
	EIF_REAL_64 tr8_1;
	EIF_INTEGER_32 ti4_1;
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	if ((arg3x.type & SK_HEAD) == SK_REF) arg3x.it_i4 = * (EIF_INTEGER_32 *) arg3x.it_r;
	if ((arg2x.type & SK_HEAD) == SK_REF) arg2x.it_r8 = * (EIF_REAL_64 *) arg2x.it_r;
	if ((arg1x.type & SK_HEAD) == SK_REF) arg1x.it_r8 = * (EIF_REAL_64 *) arg1x.it_r;
	
	RTLI(1);
	RTLR(0,Current);
	RTLIU(1);
	RTLU (SK_VOID, NULL);
	RTLU(SK_REAL64,&arg1);
	RTLU(SK_REAL64,&arg2);
	RTLU(SK_INT32,&arg3);
	RTLU (SK_REF, &Current);
	
	RTEAA(l_feature_name, 28, Current, 0, 3, 532);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(28, Current, 532);
	RTIV(Current, RTAL);
	if ((RTAL & CK_REQUIRE) || RTAC) {
		RTHOOK(1);
		RTCT("error_non_negative", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg2 >= (EIF_REAL_64) 0.0), label_1);
		RTCK;
		RTHOOK(2);
		RTCT("iterations_non_negative", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg3 >= ((EIF_INTEGER_32) 0L)), label_1);
		RTCK;
		RTJB;
label_1:
		RTCF;
	}
body:;
	RTHOOK(3);
	RTDBGAA(Current, dtype, 528, 0x20000000, 1); /* value */
	*(EIF_REAL_64 *)(Current + RTWA(528, dtype)) = (EIF_REAL_64) arg1;
	RTHOOK(4);
	RTDBGAA(Current, dtype, 529, 0x20000000, 1); /* error_bound */
	*(EIF_REAL_64 *)(Current + RTWA(529, dtype)) = (EIF_REAL_64) arg2;
	RTHOOK(5);
	RTDBGAA(Current, dtype, 530, 0x10000000, 1); /* iterations */
	*(EIF_INTEGER_32 *)(Current + RTWA(530, dtype)) = (EIF_INTEGER_32) arg3;
	if (RTAL & CK_ENSURE) {
		RTHOOK(6);
		RTCT("value_set", EX_POST);
		tr8_1 = *(EIF_REAL_64 *)(Current + RTWA(528, dtype));
		if ((EIF_BOOLEAN)(tr8_1 == arg1)) {
			RTCK;
		} else {
			RTCF;
		}
		RTHOOK(7);
		RTCT("error_bound_set", EX_POST);
		tr8_1 = *(EIF_REAL_64 *)(Current + RTWA(529, dtype));
		if ((EIF_BOOLEAN)(tr8_1 == arg2)) {
			RTCK;
		} else {
			RTCF;
		}
		RTHOOK(8);
		RTCT("iterations_set", EX_POST);
		ti4_1 = *(EIF_INTEGER_32 *)(Current + RTWA(530, dtype));
		if ((EIF_BOOLEAN)(ti4_1 == arg3)) {
			RTCK;
		} else {
			RTCF;
		}
	}
	RTVI(Current, RTAL);
	RTRS;
	RTHOOK(9);
	RTDBGLE;
	RTMD(0);
	RTLE;
	RTLO(5);
	RTEE;
#undef arg3
#undef arg2
#undef arg1
}

/* {INTEGRAL_RESULT}.value */
EIF_TYPED_VALUE F29_532 (EIF_REFERENCE Current)
{
	EIF_TYPED_VALUE r;
	r.type = SK_REAL64;
	r.it_r8 = *(EIF_REAL_64 *)(Current + RTWA(528,Dtype(Current)));
	return r;
}


/* {INTEGRAL_RESULT}.error_bound */
EIF_TYPED_VALUE F29_533 (EIF_REFERENCE Current)
{
	EIF_TYPED_VALUE r;
	r.type = SK_REAL64;
	r.it_r8 = *(EIF_REAL_64 *)(Current + RTWA(529,Dtype(Current)));
	return r;
}


/* {INTEGRAL_RESULT}.iterations */
EIF_TYPED_VALUE F29_534 (EIF_REFERENCE Current)
{
	EIF_TYPED_VALUE r;
	r.type = SK_INT32;
	r.it_i4 = *(EIF_INTEGER_32 *)(Current + RTWA(530,Dtype(Current)));
	return r;
}


/* {INTEGRAL_RESULT}.is_accurate */
EIF_TYPED_VALUE F29_535 (EIF_REFERENCE Current)
{
	GTCX
	char *l_feature_name = "is_accurate";
	RTEX;
	EIF_REAL_64 tr8_1;
	EIF_BOOLEAN Result = ((EIF_BOOLEAN) 0);
	
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	RTLI(1);
	RTLR(0,Current);
	RTLIU(1);
	RTLU (SK_BOOL, &Result);
	RTLU (SK_REF, &Current);
	
	RTEAA(l_feature_name, 28, Current, 0, 0, 536);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(28, Current, 536);
	RTIV(Current, RTAL);
	RTHOOK(1);
	RTDBGAL(0, 0x04000000, 1,0); /* Result */
	tr8_1 = *(EIF_REAL_64 *)(Current + RTWA(529, dtype));
	Result = (EIF_BOOLEAN) (EIF_BOOLEAN) (tr8_1 < (EIF_REAL_64) 1.0e-5);
	if (RTAL & CK_ENSURE) {
		RTHOOK(2);
		RTCT("result_valid", EX_POST);
		tr8_1 = *(EIF_REAL_64 *)(Current + RTWA(529, dtype));
		if ((EIF_BOOLEAN)(Result == (EIF_BOOLEAN) (tr8_1 < (EIF_REAL_64) 1.0e-5))) {
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
	{ EIF_TYPED_VALUE r; r.type = SK_BOOL; r.it_b = Result; return r; }
}

void EIF_Minit29 (void)
{
	GTCX
}


#ifdef __cplusplus
}
#endif
