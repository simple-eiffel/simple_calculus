# 06-INTERFACE-DESIGN: simple_calculus

## Executive Summary
This document specifies the public API (interface) for simple_calculus, emphasizing user ergonomics, agent-based function passing (D-004), and Tier 1/2/3 API stratification.

---

## Design Principles

1. **Simplicity First (Tier 1):** Users see minimal API; complexity hidden
2. **Agent-Based Functions (D-004):** Closures for function passing
3. **Error Transparency:** Every operation returns error bounds and convergence status
4. **Fail-Safe:** Preconditions prevent invalid operations; postconditions guarantee safety
5. **Extensibility:** Tier 2/3 provides escape hatch for advanced use

---

## Tier 1 API: Simple Operations

### User-Facing Pattern

**Philosophy:** "Works out of the box with sensible defaults"

#### Derivative Computation

```eiffel
-- Example 1: Simple function
my_function (x: REAL_64): REAL_64
    do
        Result := x * x
    end

-- Usage
calculus: SIMPLE_CALCULUS
create calculus.make
f_prime_at_1 := calculus.derivative (agent my_function, 1.0)
-- Result: approximately 2.0 (derivative of x^2 at x=1)

-- Example 2: Lambda-like closure
f_prime_at_2 := calculus.derivative (
    agent (x: REAL_64): REAL_64 do Result := x * x end,
    2.0
)
-- Result: approximately 4.0

-- Example 3: Transcendental function from simple_math
calculus.derivative (agent simple_math.sine, 0.0)
-- Result: approximately 1.0 (derivative of sin at 0)
```

**Tier 1 Signature:**
```eiffel
derivative (f: attached FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
```

**Returns:**
- Single REAL_64 value (derivative estimate)
- Automatically uses adaptive step size
- Automatically uses central difference (most accurate)
- Automatically compares methods internally

**User Responsibility:**
- Ensure function is smooth (documented assumption)
- Check if result seems reasonable (implicit error awareness)
- Use derivative_with_error if you need confidence bounds

#### Integration Computation

```eiffel
-- Example 1: Simple function
my_quadratic (x: REAL_64): REAL_64
    do
        Result := x * x
    end

-- Usage
calculus: SIMPLE_CALCULUS
create calculus.make
integral := calculus.integrate (agent my_quadratic, 0.0, 1.0)
-- Result: approximately 0.333... (∫x^2 dx from 0 to 1 = 1/3)

-- Example 2: From simple_math
integral := calculus.integrate (agent simple_math.sine, 0.0, 3.14159)
-- Result: approximately 2.0 (∫sin(x) dx from 0 to π)
```

**Tier 1 Signature:**
```eiffel
integrate (f: attached FUNCTION [REAL_64, REAL_64]; a, b: REAL_64): REAL_64
```

**Returns:**
- Single REAL_64 value (integral estimate)
- Automatically uses Simpson's rule (most accurate for smooth functions)
- Automatically refines grid until convergence

**User Responsibility:**
- Ensure function is continuous on [a,b]
- Order bounds correctly: a < b
- Validate result makes sense

---

## Tier 2 API: Advanced Control

### When Tier 1 Isn't Enough

**Scenario:** "I need error bounds" or "Simpson's rule doesn't converge"

#### Feature: derivative_with_error

```eiffel
-- User wants error estimate and convergence info
result := calculus.derivative_with_error (agent f, x)

-- result is DERIVATIVE_RESULT containing:
-- .derivative_value      -- estimated f'(x)
-- .error_bound           -- |estimated - actual| <= this
-- .convergence_status    -- CONVERGED, DIVERGED, etc.
-- .forward_diff          -- forward difference result (for comparison)
-- .backward_diff         -- backward difference result
-- .central_diff          -- central difference result (main estimate)
-- .method_agreement      -- how well three methods agree (0-1)

-- Example: Check if result trustworthy
result := calculus.derivative_with_error (agent f, x)
if result.convergence_status = CONVERGED then
    -- Safe to use result.derivative_value
    use_in_physics_calculation (result.derivative_value)
else
    -- Function probably not smooth enough
    -- Try another approach or refine function behavior
    log.error ("Derivative failed for this function")
    log.info ("Estimated error: " + result.error_bound.out)
end
```

**Signature:**
```eiffel
derivative_with_error (f: attached FUNCTION [REAL_64, REAL_64];
                      x: REAL_64): DERIVATIVE_RESULT
```

**Returns:** DERIVATIVE_RESULT with:
- `derivative_value: REAL_64` -- estimated f'(x)
- `error_bound: REAL_64` -- absolute error bound
- `convergence_status: CONVERGENCE_STATUS` -- reliability indicator
- `forward_diff, backward_diff, central_diff: REAL_64` -- three estimates
- `method_agreement: REAL_64` -- agreement metric [0,1]
- `relative_error: REAL_64` -- error_bound / |derivative_value|

#### Feature: integrate_with_error

```eiffel
-- User wants error estimate and convergence info
result := calculus.integrate_with_error (agent f, 0.0, 1.0)

-- result is INTEGRAL_RESULT containing:
-- .integral_value        -- estimated ∫f
-- .error_bound           -- |estimated - actual| <= this
-- .convergence_status    -- CONVERGED, DIVERGED, etc.
-- .iterations_required   -- how many refinements
-- .trapezoidal_value     -- trapezoidal rule result
-- .simpson_value         -- Simpson's rule result

-- Example: Verify convergence
result := calculus.integrate_with_error (agent f, a, b)
if result.convergence_status = CONVERGED and result.error_bound < 1e-9 then
    -- Highly accurate result
    critical_value := result.integral_value
elsif result.convergence_status = CONVERGED_WITH_WARNING then
    -- Acceptable but not ideal; check error bound
    acceptable_value := result.integral_value
else
    -- Failed to converge; likely discontinuous function
    handle_divergence (result.error_bound, result.iterations_required)
end
```

**Signature:**
```eiffel
integrate_with_error (f: attached FUNCTION [REAL_64, REAL_64];
                     a, b: REAL_64): INTEGRAL_RESULT
```

**Returns:** INTEGRAL_RESULT with:
- `integral_value: REAL_64` -- estimated ∫[a,b] f
- `error_bound: REAL_64` -- error estimate
- `convergence_status: CONVERGENCE_STATUS` -- reliability
- `trapezoidal_value, simpson_value: REAL_64` -- two estimates
- `iterations_required: INTEGER` -- refinement iterations
- `final_grid_size: INTEGER` -- final number of subdivisions
- `relative_error: REAL_64` -- error_bound / |integral_value|

#### Feature: derivative_with_options (Phase 2)

```eiffel
-- User specifies method, step size, tolerance
options: DERIVATIVE_OPTIONS
create options.make
options.set_method ('F')             -- Force forward difference
options.set_step_size (1e-5)         -- Override adaptive h
options.set_tolerance (1e-8)         -- Convergence tolerance

result := calculus.derivative_with_options (agent f, x, options)
-- Returns DERIVATIVE_RESULT with specified settings
```

**Signature:**
```eiffel
derivative_with_options (f: attached FUNCTION [REAL_64, REAL_64];
                        x: REAL_64;
                        options: attached DERIVATIVE_OPTIONS): DERIVATIVE_RESULT
```

**Options Class:**
```eiffel
class DERIVATIVE_OPTIONS
feature
    method: CHARACTER  -- 'F'=Forward, 'B'=Backward, 'C'=Central (default)
    set_method (m: CHARACTER)

    step_size: REAL_64  -- 0.0=adaptive (default), >0=user-specified
    set_step_size (h: REAL_64)

    tolerance: REAL_64  -- Convergence tolerance
    set_tolerance (t: REAL_64)
end
```

#### Feature: integrate_with_options (Phase 2)

```eiffel
-- User specifies method, grid, tolerance
options: INTEGRAL_OPTIONS
create options.make
options.set_method ('S')             -- Simpson's rule
options.set_initial_subdivisions (8) -- Start with 8 intervals
options.set_tolerance (1e-10)        -- Tight tolerance

result := calculus.integrate_with_options (agent f, 0.0, 1.0, options)
```

**Signature:**
```eiffel
integrate_with_options (f: attached FUNCTION [REAL_64, REAL_64];
                       a, b: REAL_64;
                       options: attached INTEGRAL_OPTIONS): INTEGRAL_RESULT
```

**Options Class:**
```eiffel
class INTEGRAL_OPTIONS
feature
    method: CHARACTER  -- 'T'=Trapezoidal, 'S'=Simpson (default), 'A'=Adaptive
    set_method (m: CHARACTER)

    initial_subdivisions: INTEGER  -- Starting grid size
    set_initial_subdivisions (n: INTEGER)

    tolerance: REAL_64  -- Convergence tolerance
    set_tolerance (t: REAL_64)

    max_iterations: INTEGER  -- Max refinement iterations
    set_max_iterations (n: INTEGER)
end
```

#### Configuration Features

```eiffel
-- Global configuration (affects Tier 1 defaults)
calculus: SIMPLE_CALCULUS
create calculus.make
calculus.set_tolerance (1e-12)         -- Default convergence tolerance
calculus.set_max_iterations (50)       -- Max refinement steps

-- Then Tier 1 calls use these defaults
result := calculus.derivative (agent f, x)
-- Uses tolerance=1e-12 internally (though Tier 1 doesn't expose it)
```

---

## Tier 3 API: Engine Access (Phase 2)

### When You Need Complete Control

**Scenario:** "I need to call the raw algorithm directly"

```eiffel
-- Instantiate engines directly
deriv_calc: DERIVATIVE_CALCULATOR
create deriv_calc.make

-- Call low-level methods
h := 1e-7
forward_est := deriv_calc.derivative_forward (agent f, x, h)
central_est := deriv_calc.derivative_central (agent f, x, h)

-- Or get full result with error estimate
result := deriv_calc.derivative_with_error (agent f, x, h)

-- Similarly for integration
integ_calc: INTEGRAL_CALCULATOR
create integ_calc.make

trap_result := integ_calc.integrate_trapezoidal (agent f, 0.0, 1.0, 100)
simp_result := integ_calc.integrate_simpson (agent f, 0.0, 1.0, 100)
result := integ_calc.integrate_with_error (agent f, 0.0, 1.0, tolerance=1e-8)
```

**When to Use Tier 3:**
- Integrating with other libraries that expect engine access
- Custom refinement strategies
- Research/experimentation
- Performance-critical inner loops

**When NOT to Use Tier 3:**
- Normal application code (use Tier 1)
- Most scientific computing (use Tier 2)
- Learning the library (start with Tier 1)

---

## API Organization in Code

### File Structure

```
simple_calculus/
├── src/
│   ├── simple_calculus.e         -- Tier 1 facade (main user interface)
│   ├── tier2/
│   │   ├── derivative_result.e
│   │   ├── integral_result.e
│   │   ├── derivative_options.e
│   │   └── integral_options.e
│   ├── engines/
│   │   ├── derivative_calculator.e
│   │   ├── integral_calculator.e
│   │   └── step_size_calculator.e
│   └── support/
│       └── convergence_status.e
```

### Import Strategy

**User imports only:**
```eiffel
import
    simple_calculus: "..."           -- Tier 1
end
```

**Advanced user imports:**
```eiffel
import
    simple_calculus: "..."           -- Tier 1
    derivative_result: "..."         -- Tier 2
    integral_result: "..."           -- Tier 2
    convergence_status: "..."        -- For status checking
end
```

**Researcher imports everything:**
```eiffel
import
    simple_calculus: "..."
    derivative_calculator: "..."
    integral_calculator: "..."
    step_size_calculator: "..."
    -- etc.
end
```

---

## Function Representation: Agent Patterns

### Basic Pattern

```eiffel
-- Pattern 1: Method reference
my_function (x: REAL_64): REAL_64
    do
        Result := x * x + 2 * x + 1
    end

f_prime := calculus.derivative (agent my_function, 1.0)
```

### Closure Pattern

```eiffel
-- Pattern 2: Inline closure
-- Capture variables from enclosing scope
threshold: REAL_64 := 0.5
f_prime := calculus.derivative (
    agent (x: REAL_64): REAL_64
        do
            Result := if x > threshold then x else 0.0 end
        end,
    1.0
)
```

### Integration with simple_math

```eiffel
-- Pattern 3: Use simple_math functions directly
math: SIMPLE_MATH
create math.make

sine_derivative := calculus.derivative (agent math.sine, 0.0)
exp_derivative := calculus.derivative (agent math.exponential, 1.0)
log_derivative := calculus.derivative (agent math.logarithm, 2.0)

-- Or wrap with scaling/transformation
sin_2x := agent (x: REAL_64): REAL_64
    do
        Result := math.sine (2.0 * x)
    end

sin_2x_derivative := calculus.derivative (sin_2x, 0.0)
```

### Multi-Parameter Capture

```eiffel
-- Pattern 4: Parameterized function
create_scaled_quadratic (scale: REAL_64): FUNCTION [REAL_64, REAL_64]
    do
        Result := agent (x: REAL_64): REAL_64
            do
                Result := scale * x * x
            end
    end

quadratic_2x := create_scaled_quadratic (2.0)
derivative := calculus.derivative (quadratic_2x, 1.0)
-- Result: 4.0 (derivative of 2x^2 at x=1)
```

---

## Error Handling Strategy

### No Exceptions by Default

**Philosophy:** Numerical methods should not throw exceptions; instead, signal problems through result status.

```eiffel
-- Tier 1 doesn't throw; returns finite result
result := calculus.derivative (agent f, x)
-- Even if f is discontinuous, returns a number
-- You may not trust it (but you got an answer)

-- Tier 2 gives you convergence_status to decide
result := calculus.derivative_with_error (agent f, x)
if result.convergence_status = DIVERGED then
    -- Handle problem gracefully
    log.warn ("Derivative diverged; function likely discontinuous")
else
    -- Safe to use
    use_result (result.derivative_value)
end
```

### Precondition Violations (Optional Checking)

Preconditions like `function_smooth` are **documented assumptions**, not runtime checks. Users read documentation and ensure compliance.

```eiffel
-- This is documented as requiring smoothness
-- If you pass non-smooth function, you violated contract
-- Eiffel compiler checks preconditions with:
--   -check_preconditions: included

-- To see precondition failures:
calculus.set_assertion_level (All_assertions)
result := calculus.derivative (agent |x|, 0.0)
-- Will report precondition violation at runtime
```

---

## API Stability and Evolution

### Backwards Compatibility Commitment

**Tier 1 is frozen:**
- `derivative(f, x): REAL_64` never changes
- `integrate(f, a, b): REAL_64` never changes
- Signature and semantics are stable

**Tier 2 can grow but not shrink:**
- Can add new `*_with_error` features
- Can add new options (via builder pattern)
- Cannot remove existing features

**Tier 3 can evolve:**
- Engine implementations can be optimized
- Internal methods may be reorganized
- Documented only for advanced users

### Migration Path from Tier 1 to Tier 2

```eiffel
-- Phase 1: Start with Tier 1
f_prime := calculus.derivative (agent f, x)

-- Phase 2: Need more control; upgrade to Tier 2
result := calculus.derivative_with_error (agent f, x)
if result.convergence_status = CONVERGED then
    f_prime := result.derivative_value
end

-- No code breakage; simply calling different method
```

---

## Example User Code

### Physics Simulation

```eiffel
class GRAVITY_SIMULATOR
feature
    gravity_potential (r: REAL_64): REAL_64
        -- V(r) = -GM/r
        do
            Result := -9.81 / r
        end

    run_simulation
        -- Compute gravitational force as F = -dV/dr
        local
            calculus: SIMPLE_CALCULUS
            distance: REAL_64
            force: REAL_64
        do
            create calculus.make
            distance := 10.0
            force := -calculus.derivative (agent gravity_potential, distance)
            print ("Force at distance %f: %f".formatted_with (distance, force))
        end
end
```

### Optimization Algorithm

```eiffel
class GRADIENT_DESCENT
feature
    minimize (f: FUNCTION [REAL_64, REAL_64]; x0: REAL_64): REAL_64
        -- Find minimum of f using gradient descent
        local
            calculus: SIMPLE_CALCULUS
            x, gradient, step_size: REAL_64
            iteration: INTEGER
        do
            create calculus.make
            x := x0
            step_size := 0.01
            from iteration := 1 until iteration > 100 loop
                -- Compute gradient (derivative)
                gradient := calculus.derivative (f, x)
                -- Move in opposite direction of gradient
                x := x - step_size * gradient
                iteration := iteration + 1
            end
            Result := x
        end
end
```

### Integration for Area Calculation

```eiffel
class AREA_CALCULATOR
feature
    compute_area_under_curve (f: FUNCTION [REAL_64, REAL_64];
                            a, b: REAL_64): REAL_64
        local
            calculus: SIMPLE_CALCULUS
        do
            create calculus.make
            Result := calculus.integrate (f, a, b)
        end

    example
        local
            semicircle: FUNCTION [REAL_64, REAL_64]
            area: REAL_64
            math: SIMPLE_MATH
        do
            create math.make
            -- f(x) = sqrt(1 - x^2) is upper half of unit circle
            semicircle := agent (x: REAL_64): REAL_64
                do
                    Result := math.sqrt (1.0 - x * x)
                end

            create math.make
            area := compute_area_under_curve (semicircle, -1.0, 1.0)
            -- Result: approximately π/2 ≈ 1.5708
        end
end
```

---

## Summary Table

| Tier | User | Complexity | Control | Return Type |
|------|------|-----------|---------|------------|
| Tier 1 | Beginners | Minimal | Automatic defaults | REAL_64 |
| Tier 2 | Scientists | Medium | Options object | Result class |
| Tier 3 | Researchers | High | Direct engine | Varies |

