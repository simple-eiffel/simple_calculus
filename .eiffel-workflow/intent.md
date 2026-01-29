# Intent: simple_calculus

## What

**simple_calculus** is a numerical calculus library that provides derivatives, integrals, and partial derivatives for Eiffel applications. It enables scientific computing, physics simulations, optimization algorithms, and machine learning through verified, contract-based differentiation and integration operations.

**Core Capabilities:**
- Numerical differentiation (forward, backward, central difference methods)
- Numerical integration (trapezoidal, Simpson's rule)
- Partial derivatives for multi-variable functions
- Error estimation and convergence validation
- Adaptive step size selection (prevents under/overflow)
- Method comparison for self-validation

## Why

**Problem:** Physics simulations, optimization algorithms, and scientific computing in Eiffel require calculus operations that don't exist in the ecosystem.

**Why it matters:**
- Wave equation (∂²u/∂t² = v²∇²u) needs derivatives
- Maxwell's equations (∂E/∂t) need partial derivatives
- Gradient descent optimization needs gradients
- Newton-Raphson solvers need Jacobians (computed from partial derivatives)
- Eiffel has NO built-in calculus library

**Impact of not solving:** Cannot build physics engines, optimization solvers, or scientific applications efficiently in Eiffel.

## Users

| User Type | Needs | Use Case |
|-----------|-------|----------|
| Physics Simulator | ∂/∂x, ∂²/∂x², ∫f(x)dx | Wave equations, field simulations |
| Optimization Engineer | Gradients, Hessians | Gradient descent, Newton-Raphson |
| ML Researcher | Backpropagation support | Neural network training |
| Financial Analyst | Numerical integration | Option pricing, risk analysis |
| Robotics Engineer | Jacobian matrices | Inverse kinematics |

## Acceptance Criteria

- [ ] Derivatives accurate to < 1e-6 relative error on test functions (polynomials, transcendental)
- [ ] Integration accurate to < 1e-5 relative error on test integrals
- [ ] All methods return error bounds (not silent failures)
- [ ] Convergence status enum signals reliability (CONVERGED, WARNING, FAILED)
- [ ] Adaptive step size works across scales (tiny x=1e-10 to large x=1e10)
- [ ] Forward/backward/central methods available for comparison
- [ ] Seamless integration with simple_probability (Monte Carlo option)
- [ ] All methods void-safe and SCOOP-compatible
- [ ] 50+ unit tests, all passing
- [ ] GitHub Pages documentation with physics examples

## Out of Scope

- **NOT Symbolic differentiation:** No parsing expressions or symbolic rules (Phase 2+)
- **NOT Higher-order derivatives:** Phase 1 focuses on 1st derivatives (Phase 2 adds 2nd order)
- **NOT Differential equation solvers:** That's simple_ode (separate library)
- **NOT Special functions:** Bessel, Hermite, etc. → simple_special
- **NOT GPU acceleration:** CPU-only, pure Eiffel

## Dependencies (REQUIRED - simple_* First Policy)

**Rule:** Always prefer simple_* libraries over ISE/Gobo. If no simple_* equivalent exists, document the gap for future development.

| Need | Library | Justification |
|------|---------|---------------|
| Basic arithmetic (sqrt, sin, cos, abs, max) | simple_math | Foundation library, required |
| Random sampling (future: Monte Carlo) | simple_random | For stochastic integration (Phase 2) |
| Probability distributions (future) | simple_probability | For Monte Carlo integration (Phase 2) |
| Fundamental types | base (ISE only) | No simple_* equivalent exists |
| Unit testing framework | testing (ISE only) | No simple_* equivalent exists |

**Gaps Identified (Potential future simple_* libraries):**
- None - all needs covered by simple_* or justified ISE use

## MML Decision (REQUIRED)

**Question:** Does this library need MML model queries for precise postconditions?

**Analysis:**
- simple_calculus is PURE COMPUTATION (no internal collections)
- No HASH_TABLE, ARRAYED_LIST, or other collections
- Operates on scalars and function objects only
- Postconditions specify mathematical properties, not collection invariants

**Decision:** **NO**

**Rationale:** Pure numerical computation with scalar results. Frame conditions will use simple inequalities (error_bound <= epsilon) rather than MML collection invariants. MML would add complexity without benefit for this library.

---

## Implementation Approach

### Phase 1 (MVP - v1.0.0)
**Deliverable:** Core differentiation and integration

**Classes:**
- SIMPLE_CALCULUS (facade)
- DERIVATIVE_CALCULATOR (engine)
- INTEGRAL_CALCULATOR (engine)
- DERIVATIVE_RESULT (data + error)
- INTEGRAL_RESULT (data + error)
- STEP_SIZE_CALCULATOR (utility)
- CONVERGENCE_STATUS (enum)

**API Tiers:**
1. **Tier 1 (Simple):** `derivative(f, x)`, `integrate(f, a, b)` - one-liners
2. **Tier 2 (Advanced):** `derivative_with_options()`, `integrate_with_options()` - control tolerance, method
3. **Tier 3 (Expert):** Direct engine access for research use

### Phase 2 (Full - v2.0.0)
- Automatic differentiation (forward/reverse mode)
- Jacobian matrix computation
- Stochastic integration (Monte Carlo)
- Taylor series expansion

### Phase 3+ (Extensions)
- Symbolic differentiation rules
- Integration with simple_ode for ODEs

---

## Design Principles

1. **Design by Contract:** Every method has require/ensure/invariant
   - Preconditions validate mathematical assumptions (smoothness, bounds)
   - Postconditions guarantee error bounds
   - Invariants enforce consistency

2. **Error Estimation:** Every operation returns error bounds
   - Users KNOW the accuracy
   - No silent failures
   - Enables reliability checking

3. **Adaptive Algorithms:** Step size selection automatic
   - h = sqrt(ε) × max(|x|, 1.0)
   - Prevents under/overflow
   - Works across different scales

4. **Method Comparison:** Forward/backward/central all computed
   - Results compared for validation
   - Convergence status reflects agreement
   - Built-in self-validation

5. **Simple API:** Facade hides complexity
   - Users call `derivative(agent f, x)`
   - Don't see forward/backward/central details
   - Don't see step size selection
   - Just get accurate results with error bounds

## Physics Integration Path

```
simple_math (foundation)
     ↓
simple_calculus (derivatives, integrals)
     ↓ computes ∂f/∂x
     ↓
simple_linalg (assembles Jacobians)
     ↓
simple_physics (solves F=ma, Maxwell, wave equations)
```

**Seamless Integration:**
- Calculus computes partial derivatives
- Linalg assembles Jacobian matrices
- Physics solvers use both together
- All use simple_* ecosystem

---

## Success Metrics

| Metric | Target |
|--------|--------|
| Derivative accuracy | < 1e-6 relative error |
| Integration accuracy | < 1e-5 relative error |
| OOSC2 compliance | 4/4 principles |
| Test coverage | 50+ tests, 100% pass |
| Void safety | void_safety="all" |
| SCOOP ready | stateless facades |
| Documentation | GitHub Pages + examples |
