# RECOMMENDATION: simple\_calculus

## Executive Summary

Build a pure Eiffel numerical calculus library providing differentiation and integration operations. Focus on reliability through Design by Contract (preconditions validate smoothness, postconditions provide error estimates) rather than trying to replicate GSL/NumPy feature-for-feature. Target primary use: physics simulations requiring derivatives and integrals.

## Recommendation

**Action:** BUILD
**Confidence:** HIGH

## Rationale

1. **Gap exists** - Eiffel ecosystem has no calculus library
2. **MVP viable** - Numerical methods are well-understood, implementable in pure Eiffel
3. **Use case validated** - Physics simulations (wave equation, electromagnetic fields) all need derivatives/integrals
4. **API design clear** - Agent-based function passing is idiomatic Eiffel
5. **Error control possible** - Contract-based design catches issues early

## Proposed Approach

### Phase 1 (MVP) - Core Differentiation \& Integration

**Release:** v1.0.0

**Features:**

* Numerical derivatives (forward, backward, central difference)
* Numerical integration (trapezoidal, Simpson's rule)
* Error estimation for both operations
* Partial derivatives for multi-variable functions
* Adaptive step size selection

**Deliverables:**

* SIMPLE\_CALCULUS facade class
* DERIVATIVE\_CALCULATOR, INTEGRAL\_CALCULATOR engines
* DERIVATIVE\_RESULT, INTEGRAL\_RESULT data classes
* Test suite with 50+ test cases
* GitHub Pages documentation

**Timeline:** 2-3 weeks

### Phase 2 (Full) - Advanced Methods

**Release:** v2.0.0 (future)

**Features:**

* Automatic differentiation (forward/reverse mode)
* Jacobian matrix computation
* Taylor series expansion
* Adaptive quadrature with error control
* C-optimized hotpath for performance

### Phase 3+ (Extensions)

**Release:** v3.0.0+ (future)

**Features:**

* Symbolic differentiation rules
* Integration with simple\_ode for differential equations
* Special functions (Bessel, Hermite, etc. - via simple\_special)

## Key Features

### 1\. Numerical Differentiation

```eiffel
create calculus.make
f\_prime := calculus.derivative (agent sin\_function, 0.5)
-- Returns derivative of sin(x) at x=0.5
```

### 2\. Numerical Integration

```eiffel
integral\_value := calculus.integrate (agent quadratic, 0.0, 1.0)
-- Computes ∫ x^2 dx from 0 to 1 ≈ 0.333...
```

### 3\. Partial Derivatives

```eiffel
df\_dx := calculus.partial\_derivative (agent f\_xy, 0, x, y)
-- ∂f/∂x at point (x, y)
```

### 4\. Error Estimation

```eiffel
result := calculus.derivative\_with\_error (agent f, x)
-- Returns (derivative\_value, error\_bound, convergence\_status)
```

## Success Criteria

* \[ ] Derivatives accurate to 1e-6 relative error on test suite
* \[ ] Integration accurate to 1e-5 relative error on test suite
* \[ ] 50+ unit tests, 100% pass rate
* \[ ] All methods void-safe and SCOOP-compatible
* \[ ] GitHub Pages documentation with examples
* \[ ] Compatible with simple\_math, simple\_probability, simple\_random

## Dependencies

|Library|Purpose|simple\_\* Preferred|
|-|-|-|
|simple\_math|Basic arithmetic, transcendental functions|YES|
|simple\_random|Random sampling for future Monte Carlo|YES|
|base|Fundamental types|(ISE allowed)|
|testing|EQA\_TEST\_SET for unit tests|(ISE allowed)|

## Gaps Identified (Future simple\_\* Libraries)

|Gap|Current Workaround|Proposed simple\_\*|
|-|-|-|
|Differential equations|Not supported|simple\_ode|
|Special functions|Custom implementations|simple\_special|
|Symbolic differentiation|Not in scope|simple\_symbolic|
|Matrix operations|Not supported|simple\_linalg|

## Next Steps

1. Run `/eiffel.research` for simple\_linalg (linear algebra)
2. Run `/eiffel.spec` to transform research into class design
3. Run `/eiffel.intent` to capture refined intent
4. Run full eiffel-\* workflow (`/eiffel.contracts` → `/eiffel.review` → ... → `/eiffel.ship`)

## Timeline

* **Research + Spec:** 1 week
* **Phase 1 Implementation:** 2-3 weeks
* **Testing + Hardening:** 1 week
* **Documentation + Release:** 1 week
* **Total MVP:** ~6 weeks
