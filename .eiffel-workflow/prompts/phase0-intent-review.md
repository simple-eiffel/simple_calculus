# Phase 0: Intent Review Request

**Instructions:** Review the intent document below and generate probing questions to clarify vague language, identify missing requirements, and surface implicit assumptions.

## Review Criteria

Look for:
1. **Vague language:** Words like "fast", "secure", "easy", "flexible" without concrete definitions
2. **Missing edge cases:** What happens with empty input? Maximum size? Invalid data?
3. **Untestable criteria:** Are acceptance criteria specific and measurable?
4. **Hidden dependencies:** What external systems or libraries are assumed?
5. **Scope ambiguity:** Is "out of scope" clearly defined?

## Output Format

Provide 5-10 probing questions. For each:
- Quote the vague phrase
- Explain why it's vague
- Offer 2-3 concrete alternatives the user can choose from

---

## Intent Document to Review

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

## Dependencies

| Need | Library | Justification |
|------|---------|---------------|
| Basic arithmetic (sqrt, sin, cos, abs, max) | simple_math | Foundation library, required |
| Random sampling (future: Monte Carlo) | simple_random | For stochastic integration (Phase 2) |
| Probability distributions (future) | simple_probability | For Monte Carlo integration (Phase 2) |
| Fundamental types | base (ISE only) | No simple_* equivalent exists |
| Unit testing framework | testing (ISE only) | No simple_* equivalent exists |

## MML Decision

**Decision:** **NO**

**Rationale:** Pure numerical computation with scalar results. Frame conditions will use simple inequalities (error_bound <= epsilon) rather than MML collection invariants.

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
