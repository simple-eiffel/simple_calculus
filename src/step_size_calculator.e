class STEP_SIZE_CALCULATOR
	-- Utility class for computing adaptive step size for numerical differentiation
	-- Formula: h = sqrt(ε) × max(|x|, 1.0)
	-- Assumption: works well for |f(x)| ~ O(1)
	-- Uses SIMPLE_MATH for all mathematical operations

create
	make

feature {NONE} -- Initialization

	make
			-- Create calculator with SIMPLE_MATH dependency
		do
			create math.make
		ensure
			math_not_void: math /= Void
		end

feature -- Constants

	machine_epsilon: REAL_64 = 2.220446049250313e-16
		-- Machine epsilon for REAL_64 (IEEE 754 double precision)

feature {NONE} -- Attributes

	math: SIMPLE_MATH
		-- Simple math library instance

feature -- Step Size Calculation

	compute_step_size (x: REAL_64): REAL_64
			-- Compute adaptive step size at point x
			-- Formula: h = sqrt(ε) × max(|x|, 1.0)
			-- Works well when |f(x)| ~ O(1)
		require
			x_valid: not x.is_nan
		local
			l_scale: REAL_64
		do
			l_scale := x.abs
			if l_scale < 1.0 then l_scale := 1.0 end
			Result := math.sqrt (machine_epsilon) * l_scale
		ensure
			result_positive: Result > 0.0
			result_not_nan: not Result.is_nan
			result_reasonable: Result >= math.sqrt(machine_epsilon) and Result <= math.sqrt(machine_epsilon) * x.abs.max(1.0) * 10.0
		end

	compute_step_size_with_magnitude (x: REAL_64; f_magnitude: REAL_64): REAL_64
			-- Compute adaptive step size with explicit function magnitude
			-- Useful when |f(x)| is known to differ significantly from O(1)
			-- Tier 2 API: allows override of default magnitude assumption
		require
			x_valid: not x.is_nan
			f_magnitude_positive: f_magnitude > 0.0
		local
			l_scale: REAL_64
		do
			l_scale := x.abs
			if l_scale < f_magnitude then l_scale := f_magnitude end
			Result := math.sqrt (machine_epsilon) * l_scale
		ensure
			result_positive: Result > 0.0
			result_not_nan: not Result.is_nan
		end

end
