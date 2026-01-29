# 05-CONTRACT-DESIGN: simple_calculus

## Executive Summary
This document defines Design by Contract (preconditions, postconditions, invariants) for all classes in simple_calculus. Contracts encode requirements as executable specifications, enabling verification and fail-fast behavior.

---

## Contract Design Philosophy

**Core Principle:** Preconditions state what callers must guarantee; postconditions state what methods guarantee in return. This explicit separation prevents silent failures and gives users predictable behavior.

**Application to Numerical Methods:**
- Preconditions validate function smoothness, continuity, boundedness (I-001: DBC for numerical methods)
- Postconditions provide error bounds and convergence indicators
- Invariants ensure consistency across operations

---

## Class-by-Class Contracts

### 1. SIMPLE_CALCULUS

#### Class Invariant

```eiffel
class invariant
    tolerance_positive: tolerance > 0.0
        -- Tolerance must be positive for convergence tests
        -- Rationale: Zero or negative tolerance is nonsensical for convergence

    max_iterations_positive: max_iterations > 0
        -- Must allow at least one iteration
        -- Rationale: Prevents infinite loops; guards against bad configuration

    max_iterations_reasonable: max_iterations <= 1000
        -- Prevent runaway computation
        -- Rationale: > 1000 iterations suggests ill-conditioned problem
```

#### Feature: derivative (Tier 1 - Simple)

```eiffel
derivative (f: attached FUNCTION [REAL_64, REAL_64];
           x: REAL_64): REAL_64
    -- Compute numerical derivative of f at point x
    -- Using adaptive step size and central difference method

require
    -- Input validation (what caller must guarantee)

    x_is_finite: x.is_finite
        -- Point must be representable in IEEE 754
        -- Rationale: Prevents NaN or Infinity inputs
        -- Implication: Caller validates input range

    x_has_neighborhood: x > {REAL_64}.min_value and x < {REAL_64}.max_value
        -- Point must allow perturbations x±h without overflow
        -- Rationale: Ensures x+h and x-h are computable
        -- Violated by: Points at extreme range boundaries

    function_computable: -- f can be evaluated near x
        -- Implicit precondition (checked at runtime)
        -- f must not raise exceptions for x±h
        -- Rationale: Assumptions about function smoothness

ensure
    -- Output guarantee (what method guarantees in return)

    result_finite: not (Result.is_nan or Result.is_infinite)
        -- Derivative estimate is a real number
        -- Rationale: Result must be usable in further computations
        -- Exception: If preconditions violated, may return NaN

    result_reasonable_magnitude: Result.abs <= 1e10
        -- Derivative not absurdly large
        -- Rationale: Suggests function is smooth; large derivatives indicate problem
        -- Not strict: Can be violated; just a sanity check

    -- Implicit postcondition (documented but not checked)
    -- error_estimate_available:
    --     User can call derivative_with_error to get error bound
    --     Rationale: Always know when to trust result

ensure -- Contract for void safety
    definition: Result = compute_derivative_with_adaptive_step (f, x)
        -- Results match algorithmic definition
        -- Rationale: Mathematical correctness specification
```

**Note on Preconditions:** Some preconditions like `function_smooth` cannot be checked automatically. They are **documented constraints** that users must ensure. This is idiomatic for numerical methods: we state assumptions about the function class.

#### Feature: integrate (Tier 1 - Simple)

```eiffel
integrate (f: attached FUNCTION [REAL_64, REAL_64];
          a, b: REAL_64): REAL_64
    -- Compute numerical integral of f from a to b using Simpson's rule

require
    -- Input validation

    a_is_finite: a.is_finite
        -- Lower bound must be representable

    b_is_finite: b.is_finite
        -- Upper bound must be representable

    bounds_ordered: a < b
        -- Interval must be forward (not backward or empty)
        -- Rationale: [a,b] with a >= b is meaningless
        -- Implication: Caller must order bounds correctly

    interval_reasonable: b - a > {REAL_64}.epsilon
        -- Interval width must exceed machine precision
        -- Rationale: Prevents meaningless zero-width integrals

    function_continuous: -- f is continuous on [a,b]
        -- Implicit precondition (documented, not checked)
        -- Rationale: Numerical integration assumes no discontinuities
        -- Violation symptom: Error estimate explodes; methods diverge

ensure
    -- Output guarantee

    result_finite: not (Result.is_nan or Result.is_infinite)
        -- Integral value is a real number

    result_reasonable: (b - a).abs <= 1e10
        -- Interval not absurdly large (would lose precision)

    -- Implicit postcondition
    -- error_estimate_available:
    --     Call integrate_with_error (f, a, b, tolerance) to get error bound
    --     Rationale: Know convergence confidence
```

#### Feature: derivative_with_options (Tier 2 - Control)

```eiffel
derivative_with_options (f: attached FUNCTION [REAL_64, REAL_64];
                        x: REAL_64;
                        options: attached DERIVATIVE_OPTIONS): DERIVATIVE_RESULT
    -- Advanced derivative computation with user control

require
    x_is_finite: x.is_finite
    x_has_neighborhood: x.abs < 1e100
        -- Point near reasonable range for perturbations
    options_configured: options.tolerance > 0.0
        -- Options must have valid tolerance

ensure
    result_not_void: Result /= Void
        -- Always returns a result object (or exception)

    result_value_finite: not (Result.derivative_value.is_nan or Result.derivative_value.is_infinite)
        -- Central value is always finite

    error_bound_valid: Result.error_bound >= 0.0
        -- Error bound non-negative (always pessimistic)
        -- Rationale: error_bound >= |estimated - actual| always

    error_consistency: Result.error_bound <= Result.derivative_value.abs * 10.0
        -- Error bound reasonable relative to result
        -- Rationale: If error > 10x the result, either:
        --   a) Function not smooth enough (precondition violated)
        --   b) Method diverged (convergence_status = DIVERGED)

    bounds_ordered: Result.lower_error_bound <= Result.upper_error_bound
        -- Confidence interval makes sense

    method_agreement_high_means_convergence:
        Result.method_agreement > 0.99 implies Result.convergence_status = CONVERGED
        -- If three methods agree > 99%, status must be CONVERGED

    divergence_detected_means_warning:
        Result.method_agreement < 0.95 implies Result.convergence_status /= CONVERGED
        -- If methods disagree, not fully converged

definition:
    -- Result computed using specified method (F/B/C)
    -- If options.step_size = 0.0: use adaptive h
    -- If options.step_size > 0.0: use specified h
    -- Error estimate = max difference between methods
```

#### Feature: integrate_with_options (Tier 2 - Control)

```eiffel
integrate_with_options (f: attached FUNCTION [REAL_64, REAL_64];
                       a, b: REAL_64;
                       options: attached INTEGRAL_OPTIONS): INTEGRAL_RESULT
    -- Advanced integration with user control

require
    bounds_ordered: a < b
    interval_reasonable: b - a > {REAL_64}.epsilon
    options_valid: options.tolerance > 0.0
    options_subdivisions_positive: options.initial_subdivisions > 0

ensure
    result_not_void: Result /= Void

    result_finite: not (Result.integral_value.is_nan or Result.integral_value.is_infinite)

    error_bound_valid: Result.error_bound >= 0.0

    error_consistency: Result.error_bound <= Result.integral_value.abs * 10.0
        -- Similar to derivative: error bound must be reasonable

    bounds_ordered: Result.lower_error_bound <= Result.upper_error_bound

    convergence_guarantee:
        Result.convergence_status = CONVERGED implies Result.error_bound < options.tolerance
        -- If converged, error is within requested tolerance

    divergence_indicator:
        Result.convergence_status = DIVERGED implies
            Result.error_bound > options.tolerance * 10.0
        -- Large error suggests convergence failed

    iterations_reasonable: Result.iterations_required <= max_iterations
        -- Computation terminates within max_iterations
```

#### Feature: set_tolerance

```eiffel
set_tolerance (t: REAL_64)
    -- Configure convergence tolerance

require
    t_positive: t > 0.0
        -- Tolerance must be positive
        -- Rationale: Zero or negative is nonsensical

    t_reasonable: t < 1.0
        -- Tolerance less than 100% error
        -- Rationale: > 1.0 tolerance is useless (anything converges)

ensure
    tolerance_set: tolerance = t
        -- Tolerance recorded exactly

    invariant_maintained: tolerance > 0.0
        -- Invariant not violated
```

---

### 2. DERIVATIVE_CALCULATOR

#### Class Invariant

```eiffel
class invariant
    adaptive_step_positive: adaptive_step > 0.0
        -- Step size must be positive
        -- Rationale: Zero or negative h is undefined

    adaptive_step_reasonable: adaptive_step < 1.0
        -- Step size must be small for local approximation
        -- Rationale: h >= 1.0 makes finite difference very crude

    cached_steps_consistent: -- If step sizes cached
        -- Cached values must be in range (epsilon.sqrt, 1.0)
        -- Rationale: Prevents bad cached values
```

#### Feature: derivative_forward

```eiffel
derivative_forward (f: attached FUNCTION [REAL_64, REAL_64];
                   x, h: REAL_64): REAL_64
    -- Forward difference: f'(x) ≈ [f(x+h) - f(x)] / h

require
    x_finite: x.is_finite
        -- Point must be representable

    h_positive: h > 0.0
        -- Step size must be positive

    h_reasonable: h < 1.0
        -- Step size must be small (local approximation)

    perturbation_safe: (x + h).is_finite
        -- Ensure x+h doesn't overflow
        -- Rationale: Prevents loss of significance

    function_smooth_near_x: -- f is at least C1 on [x, x+h]
        -- Implicit precondition (documented)
        -- Rationale: Forward difference assumes smoothness
        -- Violation: Wild oscillations → large error

ensure
    result_finite: not (Result.is_nan or Result.is_infinite)
        -- Derivative always finite number

    error_estimate_exists: -- Caller can infer error from h
        -- Error ~ (b-a)^2 * f''(ξ) / 2
        -- User responsible for estimating f''

    result_definition: Result = (f.item (x + h) - f.item (x)) / h
        -- Result matches formula exactly
```

#### Feature: derivative_central

```eiffel
derivative_central (f: attached FUNCTION [REAL_64, REAL_64];
                   x, h: REAL_64): REAL_64
    -- Central difference: f'(x) ≈ [f(x+h) - f(x-h)] / (2h)
    -- Most accurate of the three methods (error O(h^4))

require
    x_finite: x.is_finite
    h_positive: h > 0.0
    h_reasonable: h < 1.0

    perturbation_safe_both: (x + h).is_finite and (x - h).is_finite
        -- Both x±h must be valid
        -- Rationale: Central difference needs both sides

    function_smooth_on_interval: -- f at least C3 on [x-h, x+h]
        -- Implicit precondition
        -- Rationale: Central difference uses both sides
        -- Violation: Asymmetric error

ensure
    result_finite: not (Result.is_nan or Result.is_infinite)

    result_definition: Result = (f.item (x + h) - f.item (x - h)) / (2.0 * h)

    -- Implicit: Central difference more accurate than forward/backward
    -- Error ~ h^4 vs h^2 for forward/backward
```

#### Feature: derivative_with_error

```eiffel
derivative_with_error (f: attached FUNCTION [REAL_64, REAL_64];
                      x, h: REAL_64): DERIVATIVE_RESULT
    -- Compute all three methods and return with error estimate

require
    x_finite: x.is_finite
    h_positive: h > 0.0
    h_reasonable: h < 1.0
    perturbation_safe_both: (x + h).is_finite and (x - h).is_finite

    function_smooth: -- at least C2 continuous on [x-h, x+h]
        -- Implicit: Necessary for error estimates to be meaningful

ensure
    result_not_void: Result /= Void
        -- Always return result object

    all_methods_computed:
        Result.forward_diff.is_finite and
        Result.backward_diff.is_finite and
        Result.central_diff.is_finite
        -- All three methods must be computed

    central_is_main: Result.derivative_value = Result.central_diff
        -- Primary estimate is central difference (most accurate)

    error_bound_from_method_divergence:
        Result.error_bound >= (Result.forward_diff - Result.backward_diff).abs / 2.0
        -- Error at least the disagreement between forward/backward
        -- Rationale: I-003 (multiple method comparison validation)

    agreement_metric:
        -- Result.method_agreement is mean of pairwise agreements
        -- 1.0 = perfect agreement; 0.0 = complete divergence
        -- agreement = 1.0 - (divergence / typical_derivative_magnitude)

    convergence_logic:
        if Result.method_agreement > 0.99 then
            Result.convergence_status = CONVERGED
        elseif Result.method_agreement > 0.90 then
            Result.convergence_status = CONVERGED_WITH_WARNING
        else
            Result.convergence_status = DIVERGED
        end
        -- Status based on method agreement (I-001: DBC catches bad inputs)
```

#### Feature: compute_adaptive_step

```eiffel
compute_adaptive_step (x: REAL_64): REAL_64
    -- Compute optimal h = sqrt(epsilon) * max(|x|, 1.0)
    -- D-002: Adaptive h based on machine epsilon

require
    x_finite: x.is_finite
        -- Point must be representable

ensure
    h_positive: Result > 0.0
        -- Step size always positive

    h_from_formula: Result = {REAL_64}.epsilon.sqrt * x.abs.max (1.0)
        -- Result matches adaptive formula exactly

    h_reasonable: Result >= {REAL_64}.epsilon.sqrt
        -- At least machine epsilon scale

    h_small: Result < 1.0
        -- Local approximation guaranteed
```

---

### 3. INTEGRAL_CALCULATOR

#### Class Invariant

```eiffel
class invariant
    tolerance_positive: tolerance > 0.0
    max_iterations_positive: max_iterations > 0
    grid_size_positive: initial_grid_size > 0
```

#### Feature: integrate_trapezoidal

```eiffel
integrate_trapezoidal (f: attached FUNCTION [REAL_64, REAL_64];
                      a, b: REAL_64;
                      n: INTEGER): REAL_64
    -- Trapezoidal rule: ∫f ≈ (b-a)/2 * [f(a) + 2f(x_1) + ... + 2f(x_n-1) + f(b)]
    -- Error: O((b-a)^3 / (12*n^2) * f''(ξ))

require
    bounds_ordered: a < b
        -- Interval must be forward

    a_finite: a.is_finite
    b_finite: b.is_finite
        -- Bounds must be representable

    n_positive: n > 0
        -- Must have at least one interval

    interval_reasonable: (b - a) < 1e10
        -- Interval width reasonable (not astronomical)
        -- Rationale: Very wide intervals lose precision in summation

    function_continuous: -- f is continuous on [a,b]
        -- Implicit precondition
        -- Rationale: Trapezoidal rule assumes no jumps

ensure
    result_finite: not (Result.is_nan or Result.is_infinite)
        -- Integral value is finite

    result_definition:
        -- Result equals (b-a)/2 * sum of [f(a) + 2*f(x_i) + f(b)]
        -- where x_i are n equally spaced points in (a,b)
```

#### Feature: integrate_simpson

```eiffel
integrate_simpson (f: attached FUNCTION [REAL_64, REAL_64];
                  a, b: REAL_64;
                  n: INTEGER): REAL_64
    -- Simpson's rule: ∫f ≈ (b-a)/6 * [f(a) + 4f(x_1) + 2f(x_2) + 4f(x_3) + ... + f(b)]
    -- Error: O((b-a)^5 / (180*n^4) * f''''(ξ))
    -- Much more accurate than trapezoidal for smooth functions

require
    bounds_ordered: a < b
    a_finite: a.is_finite
    b_finite: b.is_finite

    n_positive: n > 0

    n_even: n \\ 2 = 0
        -- Simpson's rule requires even number of intervals
        -- Rationale: Pairs of points form parabolas

    interval_reasonable: (b - a) < 1e10

    function_smooth: -- f at least C4 on [a,b]
        -- Implicit: Simpson's rule error involves f''''

ensure
    result_finite: not (Result.is_nan or Result.is_infinite)

    result_definition:
        -- Result computed using Simpson's weighted sum
```

#### Feature: integrate_with_error

```eiffel
integrate_with_error (f: attached FUNCTION [REAL_64, REAL_64];
                     a, b: REAL_64;
                     tolerance: REAL_64): INTEGRAL_RESULT
    -- Compute integral using both Trapezoidal and Simpson's
    -- Refine grid until convergence or max_iterations

require
    bounds_ordered: a < b
    a_finite: a.is_finite
    b_finite: b.is_finite
    interval_reasonable: (b - a) < 1e10

    tolerance_positive: tolerance > 0.0
        -- Tolerance must be positive

    tolerance_reasonable: tolerance < 1.0
        -- Tolerance less than 100% error

    function_continuous: -- f continuous on [a,b]
        -- Implicit precondition

ensure
    result_not_void: Result /= Void
        -- Always return result object

    result_finite: not (Result.integral_value.is_nan or Result.integral_value.is_infinite)
        -- Integral value is finite

    error_bound_non_negative: Result.error_bound >= 0.0
        -- Error always non-negative

    simpson_more_accurate: Result.error_bound = (Result.simpson_value - Result.trapezoidal_value).abs
        -- Error estimate is difference between methods
        -- Simpson's error is O(h^5), Trapezoidal O(h^3)
        -- Difference ~ Simpson error

    convergence_guarantee:
        Result.convergence_status = CONVERGED implies Result.error_bound < tolerance
        -- If converged, error within tolerance
        -- Rationale: Definition of convergence

    divergence_means_large_error:
        Result.convergence_status = DIVERGED implies Result.error_bound > tolerance * 10.0
        -- Divergence occurs when error remains large
        -- May indicate discontinuity (RISK-003 mitigation)

    iterations_bounded: Result.iterations_required <= max_iterations
        -- Computation terminates in finite time

    monotonic_convergence:
        -- Error should decrease with refinement (implicit)
        -- If not: divergence detected, status updated

    early_termination_guarantee:
        Result.error_bound < tolerance implies Result.iterations_required < max_iterations
        -- If convergence achieved, finished before limit
```

---

### 4. DERIVATIVE_RESULT

#### Class Invariant

```eiffel
class invariant
    derivative_valid: not (derivative_value.is_nan or derivative_value.is_infinite)
        -- Main value always finite

    all_methods_finite:
        not (forward_diff.is_nan or forward_diff.is_infinite) and
        not (backward_diff.is_nan or backward_diff.is_infinite) and
        not (central_diff.is_nan or central_diff.is_infinite)
        -- All three estimates must be finite

    error_non_negative: error_bound >= 0.0
        -- Error bound never negative (always pessimistic)

    error_reasonable: error_bound < {REAL_64}.max_value / 10.0
        -- Error bound not absurdly large

    bounds_consistent:
        lower_error_bound <= derivative_value and derivative_value <= upper_error_bound
        -- Derivative within its own confidence interval
        -- Rationale: derivative_value ∈ [value-error, value+error]

    method_agreement_in_range: method_agreement >= 0.0 and method_agreement <= 1.0
        -- Agreement metric normalized to [0,1]

    status_valid: convergence_status /= Void
        -- Always have convergence status

    agreement_implies_convergence:
        method_agreement > 0.99 implies convergence_status = CONVERGED
        -- High agreement implies converged

    disagreement_prevents_convergence:
        method_agreement < 0.90 implies convergence_status = DIVERGED
        -- Low agreement means diverged
```

#### Feature: make

```eiffel
make (value: REAL_64;
     fwd, bwd, ctr: REAL_64;
     error: REAL_64;
     status: CONVERGENCE_STATUS)
    -- Constructor for DERIVATIVE_RESULT

require
    value_finite: not value.is_nan
    fwd_finite: not fwd.is_nan
    bwd_finite: not bwd.is_nan
    ctr_finite: not ctr.is_nan
        -- All method values must be finite

    error_non_negative: error >= 0.0
        -- Error bound non-negative

    status_valid: status /= Void
        -- Status must be one of enumerated values

ensure
    value_set: derivative_value = value
    forward_set: forward_diff = fwd
    backward_set: backward_diff = bwd
    central_set: central_diff = ctr
    error_set: error_bound = error
    status_set: convergence_status = status

    -- Invariants maintained by construction
```

---

### 5. INTEGRAL_RESULT

#### Class Invariant

```eiffel
class invariant
    integral_finite: not (integral_value.is_nan or integral_value.is_infinite)

    methods_finite:
        not (trapezoidal_value.is_nan or trapezoidal_value.is_infinite) and
        not (simpson_value.is_nan or simpson_value.is_infinite)

    error_non_negative: error_bound >= 0.0

    error_reasonable: error_bound < {REAL_64}.max_value / 10.0

    bounds_consistent:
        lower_error_bound <= integral_value and integral_value <= upper_error_bound

    iterations_non_negative: iterations_required >= 0

    grid_size_positive: final_grid_size > 0

    simpson_is_primary: integral_value = simpson_value
        -- Main result is Simpson (more accurate)
```

#### Feature: make

```eiffel
make (trap, simp: REAL_64;
     error: REAL_64;
     status: CONVERGENCE_STATUS;
     iters: INTEGER)
    -- Constructor for INTEGRAL_RESULT

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

### 6. CONVERGENCE_STATUS

#### Class Invariant

```eiffel
class invariant
    -- All status values are distinct and valid
    -- Can check: is_reliable, is_failed
```

#### Features

```eiffel
is_reliable: BOOLEAN
    -- True if CONVERGED or CONVERGED_WITH_WARNING
    ensure
        result: Result implies (Current = CONVERGED or Current = CONVERGED_WITH_WARNING)
    end

is_failed: BOOLEAN
    -- True if DIVERGED or FAILED
    ensure
        result: Result implies (Current = DIVERGED or Current = FAILED)
    end
```

---

## Contract Violation Scenarios

### Scenario 1: Non-Smooth Function

**Function:** f(x) = |x| (not differentiable at x=0)
**Called:** `derivative(agent |x|, 0.0)`

**Precondition Status:** Violated (`function_smooth`)
- Forward/backward/central give different results
- Error estimate explodes
- Postcondition still satisfied (returns finite number)
- **Solution:** `convergence_status = DIVERGED` alerts user

### Scenario 2: Integration Over Discontinuous Function

**Function:** f(x) = step(x) (jump at x=0.5)
**Called:** `integrate(agent step, 0.0, 1.0)`

**Precondition Status:** Violated (`function_continuous`)
- Simpson and Trapezoidal give wildly different results
- Error estimate > tolerance * 10
- **Solution:** `convergence_status = DIVERGED`; error large

### Scenario 3: Oscillatory Function

**Function:** f(x) = sin(1000*x)
**Called:** `derivative(agent oscillatory, 0.5)`

**Precondition Status:** Violated (`function_smooth` at scale h)
- h = sqrt(epsilon) ≈ 1e-8 too large for oscillations
- **Solution:** `convergence_status = CONVERGED_WITH_WARNING`; error_bound large

### Scenario 4: Overflow in Perturbation

**Point:** x = 1e308 (near REAL_64 max)
**Called:** `derivative(agent f, 1e308)`

**Precondition Status:** Violated (`x_has_neighborhood`)
- x + h overflows to infinity
- Postcondition returns NaN
- **Solution:** Precondition should prevent call; or handle gracefully

---

## Testing Contract Compliance

Each contract must be tested:

```eiffel
test_derivative_precondition_smoothness
    -- Call derivative on non-smooth function
    -- Verify: convergence_status = DIVERGED
    -- Verify: error_bound large

test_derivative_postcondition_finite
    -- For any valid input
    -- Verify: Result is finite (not NaN or Inf)

test_integral_convergence_guarantee
    -- Call integrate with small tolerance
    -- Verify: error_bound < tolerance
    -- Verify: convergence_status = CONVERGED

test_error_bound_consistency
    -- Call derivative_with_error multiple times with different h
    -- Verify: error_bound decreases as h refines
    -- Verify: bounds_consistent invariant holds
```

---

## Contract Evolution Strategy

**Phase 1:** Basic contracts (preconditions, postconditions)
- Validate inputs (finite, bounded)
- Guarantee outputs (finite, within error bounds)
- Check invariants at construction

**Phase 2:** Enhanced contracts
- Add MML for collection operations (for Jacobian/Gradient)
- Formalize function smoothness checks
- Add optimization-level contracts

**Phase 3:** Symbolic contracts
- Integrate with symbolic differentiation API
- Prove numerical results match symbolic
- Add frame conditions (which variables affected)

