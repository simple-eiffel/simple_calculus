class CONVERGENCE_STATUS
	-- Status enum for convergence of forward/backward/central difference methods
	-- Values: CONVERGED (all agree), WARNING (2 agree, 1 differs), FAILED (all differ)

feature -- Constants

	converged: INTEGER = 0
		-- All three methods agree to within tolerance

	warning: INTEGER = 1
		-- Two methods agree, one differs

	failed: INTEGER = 2
		-- All three methods disagree significantly

feature -- Conversion

	to_string (status: INTEGER): STRING
			-- String representation of status
		require
			valid_status: status = converged or status = warning or status = failed
		do
			if status = converged then
				Result := "CONVERGED"
			elseif status = warning then
				Result := "WARNING"
			else
				Result := "FAILED"
			end
		ensure
			result_not_void: Result /= Void
			valid_result: Result.is_equal ("CONVERGED") or Result.is_equal ("WARNING") or Result.is_equal ("FAILED")
		end

end
