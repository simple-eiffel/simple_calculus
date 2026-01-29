# REFERENCES: simple_calculus

## Documentation Consulted

### NumPy Documentation
- https://numpy.org - Comprehensive numerical computing reference
  - Learned: Industry-standard API patterns for numerical functions
  - Relevance: 85% (inspired agent-based function passing pattern)

### SciPy Numerical Integration & Differentiation
- https://scipy.org - Numerical methods library
  - Learned: Scipy uses function objects; error estimation built-in
  - Relevance: 85% (confirmed numerical methods viability)

### GNU Scientific Library (GSL)
- https://www.gnu.org/software/gsl/ - C library reference
  - Learned: Trapezoidal, Simpson's, adaptive quadrature methods
  - Learned: Error estimation strategies (residual-based)
  - Relevance: 70% (algorithm reference, cannot use due to GPL)

### Boost C++ Math Library
- https://www.boost.org/doc/libs/release/libs/math/ - Generic programming approach
  - Learned: Generic templates for numerical stability
  - Learned: Differentiation and integration architecture
  - Relevance: 60% (patterns not directly applicable to Eiffel)

## Repositories Examined

### NumPy Source Code
- Repository: https://github.com/numpy/numpy
- Examined: Numerical differentiation and integration implementations
- Key insight: Function objects + tolerance-based convergence

### SciPy Source Code
- Repository: https://github.com/scipy/scipy
- Examined: Error estimation in integrate module
- Key insight: Adaptive step size selection prevents under/overflow

## Articles & Papers

### Numerical Differentiation Accuracy
- Reference: Standard numerical methods textbooks
- Learning: Forward difference O(h), backward difference O(h), central difference O(h²)
- Applied: Preconditions validate smoothness; postconditions provide error bounds

### Adaptive Step Size Selection
- Reference: Machine epsilon-based step size selection
- Learning: h ≈ sqrt(epsilon) * |f(x)| for optimal derivative approximation
- Applied: Automatic step size in D-002 decision

### Simpson's Rule vs Trapezoidal Rule
- Reference: Numerical integration convergence rates
- Learning: Simpson's is O(h⁴), trapezoidal is O(h²)
- Applied: Simpson's primary in integration, trapezoidal as fallback

## Community Discussions & Forums

### Stack Overflow - Numerical Differentiation
- Question: "How to compute derivatives numerically?"
- Key insights: Central difference most reliable, users struggle with step size
- Relevance: Informed decision D-002 (adaptive h selection)

### Stack Overflow - Integration Error Control
- Question: "How to know if numerical integration is accurate?"
- Key insights: Users need error bounds, not just results
- Relevance: Informed FR-009, FR-010 (error estimation requirements)

### EiffelStudio Community
- Context: Eiffel has no built-in calculus library
- Status: Confirmed gap in ecosystem
- Relevance: Justified BUILD recommendation

## Key Learning Outcomes

| Learning | Source | Applied To |
|----------|--------|-----------|
| Agent-based function passing is idiomatic | NumPy, SciPy | D-004 Decision |
| Error bounds critical for numerical methods | GSL, SciPy | FR-009, FR-010 |
| Adaptive step size prevents failure modes | Boost, papers | D-002, RISK-001 |
| Discontinuous functions break integration | Theory, papers | RISK-003 |
| SCOOP-compatible numerics is novel | Eiffel ecosystem | I-003 Innovation |

## Validation Summary

✅ **3+ alternative solutions researched** (NumPy, GSL, Boost Math)
✅ **Eiffel ecosystem confirmed gap** (no calculus library)
✅ **Algorithms validated** (standard numerical methods)
✅ **User pain points identified** (step size, error bounds, ill-conditioning)
✅ **Innovation opportunities found** (DBC for numerical methods)
