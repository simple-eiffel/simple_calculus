class CONVERGENCE_RESULT
	-- Result of convergence analysis
	-- Returned by CONVERGENCE_ANALYZER

create
	make

feature {NONE} -- Initialization

	make (a_error_bound: REAL_64; a_status: INTEGER)
			-- Create result with error bound and status
		require
			error_non_negative: a_error_bound >= 0.0
		do
			error_bound := a_error_bound
			status := a_status
		ensure
			error_bound_set: error_bound = a_error_bound
			status_set: status = a_status
		end

feature -- Access

	error_bound: REAL_64
		-- Error bound (max distance between methods)

	status: INTEGER
		-- Convergence status

end
