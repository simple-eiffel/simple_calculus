class SIMPLE_CALCULUS
	-- Numerical calculus library facade
	-- Provides derivatives, integrals, and partial derivatives through 3-tier API
	-- Tier 1: Simple (most users), Tier 2: Advanced (control), Tier 3: Expert (research)
	-- All methods void-safe and SCOOP-compatible (immutable results)

feature -- Tier 1: Simple API (for beginners)

	derivative (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
			-- Compute derivative of f at point x using central difference
			-- Returns single REAL_64 value (error bound in Tier 2)
		require
			f_not_void: f /= Void
			x_valid: not x.is_nan
		local
			l_calc: DERIVATIVE_CALCULATOR
		do
			create l_calc.make
			Result := l_calc.central_difference (f, x)
		ensure
			result_not_nan: not Result.is_nan
		end

	integrate (f: FUNCTION [REAL_64, REAL_64]; a: REAL_64; b: REAL_64): REAL_64
			-- Compute integral of f from a to b using adaptive Simpson's rule
			-- Returns single REAL_64 value (error bound in Tier 2)
		require
			f_not_void: f /= Void
			a_less_b: a < b
			a_valid: not a.is_nan
			b_valid: not b.is_nan
		local
			l_calc: INTEGRAL_CALCULATOR
			l_result: INTEGRAL_RESULT
		do
			create l_calc.make
			l_result := l_calc.compute_adaptive (f, a, b, 1.0e-5)
			Result := l_result.value
		ensure
			result_not_nan: not Result.is_nan
		end

	partial_derivative (f: FUNCTION [ARRAY [REAL_64], REAL_64];
					  point: ARRAY [REAL_64]; var_index: INTEGER): REAL_64
			-- Compute partial derivative ∂f/∂x_i at given point
			-- Returns single REAL_64 value
		require
			f_not_void: f /= Void
			point_not_void: point /= Void
			point_not_empty: point.count > 0
			var_index_valid: var_index >= 1 and var_index <= point.count
		local
			l_calc: DERIVATIVE_CALCULATOR
		do
			create l_calc.make
			Result := l_calc.partial_derivative (f, point, var_index, 1.0e-6)
		ensure
			result_not_nan: not Result.is_nan
		end

feature -- Tier 2: Advanced API (for control and tuning)

	derivative_with_options (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64;
							method: INTEGER; tolerance: REAL_64): DERIVATIVE_RESULT
			-- Compute derivative with explicit method and tolerance control
			-- method: 1=forward, 2=backward, 3=central, 4=all with comparison
			-- Returns DERIVATIVE_RESULT with value, error_bound, and convergence_status
		require
			f_not_void: f /= Void
			x_valid: not x.is_nan
			method_valid: method >= 1 and method <= 4
			tolerance_positive: tolerance > 0.0
			tolerance_reasonable: tolerance >= 1.0e-12 and tolerance <= 1.0e-3
		local
			l_calc: DERIVATIVE_CALCULATOR
			l_fwd: REAL_64
			l_bwd: REAL_64
			l_cent: REAL_64
		do
			create l_calc.make

			if method = 1 then
				-- Forward difference only
				l_fwd := l_calc.forward_difference (f, x)
				create Result.make (l_fwd, 0.0, {CONVERGENCE_STATUS}.converged)
			elseif method = 2 then
				-- Backward difference only
				l_bwd := l_calc.backward_difference (f, x)
				create Result.make (l_bwd, 0.0, {CONVERGENCE_STATUS}.converged)
			elseif method = 3 then
				-- Central difference only
				l_cent := l_calc.central_difference (f, x)
				create Result.make (l_cent, 0.0, {CONVERGENCE_STATUS}.converged)
			else
				-- All three with comparison
				Result := l_calc.compute_with_comparison (f, x, tolerance)
			end
		ensure
			result_not_void: Result /= Void
			result_valid: not Result.value.is_nan
			error_non_negative: Result.error_bound >= 0.0
		end

	integrate_with_options (f: FUNCTION [REAL_64, REAL_64]; a: REAL_64; b: REAL_64;
							method: INTEGER; tolerance: REAL_64): INTEGRAL_RESULT
			-- Compute integral with explicit method and tolerance control
			-- method: 1=trapezoidal, 2=Simpson's, 3=adaptive (recommended)
			-- Returns INTEGRAL_RESULT with value, error_bound, and iteration count
		require
			f_not_void: f /= Void
			a_less_b: a < b
			a_valid: not a.is_nan
			b_valid: not b.is_nan
			method_valid: method >= 1 and method <= 3
			tolerance_positive: tolerance > 0.0
		local
			l_calc: INTEGRAL_CALCULATOR
			l_value: REAL_64
			l_intervals: INTEGER
		do
			create l_calc.make

			if method = 1 then
				-- Trapezoidal (fixed, 100 intervals)
				l_intervals := 100
				l_value := l_calc.trapezoidal (f, a, b, l_intervals)
				create Result.make (l_value, 0.0, 1)
			elseif method = 2 then
				-- Simpson's (fixed, 100 intervals)
				l_intervals := 100
				l_value := l_calc.simpson (f, a, b, l_intervals)
				create Result.make (l_value, 0.0, 1)
			else
				-- Adaptive Simpson's (recommended)
				Result := l_calc.compute_adaptive (f, a, b, tolerance)
			end
		ensure
			result_not_void: Result /= Void
			result_valid: not Result.value.is_nan
			error_non_negative: Result.error_bound >= 0.0
		end

	gradient (f: FUNCTION [ARRAY [REAL_64], REAL_64];
			point: ARRAY [REAL_64]): ARRAY [REAL_64]
			-- Compute all partial derivatives at once (gradient vector)
			-- Returns array where result[i] = ∂f/∂x_i
		require
			f_not_void: f /= Void
			point_not_void: point /= Void
			point_not_empty: point.count > 0
		local
			l_calc: DERIVATIVE_CALCULATOR
			i: INTEGER
		do
			create l_calc.make
			create Result.make_filled (0.0, 1, point.count)

			from i := 1 until i > point.count loop
				Result [i] := l_calc.partial_derivative (f, point, i, 1.0e-6)
				i := i + 1
			end
		ensure
			result_not_void: Result /= Void
			result_size_matches: Result.count = point.count
			all_valid: across Result as r all not r.item.is_nan end
		end

feature -- Tier 3: Expert API (for research and advanced use)

	create_derivative_calculator: DERIVATIVE_CALCULATOR
			-- Create derivative calculator for direct engine access
			-- Tier 3 expert use case: research, custom algorithms, performance tuning
		do
			create Result.make
		ensure
			result_not_void: Result /= Void
		end

	create_integral_calculator: INTEGRAL_CALCULATOR
			-- Create integral calculator for direct engine access
			-- Tier 3 expert use case: research, custom algorithms, performance tuning
		do
			create Result.make
		ensure
			result_not_void: Result /= Void
		end

end
