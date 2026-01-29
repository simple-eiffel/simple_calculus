class INTEGRAL_RESULT
	-- Result of numerical integration containing value, error bound, and iteration count
	-- Immutable: enables SCOOP concurrent use

create
	make

feature {NONE} -- Initialization

	make (a_value: REAL_64; a_error_bound: REAL_64; a_iterations: INTEGER)
			-- Create result with integral value, error bound, and iteration count
		require
			error_non_negative: a_error_bound >= 0.0
			iterations_non_negative: a_iterations >= 0
		do
			value := a_value
			error_bound := a_error_bound
			iterations := a_iterations
		ensure
			value_set: value = a_value
			error_bound_set: error_bound = a_error_bound
			iterations_set: iterations = a_iterations
		end

feature -- Access

	value: REAL_64
		-- Computed integral value

	error_bound: REAL_64
		-- Error bound estimate for integral
		-- Computed from difference between Richardson extrapolation results

	iterations: INTEGER
		-- Number of iterations performed by integration method
		-- Higher iterations indicate finer subdivision for better accuracy

feature -- Queries

	is_accurate: BOOLEAN
			-- True if error bound is within typical acceptable range (< 1e-5)
		do
			Result := error_bound < 1.0e-5
		ensure
			result_valid: Result = (error_bound < 1.0e-5)
		end

end
