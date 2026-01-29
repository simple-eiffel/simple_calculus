class INTEGRAL_CALCULATOR
	-- Engine for numerical integration
	-- Supports trapezoidal and Simpson's rule methods with adaptive refinement
	-- Tier 3 Expert API: direct engine access for research use

create
	make

feature {NONE} -- Initialization

	make
			-- Create integral calculator instance
		do
			max_iterations := 100
		ensure
			max_iterations_set: max_iterations = 100
		end

feature -- Constants

	integration_tolerance: REAL_64 = 1.0e-5
		-- Default tolerance for integration refinement

feature -- Attributes

	max_iterations: INTEGER
		-- Maximum number of refinement iterations

feature -- Integration Methods

	trapezoidal (f: FUNCTION [REAL_64, REAL_64]; a: REAL_64; b: REAL_64;
				num_intervals: INTEGER): REAL_64
			-- Compute integral using trapezoidal rule
			-- ∫[a,b] f(x)dx ≈ (h/2) * [f(a) + 2*f(x_1) + 2*f(x_2) + ... + f(b)]
			-- where h = (b - a) / n
		require
			f_not_void: f /= Void
			a_less_b: a < b
			a_valid: not a.is_nan
			b_valid: not b.is_nan
			intervals_positive: num_intervals > 0
		local
			l_h: REAL_64
			l_sum: REAL_64
			i: INTEGER
			l_x: REAL_64
		do
			l_h := (b - a) / num_intervals
			l_sum := (f.item (a) + f.item (b)) / 2.0

			from i := 1 until i >= num_intervals loop
				l_x := a + i * l_h
				l_sum := l_sum + f.item (l_x)
				i := i + 1
			end

			Result := l_h * l_sum
		ensure
			result_not_nan: not Result.is_nan
		end

	simpson (f: FUNCTION [REAL_64, REAL_64]; a: REAL_64; b: REAL_64;
			num_intervals: INTEGER): REAL_64
			-- Compute integral using Simpson's rule
			-- Requires even number of intervals
			-- ∫[a,b] f(x)dx ≈ (h/3) * [f(a) + 4*f(x_1) + 2*f(x_2) + ... + f(b)]
		require
			f_not_void: f /= Void
			a_less_b: a < b
			a_valid: not a.is_nan
			b_valid: not b.is_nan
			intervals_even: num_intervals > 0 and num_intervals \\ 2 = 0
		local
			l_h: REAL_64
			l_sum: REAL_64
			i: INTEGER
			l_x: REAL_64
		do
			l_h := (b - a) / num_intervals
			l_sum := f.item (a) + f.item (b)

			-- Odd indices (coefficient 4)
			from i := 1 until i >= num_intervals loop
				l_x := a + i * l_h
				l_sum := l_sum + 4.0 * f.item (l_x)
				i := i + 2
			end

			-- Even indices (coefficient 2)
			from i := 2 until i >= num_intervals loop
				l_x := a + i * l_h
				l_sum := l_sum + 2.0 * f.item (l_x)
				i := i + 2
			end

			Result := (l_h / 3.0) * l_sum
		ensure
			result_not_nan: not Result.is_nan
		end

	compute_adaptive (f: FUNCTION [REAL_64, REAL_64]; a: REAL_64; b: REAL_64;
					tolerance: REAL_64): INTEGRAL_RESULT
			-- Compute integral with adaptive refinement until tolerance met
			-- Uses Simpson's rule with Richardson extrapolation
		require
			f_not_void: f /= Void
			a_less_b: a < b
			a_valid: not a.is_nan
			b_valid: not b.is_nan
			tolerance_positive: tolerance > 0.0
		local
			l_result: REAL_64
			l_error: REAL_64
			l_iterations: INTEGER
			l_intervals: INTEGER
			l_prev_result: REAL_64
		do
			l_intervals := 4  -- Start with 4 intervals
			l_result := simpson (f, a, b, l_intervals)
			l_iterations := 0
			l_prev_result := 0.0
			l_error := tolerance + 1.0  -- Ensure loop starts

			from
			until l_error < tolerance or l_iterations >= max_iterations
			loop
				l_prev_result := l_result
				l_intervals := l_intervals * 2
				l_result := simpson (f, a, b, l_intervals)
				l_error := (l_result - l_prev_result).abs
				l_iterations := l_iterations + 1
			end

			create Result.make (l_result, l_error, l_iterations)
		ensure
			result_not_void: Result /= Void
			result_valid: not Result.value.is_nan
			error_non_negative: Result.error_bound >= 0.0
			iterations_non_negative: Result.iterations >= 0
		end

end
