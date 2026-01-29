# 04-CLASS-DESIGN: simple_calculus

## Executive Summary
This document defines the Eiffel class structure for simple_calculus using OOSC2 principles. Classes are organized in a facade + engine pattern with clear separation of concerns, void-safe design, and SCOOP-ready concurrency support.

---

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│ User Code                                                    │
│   calculus.derivative(agent f, x)                           │
│   calculus.integrate(agent f, a, b)                         │
└──────────────────┬──────────────────────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────────────────────┐
│ SIMPLE_CALCULUS (Facade)                                    │
│  - derivative / derivative_with_options                     │
│  - integrate / integrate_with_options                       │
│  - partial_derivative (Phase 2)                             │
│  - gradient / jacobian (Phase 2)                            │
└──────────────────┬──────────────────────────────────────────┘
                   │
        ┌──────────┴──────────┬──────────────┐
        │                     │              │
        ▼                     ▼              ▼
┌──────────────────┐ ┌──────────────────┐ ┌──────────────────┐
│ DERIVATIVE_      │ │ INTEGRAL_        │ │ STEP_SIZE_       │
│ CALCULATOR       │ │ CALCULATOR       │ │ CALCULATOR       │
│  (Engine)        │ │  (Engine)        │ │  (Utility)       │
└──────────────────┘ └──────────────────┘ └──────────────────┘
        │                     │
        └──────────┬──────────┘
                   │
        ┌──────────┴──────────┐
        │                     │
        ▼                     ▼
┌──────────────────┐ ┌──────────────────┐
│ DERIVATIVE_      │ │ INTEGRAL_        │
│ RESULT           │ │ RESULT           │
│  (Data Class)    │ │  (Data Class)    │
└──────────────────┘ └──────────────────┘
```

---

## Class Definitions

### 1. SIMPLE_CALCULUS (Facade)

**Purpose:** User-facing interface providing simple API (Tier 1) for differentiation and integration.

**Principle Applied:** OOSC2 Principle 3 - Abstraction (hide engine details)

**Classification:** Stateless facade (no state beyond configuration)

**Key Invariants:**
```eiffel
class invariant
    tolerance_positive: tolerance > 0.0
    max_iterations_positive: max_iterations > 0
```

#### Tier 1 (Simple) Features

```eiffel
feature -- Derivative Operations (Tier 1)

    derivative (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
        -- Compute numerical derivative of f at point x
        -- Uses adaptive step size and central difference method
        require
            f_valid: f /= Void
            x_in_domain: x.is_finite
            point_valid: -- function_smooth (documented in DBC)
        ensure
            result_valid: not (Result.is_nan or Result.is_infinite)
        do
            -- Delegates to DERIVATIVE_CALCULATOR
            -- Returns mean of forward/central/backward
        end

    integrate (f: FUNCTION [REAL_64, REAL_64]; a, b: REAL_64): REAL_64
        -- Compute numerical integral of f from a to b
        -- Uses Simpson's rule with automatic step refinement
        require
            f_valid: f /= Void
            a_valid: a.is_finite
            b_valid: b.is_finite
            bounds_valid: a < b
            function_continuous: -- documented in DBC
        ensure
            result_valid: not (Result.is_nan or Result.is_infinite)
        do
            -- Delegates to INTEGRAL_CALCULATOR
            -- Integrates using Simpson's rule with tolerance check
        end
```

#### Tier 2 (Control) Features

```eiffel
feature -- Advanced Options (Tier 2)

    derivative_with_options (f: FUNCTION [REAL_64, REAL_64];
                            x: REAL_64;
                            options: DERIVATIVE_OPTIONS): DERIVATIVE_RESULT
        -- Compute derivative with user-specified options
        require
            f_valid: f /= Void
            x_valid: x.is_finite
            options_valid: options /= Void
        ensure
            result_valid: Result /= Void
            error_bounded: Result.error_bound >= 0.0
        do
            -- Uses options to select method (forward/backward/central)
            -- Uses options.step_size if provided; else auto-adapt
            -- Returns DERIVATIVE_RESULT with error bound
        end

    integrate_with_options (f: FUNCTION [REAL_64, REAL_64];
                           a, b: REAL_64;
                           options: INTEGRAL_OPTIONS): INTEGRAL_RESULT
        -- Compute integral with user-specified options
        require
            f_valid: f /= Void
            bounds_valid: a < b
            options_valid: options /= Void
        ensure
            result_valid: Result /= Void
            error_bounded: Result.error_bound >= 0.0
        do
            -- Uses options to select method (trapezoidal/Simpson/adaptive)
            -- Uses options.tolerance for convergence check
            -- Returns INTEGRAL_RESULT with error bound
        end
```

#### Configuration Features

```eiffel
feature -- Configuration

    set_tolerance (t: REAL_64)
        require
            t_positive: t > 0.0
        do
            tolerance := t
        ensure
            tolerance_set: tolerance = t
        end

    set_max_iterations (n: INTEGER)
        require
            n_positive: n > 0
        do
            max_iterations := n
        ensure
            max_iterations_set: max_iterations = n
        end

    tolerance: REAL_64
        -- Convergence tolerance (default 1e-9)

    max_iterations: INTEGER
        -- Maximum iterations for convergence (default 100)
```

---

### 2. DERIVATIVE_CALCULATOR (Engine)

**Purpose:** Implements numerical differentiation algorithms using finite differences.

**Principle Applied:** OOSC2 Principle 4 - Reusability (encapsulate algorithm)

**Classification:** Stateless algorithm engine (can be instantiated once and reused)

**Key Invariants:**
```eiffel
class invariant
    algorithm_valid: algorithm_type /= Void
    step_size_positive: adaptive_step > 0.0
```

#### Core Features

```eiffel
feature -- Differentiation Methods

    derivative_forward (f: FUNCTION [REAL_64, REAL_64];
                       x: REAL_64;
                       h: REAL_64): REAL_64
        -- Forward difference: f'(x) ≈ [f(x+h) - f(x)] / h
        require
            f_valid: f /= Void
            x_valid: x.is_finite
            h_positive: h > 0.0
            h_small: h < 1.0
        ensure
            result_valid: not (Result.is_nan or Result.is_infinite)
        do
            Result := (f.item (x + h) - f.item (x)) / h
        end

    derivative_backward (f: FUNCTION [REAL_64, REAL_64];
                        x: REAL_64;
                        h: REAL_64): REAL_64
        -- Backward difference: f'(x) ≈ [f(x) - f(x-h)] / h
        require
            f_valid: f /= Void
            x_valid: x.is_finite
            h_positive: h > 0.0
            h_small: h < 1.0
        ensure
            result_valid: not (Result.is_nan or Result.is_infinite)
        do
            Result := (f.item (x) - f.item (x - h)) / h
        end

    derivative_central (f: FUNCTION [REAL_64, REAL_64];
                       x: REAL_64;
                       h: REAL_64): REAL_64
        -- Central difference: f'(x) ≈ [f(x+h) - f(x-h)] / (2h)
        -- Most accurate of the three methods (error O(h^2))
        require
            f_valid: f /= Void
            x_valid: x.is_finite
            h_positive: h > 0.0
            h_small: h < 1.0
        ensure
            result_valid: not (Result.is_nan or Result.is_infinite)
        do
            Result := (f.item (x + h) - f.item (x - h)) / (2.0 * h)
        end

    derivative_with_error (f: FUNCTION [REAL_64, REAL_64];
                          x: REAL_64;
                          h: REAL_64): DERIVATIVE_RESULT
        -- Compute all three methods and return with error estimate
        require
            f_valid: f /= Void
            x_valid: x.is_finite
            h_positive: h > 0.0
        ensure
            result_valid: Result /= Void
            methods_computed: Result.forward_diff /= 0.0 implies Result.backward_diff /= 0.0
            error_bounded: Result.error_bound >= 0.0
        do
            -- Compute forward, backward, central differences
            -- Compare for agreement (I-003: method comparison validation)
            -- Return DERIVATIVE_RESULT with:
            --   derivative_value: mean of three methods
            --   error_bound: max difference between methods
            --   convergence_status: CONVERGED if methods agree, DIVERGED if not
        end
```

#### Adaptive Features

```eiffel
feature -- Step Size Adaptation

    compute_adaptive_step (x: REAL_64): REAL_64
        -- Compute optimal h based on machine epsilon and function magnitude
        -- Formula: h = sqrt(epsilon) * max(|x|, 1.0)
        require
            x_finite: x.is_finite
        ensure
            h_positive: Result > 0.0
            h_reasonable: Result >= {REAL_64}.epsilon.sqrt
        do
            -- Use STEP_SIZE_CALCULATOR
        end
```

---

### 3. INTEGRAL_CALCULATOR (Engine)

**Purpose:** Implements numerical integration algorithms using quadrature rules.

**Principle Applied:** OOSC2 Principle 4 - Reusability (encapsulate algorithm)

**Classification:** Stateless algorithm engine

**Key Invariants:**
```eiffel
class invariant
    algorithm_valid: algorithm_type /= Void
    tolerance_positive: tolerance > 0.0
```

#### Core Features

```eiffel
feature -- Integration Methods

    integrate_trapezoidal (f: FUNCTION [REAL_64, REAL_64];
                          a, b: REAL_64;
                          n: INTEGER): REAL_64
        -- Trapezoidal rule: ∫f ≈ (b-a)/2 * [f(a) + 2f(x_1) + 2f(x_2) + ... + f(b)]
        -- Error: O((b-a)^3 / (12*n^2) * f''(ξ))
        require
            f_valid: f /= Void
            a_valid: a.is_finite
            b_valid: b.is_finite
            bounds_valid: a < b
            n_positive: n > 0
        ensure
            result_valid: not (Result.is_nan or Result.is_infinite)
        do
            -- Subdivide [a,b] into n intervals
            -- Compute trapezoid area for each
            -- Sum all trapezoids
        end

    integrate_simpson (f: FUNCTION [REAL_64, REAL_64];
                      a, b: REAL_64;
                      n: INTEGER): REAL_64
        -- Simpson's rule: Uses parabolic approximation
        -- Error: O((b-a)^5 / (180*n^4) * f''''(ξ))
        -- More accurate than trapezoidal for smooth functions
        require
            f_valid: f /= Void
            bounds_valid: a < b
            n_valid: n > 0 and n \\ 2 = 0  -- n must be even
        ensure
            result_valid: not (Result.is_nan or Result.is_infinite)
        do
            -- Subdivide [a,b] into n intervals (n even)
            -- Apply Simpson's formula to pairs
        end

    integrate_with_error (f: FUNCTION [REAL_64, REAL_64];
                         a, b: REAL_64;
                         tolerance: REAL_64): INTEGRAL_RESULT
        -- Compute integral using both Trapezoidal and Simpson's
        -- Refine grid until convergence or max_iterations reached
        require
            f_valid: f /= Void
            bounds_valid: a < b
            tolerance_positive: tolerance > 0.0
        ensure
            result_valid: Result /= Void
            error_bounded: Result.error_bound >= 0.0
            convergence_guaranteed: Result.convergence_status /= DIVERGED implies Result.error_bound < tolerance
        do
            -- Start with n=4
            -- Compute both Trap and Simpson
            -- Compare results; if difference < tolerance, converged
            -- Else double n and repeat
            -- Return INTEGRAL_RESULT with:
            --   integral_value: Simpson result (more accurate)
            --   error_bound: |Simpson - Trapezoidal|
            --   convergence_status: CONVERGED/DIVERGED based on comparison
        end
```

---

### 4. DERIVATIVE_RESULT (Data Class)

**Purpose:** Encapsulate the result of numerical differentiation with error information.

**Principle Applied:** OOSC2 Principle 1 - Explicit Data Invariant

**Classification:** Immutable data class (once created, never changes)

**Key Invariants:**
```eiffel
class invariant
    derivative_valid: not (derivative_value.is_nan or derivative_value.is_infinite)
    error_non_negative: error_bound >= 0.0
    error_reasonable: error_bound < {REAL_64}.max_value
    bounds_consistent: lower_error_bound <= derivative_value and derivative_value <= upper_error_bound
    forward_backward_agreement: (forward_diff - backward_diff).abs <= max_method_divergence
```

#### Features

```eiffel
class DERIVATIVE_RESULT

feature -- Result Values

    derivative_value: REAL_64
        -- Estimated f'(x), typically mean of three methods

    forward_diff: REAL_64
        -- Forward difference estimate

    backward_diff: REAL_64
        -- Backward difference estimate

    central_diff: REAL_64
        -- Central difference estimate (most accurate)

feature -- Error Estimation

    error_bound: REAL_64
        -- Upper bound on |estimated - actual|
        -- Conservative estimate; actual error likely smaller

    relative_error: REAL_64
        -- error_bound / |derivative_value| (or 1.0 if value near zero)

    absolute_error: REAL_64
        -- Same as error_bound

    lower_error_bound: REAL_64
        -- derivative_value - error_bound

    upper_error_bound: REAL_64
        -- derivative_value + error_bound

feature -- Convergence Information

    convergence_status: CONVERGENCE_STATUS
        -- CONVERGED, CONVERGED_WITH_WARNING, DIVERGED, or FAILED
        -- Indicates reliability of result

    method_agreement: REAL_64
        -- Measure of how well forward/backward/central agree (0-1)
        -- 1.0 = perfect agreement; 0.0 = complete divergence

feature -- Creation

    make (value: REAL_64;
          fwd, bwd, ctr: REAL_64;
          error: REAL_64;
          status: CONVERGENCE_STATUS)
        require
            error_non_negative: error >= 0.0
            value_valid: not value.is_nan
            status_valid: status /= Void
        ensure
            derivative_value = value
            error_bound = error
            convergence_status = status
        do
            derivative_value := value
            forward_diff := fwd
            backward_diff := bwd
            central_diff := ctr
            error_bound := error
            convergence_status := status
        end

end
```

---

### 5. INTEGRAL_RESULT (Data Class)

**Purpose:** Encapsulate the result of numerical integration with error information.

**Principle Applied:** OOSC2 Principle 1 - Explicit Data Invariant

**Classification:** Immutable data class

**Key Invariants:**
```eiffel
class invariant
    integral_valid: not (integral_value.is_nan or integral_value.is_infinite)
    error_non_negative: error_bound >= 0.0
    error_reasonable: error_bound < {REAL_64}.max_value
    bounds_consistent: lower_error_bound <= integral_value and integral_value <= upper_error_bound
    method_agreement: (trapezoidal - simpson).abs <= max_method_divergence
```

#### Features

```eiffel
class INTEGRAL_RESULT

feature -- Result Values

    integral_value: REAL_64
        -- Estimated ∫[a,b] f(x) dx
        -- Typically Simpson's result (more accurate)

    trapezoidal_value: REAL_64
        -- Trapezoidal rule estimate

    simpson_value: REAL_64
        -- Simpson's rule estimate

feature -- Error Estimation

    error_bound: REAL_64
        -- Upper bound on |estimated - actual|
        -- Typically |Simpson - Trapezoidal|

    relative_error: REAL_64
        -- error_bound / |integral_value|

    absolute_error: REAL_64
        -- Same as error_bound

    lower_error_bound: REAL_64
        -- integral_value - error_bound

    upper_error_bound: REAL_64
        -- integral_value + error_bound

feature -- Convergence Information

    convergence_status: CONVERGENCE_STATUS
        -- CONVERGED, CONVERGED_WITH_WARNING, DIVERGED, or FAILED

    iterations_required: INTEGER
        -- Number of refinement iterations until convergence

    final_grid_size: INTEGER
        -- Number of intervals in final grid

feature -- Creation

    make (trap, simp: REAL_64;
          error: REAL_64;
          status: CONVERGENCE_STATUS;
          iters: INTEGER)
        require
            error_non_negative: error >= 0.0
            trap_valid: not trap.is_nan
            simp_valid: not simp.is_nan
            status_valid: status /= Void
            iters_non_negative: iters >= 0
        ensure
            integral_value = simp
            error_bound = error
            convergence_status = status
            iterations_required = iters
        do
            trapezoidal_value := trap
            simpson_value := simp
            integral_value := simp
            error_bound := error
            convergence_status := status
            iterations_required := iters
        end

end
```

---

### 6. STEP_SIZE_CALCULATOR (Utility)

**Purpose:** Compute optimal step size h for finite differences.

**Principle Applied:** OOSC2 Principle 4 - Reusability (isolate calculation)

**Classification:** Stateless utility

#### Features

```eiffel
class STEP_SIZE_CALCULATOR

feature -- Step Size Computation

    adaptive_step_size (x: REAL_64;
                       f_magnitude: REAL_64): REAL_64
        -- Compute optimal h based on machine epsilon
        -- Formula: h = sqrt(epsilon) * max(|f_magnitude|, 1.0)
        require
            x_finite: x.is_finite
            f_magnitude_non_negative: f_magnitude >= 0.0
        ensure
            h_positive: Result > 0.0
            h_reasonable: Result >= {REAL_64}.epsilon.sqrt
            h_small: Result < 1.0
        do
            local_magnitude := f_magnitude.max (1.0)
            Result := {REAL_64}.epsilon.sqrt * local_magnitude
        end

    refine_step_size (h: REAL_64): REAL_64
        -- Halve step size for refinement (used in adaptive quadrature)
        require
            h_positive: h > 0.0
        ensure
            refined_h_positive: Result > 0.0
            refined_h_smaller: Result < h
            refined_h_valid: Result = h / 2.0
        do
            Result := h / 2.0
        end

end
```

---

### 7. CONVERGENCE_STATUS (Enumeration)

**Purpose:** Signal numerical stability and reliability of computed result.

**Principle Applied:** OOSC2 Principle 2 - DBC (explicit status values)

#### Definition

```eiffel
class CONVERGENCE_STATUS

feature -- Status Values

    CONVERGED: CONVERGENCE_STATUS
        -- Methods agree well, error bound is reliable
        -- Result is trustworthy within stated error bound

    CONVERGED_WITH_WARNING: CONVERGENCE_STATUS
        -- Methods agree reasonably but show some divergence
        -- Error bound may be conservative
        -- Result acceptable for most applications

    DIVERGED: CONVERGENCE_STATUS
        -- Methods disagree significantly
        -- Function may be discontinuous, non-smooth, or oscillatory
        -- Result NOT TRUSTWORTHY; error bound may be invalid

    FAILED: CONVERGENCE_STATUS
        -- Computation did not complete (precondition violation, overflow, etc.)
        -- No result available

feature -- Testing

    is_reliable: BOOLEAN
        -- True if CONVERGED or CONVERGED_WITH_WARNING
        do
            Result := Current = CONVERGED or Current = CONVERGED_WITH_WARNING
        end

    is_failed: BOOLEAN
        -- True if DIVERGED or FAILED
        do
            Result := Current = DIVERGED or Current = FAILED
        end

end
```

---

### 8. DERIVATIVE_OPTIONS (Configuration Class - Phase 2)

**Purpose:** Enable Tier 2 control over derivative computation.

**Principle Applied:** OOSC2 Principle 3 - Abstraction (options pattern)

#### Features

```eiffel
class DERIVATIVE_OPTIONS

feature -- Method Selection

    method: CHARACTER
        -- 'F' = Forward, 'B' = Backward, 'C' = Central (default)

    set_method (m: CHARACTER)
        require
            m_valid: m = 'F' or m = 'B' or m = 'C'
        do
            method := m
        ensure
            method_set: method = m
        end

feature -- Step Size Control

    step_size: REAL_64
        -- User-specified h; if 0.0, use adaptive

    set_step_size (h: REAL_64)
        require
            h_zero_or_positive: h >= 0.0
        do
            step_size := h
        ensure
            step_size_set: step_size = h
        end

feature -- Tolerance Control

    tolerance: REAL_64
        -- Convergence tolerance for method refinement

    set_tolerance (t: REAL_64)
        require
            t_positive: t > 0.0
        do
            tolerance := t
        ensure
            tolerance_set: tolerance = t
        end

end
```

---

### 9. INTEGRAL_OPTIONS (Configuration Class - Phase 2)

**Purpose:** Enable Tier 2 control over integration computation.

**Principle Applied:** OOSC2 Principle 3 - Abstraction (options pattern)

#### Features

```eiffel
class INTEGRAL_OPTIONS

feature -- Method Selection

    method: CHARACTER
        -- 'T' = Trapezoidal, 'S' = Simpson (default), 'A' = Adaptive

    set_method (m: CHARACTER)
        require
            m_valid: m = 'T' or m = 'S' or m = 'A'
        do
            method := m
        ensure
            method_set: method = m
        end

feature -- Grid Control

    initial_subdivisions: INTEGER
        -- Number of initial subdivisions (default 4)

    set_initial_subdivisions (n: INTEGER)
        require
            n_positive: n > 0
        do
            initial_subdivisions := n
        ensure
            subdivisions_set: initial_subdivisions = n
        end

feature -- Tolerance Control

    tolerance: REAL_64
        -- Convergence tolerance

    set_tolerance (t: REAL_64)
        require
            t_positive: t > 0.0
        do
            tolerance := t
        ensure
            tolerance_set: tolerance = t
        end

end
```

---

## Class Dependencies

### Dependency Graph

```
SIMPLE_CALCULUS
    ├─> DERIVATIVE_CALCULATOR
    │   └─> STEP_SIZE_CALCULATOR
    │   └─> CONVERGENCE_STATUS
    │   └─> DERIVATIVE_RESULT
    │
    ├─> INTEGRAL_CALCULATOR
    │   └─> STEP_SIZE_CALCULATOR
    │   └─> CONVERGENCE_STATUS
    │   └─> INTEGRAL_RESULT
    │
    ├─> DERIVATIVE_OPTIONS (Tier 2)
    ├─> INTEGRAL_OPTIONS (Tier 2)
    └─> SIMPLE_MATH (external: trig, exp, etc.)
```

### External Dependencies

| Dependency | Purpose | Why Needed |
|-----------|---------|-----------|
| simple_math | Transcendental functions (sin, cos, exp, log) | For testing and example functions |
| base | REAL_64, FUNCTION types | Fundamental Eiffel types |
| testing | EQA_TEST_SET | For unit test infrastructure |

---

## Void Safety Design

All classes designed for `void_safety="all"`:

1. **No void attributes** - All class attributes initialized in `make`
2. **Proper Void checks** - All incoming parameters checked before use
3. **Attached declarations** - Type declarations include `attached` where needed
4. **Result initialization** - All query results guaranteed non-void

Example:

```eiffel
derivative (f: attached FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
    -- Note: f is attached (non-void) because required
    require
        x_in_domain: x.is_finite
    ensure
        result_valid: not (Result.is_nan or Result.is_infinite)
    do
        -- f is guaranteed non-void; no null checks needed
        Result := (f.item (x + h) - f.item (x)) / h
    end
```

---

## SCOOP Compatibility Design

All classes designed for SCOOP (Eiffel concurrency):

1. **No shared mutable state** - Each operation is stateless or local
2. **Immutable results** - DERIVATIVE_RESULT, INTEGRAL_RESULT never modified
3. **Thread-safe factories** - SIMPLE_CALCULUS can be shared; its features are queries
4. **No separate objects** - Calculators are stateless; can be shared across threads

Example SCOOP usage (Phase 2):

```eiffel
calculus: separate SIMPLE_CALCULUS
create calculus.make
-- Can now use calculus across multiple processors safely
f_prime := calculus.derivative (agent f, 0.5)
```

---

## Summary

| Class | Purpose | Phase | Status |
|-------|---------|-------|--------|
| SIMPLE_CALCULUS | User facade | 1 | MVP |
| DERIVATIVE_CALCULATOR | Differentiation engine | 1 | MVP |
| INTEGRAL_CALCULATOR | Integration engine | 1 | MVP |
| DERIVATIVE_RESULT | Difference result | 1 | MVP |
| INTEGRAL_RESULT | Integration result | 1 | MVP |
| STEP_SIZE_CALCULATOR | Step size utility | 1 | MVP |
| CONVERGENCE_STATUS | Status enumeration | 1 | MVP |
| DERIVATIVE_OPTIONS | Tier 2 control | 2 | Deferred |
| INTEGRAL_OPTIONS | Tier 2 control | 2 | Deferred |
| PARTIAL_DERIVATIVE | Multivariate diff | 2 | Deferred |
| GRADIENT_CALCULATOR | Gradient computation | 2 | Deferred |
| JACOBIAN_CALCULATOR | Jacobian computation | 2 | Deferred |

