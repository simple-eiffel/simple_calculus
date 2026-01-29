class DERIVATIVE_CALCULATOR
	-- Engine for numerical differentiation
	-- Computes forward, backward, and central differences with automatic comparison
	-- Tier 3 Expert API: direct engine access for research use

create
	make

feature {NONE} -- Initialization

	make
			-- Create derivative calculator instance
		do
			create step_calculator.make
			create analyzer.default_create
		ensure
			calculator_initialized: step_calculator /= Void and analyzer /= Void
		end

feature {NONE} -- Attributes

	step_calculator: STEP_SIZE_CALCULATOR
		-- Utility for computing adaptive step sizes

	analyzer: CONVERGENCE_ANALYZER
		-- Utility for analyzing method convergence

feature -- Derivative Computation

	forward_difference (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
			-- Compute derivative using forward difference formula
			-- f'(x) ≈ (f(x + h) - f(x)) / h
		require
			f_not_void: f /= Void
			x_valid: not x.is_nan
		local
			l_h: REAL_64
			l_f_x: REAL_64
			l_f_xh: REAL_64
		do
			l_h := step_calculator.compute_step_size (x)
			l_f_x := f.item (x)
			l_f_xh := f.item (x + l_h)
			Result := (l_f_xh - l_f_x) / l_h
		ensure
			result_not_nan: not Result.is_nan
		end

	backward_difference (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
			-- Compute derivative using backward difference formula
			-- f'(x) ≈ (f(x) - f(x - h)) / h
		require
			f_not_void: f /= Void
			x_valid: not x.is_nan
		local
			l_h: REAL_64
			l_f_x: REAL_64
			l_f_xh: REAL_64
		do
			l_h := step_calculator.compute_step_size (x)
			l_f_x := f.item (x)
			l_f_xh := f.item (x - l_h)
			Result := (l_f_x - l_f_xh) / l_h
		ensure
			result_not_nan: not Result.is_nan
		end

	central_difference (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
			-- Compute derivative using central difference formula (most accurate)
			-- f'(x) ≈ (f(x + h) - f(x - h)) / (2h)
		require
			f_not_void: f /= Void
			x_valid: not x.is_nan
		local
			l_h: REAL_64
			l_f_xh: REAL_64
			l_f_xhm: REAL_64
		do
			l_h := step_calculator.compute_step_size (x)
			l_f_xh := f.item (x + l_h)
			l_f_xhm := f.item (x - l_h)
			Result := (l_f_xh - l_f_xhm) / (2.0 * l_h)
		ensure
			result_not_nan: not Result.is_nan
		end

	compute_with_comparison (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64;
							tolerance: REAL_64): DERIVATIVE_RESULT
			-- Compute derivative using all three methods and return result with error bound
			-- Automatically analyzes convergence
		require
			f_not_void: f /= Void
			x_valid: not x.is_nan
			tolerance_positive: tolerance > 0.0
		local
			l_fwd: REAL_64
			l_bwd: REAL_64
			l_cent: REAL_64
			l_analysis: CONVERGENCE_RESULT
		do
			-- Compute all three methods
			l_fwd := forward_difference (f, x)
			l_bwd := backward_difference (f, x)
			l_cent := central_difference (f, x)

			-- Analyze convergence
			l_analysis := analyzer.analyze (l_fwd, l_bwd, l_cent, tolerance)

			-- Return central difference result (most accurate) with error bound
			create Result.make (l_cent, l_analysis.error_bound, l_analysis.status)
		ensure
			result_not_void: Result /= Void
			result_valid: not Result.value.is_nan
			error_non_negative: Result.error_bound >= 0.0
		end

feature -- Partial Derivatives

	partial_derivative (f: FUNCTION [ARRAY [REAL_64], REAL_64];
					  point: ARRAY [REAL_64]; var_index: INTEGER;
					  tolerance: REAL_64): REAL_64
			-- Compute partial derivative ∂f/∂x_i at given point
			-- Perturbs x_i while holding other variables constant
		require
			f_not_void: f /= Void
			point_not_void: point /= Void
			point_not_empty: point.count > 0
			var_index_valid: var_index >= 1 and var_index <= point.count
			tolerance_positive: tolerance > 0.0
		local
			l_h: REAL_64
			l_f_base: REAL_64
			l_f_plus: REAL_64
			l_f_minus: REAL_64
			l_point_plus: ARRAY [REAL_64]
			l_point_minus: ARRAY [REAL_64]
		do
			-- Adaptive step size based on current variable value
			l_h := step_calculator.compute_step_size (point [var_index])

			-- Create perturbed point arrays
			create l_point_plus.make_from_array (point)
			create l_point_minus.make_from_array (point)

			-- Perturb variable
			l_point_plus [var_index] := point [var_index] + l_h
			l_point_minus [var_index] := point [var_index] - l_h

			-- Evaluate function at perturbed points
			l_f_base := f.item (point)
			l_f_plus := f.item (l_point_plus)
			l_f_minus := f.item (l_point_minus)

			-- Central difference formula
			Result := (l_f_plus - l_f_minus) / (2.0 * l_h)
		ensure
			result_not_nan: not Result.is_nan
		end

end
