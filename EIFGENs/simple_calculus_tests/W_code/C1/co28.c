/*
 * Code for class CONVERGENCE_RESULT
 */

#include "eif_eiffel.h"
#include "../E1/estructure.h"


#ifdef __cplusplus
extern "C" {
#endif

extern void F28_528(EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE);
extern EIF_TYPED_VALUE F28_529(EIF_REFERENCE);
extern EIF_TYPED_VALUE F28_530(EIF_REFERENCE);
extern void EIF_Minit28(void);

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

/* {CONVERGENCE_RESULT}.make */
void F28_528 (EIF_REFERENCE Current, EIF_TYPED_VALUE arg1x, EIF_TYPED_VALUE arg2x)
{
	GTCX
	char *l_feature_name = "make";
	RTEX;
#define arg1 arg1x.it_r8
#define arg2 arg2x.it_i4
	EIF_REAL_64 tr8_1;
	EIF_INTEGER_32 ti4_1;
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	if ((arg2x.type & SK_HEAD) == SK_REF) arg2x.it_i4 = * (EIF_INTEGER_32 *) arg2x.it_r;
	if ((arg1x.type & SK_HEAD) == SK_REF) arg1x.it_r8 = * (EIF_REAL_64 *) arg1x.it_r;
	
	RTLI(1);
	RTLR(0,Current);
	RTLIU(1);
	RTLU (SK_VOID, NULL);
	RTLU(SK_REAL64,&arg1);
	RTLU(SK_INT32,&arg2);
	RTLU (SK_REF, &Current);
	
	RTEAA(l_feature_name, 27, Current, 0, 2, 529);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(27, Current, 529);
	RTIV(Current, RTAL);
	if ((RTAL & CK_REQUIRE) || RTAC) {
		RTHOOK(1);
		RTCT("error_non_negative", EX_PRE);
		RTTE((EIF_BOOLEAN) (arg1 >= (EIF_REAL_64) 0.0), label_1);
		RTCK;
		RTJB;
label_1:
		RTCF;
	}
body:;
	RTHOOK(2);
	RTDBGAA(Current, dtype, 525, 0x20000000, 1); /* error_bound */
	*(EIF_REAL_64 *)(Current + RTWA(525, dtype)) = (EIF_REAL_64) arg1;
	RTHOOK(3);
	RTDBGAA(Current, dtype, 526, 0x10000000, 1); /* status */
	*(EIF_INTEGER_32 *)(Current + RTWA(526, dtype)) = (EIF_INTEGER_32) arg2;
	if (RTAL & CK_ENSURE) {
		RTHOOK(4);
		RTCT("error_bound_set", EX_POST);
		tr8_1 = *(EIF_REAL_64 *)(Current + RTWA(525, dtype));
		if ((EIF_BOOLEAN)(tr8_1 == arg1)) {
			RTCK;
		} else {
			RTCF;
		}
		RTHOOK(5);
		RTCT("status_set", EX_POST);
		ti4_1 = *(EIF_INTEGER_32 *)(Current + RTWA(526, dtype));
		if ((EIF_BOOLEAN)(ti4_1 == arg2)) {
			RTCK;
		} else {
			RTCF;
		}
	}
	RTVI(Current, RTAL);
	RTRS;
	RTHOOK(6);
	RTDBGLE;
	RTMD(0);
	RTLE;
	RTLO(4);
	RTEE;
#undef arg2
#undef arg1
}

/* {CONVERGENCE_RESULT}.error_bound */
EIF_TYPED_VALUE F28_529 (EIF_REFERENCE Current)
{
	EIF_TYPED_VALUE r;
	r.type = SK_REAL64;
	r.it_r8 = *(EIF_REAL_64 *)(Current + RTWA(525,Dtype(Current)));
	return r;
}


/* {CONVERGENCE_RESULT}.status */
EIF_TYPED_VALUE F28_530 (EIF_REFERENCE Current)
{
	EIF_TYPED_VALUE r;
	r.type = SK_INT32;
	r.it_i4 = *(EIF_INTEGER_32 *)(Current + RTWA(526,Dtype(Current)));
	return r;
}


void EIF_Minit28 (void)
{
	GTCX
}


#ifdef __cplusplus
}
#endif
