# SCOPE: simple_calculus

## Problem Statement
Scientists, engineers, and researchers need robust, verified calculus operations (derivatives, integrals, partial derivatives) in Eiffel without relying on external C libraries or proprietary systems.

What's wrong today: Eiffel lacks a native calculus library for numerical and symbolic operations.
Who experiences this: Physics simulations, optimization algorithms, engineering analysis, scientific computing.
Impact of not solving: Cannot build physics engines, optimization solvers, or scientific applications efficiently in Eiffel.

## Target Users
| User Type | Needs | Pain Level |
|-----------|-------|-----------|
| Physics Simulator | Numerical derivatives, gradient calculations | HIGH |
| Optimization Algorithm | Gradient descent, line search | HIGH |
| Financial Analyst | Numerical integration, option pricing | MEDIUM |
| ML Researcher | Backpropagation (chain rule), gradient computation | HIGH |

## Success Criteria
| Level | Criterion | Measure |
|-------|-----------|---------|
| MVP | Numerical derivatives (forward/backward/central difference) | < 1e-6 error on test functions |
| MVP | Numerical integration (trapezoidal, Simpson's) | < 1e-5 error on test integrals |
| Full | Partial derivatives (∂f/∂x, ∂f/∂y) | Multi-variable support |
| Full | Gradient vectors and Jacobian matrices | Full support for vector functions |

## Scope Boundaries
### In Scope (MUST)
- Numerical differentiation (forward, backward, central difference)
- Numerical integration (trapezoidal, Simpson's, adaptive quadrature)
- Partial derivatives with respect to specified variables
- Gradient computation for multi-variable functions
- Error estimation and convergence analysis

### In Scope (SHOULD)
- Symbolic differentiation rules (chain rule, product rule, quotient rule)
- Automatic differentiation (forward mode, reverse mode)
- Taylor series expansion
- Numerical stability analysis

### Out of Scope
- Computer algebra system (CAS) symbolic manipulation
- Differential equation solvers (separate library: simple_ode)
- Special functions (Bessel, Legendre - use simple_special)

### Deferred to Future
- Multi-dimensional adaptive integration
- Specialized algorithms for stiff problems

## Constraints
| Type | Constraint |
|------|-----------|
| Technical | SCOOP-compatible, void-safe (void_safety="all") |
| Resource | No external C libraries, pure Eiffel where possible |
| Accuracy | Target 1e-6 to 1e-9 relative error for standard functions |

## Assumptions to Validate
| ID | Assumption | Risk if False |
|----|-----------|--------------|
| A-1 | Numerical methods sufficient for most use cases | May need symbolic differentiation |
| A-2 | Floating-point arithmetic (REAL_64) adequate for physics | May need arbitrary precision |
| A-3 | Simple interface preferred over feature-rich API | Adoption of complex library instead |

## Research Questions
- What accuracy levels are required for physics simulations?
- Should we support symbolic differentiation?
- How important is performance vs. accuracy?
- What about special edge cases (discontinuities, singularities)?
