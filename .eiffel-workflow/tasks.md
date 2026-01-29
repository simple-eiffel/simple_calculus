# Implementation Tasks: simple_calculus

**Phase:** 3 - Task Decomposition
**Date:** 2026-01-29
**Status:** READY FOR IMPLEMENTATION

---

## Overview

simple_calculus is a numerical calculus library with 9 classes implementing:
- Adaptive derivatives (forward/backward/central with automatic comparison)
- Adaptive integration (Simpson's rule with Richardson extrapolation)
- 3-tier API (simple/advanced/expert)
- Immutable results (SCOOP-safe concurrency)

**Total Tasks:** 9 implementation units + 2 fix-contract tasks = 11 total

---

## Fix-Contract Tasks (Do First)

### FIX-1: Contract Issues - High Priority
**Files:** src/step_size_calculator.e, src/integral_calculator.e, src/eigenvalue_result.e
**Severity:** HIGH (blocks Phase 1 completion)
**Dependencies:** None

### Acceptance Criteria
- [ ] STEP_SIZE_CALCULATOR.compute_step_size: Change postcondition `result_reasonable: Result > 1.0e-15 and Result < 1.0e-5` to scale-aware bound
- [ ] INTEGRAL_CALCULATOR.compute_adaptive: Change postcondition `iterations_positive: Result.iterations > 0` to `iterations_non_negative: Result.iterations >= 0`
- [ ] Remove dependency: determinant() stub breaking inverse() precondition (Phase 2 only)
- [ ] Add precondition to solve(): `well_conditioned: condition_number <= 1.0e12`

### Implementation Notes
From approach.md:
- Step size formula: h = sqrt(machine_epsilon) × max(|x|, 1.0)
- Postcondition should validate: `result >= sqrt(2.2e-16) and result <= sqrt(2.2e-16) * max(|x|, 1.0) * 10.0`
- Iterations >= 0 allows immediate convergence (tolerance already satisfied on first call)

---

### FIX-2: Contract Documentation
**Files:** src/derivative_result.e, src/integral_result.e
**Severity:** MEDIUM
**Dependencies:** FIX-1

### Acceptance Criteria
- [ ] DERIVATIVE_RESULT: Add postcondition clarifying error_bound semantics: "error_bound = max(|forward - central|, |backward - central|) (absolute difference, not relative)"
- [ ] INTEGRAL_RESULT: Add postcondition clarifying error_bound: "error_bound = |result_n - result_{n-1}| (Richardson extrapolation estimate, not guaranteed bound)"
- [ ] Both: Document that error_bound is absolute, not relative to value magnitude

### Implementation Notes
From Ollama/Claude review findings:
- Users need to understand when error_bound is absolute vs relative
- Prevents misuse when values are very large/small

---

## Implementation Tasks (Core Features)

### TASK-1: CONVERGENCE_STATUS Enum
**Files:** src/convergence_status.e
**Features:** `converged`, `warning`, `failed` (constants), `to_string(status)`
**Complexity:** Trivial
**Estimated LOC:** 30
**Dependencies:** None

### Acceptance Criteria
- [ ] Feature `converged`: Returns 0 (or equivalent constant)
- [ ] Feature `warning`: Returns 1
- [ ] Feature `failed`: Returns 2
- [ ] Feature `to_string(status: INTEGER): STRING` returns "CONVERGED", "WARNING", or "FAILED"
- [ ] Precondition `valid_status: status = converged or status = warning or status = failed`
- [ ] Default case: Fallback to "FAILED" if invalid (with note in postcondition)
- [ ] Compiles clean (no warnings)
- [ ] Skeletal test passes

### Implementation Notes
- Simple enum replacement (Eiffel doesn't have enums, so use constants + functions)
- Used by CONVERGENCE_RESULT and DERIVATIVE_RESULT
- No external dependencies

---

### TASK-2: STEP_SIZE_CALCULATOR
**Files:** src/step_size_calculator.e
**Features:** `compute_step_size(x: REAL_64): REAL_64`
**Complexity:** Low
**Estimated LOC:** 40
**Dependencies:** SIMPLE_MATH (must exist)

### Acceptance Criteria
- [ ] Feature `compute_step_size` computes: h = sqrt(machine_epsilon) × max(|x|, 1.0)
- [ ] Machine epsilon value: 2.220446049250313e-16 (IEEE 754 REAL_64)
- [ ] Precondition: `x_valid: not x.is_nan`, `x_finite: not x.is_infinite` (fix from FIX-1)
- [ ] Postcondition: `result_positive: Result > 0.0`, `result_valid: not Result.is_nan`
- [ ] Postcondition: Fixed formula-aware bound (from FIX-1)
- [ ] Uses SIMPLE_MATH.sqrt for square root
- [ ] Compiles clean
- [ ] Unit test: test_compute_step_size_at_origin (x=0 → h ≈ 1.49e-8)
- [ ] Unit test: test_compute_step_size_at_one (x=1 → h ≈ 1.49e-8)
- [ ] Unit test: test_compute_step_size_at_large_x (x=1e6 → h ≈ 1.49e-2)

### Implementation Notes
- Core utility used by DERIVATIVE_CALCULATOR
- No loops, no state, pure computation
- Machine epsilon defined at class level or computed once
- See approach.md line 131-143 for formula details

---

### TASK-3: CONVERGENCE_ANALYZER
**Files:** src/convergence_analyzer.e
**Features:** `analyze(forward_deriv, backward_deriv, central_deriv, tolerance: REAL_64): CONVERGENCE_RESULT`
**Complexity:** Low
**Estimated LOC:** 60
**Dependencies:** CONVERGENCE_STATUS, CONVERGENCE_RESULT

### Acceptance Criteria
- [ ] Feature `analyze` compares three derivatives via absolute differences
- [ ] Computes: `forward_diff = |forward_deriv - central_deriv|`
- [ ] Computes: `backward_diff = |backward_deriv - central_deriv|`
- [ ] Assigns status based on tolerance:
  - CONVERGED: Both diffs < tolerance
  - WARNING: One diff < tolerance, one >= tolerance
  - FAILED: Both diffs >= tolerance
- [ ] Returns CONVERGENCE_RESULT with error_bound = max(forward_diff, backward_diff)
- [ ] Precondition: `tolerance_positive: tolerance > 0.0`, `tolerance_reasonable: tolerance >= 1.0e-12 and tolerance <= 1.0e-3`
- [ ] No NaN/Infinity handling (assume valid input from DERIVATIVE_CALCULATOR)
- [ ] Compiles clean
- [ ] Unit test: test_analyze_converged (all three methods close)
- [ ] Unit test: test_analyze_warning (one method off)
- [ ] Unit test: test_analyze_failed (all methods diverge)

### Implementation Notes
- Called by DERIVATIVE_CALCULATOR.compute_with_comparison
- Pure function: no state, no I/O
- Error metric is absolute difference from central method (most accurate)
- See approach.md line 46-55 for convergence logic

---

### TASK-4: DERIVATIVE_RESULT Data Class
**Files:** src/derivative_result.e
**Features:** `make(a_value, a_error_bound, a_status)`, value, error_bound, convergence_status (getters)
**Complexity:** Trivial
**Estimated LOC:** 40
**Dependencies:** None

### Acceptance Criteria
- [ ] Feature `make` stores three fields: value, error_bound, convergence_status
- [ ] Postcondition: `value_set: value = a_value`
- [ ] Postcondition: `error_bound_set: error_bound = a_error_bound` (clarify semantics from FIX-2)
- [ ] Postcondition: `convergence_status_set: convergence_status = a_status`
- [ ] All fields immutable (no setters) → SCOOP-safe
- [ ] Compiles clean
- [ ] Skeletal test: test_derivative_result_creation

### Implementation Notes
- Pure data class (immutable container)
- Returned by Tier 2 derivative methods
- From approach.md line 97-101

---

### TASK-5: INTEGRAL_RESULT Data Class
**Files:** src/integral_result.e
**Features:** `make(a_value, a_error_bound, a_iterations)`, value, error_bound, iterations (getters)
**Complexity:** Trivial
**Estimated LOC:** 40
**Dependencies:** None

### Acceptance Criteria
- [ ] Feature `make` stores three fields: value, error_bound, iterations
- [ ] Postcondition: `value_set: value = a_value`
- [ ] Postcondition: `error_bound_set: error_bound = a_error_bound` (clarify semantics from FIX-2)
- [ ] Postcondition: `iterations_set: iterations = a_iterations`
- [ ] All fields immutable (no setters) → SCOOP-safe
- [ ] Compiles clean
- [ ] Skeletal test: test_integral_result_creation

### Implementation Notes
- Pure data class (immutable container)
- Returned by Tier 2 integral methods
- From approach.md line 102-106

---

### TASK-6: DERIVATIVE_CALCULATOR Engine
**Files:** src/derivative_calculator.e
**Features:** `forward_difference(f, x, h)`, `backward_difference(f, x, h)`, `central_difference(f, x, h)`, `compute_with_comparison(f, x, h, tolerance)`
**Complexity:** Medium
**Estimated LOC:** 120
**Dependencies:** SIMPLE_MATH, CONVERGENCE_ANALYZER, DERIVATIVE_RESULT, STEP_SIZE_CALCULATOR

### Acceptance Criteria
- [ ] Feature `forward_difference` computes: (f(x+h) - f(x)) / h
- [ ] Feature `backward_difference` computes: (f(x) - f(x-h)) / h
- [ ] Feature `central_difference` computes: (f(x+h) - f(x-h)) / (2*h)
- [ ] All three methods return REAL_64
- [ ] Precondition on all: `f_valid: f /= Void`, `x_valid: not x.is_nan`, `h_valid: h > 0.0`
- [ ] Feature `compute_with_comparison` calls all three methods, then CONVERGENCE_ANALYZER
- [ ] Returns DERIVATIVE_RESULT with value (central), error_bound, convergence_status
- [ ] Compiles clean
- [ ] Unit test: test_forward_difference_on_linear (f(x)=2x, exact at h→0)
- [ ] Unit test: test_backward_difference_on_linear
- [ ] Unit test: test_central_difference_on_linear
- [ ] Unit test: test_convergence_via_comparison

### Implementation Notes
- Core engine for derivative computation
- FUNCTION agent used for f (from Eiffel 6.2+ or simple_function agent library)
- Three methods always computed (minimal overhead)
- See approach.md line 30-60 for algorithm details

---

### TASK-7: INTEGRAL_CALCULATOR Engine
**Files:** src/integral_calculator.e
**Features:** `trapezoidal(f, a, b, n_intervals)`, `simpson(f, a, b, n_intervals)`, `compute_adaptive(f, a, b, tolerance, max_iterations)`
**Complexity:** Medium
**Estimated LOC:** 150
**Dependencies:** SIMPLE_MATH, INTEGRAL_RESULT

### Acceptance Criteria
- [ ] Feature `trapezoidal` computes Simpson's rule with n intervals (O(h²) error)
- [ ] Feature `simpson` computes Simpson's rule (O(h⁴) error, requires even n)
- [ ] Feature `compute_adaptive` uses Richardson extrapolation:
  - Start with n intervals
  - Double intervals, recompute
  - Check: |result_new - result_old| < tolerance
  - Repeat up to max_iterations (default 100)
- [ ] Returns INTEGRAL_RESULT with value, error_bound (difference), iterations (count)
- [ ] Precondition: `a_less_than_b: a < b`, `tolerance_positive: tolerance > 0.0`, `max_iterations_positive: max_iterations > 0`
- [ ] Postcondition: `iterations_non_negative: Result.iterations >= 0` (fixed from FIX-1)
- [ ] Compiles clean
- [ ] Unit test: test_trapezoidal_on_linear
- [ ] Unit test: test_simpson_on_quadratic
- [ ] Unit test: test_adaptive_convergence

### Implementation Notes
- Tier 1 default: adaptive with tolerance 1e-5
- Tier 2 allows custom tolerance and max_iterations
- Richardson extrapolation: compare two different discretizations
- See approach.md line 61-86 for algorithm details

---

### TASK-8: SIMPLE_CALCULUS Facade - Tier 1 (Simple API)
**Files:** src/simple_calculus.e
**Features:** `derivative(f, x)`, `integrate(f, a, b)`, `partial_derivative(f, x_index, x_array)`
**Complexity:** Low
**Estimated LOC:** 80
**Dependencies:** STEP_SIZE_CALCULATOR, DERIVATIVE_CALCULATOR, INTEGRAL_CALCULATOR

### Acceptance Criteria
- [ ] Feature `derivative` computes central difference with auto step size
  - Calls STEP_SIZE_CALCULATOR.compute_step_size(x)
  - Calls DERIVATIVE_CALCULATOR.central_difference(f, x, h)
  - Returns REAL_64 (just the value, no error_bound)
- [ ] Feature `integrate` adaptive integration with default tolerance 1e-5
  - Calls INTEGRAL_CALCULATOR.compute_adaptive(f, a, b, 1e-5, 100)
  - Returns REAL_64 (just the value)
- [ ] Feature `partial_derivative` computes ∂f/∂x_i
  - Perturb only variable at index i in array
  - Use central difference (most accurate)
  - Returns REAL_64
- [ ] All preconditions check input validity
- [ ] Compiles clean
- [ ] Unit test: test_derivative_of_parabola
- [ ] Unit test: test_integral_of_parabola
- [ ] Unit test: test_partial_derivative

### Implementation Notes
- Simplest API: just call main computation methods
- Default tolerances from approach.md: 1e-6 (derivative), 1e-5 (integral)
- Partial derivative: perturb one component at a time
- No error bounds returned (Tier 1 = simple)

---

### TASK-9: SIMPLE_CALCULUS Facade - Tier 2 (Advanced API)
**Files:** src/simple_calculus.e (addition)
**Features:** `derivative_with_options(f, x, step_size)`, `integrate_with_options(f, a, b, tolerance, max_iterations)`, `gradient(f, x_array)`
**Complexity:** Medium
**Estimated LOC:** 80
**Dependencies:** DERIVATIVE_RESULT, INTEGRAL_RESULT, DERIVATIVE_CALCULATOR, INTEGRAL_CALCULATOR

### Acceptance Criteria
- [ ] Feature `derivative_with_options` allows custom step_size
  - Calls DERIVATIVE_CALCULATOR.compute_with_comparison(f, x, step_size, 1e-6)
  - Returns DERIVATIVE_RESULT with value, error_bound, convergence_status
- [ ] Feature `integrate_with_options` allows custom tolerance and max_iterations
  - Calls INTEGRAL_CALCULATOR.compute_adaptive(f, a, b, tolerance, max_iterations)
  - Returns INTEGRAL_RESULT with value, error_bound, iterations
- [ ] Feature `gradient` computes ∇f = [∂f/∂x_1, ∂f/∂x_2, ..., ∂f/∂x_n]
  - Returns VECTOR_N of partial derivatives
  - Uses auto step size for each component
- [ ] All preconditions validate inputs
- [ ] Postconditions validate results
- [ ] Compiles clean
- [ ] Unit test: test_derivative_with_custom_step_size
- [ ] Unit test: test_integrate_with_custom_tolerance
- [ ] Unit test: test_gradient_computation

### Implementation Notes
- Tier 2 = advanced: users control step size, tolerance, precision
- DERIVATIVE_RESULT/INTEGRAL_RESULT give quality metrics
- Gradient is vector of partial derivatives (multi-variable calculus)
- See approach.md line 54-60 for Tier 2 API structure

---

### TASK-10: SIMPLE_CALCULUS Facade - Tier 3 (Expert API)
**Files:** src/simple_calculus.e (addition)
**Features:** `create_derivative_calculator()`, `create_integral_calculator()`
**Complexity:** Trivial
**Estimated LOC:** 20
**Dependencies:** DERIVATIVE_CALCULATOR, INTEGRAL_CALCULATOR

### Acceptance Criteria
- [ ] Feature `create_derivative_calculator` returns new DERIVATIVE_CALCULATOR instance
  - With pre-configured STEP_SIZE_CALCULATOR and CONVERGENCE_ANALYZER
  - Users can call individual methods directly
- [ ] Feature `create_integral_calculator` returns new INTEGRAL_CALCULATOR instance
  - For custom integration algorithms
- [ ] Postconditions ensure objects are properly initialized
- [ ] Compiles clean
- [ ] Skeletal test: test_expert_access

### Implementation Notes
- Tier 3 = expert: direct access to engines for custom logic
- Users might extend DERIVATIVE_CALCULATOR with custom convergence criteria
- From approach.md line 54-60

---

## Task Dependencies

```
FIX-1 (Contract Issues)
├── FIX-2 (Contract Documentation)
└── TASK-1 (CONVERGENCE_STATUS)
    ├── TASK-3 (CONVERGENCE_ANALYZER)
    │   └── TASK-6 (DERIVATIVE_CALCULATOR)
    │       ├── TASK-2 (STEP_SIZE_CALCULATOR)
    │       └── TASK-8 (SIMPLE_CALCULUS Tier 1)
    │           └── TASK-9 (SIMPLE_CALCULUS Tier 2)
    │               └── TASK-10 (SIMPLE_CALCULUS Tier 3)
    │
    ├── TASK-4 (DERIVATIVE_RESULT)
    │   └── TASK-6 (above)
    │
    └── TASK-5 (INTEGRAL_RESULT)
        └── TASK-7 (INTEGRAL_CALCULATOR)
            └── TASK-8 (above)
```

**Build Order:**
1. FIX-1, FIX-2 (contracts)
2. TASK-1 (enum)
3. TASK-2 (step size)
4. TASK-3, TASK-4, TASK-5 (utilities & data)
5. TASK-6, TASK-7 (engines)
6. TASK-8, TASK-9, TASK-10 (facade)

---

## Compilation Gates

After each task implementation:
```bash
cd /d/prod/simple_calculus && /d/prod/ec.sh -batch -config simple_calculus.ecf -target simple_calculus_tests -c_compile
```

**Expected:** "System Recompiled"
**Zero warnings policy:** Fix immediately if any warnings appear

---

## Testing Strategy

### Unit Tests (Per Task)
- Written in test/test_simple_calculus.e
- Each task has 2-3 acceptance criteria tests
- Use mathematical functions for verification:
  - Linear: f(x) = 2x (derivatives should be exact at h→0)
  - Quadratic: f(x) = x² (derivatives, integrals exact)
  - Transcendental: f(x) = sin(x), e^x (convergence tests)

### Integration Tests (After All Tasks)
- Test full Tier 1, Tier 2, Tier 3 workflows
- Verify immutability (no state leaks)
- Verify SCOOP safety (concurrent calls)

---

## Summary

| Task | Type | LOC | Deps | Priority |
|------|------|-----|------|----------|
| FIX-1 | Fix | 10 | 0 | Critical |
| FIX-2 | Fix | 5 | 0 | High |
| TASK-1 | Code | 30 | 0 | High |
| TASK-2 | Code | 40 | simple_math | High |
| TASK-3 | Code | 60 | TASK-1 | High |
| TASK-4 | Code | 40 | 0 | High |
| TASK-5 | Code | 40 | 0 | High |
| TASK-6 | Code | 120 | TASK-2,3,4 | Critical |
| TASK-7 | Code | 150 | simple_math | Critical |
| TASK-8 | Code | 80 | TASK-2,6,7 | Critical |
| TASK-9 | Code | 80 | TASK-6,7,4,5 | High |
| TASK-10 | Code | 20 | TASK-6,7 | Medium |
| **Total** | **Code** | **~675** | | |

**Estimated Implementation Time:** 2-3 days for experienced Eiffel developer

---

## Success Criteria

- ✅ All 11 tasks implemented
- ✅ Compiles clean (zero warnings)
- ✅ All tests pass (40+ unit tests)
- ✅ Contracts verified (DBC intact)
- ✅ SCOOP-safe (no shared mutable state)
- ✅ Ready for Phase 4 (API documentation)

---

**Status:** READY FOR PHASE 4 (Implementation)
**Approved by:** [User confirmation needed]
**Date:** 2026-01-29
