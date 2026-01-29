# 07-SPECIFICATION: simple_calculus

## Executive Summary
This document provides the formal OOSC2 specification for all classes in simple_calculus, including complete contracts, invariants, and implementation guidelines.

---

## SPECIFICATION DOCUMENT STRUCTURE

Each class specification includes:
1. **Class Clause** - Purpose, abstraction, invariants
2. **Feature Specifications** - Each public feature with full contracts
3. **Implementation Hints** - Algorithms and design guidance
4. **Correspondence** to Eiffel Code

---

## CLASS SPECIFICATION: SIMPLE_CALCULUS

### 1.1 Class Purpose and Abstraction

**Purpose:** Provide user-facing facade for numerical differentiation and integration operations on real-valued functions.

**Abstraction:** Encapsulates choice of algorithm, step size selection, error estimation, and convergence validation. Users see simple API; implementation details hidden.

**Implementation Form:** Stateless facade. No persistent state beyond configuration.

### 1.2 Class Invariant

```eiffel
invariant
    tolerance_positive: tolerance > 0.0
        -- Convergence tolerance must be positive
        -- Rationale: Zero/negative tolerance is meaningless
        -- Usage: Guards convergence checks

    max_iterations_positive: max_iterations > 0
        -- Maximum iterations must allow at least one
        -- Rationale: Prevents infinite loops
        -- Usage: Bounds refinement loops

    max_iterations_reasonable: max_iterations <= 10000
        -- Guard against runaway computation
        -- Rationale: >10000 iterations suggests unfixable problem
        -- Usage: Fail-safe for ill-conditioned functions
```

### 1.3 Specification: derivative

```eiffel
feature -- Tier 1

derivative (f: attached FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
    -- Numerical derivative of f at point x
    -- Using adaptive central difference (most accurate)

    require
        x_is_finite: x.is_finite
            -- x must not be NaN or Infinity
            -- Violation: Silent failure (returns NaN)
            -- Recovery: Caller validates input

        x_in_reasonable_range: x.abs < {REAL_64}.max_value / 100.0
            -- x not too close to extremes (avoid overflow on x±h)
            -- Violation: May return NaN
            -- Recovery: Scale or translate function

    ensure
        result_is_finite: not (Result.is_nan or Result.is_infinite)
            -- Output always computable
            -- Interpretation: Result may not be meaningful if preconditions violated
            -- Usage: Further computation with result is safe

    definition: -- Mathematical specification
        -- Result approximates f'(x) using:
        -- f'(x) ≈ [f(x+h) - f(x-h)] / (2h) where h = sqrt(epsilon) * max(|x|, 1.0)
        -- Error: O(h²) = O(epsilon^(2/3)) ≈ 1e-11 for well-behaved f
        -- If f not smooth: Result may be arbitrarily inaccurate

    algorithm:
        -- 1. Compute h = sqrt(machine_epsilon) * max(|x|, 1.0)
        -- 2. Evaluate f at x-h, x, x+h
        -- 3. Compute forward, backward, central differences
        -- 4. Return central difference (most accurate)
        -- 5. Internally compare methods; if divergence detected, result unreliable
```

### 1.4 Specification: integrate

```eiffel
feature -- Tier 1

integrate (f: attached FUNCTION [REAL_64, REAL_64]; a, b: REAL_64): REAL_64
    -- Numerical integral of f from a to b using Simpson's rule

    require
        a_is_finite: a.is_finite
            -- Lower bound representable

        b_is_finite: b.is_finite
            -- Upper bound representable

        bounds_ordered: a < b
            -- Interval must be forward (not backward, not zero-width)
            -- Violation: Returns garbage or exception
            -- Recovery: Validate bounds before call

        interval_not_degenerate: b - a > {REAL_64}.epsilon
            -- Interval width must exceed machine epsilon
            -- Violation: Lost significance; returns meaningless result
            -- Recovery: Ensure interval is meaningful

    ensure
        result_is_finite: not (Result.is_nan or Result.is_infinite)
            -- Output always computable

    definition: -- Mathematical specification
        -- Result approximates ∫[a,b] f(x) dx using Simpson's rule
        -- Starting grid: n=4 intervals
        -- Refinement: Double n until |Simpson_n - Trapezoidal_n| < tolerance
        -- Result = Simpson estimate after convergence
        -- Error: O((b-a)^5 / (180*n^4)) ≈ 1e-12 for smooth f with n~100

    algorithm:
        -- 1. Start with n = 4 intervals
        -- 2. Compute trapezoidal rule estimate (T_n)
        -- 3. Compute Simpson rule estimate (S_n)
        -- 4. If |S_n - T_n| < tolerance: return S_n (converged)
        -- 5. Else: double n, repeat steps 2-4
        -- 6. Abort if iterations > max_iterations
```

### 1.5 Specification: derivative_with_error

```eiffel
feature -- Tier 2

derivative_with_error (f: attached FUNCTION [REAL_64, REAL_64];
                      x: REAL_64): DERIVATIVE_RESULT
    -- Derivative with error estimate and convergence status

    require
        x_is_finite: x.is_finite
        x_in_range: x.abs < {REAL_64}.max_value / 100.0

    ensure
        result_not_void: Result /= Void
            -- Always returns result object

        result_value_finite: not (Result.derivative_value.is_nan or Result.derivative_value.is_infinite)
            -- Main estimate always finite

        error_bound_non_negative: Result.error_bound >= 0.0
            -- Error pessimistic (>= true error)

        error_bound_reasonable: Result.error_bound <= 10.0 * Result.derivative_value.abs + 1.0
            -- Error not absurdly large compared to result

        bounds_consistent: Result.lower_error_bound <= Result.upper_error_bound
            -- Confidence interval makes mathematical sense

        method_agreement_valid: Result.method_agreement >= 0.0 and Result.method_agreement <= 1.0
            -- Agreement metric normalized

    definition: -- Mathematical specification
        -- Result contains:
        -- .derivative_value: mean of forward, backward, central differences
        -- .forward_diff: [f(x+h) - f(x)] / h
        -- .backward_diff: [f(x) - f(x-h)] / h
        -- .central_diff: [f(x+h) - f(x-h)] / (2h)
        -- .error_bound: max(|forward-central|, |backward-central|) / 2
        -- .method_agreement: 1 - (method_divergence / typical_derivative_magnitude)
        -- .convergence_status: CONVERGED if methods agree >99%, DIVERGED if <90%

    algorithm:
        -- 1. Compute h = sqrt(epsilon) * max(|x|, 1.0)
        -- 2. Evaluate f at x-h, x, x+h
        -- 3. Compute forward, backward, central differences
        -- 4. Compute error_bound = max difference between methods
        -- 5. Compute method_agreement metric
        -- 6. Determine convergence_status from agreement
        -- 7. Return DERIVATIVE_RESULT with all values
```

### 1.6 Specification: integrate_with_error

```eiffel
feature -- Tier 2

integrate_with_error (f: attached FUNCTION [REAL_64, REAL_64];
                     a, b: REAL_64): INTEGRAL_RESULT
    -- Integration with error estimate and convergence status

    require
        bounds_ordered: a < b
        a_is_finite: a.is_finite
        b_is_finite: b.is_finite
        interval_not_degenerate: b - a > {REAL_64}.epsilon

    ensure
        result_not_void: Result /= Void

        result_finite: not (Result.integral_value.is_nan or Result.integral_value.is_infinite)

        error_bound_non_negative: Result.error_bound >= 0.0

        error_consistency: Result.error_bound <= 10.0 * Result.integral_value.abs + 1.0

        bounds_consistent: Result.lower_error_bound <= Result.upper_error_bound

        convergence_guarantee:
            Result.convergence_status = CONVERGED implies Result.error_bound < tolerance

        iterations_bounded: Result.iterations_required <= max_iterations

        early_termination:
            Result.error_bound < tolerance implies Result.iterations_required < max_iterations

    definition: -- Mathematical specification
        -- Result contains:
        -- .integral_value: Simpson's rule estimate
        -- .trapezoidal_value: Trapezoidal rule estimate
        -- .simpson_value: Simpson's rule estimate
        -- .error_bound: |simpson - trapezoidal|
        -- .convergence_status: CONVERGED if error < tolerance after refinement
        -- .iterations_required: Number of grid refinements until convergence
        -- .final_grid_size: Number of intervals in final grid

    algorithm:
        -- 1. Start with n = 4 intervals
        -- 2. Compute trapezoidal rule (T_n)
        -- 3. Compute Simpson rule (S_n)
        -- 4. Compute error_bound = |S_n - T_n|
        -- 5. If error_bound < tolerance: converged; set status=CONVERGED
        -- 6. Else: double n, increment iteration counter, repeat from step 2
        -- 7. If iterations >= max_iterations: set status=DIVERGED
        -- 8. Return INTEGRAL_RESULT with all values
```

### 1.7 Feature: set_tolerance

```eiffel
feature

set_tolerance (t: REAL_64)
    -- Configure convergence tolerance

    require
        t_positive: t > 0.0
            -- Tolerance must be positive

        t_reasonable: t < 1.0
            -- Tolerance < 100% error (otherwise meaningless)

    ensure
        tolerance_set: tolerance = t
            -- Tolerance recorded exactly

        invariant_maintained: tolerance > 0.0
            -- Invariant not violated by setter
```

---

## CLASS SPECIFICATION: DERIVATIVE_CALCULATOR

### 2.1 Class Purpose

**Purpose:** Implement numerical differentiation algorithms (forward, backward, central difference).

**Abstraction:** Encapsulates finite difference computation with error estimation.

**Implementation Form:** Stateless algorithm engine.

### 2.2 Class Invariant

```eiffel
invariant
    -- No state to maintain invariant (stateless)
```

### 2.3 Specification: derivative_central

```eiffel
feature

derivative_central (f: attached FUNCTION [REAL_64, REAL_64]; x, h: REAL_64): REAL_64
    -- Central difference derivative estimate
    -- f'(x) ≈ [f(x+h) - f(x-h)] / (2h)

    require
        x_finite: x.is_finite
        h_positive: h > 0.0
        h_small: h < 1.0
        perturbations_safe: (x + h).is_finite and (x - h).is_finite

    ensure
        result_finite: not (Result.is_nan or Result.is_infinite)

    definition:
        -- Result = (f.item(x+h) - f.item(x-h)) / (2*h)
        -- Assumes: f is C^3 continuous on [x-h, x+h]
        -- Error: O(h^4) for f''''(ξ) term, plus rounding error ~machine_epsilon
        -- Optimal h ~ epsilon^(1/3) * max(|f(x)|, 1) [for minimizing total error]

    algorithm:
        -- 1. Compute f_plus = f(x+h)
        -- 2. Compute f_minus = f(x-h)
        -- 3. Return (f_plus - f_minus) / (2*h)
```

### 2.4 Specification: derivative_with_error

```eiffel
feature

derivative_with_error (f: attached FUNCTION [REAL_64, REAL_64];
                      x, h: REAL_64): DERIVATIVE_RESULT
    -- Compute all three methods; compare and return with error estimate

    require
        x_finite: x.is_finite
        h_positive: h > 0.0
        h_small: h < 1.0
        perturbations_safe: (x + h).is_finite and (x - h).is_finite

    ensure
        result_not_void: Result /= Void

        all_methods_finite:
            not (Result.forward_diff.is_nan or Result.forward_diff.is_infinite) and
            not (Result.backward_diff.is_nan or Result.backward_diff.is_infinite) and
            not (Result.central_diff.is_nan or Result.central_diff.is_infinite)

        error_non_negative: Result.error_bound >= 0.0

        agreement_in_range: 0.0 <= Result.method_agreement and Result.method_agreement <= 1.0

        convergence_consistency:
            Result.method_agreement > 0.99 implies Result.convergence_status = CONVERGED and
            Result.method_agreement < 0.90 implies Result.convergence_status = DIVERGED

    definition:
        -- Let: F = forward difference
        --      B = backward difference
        --      C = central difference
        -- Result.derivative_value = C (most accurate)
        -- Result.error_bound = max(|F-C|, |B-C|) / 2
        -- Result.method_agreement = 1 - (max_divergence / typical_magnitude)
        --     where max_divergence = max(|F-C|, |B-C|)
        --     and typical_magnitude = |C| + epsilon

    algorithm:
        -- 1. Compute forward difference
        -- 2. Compute backward difference
        -- 3. Compute central difference
        -- 4. Compute max difference between pairs
        -- 5. Compute agreement metric from divergence
        -- 6. Determine convergence status from agreement
        -- 7. Return DERIVATIVE_RESULT with all values
```

---

## CLASS SPECIFICATION: INTEGRAL_CALCULATOR

### 3.1 Class Purpose

**Purpose:** Implement numerical integration algorithms (trapezoidal, Simpson's rule).

**Abstraction:** Encapsulates quadrature computation with adaptive grid refinement.

**Implementation Form:** Stateless algorithm engine.

### 3.2 Specification: integrate_simpson

```eiffel
feature

integrate_simpson (f: attached FUNCTION [REAL_64, REAL_64];
                  a, b: REAL_64;
                  n: INTEGER): REAL_64
    -- Simpson's rule for numerical integration
    -- ∫[a,b] f ≈ (b-a)/6 * [f(a) + 4*sum(odd indices) + 2*sum(even indices) + f(b)]

    require
        bounds_ordered: a < b
        a_finite: a.is_finite
        b_finite: b.is_finite
        n_positive: n > 0
        n_even: n \\ 2 = 0
        interval_reasonable: (b - a) < 1e100

    ensure
        result_finite: not (Result.is_nan or Result.is_infinite)

    definition:
        -- Let h = (b - a) / n
        -- Let x_i = a + i*h for i = 0, 1, ..., n
        -- Result = (h/3) * [f(x_0) + 4*f(x_1) + 2*f(x_2) + 4*f(x_3) + ... + 2*f(x_n-2) + 4*f(x_n-1) + f(x_n)]
        -- Assumes: f is C^4 continuous on [a,b]
        -- Error: O((b-a)^5 / (180*n^4) * f''''(ξ))
        --        ≈ 1e-12 for smooth f with n~100

    algorithm:
        -- 1. Compute h = (b - a) / n
        -- 2. Initialize sum = f(a) + f(b)
        -- 3. For i = 1 to n-1:
        --      x_i = a + i*h
        --      If i is odd: sum += 4 * f(x_i)
        --      If i is even: sum += 2 * f(x_i)
        -- 4. Return (h/3) * sum
```

### 3.3 Specification: integrate_with_error

```eiffel
feature

integrate_with_error (f: attached FUNCTION [REAL_64, REAL_64];
                     a, b: REAL_64;
                     tolerance: REAL_64): INTEGRAL_RESULT
    -- Adaptive integration: refine grid until convergence

    require
        bounds_ordered: a < b
        a_finite: a.is_finite
        b_finite: b.is_finite
        tolerance_positive: tolerance > 0.0
        tolerance_reasonable: tolerance < 1.0
        interval_reasonable: (b - a) < 1e100

    ensure
        result_not_void: Result /= Void

        result_finite: not (Result.integral_value.is_nan or Result.integral_value.is_infinite)

        error_non_negative: Result.error_bound >= 0.0

        convergence_guarantee:
            Result.convergence_status = CONVERGED implies Result.error_bound < tolerance

        iterations_reasonable: Result.iterations_required >= 0

    definition:
        -- Iteratively refine integration grid:
        -- Iteration 0: n = 4
        -- Compute T_n = trapezoidal(n), S_n = simpson(n)
        -- error_bound = |S_n - T_n|
        -- If error_bound < tolerance: converged
        -- Else: n := 2*n, repeat
        -- Abort if iterations >= max_iterations
        -- Result.integral_value = S_n at termination
        -- Result.convergence_status = CONVERGED if error < tolerance
        --                            = DIVERGED if max_iterations reached

    algorithm:
        -- 1. Set n := 4, iteration := 0
        -- 2. Compute T_n (trapezoidal)
        -- 3. Compute S_n (Simpson)
        -- 4. Compute error_bound = |S_n - T_n|
        -- 5. If error_bound < tolerance:
        --      set convergence_status := CONVERGED
        --      return S_n with error_bound
        -- 6. Else if iteration >= max_iterations:
        --      set convergence_status := DIVERGED
        --      return S_n with error_bound (not converged)
        -- 7. Else:
        --      n := 2*n
        --      iteration := iteration + 1
        --      goto step 2
```

---

## CLASS SPECIFICATION: DERIVATIVE_RESULT

### 4.1 Class Purpose

**Purpose:** Encapsulate result of derivative computation with error and convergence information.

**Abstraction:** Immutable data structure.

**Implementation Form:** Simple value class.

### 4.2 Class Invariant

```eiffel
invariant
    derivative_valid: not (derivative_value.is_nan or derivative_value.is_infinite)

    all_methods_finite:
        not (forward_diff.is_nan or forward_diff.is_infinite) and
        not (backward_diff.is_nan or backward_diff.is_infinite) and
        not (central_diff.is_nan or central_diff.is_infinite)

    error_non_negative: error_bound >= 0.0

    bounds_consistent: lower_error_bound <= derivative_value and derivative_value <= upper_error_bound

    status_valid: convergence_status /= Void

    agreement_normalized: method_agreement >= 0.0 and method_agreement <= 1.0

    agreement_implies_convergence:
        method_agreement > 0.99 implies convergence_status = CONVERGED
```

### 4.3 Specification: make

```eiffel
feature

make (value: REAL_64; fwd, bwd, ctr: REAL_64; error: REAL_64; status: CONVERGENCE_STATUS)
    -- Construct result

    require
        value_finite: not value.is_nan
        methods_finite: not fwd.is_nan and not bwd.is_nan and not ctr.is_nan
        error_non_negative: error >= 0.0
        status_valid: status /= Void

    ensure
        value_set: derivative_value = value
        forward_set: forward_diff = fwd
        backward_set: backward_diff = bwd
        central_set: central_diff = ctr
        error_set: error_bound = error
        status_set: convergence_status = status
```

### 4.4 Specification: Properties

```eiffel
feature -- Computed Properties

upper_error_bound: REAL_64
    -- Pessimistic upper bound on true derivative
    ensure
        result = derivative_value + error_bound

lower_error_bound: REAL_64
    -- Pessimistic lower bound on true derivative
    ensure
        result = derivative_value - error_bound

relative_error: REAL_64
    -- Error as fraction of result
    ensure
        if derivative_value.abs < epsilon then
            result = 1.0  -- Relative error undefined for near-zero result
        else
            result = error_bound / derivative_value.abs
        end
```

---

## CLASS SPECIFICATION: INTEGRAL_RESULT

### 5.1 Class Purpose

**Purpose:** Encapsulate result of integration computation with error and convergence information.

**Abstraction:** Immutable data structure.

**Implementation Form:** Simple value class.

### 5.2 Class Invariant

```eiffel
invariant
    integral_finite: not (integral_value.is_nan or integral_value.is_infinite)

    methods_finite:
        not (trapezoidal_value.is_nan or trapezoidal_value.is_infinite) and
        not (simpson_value.is_nan or simpson_value.is_infinite)

    error_non_negative: error_bound >= 0.0

    bounds_consistent: lower_error_bound <= integral_value and integral_value <= upper_error_bound

    status_valid: convergence_status /= Void

    simpson_is_primary: integral_value = simpson_value

    iterations_non_negative: iterations_required >= 0

    grid_positive: final_grid_size > 0

    convergence_implies_error_small:
        convergence_status = CONVERGED implies error_bound < {REAL_64}.max_value
```

### 5.3 Specification: make

```eiffel
feature

make (trap, simp: REAL_64; error: REAL_64; status: CONVERGENCE_STATUS; iters: INTEGER)
    -- Construct result

    require
        trap_finite: not trap.is_nan
        simp_finite: not simp.is_nan
        error_non_negative: error >= 0.0
        status_valid: status /= Void
        iters_non_negative: iters >= 0

    ensure
        trapezoidal_set: trapezoidal_value = trap
        simpson_set: simpson_value = simp
        integral_set: integral_value = simp
        error_set: error_bound = error
        status_set: convergence_status = status
        iterations_set: iterations_required = iters
```

---

## CLASS SPECIFICATION: CONVERGENCE_STATUS

### 6.1 Enumeration Definition

```eiffel
class CONVERGENCE_STATUS

feature -- Status Values

CONVERGED: CONVERGENCE_STATUS
    -- Methods agree well (>99%), error bound reliable
    -- User can trust result

CONVERGED_WITH_WARNING: CONVERGENCE_STATUS
    -- Methods agree reasonably (90-99%), error may be conservative
    -- Result acceptable for most purposes

DIVERGED: CONVERGENCE_STATUS
    -- Methods disagree (< 90%), likely cause:
    --   - Function discontinuous (integration)
    --   - Function non-smooth (differentiation)
    --   - Function oscillatory
    -- Result NOT TRUSTWORTHY

FAILED: CONVERGENCE_STATUS
    -- Computation aborted (precondition violation, overflow)
    -- No result available

feature -- Query

is_reliable: BOOLEAN
    ensure
        result = (Current = CONVERGED or Current = CONVERGED_WITH_WARNING)
    end

is_failed: BOOLEAN
    ensure
        result = (Current = DIVERGED or Current = FAILED)
    end

end -- CONVERGENCE_STATUS
```

---

## CLASS SPECIFICATION: STEP_SIZE_CALCULATOR

### 7.1 Class Purpose

**Purpose:** Compute optimal step size h for finite differences.

**Abstraction:** Encapsulate h selection strategy.

**Implementation Form:** Stateless utility.

### 7.2 Specification: adaptive_step_size

```eiffel
feature

adaptive_step_size (x: REAL_64; f_magnitude: REAL_64): REAL_64
    -- Compute optimal h = sqrt(epsilon) * max(|f_magnitude|, 1.0)
    -- Based on balancing truncation and rounding errors

    require
        x_finite: x.is_finite
        f_magnitude_non_negative: f_magnitude >= 0.0

    ensure
        h_positive: Result > 0.0
        h_from_formula: Result = {REAL_64}.epsilon.sqrt * f_magnitude.max (1.0)
        h_reasonable: Result >= {REAL_64}.epsilon.sqrt
        h_small: Result < 1.0

    definition:
        -- h = sqrt(machine_epsilon) * scale_factor
        -- where scale_factor = max(|f(x)|, 1.0)
        -- Rationale: Balances truncation error (h^2*f'') and rounding error (epsilon/h)
        -- Optimal h ~ epsilon^(1/3) for central difference
        -- This formula uses sqrt(epsilon) as practical compromise

    algorithm:
        -- 1. Compute scale = max(|f_magnitude|, 1.0)
        -- 2. Compute sqrt_epsilon = sqrt({REAL_64}.epsilon)
        -- 3. Return sqrt_epsilon * scale
```

---

## Correspondence to Eiffel Implementation

### File Mapping

| Specification | Eiffel File | Status |
|---|---|---|
| SIMPLE_CALCULUS | src/simple_calculus.e | Phase 1 |
| DERIVATIVE_CALCULATOR | src/engines/derivative_calculator.e | Phase 1 |
| INTEGRAL_CALCULATOR | src/engines/integral_calculator.e | Phase 1 |
| DERIVATIVE_RESULT | src/tier2/derivative_result.e | Phase 1 |
| INTEGRAL_RESULT | src/tier2/integral_result.e | Phase 1 |
| CONVERGENCE_STATUS | src/support/convergence_status.e | Phase 1 |
| STEP_SIZE_CALCULATOR | src/engines/step_size_calculator.e | Phase 1 |
| DERIVATIVE_OPTIONS | src/tier2/derivative_options.e | Phase 2 |
| INTEGRAL_OPTIONS | src/tier2/integral_options.e | Phase 2 |

### Implementation Checklist

- [ ] All classes compile with void_safety="all"
- [ ] All features have preconditions and postconditions
- [ ] All classes have class invariants
- [ ] All preconditions documented in user guide
- [ ] Test suite covers all features and contracts
- [ ] Error cases documented and handled
- [ ] Performance acceptable (>1M calls/sec)

---

## Notes for Implementation

1. **Agent Calling:** Use `f.item(x)` to invoke agent functions in Eiffel

2. **REAL_64 Operations:** Use standard Eiffel REAL_64 operations; no special libraries needed

3. **Void Safety:** All parameters use `attached` keyword; no void checks needed inside methods

4. **Error Handling:** No exceptions; signal problems via convergence_status

5. **Testing:** Every feature needs at least one test case for happy path and precondition violation

