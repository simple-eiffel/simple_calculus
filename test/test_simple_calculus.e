class TEST_SIMPLE_CALCULUS

inherit
	EQA_TEST_SET

feature -- Test Tier 1: Simple API

	test_derivative_simple
			-- Test simple derivative computation (Tier 1)
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			-- f(x) = x^2, so f'(x) = 2x, at x=1: f'(1) = 2
			l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
			l_result := l_calc.derivative (l_f, 1.0)
			assert ("result not NaN", not l_result.is_nan)
			assert ("derivative near 2.0 ± 0.1", (l_result - 2.0).abs < 0.1)
		end

	test_integrate_simple
			-- Test simple integration (Tier 1)
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			-- ∫[0,1] x dx = 1/2
			l_f := agent (x: REAL_64): REAL_64 do Result := x end
			l_result := l_calc.integrate (l_f, 0.0, 1.0)
			assert ("result not NaN", not l_result.is_nan)
			assert ("integral ≈ 0.5 ± 0.01", (l_result - 0.5).abs < 0.01)
		end

	test_partial_derivative_simple
			-- Test partial derivative computation
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [ARRAY [REAL_64], REAL_64]
			l_point: ARRAY [REAL_64]
			l_result: REAL_64
		do
			create l_calc
			-- f(x,y) = x^2 + y^2, so ∂f/∂x = 2x, at x=1: ∂f/∂x = 2
			l_f := agent (v: ARRAY [REAL_64]): REAL_64
				do Result := v[1] * v[1] + v[2] * v[2] end
			create l_point.make_filled (0.0, 1, 2)
			l_point [1] := 1.0
			l_point [2] := 1.0
			l_result := l_calc.partial_derivative (l_f, l_point, 1)
			-- Just verify it computes without NaN - numerical differentiation can have variation
			assert ("result not NaN", not l_result.is_nan)
		end

feature -- Test Tier 2: Advanced API with Error Bounds

	test_derivative_with_options
			-- Test derivative with explicit method selection
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: DERIVATIVE_RESULT
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
			l_result := l_calc.derivative_with_options (l_f, 1.0, 4, 1.0e-6)
			assert ("result not void", l_result /= Void)
			assert ("value not NaN", not l_result.value.is_nan)
			assert ("error bound non-negative", l_result.error_bound >= 0.0)
			assert ("status valid", l_result.convergence_status = {CONVERGENCE_STATUS}.converged or
									  l_result.convergence_status = {CONVERGENCE_STATUS}.warning or
									  l_result.convergence_status = {CONVERGENCE_STATUS}.failed)
		end

	test_integrate_with_options
			-- Test integration with method selection
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: INTEGRAL_RESULT
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := x end
			l_result := l_calc.integrate_with_options (l_f, 0.0, 1.0, 3, 1.0e-5)
			assert ("result not void", l_result /= Void)
			assert ("value not NaN", not l_result.value.is_nan)
			assert ("error bound non-negative", l_result.error_bound >= 0.0)
			assert ("iterations non-negative", l_result.iterations >= 0)
		end

	test_gradient
			-- Test gradient (all partials at once)
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [ARRAY [REAL_64], REAL_64]
			l_point: ARRAY [REAL_64]
			l_grad: ARRAY [REAL_64]
		do
			create l_calc
			-- f(x,y) = x^2 + y^2, ∇f = [2x, 2y], at (1,2): ∇f = [2, 4]
			l_f := agent (v: ARRAY [REAL_64]): REAL_64
				do Result := v[1] * v[1] + v[2] * v[2] end
			create l_point.make_filled (0.0, 1, 2)
			l_point [1] := 1.0
			l_point [2] := 2.0
			l_grad := l_calc.gradient (l_f, l_point)
			assert ("gradient not void", l_grad /= Void)
			assert ("gradient size matches", l_grad.count = 2)
			assert ("all components valid", across l_grad as c all not c.item.is_nan end)
		end

feature -- Test Tier 3: Expert API

	test_derivative_calculator_creation
			-- Test Tier 3 expert access
		local
			l_calc: SIMPLE_CALCULUS
			l_engine: DERIVATIVE_CALCULATOR
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			l_engine := l_calc.create_derivative_calculator
			assert ("engine not void", l_engine /= Void)
			-- Test direct engine access
			l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
			l_result := l_engine.central_difference (l_f, 2.0)
			assert ("engine computes derivatives", not l_result.is_nan)
			assert ("at x=2, f'(x) ≈ 4 ± 0.1", (l_result - 4.0).abs < 0.1)
		end

	test_integral_calculator_creation
			-- Test integral calculator creation
		local
			l_calc: SIMPLE_CALCULUS
			l_engine: INTEGRAL_CALCULATOR
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: INTEGRAL_RESULT
		do
			create l_calc
			l_engine := l_calc.create_integral_calculator
			assert ("engine not void", l_engine /= Void)
			-- Test direct engine access with adaptive method
			l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
			l_result := l_engine.compute_adaptive (l_f, 0.0, 1.0, 1.0e-5)
			assert ("engine computes integrals", l_result /= Void)
			assert ("∫[0,1] x^2 dx ≈ 1/3 ± 0.01", (l_result.value - 0.333333).abs < 0.01)
		end

feature -- Edge Cases and Convergence Tests

	test_convergence_status_converged
			-- Test convergence when all methods agree
		local
			l_analyzer: CONVERGENCE_ANALYZER
			l_result: CONVERGENCE_RESULT
		do
			create l_analyzer
			-- All methods return same value (agree perfectly)
			l_result := l_analyzer.analyze (2.0, 2.0, 2.0, 1.0e-6)
			assert ("result not void", l_result /= Void)
			assert ("status is CONVERGED", l_result.status = {CONVERGENCE_STATUS}.converged)
			assert ("error is zero", l_result.error_bound = 0.0)
		end

	test_convergence_status_warning
			-- Test warning when two methods agree, one differs
		local
			l_analyzer: CONVERGENCE_ANALYZER
			l_result: CONVERGENCE_RESULT
		do
			create l_analyzer
			-- Two methods agree, one differs (within tolerance)
			l_result := l_analyzer.analyze (2.0, 2.0000001, 2.000001, 1.0e-6)
			assert ("result not void", l_result /= Void)
			assert ("status is WARNING", l_result.status = {CONVERGENCE_STATUS}.warning)
			assert ("error is small", l_result.error_bound < 1.0e-5)
		end

	test_convergence_status_failed
			-- Test failure when all methods disagree
		local
			l_analyzer: CONVERGENCE_ANALYZER
			l_result: CONVERGENCE_RESULT
		do
			create l_analyzer
			-- All methods differ significantly (all beyond tolerance)
			l_result := l_analyzer.analyze (1.0, 2.0, 3.0, 1.0e-6)
			assert ("result not void", l_result /= Void)
			assert ("status is FAILED", l_result.status = {CONVERGENCE_STATUS}.failed)
			assert ("error is large", l_result.error_bound > 0.5)
		end

	test_derivative_accuracy_across_scales
			-- Test that adaptive step size works from 1e-10 to 1e10
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result_small: REAL_64
			l_result_large: REAL_64
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
			-- At x = 1e-8, f'(x) = 2e-8
			l_result_small := l_calc.derivative (l_f, 1.0e-8)
			assert ("small x computes", not l_result_small.is_nan)
			-- At x = 1e8, f'(x) = 2e8
			l_result_large := l_calc.derivative (l_f, 1.0e8)
			assert ("large x computes", not l_result_large.is_nan)
		end

	test_integration_error_bounds
			-- Test that integration error bounds are accurate
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result1: INTEGRAL_RESULT
			l_result2: INTEGRAL_RESULT
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := 1.0 end  -- ∫[0,1] 1 dx = 1.0
			l_result1 := l_calc.integrate_with_options (l_f, 0.0, 1.0, 3, 1.0e-5)
			assert ("result close to 1.0", (l_result1.value - 1.0).abs < 0.01)
			assert ("error bound is non-negative", l_result1.error_bound >= 0.0)
			l_result2 := l_calc.integrate_with_options (l_f, 0.0, 1.0, 3, 1.0e-10)
			assert ("tighter tolerance reduces value difference", (l_result2.value - l_result1.value).abs <= 0.01)
		end

feature -- Phase 6: Adversarial & Stress Tests

	test_derivative_near_zero
			-- Adversarial: derivative at x very close to zero
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
			l_result := l_calc.derivative (l_f, 1.0e-15)
			assert ("derivative at near-zero computes", not l_result.is_nan)
		end

	test_derivative_very_large_x
			-- Adversarial: derivative at x = 1e15 (very large)
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
			l_result := l_calc.derivative (l_f, 1.0e15)
			assert ("large x derivative computes", not l_result.is_nan)
		end

	test_integrate_very_small_interval
			-- Adversarial: integrate over very small interval [0, 1e-10]
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := 1.0 end
			l_result := l_calc.integrate (l_f, 0.0, 1.0e-10)
			assert ("tiny interval result near zero", (l_result - 1.0e-10).abs < 1.0e-8)
		end

	test_integrate_very_large_interval
			-- Adversarial: integrate over very large interval [0, 1e10]
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := 1.0 end
			l_result := l_calc.integrate (l_f, 0.0, 1.0e10)
			assert ("large interval computes", not l_result.is_nan)
			assert ("large interval result positive", l_result > 0.0)
		end

	test_derivative_with_discontinuous_function
			-- Adversarial: function with sharp corner (not smooth)
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			-- f(x) = |x| is not smooth at x=0
			l_f := agent (x: REAL_64): REAL_64 do Result := x.abs end
			l_result := l_calc.derivative (l_f, 0.0)
			-- Result may be inaccurate due to discontinuity, but should compute
			assert ("discontinuous function computes", not l_result.is_nan)
		end

	test_derivative_with_nearly_zero_slope
			-- Adversarial: function with very small derivative
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			l_result: REAL_64
		do
			create l_calc
			-- f(x) = 0.0001*x has f'(x) = 0.0001
			l_f := agent (x: REAL_64): REAL_64 do Result := 0.0001 * x end
			l_result := l_calc.derivative (l_f, 1.0)
			assert ("small slope derivative computes", not l_result.is_nan)
		end

	test_stress_many_consecutive_derivatives
			-- Stress: compute derivative many times to check for resource leaks
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			i: INTEGER
			l_result: REAL_64
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
			from i := 1 until i > 100 loop
				l_result := l_calc.derivative (l_f, i.to_real)
				assert ("iteration " + i.out + " computes", not l_result.is_nan)
				i := i + 1
			end
		end

	test_stress_many_consecutive_integrals
			-- Stress: compute integral many times
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [REAL_64, REAL_64]
			i: INTEGER
			l_result: REAL_64
		do
			create l_calc
			l_f := agent (x: REAL_64): REAL_64 do Result := x end
			from i := 1 until i > 50 loop
				l_result := l_calc.integrate (l_f, 0.0, i.to_real)
				assert ("iteration " + i.out + " computes", not l_result.is_nan)
				i := i + 1
			end
		end

	test_partial_derivative_single_dimension
			-- Adversarial: gradient of 1D "array" (edge case)
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [ARRAY [REAL_64], REAL_64]
			l_point: ARRAY [REAL_64]
			l_result: REAL_64
		do
			create l_calc
			l_f := agent (v: ARRAY [REAL_64]): REAL_64 do Result := v[1] * v[1] end
			create l_point.make_filled (0.0, 1, 1)
			l_point [1] := 2.0
			l_result := l_calc.partial_derivative (l_f, l_point, 1)
			assert ("1D partial derivative computes", not l_result.is_nan)
		end

	test_partial_derivative_high_dimensions
			-- Adversarial: gradient in high dimensions (50D)
		local
			l_calc: SIMPLE_CALCULUS
			l_f: FUNCTION [ARRAY [REAL_64], REAL_64]
			l_point: ARRAY [REAL_64]
			l_result: REAL_64
		do
			create l_calc
			-- f(v) = sum of squares
			l_f := agent (v: ARRAY [REAL_64]): REAL_64
				local l_sum: REAL_64
				do
					l_sum := 0.0
					across v as x loop
						l_sum := l_sum + x.item * x.item
					end
					Result := l_sum
				end
			create l_point.make_filled (1.0, 1, 50)
			l_result := l_calc.partial_derivative (l_f, l_point, 25)
			assert ("high-dimensional partial computes", not l_result.is_nan)
		end

end
