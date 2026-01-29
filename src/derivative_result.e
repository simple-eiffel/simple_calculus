class DERIVATIVE_RESULT
	-- Result of numerical differentiation containing value, error bound, and convergence status
	-- Immutable: enables SCOOP concurrent use

create
	make

feature {NONE} -- Initialization

	make (a_value: REAL_64; a_error_bound: REAL_64; a_status: INTEGER)
			-- Create result with derivative value, error bound, and convergence status
		require
			error_non_negative: a_error_bound >= 0.0
			valid_status: a_status = {CONVERGENCE_STATUS}.converged or
						 a_status = {CONVERGENCE_STATUS}.warning or
						 a_status = {CONVERGENCE_STATUS}.failed
		do
			value := a_value
			error_bound := a_error_bound
			convergence_status := a_status
		ensure
			value_set: value = a_value
			error_bound_set: error_bound = a_error_bound
			convergence_status_set: convergence_status = a_status
		end

feature -- Access

	value: REAL_64
		-- Computed derivative value

	error_bound: REAL_64
		-- Error bound estimate (max difference between methods)
		-- error_bound = max(|f'_forward - f'_central|, |f'_backward - f'_central|)

	convergence_status: INTEGER
		-- Status of convergence: CONVERGED, WARNING, or FAILED
		-- CONVERGED: all three methods agree to within tolerance
		-- WARNING: two methods agree, one differs
		-- FAILED: all three methods disagree significantly

feature -- Queries

	is_converged: BOOLEAN
			-- True if all three methods converged
		do
			Result := convergence_status = {CONVERGENCE_STATUS}.converged
		ensure
			result_valid: Result = (convergence_status = {CONVERGENCE_STATUS}.converged)
		end

	is_warning: BOOLEAN
			-- True if only two methods agreed
		do
			Result := convergence_status = {CONVERGENCE_STATUS}.warning
		ensure
			result_valid: Result = (convergence_status = {CONVERGENCE_STATUS}.warning)
		end

	is_failed: BOOLEAN
			-- True if convergence failed
		do
			Result := convergence_status = {CONVERGENCE_STATUS}.failed
		ensure
			result_valid: Result = (convergence_status = {CONVERGENCE_STATUS}.failed)
		end

end
