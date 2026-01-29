# Intent: simple_calculus (v2 - Post-Review)

**Status:** REFINED & APPROVED
**Date:** 2026-01-29 14:35 UTC
**Review:** AI review complete, all clarifications resolved

---

## What

**simple_calculus** is a numerical calculus library that provides derivatives, integrals, and partial derivatives for Eiffel applications. It enables scientific computing, physics simulations, optimization algorithms, and machine learning through verified, contract-based differentiation and integration operations.

**Core Capabilities:**
- Numerical differentiation (forward, backward, central difference methods with automatic comparison)
- Numerical integration (trapezoidal, Simpson's rule, with Monte Carlo option in Phase 2)
- Partial derivatives for multi-variable functions
- Error estimation (via method comparison)
- Convergence validation (CONVERGED/WARNING/FAILED status)
- Adaptive step size selection (h = sqrt(ε) × max(|x|, 1.0), works for |f(x)| ~ O(1))

---

## Why

**Problem:** Physics simulations, optimization algorithms, and scientific computing in Eiffel require calculus operations that don't exist in the ecosystem.

**Why it matters:**
- Wave equation (∂²u/∂t² = v²∇²u) needs derivatives
- Maxwell's equations (∂E/∂t) need partial derivatives
- Gradient descent optimization needs gradients
- Newton-Raphson solvers need Jacobians (computed from partial derivatives in Phase 2)
- Eiffel has NO built-in calculus library

**Impact of not solving:** Cannot build physics engines, optimization solvers, or scientific applications efficiently in Eiffel.

---

## Users

| User Type | Needs | Use Case |
|-----------|-------|----------|
| Physics Simulator | ∂/∂x, ∫f(x)dx | Wave equations, field simulations |
| Optimization Engineer | Gradients | Gradient descent, Newton-Raphson |
| ML Researcher | Backpropagation framework | Neural network training (Phase 2+) |
| Financial Analyst | Numerical integration | Option pricing, risk analysis |
| Robotics Engineer | Jacobian matrices | Inverse kinematics (Phase 2) |

---

## Acceptance Criteria (Measurable)

- [ ] Derivatives accurate to < 1e-6 relative error on test set (x², x³, sin, cos, exp, ln)
  - Test: |f'_computed - f'_analytical| / |f'_analytical| < 1e-6
  - Across scales: x ∈ [1e-10, 1e10]
  - Functions with |f(x)| ~ O(1) assumed (standard in numerics)

- [ ] Integration accurate to < 1e-5 relative error on test integrals
  - Test: |∫_computed - ∫_analytical| / |∫_analytical| < 1e-5

- [ ] All methods return error bounds (not silent failures)
  - Error bound = max(|f'_forward - f'_central|, |f'_backward - f'_central|)
  - Returned in DERIVATIVE_RESULT.error_bound

- [ ] Convergence status enum signals reliability
  - CONVERGED: All three methods agree to within tolerance
  - WARNING: Two methods agree, one differs
  - FAILED: All three methods disagree significantly

- [ ] Adaptive step size works across scales [1e-10, 1e10]
  - Formula: h = sqrt(ε) × max(|x|, 1.0)
  - Documented: works best for |f(x)| ~ O(1); Tier 2 allows override

- [ ] Forward/backward/central methods available for comparison
  - All three computed automatically
  - Comparison results returned as CONVERGENCE_STATUS

- [ ] Phase 2: Seamless integration with simple_probability (Monte Carlo option)
  - Phase 1: Stub with Tier 2 option flag
  - Phase 2: Delegates to simple_probability for sampling

- [ ] All methods void-safe and SCOOP-compatible
  - void_safety="all" in ECF
  - Stateless facades enable concurrent use

- [ ] 50+ unit tests, all passing
  - Coverage: forward/backward/central, error bounds, convergence status, edge cases

- [ ] GitHub Pages documentation with physics examples
  - Examples: gravity simulation, wave equation gradient, optimization

---

## Out of Scope

- **NOT Symbolic differentiation:** No parsing expressions or symbolic rules (Phase 2+)
- **NOT Higher-order derivatives:** Phase 1 focuses on 1st derivatives (Phase 2 adds 2nd order)
- **NOT Differential equation solvers:** That's simple_ode (separate library)
- **NOT Special functions:** Bessel, Hermite, etc. → simple_special
- **NOT GPU acceleration:** CPU-only, pure Eiffel
- **NOT Functions with extreme magnitudes:** Phase 1 assumes |f(x)| ~ O(1) for standard accuracy

---

## Dependencies (REQUIRED - simple_* First Policy)

| Need | Library | Justification |
|------|---------|---------------|
| Basic arithmetic (sqrt, sin, cos, abs, max) | simple_math | Foundation library, required |
| Random sampling (future: Monte Carlo) | simple_random | For stochastic integration (Phase 2) |
| Probability distributions (future) | simple_probability | For Monte Carlo integration (Phase 2) |
| Fundamental types | base (ISE only) | No simple_* equivalent exists |
| Unit testing framework | testing (ISE only) | No simple_* equivalent exists |

**Gaps Identified:** None - all needs covered by simple_* or justified ISE use.

---

## MML Decision (REQUIRED)

**Question:** Does this library need MML model queries for precise postconditions?

**Decision:** **NO**

**Rationale:** Pure numerical computation with scalar results. No internal collections (HASH_TABLE, ARRAYED_LIST). Postconditions specify mathematical properties (error bounds, convergence status) using simple inequalities. MML would add complexity without benefit.

---

## Implementation Approach

### Phase 1 (MVP - v1.0.0)
**Deliverable:** Core differentiation and integration

**Classes:**
1. SIMPLE_CALCULUS (facade)
2. DERIVATIVE_CALCULATOR (engine - computes forward/backward/central)
3. INTEGRAL_CALCULATOR (engine - computes trapezoidal/Simpson's)
4. DERIVATIVE_RESULT (data: value, error_bound, convergence_status)
5. INTEGRAL_RESULT (data: value, error_bound, iterations)
6. STEP_SIZE_CALCULATOR (utility: computes h = sqrt(ε) × max(|x|, 1.0))
7. CONVERGENCE_STATUS (enum: CONVERGED, WARNING, FAILED)
8. CONVERGENCE_ANALYZER (utility: compares forward/backward/central methods)

**API Tiers:**

**Tier 1 (Simple - Most Users):**
```eiffel
derivative (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64): REAL_64
integrate (f: FUNCTION [REAL_64, REAL_64]; a, b: REAL_64): REAL_64
partial_derivative (f: FUNCTION [ARRAY [REAL_64], REAL_64];
                   point: ARRAY [REAL_64]; var_index: INTEGER): REAL_64
```

**Tier 2 (Advanced - Control-Oriented):**
```eiffel
derivative_with_options (f: FUNCTION [REAL_64, REAL_64]; x: REAL_64;
                        method: DERIVATIVE_METHOD; -- FORWARD, BACKWARD, CENTRAL, ALL
                        tolerance: REAL_64): DERIVATIVE_RESULT

integrate_with_options (f: FUNCTION [REAL_64, REAL_64]; a, b: REAL_64;
                       method: INTEGRATION_METHOD; -- TRAPEZOIDAL, SIMPSON, MONTE_CARLO (Phase 2)
                       tolerance: REAL_64): INTEGRAL_RESULT

gradient (f: FUNCTION [ARRAY [REAL_64], REAL_64];
         point: ARRAY [REAL_64]): ARRAY [REAL_64]  -- All partials at once
```

**Tier 3 (Expert - Research):**
```eiffel
create_derivative_calculator (): DERIVATIVE_CALCULATOR  -- Direct engine access
create_integral_calculator (): INTEGRAL_CALCULATOR
```

### Phase 2 (Full - v2.0.0)
- Automatic differentiation (forward/reverse mode)
- Jacobian matrix computation (assembles partials into MATRIX)
- Stochastic integration (Monte Carlo via simple_probability)
- Taylor series expansion
- Higher-order derivatives (2nd, 3rd, etc.)

### Phase 3+ (Extensions)
- Symbolic differentiation rules
- Integration with simple_ode for differential equations
- Complex-valued derivatives (Phase 3+)

---

## Design Principles

1. **Design by Contract:** Every method has require/ensure/invariant
   - Preconditions validate mathematical assumptions (smoothness, bounds)
   - Postconditions guarantee error bounds
   - Invariants enforce consistency

2. **Error Estimation:** Every operation returns error bounds
   - Method: Comparison between forward/backward/central differences
   - Cost: Free (all three computed anyway)
   - Formula: error_bound = max(|f'_fwd - f'_cent|, |f'_bwd - f'_cent|)
   - Users KNOW the accuracy; No silent failures

3. **Adaptive Algorithms:** Step size selection automatic
   - Formula: h = sqrt(ε) × max(|x|, 1.0)
   - Assumption: Works well for |f(x)| ~ O(1)
   - Prevents under/overflow automatically
   - Works across different x scales [1e-10, 1e10]
   - Tier 2 allows override for non-standard function magnitudes

4. **Method Comparison:** Forward/backward/central all computed
   - Results compared automatically
   - CONVERGENCE_STATUS reflects agreement:
     - CONVERGED: All three agree
     - WARNING: Two agree, one differs
     - FAILED: All three disagree
   - Built-in self-validation without extra cost

5. **Simple API:** Facade hides complexity
   - Tier 1: Users call `derivative(agent f, x)` and get REAL_64
   - Don't see forward/backward/central details
   - Don't see step size selection
   - Just get accurate results with error bounds
   - Can ask for convergence status if desired

---

## Error Handling Strategy

**All errors signaled via convergence status, not exceptions:**
- CONVERGED: Result is trustworthy; use with confidence
- WARNING: Result may be unreliable; consider using Tier 2 with manual h tuning
- FAILED: Result is unreliable; function likely not smooth or other issue

**Mathematical assumptions (preconditions):**
- Function must be smooth (continuous derivatives) on [a, b] interval
- For integration: function must be continuous on [a, b]
- For differentiation: function must be continuously differentiable near x

---

## Physics Integration Path

```
simple_math (foundation: sqrt, sin, cos, etc.)
     ↓
simple_calculus (Phase 1: ∂f/∂x)
     ↓
simple_calculus (Phase 2: Jacobian assembly)
     ↓
simple_linalg (solves linear systems with Jacobians)
     ↓
simple_physics (solves F=ma, Maxwell, wave equations)
```

**Seamless Integration:**
- Calculus Phase 1: Computes partial derivatives ∂f/∂x_i
- Calculus Phase 2: Assembles Jacobian matrix J (m×n matrix)
- Linalg: Solves J·δx = -f(x) for Newton-Raphson
- Physics: Uses both for electromagnetic, structural, fluid simulations

---

## Success Metrics

| Metric | Target | Measurement |
|--------|--------|------------|
| Derivative accuracy | < 1e-6 relative error | Standard test functions (polynomial, transcendental) |
| Integration accuracy | < 1e-5 relative error | Analytical integrals vs numerical |
| Error estimation quality | Practical bounds | Compare estimated vs actual error |
| Convergence detection | Reliable status | All three methods agree on smooth functions |
| OOSC2 compliance | 4/4 principles | Contract language, abstraction, reusability |
| Test coverage | 50+ tests, 100% pass | Forward/backward/central, edge cases, scales |
| Void safety | void_safety="all" | Compiler enforced |
| SCOOP ready | Stateless facades | No mutable shared state |
| Documentation | GitHub Pages + examples | Physics examples, API documentation |

---

## Status

✅ **Intent APPROVED**
- Research: Complete
- Specification: Complete
- AI Review: Complete
- All clarifications resolved
- Ready for Phase 1: /eiffel.contracts
