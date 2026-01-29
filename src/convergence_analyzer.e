class CONVERGENCE_ANALYZER
	-- Utility class for analyzing convergence of forward/backward/central difference methods
	-- Compares three derivative estimates and assigns convergence status

create
	default_create

feature -- Constants

	default_tolerance: REAL_64 = 1.0e-6
		-- Default relative tolerance for method agreement

feature -- Analysis

	analyze (forward_deriv: REAL_64; backward_deriv: REAL_64; central_deriv: REAL_64;
			tolerance: REAL_64): CONVERGENCE_RESULT
			-- Analyze convergence of three methods
			-- Return status and error bound
		require
			tolerance_positive: tolerance > 0.0
			tolerance_reasonable: tolerance >= 1.0e-12 and tolerance <= 1.0e-3
			forward_valid: not forward_deriv.is_nan
			backward_valid: not backward_deriv.is_nan
			central_valid: not central_deriv.is_nan
		local
			l_error_fwd_cent: REAL_64
			l_error_bwd_cent: REAL_64
			l_error_bound: REAL_64
			l_status: INTEGER
		do
			-- Compute differences from central (most accurate)
			l_error_fwd_cent := (forward_deriv - central_deriv).abs
			l_error_bwd_cent := (backward_deriv - central_deriv).abs
			if l_error_fwd_cent >= l_error_bwd_cent then
				l_error_bound := l_error_fwd_cent
			else
				l_error_bound := l_error_bwd_cent
			end

			-- Determine status based on method agreement
			if l_error_fwd_cent < tolerance and l_error_bwd_cent < tolerance then
				-- All three agree
				l_status := {CONVERGENCE_STATUS}.converged
			elseif (l_error_fwd_cent < tolerance) or (l_error_bwd_cent < tolerance) then
				-- Two methods agree
				l_status := {CONVERGENCE_STATUS}.warning
			else
				-- All methods differ significantly
				l_status := {CONVERGENCE_STATUS}.failed
			end

			create Result.make (l_error_bound, l_status)
		ensure
			result_not_void: Result /= Void
			error_non_negative: Result.error_bound >= 0.0
			status_valid: Result.status = {CONVERGENCE_STATUS}.converged or
						 Result.status = {CONVERGENCE_STATUS}.warning or
						 Result.status = {CONVERGENCE_STATUS}.failed
		end

end
