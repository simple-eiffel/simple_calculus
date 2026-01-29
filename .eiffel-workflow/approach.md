# Implementation Approach: simple_calculus

**Phase 2 Status:** Contract Review Ready

---

## Architecture Overview

### Facade Pattern (SIMPLE_CALCULUS)
```
SIMPLE_CALCULUS (public interface)
├── Tier 1: derivative(), integrate(), partial_derivative()
├── Tier 2: derivative_with_options(), integrate_with_options(), gradient()
└── Tier 3: create_derivative_calculator(), create_integral_calculator()
```

### Engine Pattern
- **DERIVATIVE_CALCULATOR**: Computes forward/backward/central differences
- **INTEGRAL_CALCULATOR**: Trapezoidal, Simpson's, and adaptive integration

### Strategy Pattern
- All three difference methods computed automatically
- Methods automatically compared via CONVERGENCE_ANALYZER
- Status enum (CONVERGED/WARNING/FAILED) replaces exceptions

---

## Implementation Details

### Derivative Computation

**Adaptive Step Size (Phase 1):**
```
h = sqrt(machine_epsilon) × max(|x|, 1.0)
machine_epsilon = 2.220446049250313e-16 (IEEE 754 for REAL_64)

Assumption: Works well for |f(x)| ~ O(1)
Tier 2: User can override h explicitly
```

**Three Methods (all computed):**
1. Forward: f'(x) ≈ (f(x+h) - f(x)) / h [O(h) error]
2. Backward: f'(x) ≈ (f(x) - f(x-h)) / h [O(h) error]
3. Central: f'(x) ≈ (f(x+h) - f(x-h)) / (2h) [O(h²) error] ✓ Most accurate

**Error Estimation:**
```
error_bound = max(|f'_forward - f'_central|, |f'_backward - f'_central|)
```

**Convergence Status Logic:**
- CONVERGED: Both forward and backward agree with central (within tolerance)
- WARNING: One method agrees with central, one differs
- FAILED: Both methods differ from central by more than tolerance

**Return Value Strategy:**
- Tier 1: Returns single REAL_64 (central difference result)
- Tier 2: Returns DERIVATIVE_RESULT with value, error_bound, convergence_status
- Tier 3: Direct access to DERIVATIVE_CALCULATOR for custom logic

### Integration Computation

**Trapezoidal Rule (Tier 1/2):**
```
∫[a,b] f(x)dx ≈ (h/2) * [f(a) + 2*f(x_1) + 2*f(x_2) + ... + f(b)]
where h = (b - a) / n_intervals
```

**Simpson's Rule (Tier 2):**
```
Requires even number of intervals
∫[a,b] f(x)dx ≈ (h/3) * [f(a) + 4*f(x_1) + 2*f(x_2) + ... + f(b)]
Accuracy: O(h⁴) vs Trapezoidal O(h²)
```

**Adaptive Integration (Tier 1 default, Tier 2 recommended):**
```
Algorithm: Simpson's rule with Richardson extrapolation
1. Compute with n intervals
2. Double intervals, recompute
3. Check: |result_new - result_old| < tolerance
4. Repeat up to max_iterations (100)
5. Return result + error bound + iteration count

Postcondition: error_bound < 1e-5 (default)
```

**Partial Derivatives (multi-variable):**
```
∂f/∂x_i ≈ (f(..., x_i + h, ...) - f(..., x_i - h, ...)) / (2*h)
Perturb only variable i, hold others constant
Use central difference (most accurate)
```

### Data Objects

**DERIVATIVE_RESULT:**
- `value`: The computed derivative (REAL_64)
- `error_bound`: Estimate from method comparison (≥ 0)
- `convergence_status`: CONVERGED/WARNING/FAILED enum

**INTEGRAL_RESULT:**
- `value`: The computed integral (REAL_64)
- `error_bound`: Richardson extrapolation difference
- `iterations`: Number of adaptive refinement steps

**CONVERGENCE_STATUS:**
- Constants: `converged` (0), `warning` (1), `failed` (2)
- Feature: `to_string(status)` for display

---

## Key Design Decisions

### 1. No Symbolic Differentiation
- Numerical only (finite differences)
- Users must provide function as FUNCTION agent
- Phase 2+: Could add symbolic rules

### 2. Error Via Comparison, Not Magnitude
- Don't estimate error from |f'_forward - f'_backward| alone
- Use comparison to central (most accurate)
- Prevents overconfidence in wrong results

### 3. All Three Methods Computed
- Cost: 3 function evaluations per derivative (minimal)
- Benefit: Automatic self-validation
- Convergence status gives immediate confidence metric

### 4. Tolerance is User Responsibility
- Precondition: `tolerance_positive: tolerance > 0.0` and `tolerance_reasonable: tolerance >= 1.0e-12 and tolerance <= 1.0e-3`
- Users choose: 1e-6 for normal, 1e-10 for high precision
- Phase 1 defaults: 1e-6 (derivative), 1e-5 (integral)

### 5. Adaptive h, Not Adaptive f'
- Step size chosen once at entry
- All three methods use same h
- Simplifies error analysis, consistent behavior

### 6. Step Size Formula Documented
- h = sqrt(ε) × max(|x|, 1.0)
- Assumption: |f(x)| ~ O(1) (stated in postcondition)
- Tier 2 allows override for non-standard magnitudes

---

## Numerical Stability

### Machine Epsilon Handling
```eiffel
machine_epsilon: REAL_64 = 2.220446049250313e-16
```

- IEEE 754 double precision value
- Used in h = sqrt(ε) × scale
- Prevents underflow/overflow

### Convergence Criterion
```
|f'_method - f'_central| < tolerance
```

- Default tolerance: 1e-6 (derivative), 1e-5 (integral)
- Relative vs absolute: Absolute (simpler, works for O(1) functions)

### Edge Cases Handled

1. **x = 0**: h = sqrt(ε) × 1.0 ✓
2. **x = ±Infinity**: NaN check in postcondition
3. **f(x) = constant**: All three methods return 0 ✓
4. **f(x) unbounded**: User responsible (precondition)
5. **Zero integral**: Result = 0.0 ✓

---

## Tier Structure

### Tier 1: Simple (Beginners)
```eiffel
derivative(f, x) → REAL_64
integrate(f, a, b) → REAL_64
partial_derivative(f, point, var_index) → REAL_64
```
- One line: `Result := l_calc.central_difference(f, x)`
- No error bound, no status
- Just the result

### Tier 2: Advanced (Control-Oriented)
```eiffel
derivative_with_options(f, x, method, tolerance) → DERIVATIVE_RESULT
integrate_with_options(f, a, b, method, tolerance) → INTEGRAL_RESULT
gradient(f, point) → ARRAY [REAL_64]
```
- method: 1=forward, 2=backward, 3=central, 4=all with comparison
- Returns data objects with error bounds
- Users can tune tolerance

### Tier 3: Expert (Research)
```eiffel
create_derivative_calculator() → DERIVATIVE_CALCULATOR
create_integral_calculator() → INTEGRAL_CALCULATOR
```
- Direct engine access
- Custom algorithms possible
- Full control over step size, methods, etc.

---

## Testing Strategy

### Phase 1 Test Stubs (skeletal)
- test_derivative_simple
- test_integrate_simple
- test_partial_derivative_simple
- test_derivative_with_options
- test_integrate_with_options
- test_gradient
- test_derivative_calculator_creation
- test_integral_calculator_creation
- test_convergence_status_*
- test_derivative_accuracy_across_scales
- test_integration_error_bounds

### Phase 5 Full Tests (implementation phase)
**Unit Tests (30+):**
- Polynomials (x², x³, x⁴)
- Transcendental (sin, cos, exp, ln)
- Across scales [1e-10, 1e10]
- Edge cases (zero, infinity, discontinuity)

**Integration Tests:**
- Compare against analytical solutions
- Verify convergence status accuracy
- Test all three methods agree on smooth functions

**Adversarial Tests:**
- Non-smooth functions (|x|)
- Highly oscillatory (sin(1/x))
- Stiff functions
- Verify WARNING/FAILED status triggered correctly

---

## SIMPLE_MATH Integration

All sqrt operations delegate to SIMPLE_MATH:
```eiffel
create l_math.make
Result := l_math.sqrt(machine_epsilon)
```

**Rationale:** simple_* first policy - use SIMPLE_MATH before stdlib.

---

## Performance Characteristics

### Derivative Computation
```
Function evaluations: 6 per derivative (3 methods × 2 points each)
Time complexity: O(1) per call (constant number of evaluations)
Space complexity: O(1) (local variables only)
```

### Integration (Adaptive)
```
Function evaluations: 2^k where k = number of refinements
Worst case: 2^7 = 128 evaluations (max 100 iterations)
Time complexity: O(2^k) exponential in refinements
Space complexity: O(1) (no array storage)
```

### Partial Derivatives (n-variable)
```
Function evaluations: 2*n per gradient (central difference × n variables)
Time complexity: O(n)
Space complexity: O(n) for gradient array result
```

---

## Phase Dependencies

### Phase 1 (Current)
- ✅ Core differentiation/integration
- ✅ Partial derivatives (single calls)
- ✅ No Jacobian assembly

### Phase 2
- [ ] Jacobian matrix assembly convenience
- [ ] Monte Carlo integration option
- [ ] Automatic differentiation framework

### Phase 3+
- [ ] Symbolic differentiation rules
- [ ] Integration with simple_ode
- [ ] Complex-valued derivatives

---

## Success Criteria

### Numerical Accuracy
- Derivative: < 1e-6 relative error on smooth test functions
- Integral: < 1e-5 relative error on analytical integrals
- Error bounds: Practical (actual error < estimated bound)

### Convergence Detection
- CONVERGED: All three methods agree on smooth functions
- WARNING: Exactly one method differs (catches oscillations)
- FAILED: All three differ (catches non-smooth functions)

### Code Quality
- All preconditions enforced
- All postconditions verified by tests
- Invariants maintained
- No silent failures (convergence status always returned)

### OOSC2 Compliance
- Single responsibility: Each class has one job
- Open/closed: Easy to extend with new methods (Phase 2)
- Liskov: Results are substitutable (immutable)
- Interface segregation: 3-tier API (not overloaded)

---

## Known Limitations (Phase 1)

1. **Assumes |f(x)| ~ O(1)**: Tier 2 allows override
2. **No symbolic rules**: All numerical (Phase 2+)
3. **No higher-order derivatives**: Phase 2
4. **No Monte Carlo**: Phase 2 (delegates to simple_probability)
5. **Central difference only for partials**: Phase 2 can add forward/backward
6. **Fixed tolerances**: Tier 2 allows override

---

## Future Extensions (Phase 2+)

- Jacobian matrix assembly from partial derivatives
- Automatic differentiation (forward/reverse mode)
- Higher-order derivatives
- Monte Carlo integration
- Symbolic differentiation rules
- Integration with simple_ode for differential equations

