/*
 * Code for class TEST_APP
 */

#include "eif_eiffel.h"
#include "../E1/estructure.h"


#ifdef __cplusplus
extern "C" {
#endif

extern void F39_835(EIF_REFERENCE);
extern void F39_836(EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE);
extern void EIF_Minit39(void);
extern EIF_REFERENCE _A59_56();
extern EIF_REFERENCE _A59_67();
extern EIF_REFERENCE _A59_61();
extern EIF_REFERENCE _A59_72();
extern EIF_REFERENCE _A59_55();
extern EIF_REFERENCE _A59_66();
extern EIF_REFERENCE _A59_60();
extern EIF_REFERENCE _A59_71();
extern EIF_REFERENCE _A59_54();
extern EIF_REFERENCE _A59_65();
extern EIF_REFERENCE _A59_59();
extern EIF_REFERENCE _A59_70();
extern EIF_REFERENCE _A59_53();
extern EIF_REFERENCE _A59_64();
extern EIF_REFERENCE _A59_58();
extern EIF_REFERENCE _A59_69();
extern EIF_REFERENCE _A59_52();
extern EIF_REFERENCE _A59_63();
extern EIF_REFERENCE _A59_57();
extern EIF_REFERENCE _A59_68();
extern EIF_REFERENCE _A59_51();
extern EIF_REFERENCE _A59_62();
extern EIF_REFERENCE _A59_73();

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

/* {TEST_APP}.make */
void F39_835 (EIF_REFERENCE Current)
{
	GTCX
	char *l_feature_name = "make";
	RTEX;
	EIF_REFERENCE loc1 = (EIF_REFERENCE) 0;
	EIF_TYPED_VALUE ur1x = {{0}, SK_REF};
#define ur1 ur1x.it_r
	EIF_TYPED_VALUE ur2x = {{0}, SK_REF};
#define ur2 ur2x.it_r
	EIF_REFERENCE tr1 = NULL;
	EIF_REFERENCE tr2 = NULL;
	EIF_REFERENCE tr3 = NULL;
	RTCFDT;
	RTCDT;
	RTSN;
	RTDA;
	RTLD;
	
	RTLI(7);
	RTLR(0,tr1);
	RTLR(1,ur1);
	RTLR(2,Current);
	RTLR(3,loc1);
	RTLR(4,tr2);
	RTLR(5,tr3);
	RTLR(6,ur2);
	RTLIU(7);
	RTLU (SK_VOID, NULL);
	RTLU (SK_REF, &Current);
	RTLU(SK_REF, &loc1);
	
	RTEAA(l_feature_name, 38, Current, 1, 0, 923);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(38, Current, 923);
	RTIV(Current, RTAL);
	RTHOOK(1);
	tr1 = RTMS_EX_H("simple_calculus test suite\012",27,63507466);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(2);
	tr1 = RTMS_EX_H("Phase 5: Test Verification\012\012",28,1049309194);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(3);
	RTDBGAL(1, 0xF800003A, 0, 0); /* loc1 */
	tr1 = RTLN(eif_new_type(58, 0x01).id);
	(FUNCTION_CAST(void, (EIF_REFERENCE)) RTWC(32, Dtype(tr1)))(tr1);
	RTNHOOK(3,1);
	loc1 = (EIF_REFERENCE) RTCCL(tr1);
	RTHOOK(4);
	tr1 = RTMS_EX_H("=== Tier 1: Simple API ===\012",27,1280318730);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(5);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_51, (EIF_POINTER)(0),1043, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("derivative_simple",17,672568165);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(6);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_52, (EIF_POINTER)(0),1044, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("integrate_simple",16,113519461);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(7);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_53, (EIF_POINTER)(0),1045, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("partial_derivative_simple",25,102129765);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(8);
	tr1 = RTMS_EX_H("\012=== Tier 2: Advanced API ===\012",30,435091466);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(9);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_54, (EIF_POINTER)(0),1046, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("derivative_with_options",23,228672883);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(10);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_55, (EIF_POINTER)(0),1047, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("integrate_with_options",22,1742594163);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(11);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_56, (EIF_POINTER)(0),1048, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("gradient",8,1379587956);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(12);
	tr1 = RTMS_EX_H("\012=== Tier 3: Expert API ===\012",28,1384707338);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(13);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_57, (EIF_POINTER)(0),1049, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("derivative_calculator_creation",30,1280757358);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(14);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_58, (EIF_POINTER)(0),1050, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("integral_calculator_creation",28,815020142);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(15);
	tr1 = RTMS_EX_H("\012=== Edge Cases & Convergence ===\012",34,152729610);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(16);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_59, (EIF_POINTER)(0),1051, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("convergence_status_converged",28,795441764);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(17);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_60, (EIF_POINTER)(0),1052, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("convergence_status_warning",26,170813287);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(18);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_61, (EIF_POINTER)(0),1053, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("convergence_status_failed",25,814359396);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(19);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_62, (EIF_POINTER)(0),1054, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("derivative_accuracy_across_scales",33,2092796275);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(20);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_63, (EIF_POINTER)(0),1055, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("integration_error_bounds",24,102174323);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(21);
	tr1 = RTMS_EX_H("\012=== Phase 6: Adversarial & Stress Tests ===\012",45,937677066);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(22);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_64, (EIF_POINTER)(0),1056, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("derivative_near_zero",20,866353007);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(23);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_65, (EIF_POINTER)(0),1057, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("derivative_very_large_x",23,2021272184);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(24);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_66, (EIF_POINTER)(0),1058, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("integrate_very_small_interval",29,1562565740);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(25);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_67, (EIF_POINTER)(0),1059, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("integrate_very_large_interval",29,1223732076);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(26);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_68, (EIF_POINTER)(0),1060, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("derivative_with_discontinuous_function",38,1949440622);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(27);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_69, (EIF_POINTER)(0),1061, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("derivative_with_nearly_zero_slope",33,44380261);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(28);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_70, (EIF_POINTER)(0),1062, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("stress_many_consecutive_derivatives",35,830219891);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(29);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_71, (EIF_POINTER)(0),1063, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("stress_many_consecutive_integrals",33,1153341811);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(30);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_72, (EIF_POINTER)(0),1064, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("partial_derivative_single_dimension",35,1211920494);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(31);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFFF9,1,222,0xFF01,58,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr1 = RTLNTS(typres0.id, 2, 0);
	}
	((EIF_TYPED_VALUE *)tr1+1)->it_r = loc1;
	RTAR(tr1,loc1);
	
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(dftype, typarr0)));
		tr2= RTLNRW(typres0.id, 0, (EIF_POINTER) _A59_73, (EIF_POINTER)(0),1065, 0, 0, 1, -1, tr1, 0);
	}
	ur1 = RTCCL(tr2);
	tr3 = RTMS_EX_H("partial_derivative_high_dimensions",34,1093766771);
	ur2 = tr3;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE, EIF_TYPED_VALUE)) RTWF(833, dtype))(Current, ur1x, ur2x);
	RTHOOK(32);
	tr1 = RTMS_EX_H("\012=== Summary ===\012",17,1177101066);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(33);
	tr1 = RTMS_EX_H("Phase 6 hardening verification complete\012",40,2053635082);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTVI(Current, RTAL);
	RTRS;
	RTHOOK(34);
	RTDBGLE;
	RTMD(0);
	RTLE;
	RTLO(3);
	RTEE;
#undef ur1
#undef ur2
}

/* {TEST_APP}.safe_run_test */
#undef EIF_VOLATILE
#define EIF_VOLATILE volatile
void F39_836 (EIF_REFERENCE Current, EIF_TYPED_VALUE arg1x, EIF_TYPED_VALUE arg2x)
{
	GTCX
	char *l_feature_name = "safe_run_test";
	RTEX;
	RTED;
	EIF_REFERENCE EIF_VOLATILE saved_except = (EIF_REFERENCE) 0;
#define arg1 arg1x.it_r
#define arg2 arg2x.it_r
	RTS_SDX;
	EIF_TYPED_VALUE up1x = {{0}, SK_POINTER};
#define up1 up1x.it_p
	EIF_TYPED_VALUE ur1x = {{0}, SK_REF};
#define ur1 ur1x.it_r
	EIF_REFERENCE  EIF_VOLATILE tr1 = NULL;
	EIF_REFERENCE  EIF_VOLATILE tr2 = NULL;
	RTCDT;
	RTSN;
	RTDA;
	RTDT;
	RTLD;
	RTXD;
	RTLXD;
	
	
	RTLI(7);
	RTLR(0,arg1);
	RTLR(1,arg2);
	RTLR(2,tr1);
	RTLR(3,ur1);
	RTLR(4,tr2);
	RTLR(5,Current);
	RTLR(6,saved_except);
	RTLIU(7);
	RTXSLS;
	RTLU (SK_VOID, NULL);
	RTLU(SK_REF,&arg1);
	RTLU(SK_REF,&arg2);
	RTLU (SK_REF, &Current);
	RTLXL;
	
	RTEAA(l_feature_name, 38, Current, 0, 2, 924);
	RTSA(dtype);
	RTSC;
	RTME(dtype, 0);
	RTGC;
	RTDBGEAA(38, Current, 924);
	{
		static EIF_TYPE_INDEX typarr0[] = {0xFF01,310,0xFF01,0xFFF9,0,222,0xFFFF};
		EIF_TYPE typres0;
		static EIF_TYPE typcache0 = {INVALID_DTYPE, 0};
		
		typres0 = (typcache0.id != INVALID_DTYPE ? typcache0 : (typcache0 = eif_compound_id(Dftype(Current), typarr0)));
		RTCC(arg1, 38, l_feature_name, 1, typres0, 0x01);
	}
	RTCC(arg2, 38, l_feature_name, 2, eif_new_type(270, 0x01), 0x01);
	RTIV(Current, RTAL);
	RTE_T
	RTHOOK(1);
	tr1 = RTMS_EX_H("  \342\234\223 ",6,1717592608);
	ur1 = RTCCL(arg2);
	tr2 = ((up1x = (FUNCTION_CAST(EIF_TYPED_VALUE, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4841, "plus", tr1))(tr1, ur1x)), (((up1x.type & SK_HEAD) == SK_REF)? (EIF_REFERENCE) 0: (up1x.it_r = RTBU(up1x))), (up1x.type = SK_POINTER), up1x.it_r);
	ur1 = RTCCL(tr2);
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTHOOK(2);
	ur1 = NULL;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTVF(4658, "call", arg1))(arg1, ur1x);
	RTHOOK(3);
	tr1 = RTMS_EX_H(" - PASS\012",8,193845258);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTVI(Current, RTAL);
	RTRS;
	RTE_E
	RTLXE;
	RTXSC;
	RTS_SRR
	RTHOOK(4);
	tr1 = RTMS_EX_H(" - FAIL\012",8,193111306);
	ur1 = tr1;
	(FUNCTION_CAST(void, (EIF_REFERENCE, EIF_TYPED_VALUE)) RTWF(30, dtype))(Current, ur1x);
	RTMD(0);
	/* NOTREACHED */
	RTE_EE
	RTHOOK(5);
	RTDBGLE;
	RTMD(0);
	RTEOK;
	RTLE;
	RTLO(4);
#undef up1
#undef ur1
#undef arg2
#undef arg1
}
#undef EIF_VOLATILE
#define EIF_VOLATILE

void EIF_Minit39 (void)
{
	GTCX
}


#ifdef __cplusplus
}
#endif
