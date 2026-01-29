# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-01-29

### Added

- **Derivative Computation**
  - Forward difference formula: `f'(x) ≈ (f(x+h) - f(x)) / h`
  - Backward difference formula: `f'(x) ≈ (f(x) - f(x-h)) / h`
  - Central difference formula: `f'(x) ≈ (f(x+h) - f(x-h)) / (2h)` (most accurate)
  - Adaptive step size calculation based on variable magnitude
  - Three-method comparison with convergence analysis

- **Integral Computation**
  - Trapezoid rule for basic integration
  - Simpson's rule for improved accuracy
  - Adaptive Richardson extrapolation for automatic error control
  - Configurable maximum iterations and convergence tolerance

- **Partial Derivatives & Gradients**
  - Partial derivative computation with respect to individual variables
  - Full gradient computation (all partials at once)
  - Support for multi-dimensional functions via ARRAY [REAL_64]
  - Adaptive step size for each dimension

- **Convergence Analysis**
  - Automatic convergence status detection (CONVERGED, WARNING, FAILED)
  - Error bound estimation for derivatives and integrals
  - Three-way comparison of numerical methods for reliability

- **Three-Tier API**
  - **Tier 1 (Simple)**: `derivative()`, `integrate()`, `partial_derivative()`, `gradient()`
  - **Tier 2 (Advanced)**: `derivative_with_options()`, `integrate_with_options()` with method selection
  - **Tier 3 (Expert)**: Direct engine access via `create_derivative_calculator()`, `create_integral_calculator()`

- **Comprehensive Test Suite**
  - 15 baseline tests covering all Tier 1-3 APIs
  - 8 adversarial/stress tests including:
    - Very small x values (1e-15)
    - Very large x values (1e15)
    - Tiny integration intervals (1e-10)
    - Large integration intervals (1e10)
    - Discontinuous functions
    - Near-zero slopes
    - 100 consecutive derivative computations (stress test)
    - 50 consecutive integral computations (stress test)
  - Total: 23 tests, 100% pass rate

### Technical Details

- **DBC**: 51 contract clauses (require/ensure/invariant)
- **Classes**: 9 (SIMPLE_CALCULUS, DERIVATIVE_CALCULATOR, INTEGRAL_CALCULATOR, CONVERGENCE_ANALYZER, etc.)
- **Dependencies**: simple_math (for sqrt, transcendental functions)
- **Void Safety**: Full void safety enabled
- **SCOOP**: Concurrency support enabled (immutable results)

### Documentation

- Full API documentation with examples
- User guide with Tier 1-3 usage patterns
- Architecture documentation explaining three-method comparison strategy
- Mathematical background for each algorithm

### Quality Assurance

- Design by Contract throughout (all public features have contracts)
- Convergence analysis prevents incorrect results
- Error bounds provide confidence in numerical accuracy
- Comprehensive adversarial testing ensures robustness

---

## Future Work (Post v1.0.0)

- Integration with simple_ode for ODE solver support
- Integration with simple_optimization for gradient-based algorithms
- Support for symbolic differentiation (future analysis layer)
- GPU acceleration for high-dimensional gradients (future)
