note
	description: "Test runner for simple_calculus"

class TEST_APP

create
	make

feature {NONE}

	make
			-- Run all tests
		local
			l_test_suite: TEST_SIMPLE_CALCULUS
		do
			print ("simple_calculus test suite%N")
			print ("Phase 5: Test Verification%N%N")

			create l_test_suite

			-- Tier 1 tests
			print ("=== Tier 1: Simple API ===%N")
			safe_run_test (agent l_test_suite.test_derivative_simple, "derivative_simple")
			safe_run_test (agent l_test_suite.test_integrate_simple, "integrate_simple")
			safe_run_test (agent l_test_suite.test_partial_derivative_simple, "partial_derivative_simple")

			-- Tier 2 tests
			print ("%N=== Tier 2: Advanced API ===%N")
			safe_run_test (agent l_test_suite.test_derivative_with_options, "derivative_with_options")
			safe_run_test (agent l_test_suite.test_integrate_with_options, "integrate_with_options")
			safe_run_test (agent l_test_suite.test_gradient, "gradient")

			-- Tier 3 tests
			print ("%N=== Tier 3: Expert API ===%N")
			safe_run_test (agent l_test_suite.test_derivative_calculator_creation, "derivative_calculator_creation")
			safe_run_test (agent l_test_suite.test_integral_calculator_creation, "integral_calculator_creation")

			-- Edge cases
			print ("%N=== Edge Cases & Convergence ===%N")
			safe_run_test (agent l_test_suite.test_convergence_status_converged, "convergence_status_converged")
			safe_run_test (agent l_test_suite.test_convergence_status_warning, "convergence_status_warning")
			safe_run_test (agent l_test_suite.test_convergence_status_failed, "convergence_status_failed")
			safe_run_test (agent l_test_suite.test_derivative_accuracy_across_scales, "derivative_accuracy_across_scales")
			safe_run_test (agent l_test_suite.test_integration_error_bounds, "integration_error_bounds")

			-- Adversarial & Stress Tests (Phase 6)
			print ("%N=== Phase 6: Adversarial & Stress Tests ===%N")
			safe_run_test (agent l_test_suite.test_derivative_near_zero, "derivative_near_zero")
			safe_run_test (agent l_test_suite.test_derivative_very_large_x, "derivative_very_large_x")
			safe_run_test (agent l_test_suite.test_integrate_very_small_interval, "integrate_very_small_interval")
			safe_run_test (agent l_test_suite.test_integrate_very_large_interval, "integrate_very_large_interval")
			safe_run_test (agent l_test_suite.test_derivative_with_discontinuous_function, "derivative_with_discontinuous_function")
			safe_run_test (agent l_test_suite.test_derivative_with_nearly_zero_slope, "derivative_with_nearly_zero_slope")
			safe_run_test (agent l_test_suite.test_stress_many_consecutive_derivatives, "stress_many_consecutive_derivatives")
			safe_run_test (agent l_test_suite.test_stress_many_consecutive_integrals, "stress_many_consecutive_integrals")
			safe_run_test (agent l_test_suite.test_partial_derivative_single_dimension, "partial_derivative_single_dimension")
			safe_run_test (agent l_test_suite.test_partial_derivative_high_dimensions, "partial_derivative_high_dimensions")

			print ("%N=== Summary ===%N")
			print ("Phase 6 hardening verification complete%N")
		end

	safe_run_test (test: PROCEDURE; test_name: STRING)
			-- Run a test safely and catch exceptions
		do
			print ("  ✓ " + test_name)
			test.call (Void)
			print (" - PASS%N")
		rescue
			print (" - FAIL%N")
		end

end
