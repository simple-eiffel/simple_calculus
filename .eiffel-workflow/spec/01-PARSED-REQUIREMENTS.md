# 01-PARSED-REQUIREMENTS: simple_calculus

## Executive Summary
Extracted and organized requirements from research phase. All requirements are derived from SCOPE.md, REQUIREMENTS.md, DECISIONS.md, and INNOVATION.md. This document serves as the authoritative source for what must be implemented.

## Functional Requirements (FR)

### Differentiation Operations (Core)
| ID | Requirement | Source | Priority | Acceptance Criteria |
|----|-------------|--------|----------|---------------------|
| FR-001 | Forward difference numerical derivative | REQUIREMENTS | MUST | Error < 1e-5 for f(x)=x^2 at x=1.0 |
| FR-002 | Backward difference numerical derivative | REQUIREMENTS | MUST | Error < 1e-5 for f(x)=x^2 at x=1.0 |
| FR-003 | Central difference numerical derivative | REQUIREMENTS | MUST | Error < 1e-6 for f(x)=x^2 at x=1.0 |
| FR-004 | Adaptive step size for derivatives | DECISIONS (D-002) | MUST | h chosen automatically based on machine epsilon and function magnitude |
| FR-005 | User override for step size | DECISIONS (D-002) | SHOULD | Allow h parameter when adaptive is insufficient |

### Integration Operations (Core)
| ID | Requirement | Source | Priority | Acceptance Criteria |
|----|-------------|--------|----------|---------------------|
| FR-006 | Trapezoidal rule integration | REQUIREMENTS | MUST | Error < 1e-4 for ∫x^2 dx [0,1] |
| FR-007 | Simpson's rule integration | REQUIREMENTS | MUST | Error < 1e-6 for ∫x^2 dx [0,1] |
| FR-008 | Bounded interval requirement | RISKS (RISK-004) | MUST | Precondition: a < b, both finite |

### Multivariate Operations (Phase 1 or 2)
| ID | Requirement | Source | Priority | Acceptance Criteria |
|----|-------------|--------|----------|---------------------|
| FR-009 | Partial derivatives ∂f/∂x for f(x,y) | REQUIREMENTS | SHOULD | Multi-variable support with variable selection |
| FR-010 | Gradient vector ∇f for f(x,y,z,...) | REQUIREMENTS | SHOULD | All partial derivatives computed at once |
| FR-011 | Jacobian matrix for vector functions | REQUIREMENTS | SHOULD | m×n matrix of all first partial derivatives |

### Error Handling and Validation (Core)
| ID | Requirement | Source | Priority | Acceptance Criteria |
|----|-------------|--------|----------|---------------------|
| FR-012 | Error estimation for derivatives | REQUIREMENTS | SHOULD | Return estimated error bound with result |
| FR-013 | Error estimation for integrals | REQUIREMENTS | SHOULD | Adaptive quadrature with error control |
| FR-014 | Method comparison validation | INNOVATIONS (I-003) | SHOULD | Compare forward/backward/central; flag divergence |
| FR-015 | Smoothness precondition | RISKS (RISK-001) | MUST | Precondition warns about required smoothness |
| FR-016 | Continuity precondition for integration | RISKS (RISK-003) | MUST | Precondition requires continuous function on [a,b] |

## Non-Functional Requirements (NFR)

### Accuracy Requirements
| ID | Requirement | Category | Measure | Target |
|----|-------------|----------|---------|--------|
| NFR-001 | Numerical derivative accuracy | ACCURACY | Relative error | < 1e-6 on standard test functions |
| NFR-002 | Numerical integration accuracy | ACCURACY | Relative error | < 1e-5 on standard test functions |
| NFR-003 | Supported function scales | ACCURACY | Range of f(x) | From 1e-10 to 1e+10 (IEEE 754 range) |

### Safety and Type Requirements
| ID | Requirement | Category | Measure | Target |
|----|-------------|----------|---------|--------|
| NFR-004 | Void safety | SAFETY | Compiler setting | void_safety="all" |
| NFR-005 | SCOOP compatibility | CONCURRENCY | Design pattern | Separable/SCOOP-ready |
| NFR-006 | Type safety | SAFETY | Real type | REAL_64 (double precision) |

### Performance Requirements
| ID | Requirement | Category | Measure | Target |
|----|-------------|----------|---------|--------|
| NFR-007 | Single call throughput | PERFORMANCE | Calls/second | > 1,000,000 |
| NFR-008 | Step size caching | PERFORMANCE | Optimization | Cache h for repeated evaluations |

### Dependency and Ecosystem Requirements
| ID | Requirement | Category | Measure | Target |
|----|-------------|----------|---------|--------|
| NFR-009 | No external C dependencies | DEPENDENCY | External libs | 0 (pure Eiffel) |
| NFR-010 | simple_* ecosystem integration | ECOSYSTEM | Library preference | Use simple_math, simple_probability, simple_random |
| NFR-011 | Eiffel idiom compliance | INTEGRATION | Design pattern | Agent-based function passing (D-004) |

## Design by Contract Requirements (DBC)

### Preconditions Required
| ID | Feature | Required Precondition |
|----|---------|---------------------|
| DBC-001 | derivative_* | function_smooth: Function must be sufficiently smooth (at least C2 continuous) |
| DBC-002 | derivative_* | point_in_domain: x must be in valid computation domain |
| DBC-003 | integrate_* | function_continuous: Function must be continuous on [a,b] |
| DBC-004 | integrate_* | bounded_interval: a < b, both finite |
| DBC-005 | adapt_step_size | function_computable: Function must be evaluable at points near x |

### Postconditions Required
| ID | Feature | Required Postcondition |
|----|---------|---------------------|
| DBC-006 | derivative_* | result_valid: Returned derivative is finite (not NaN or Inf) |
| DBC-007 | derivative_* | error_bound_computed: Error estimate provided or documented as N/A |
| DBC-008 | integrate_* | result_valid: Returned integral is finite |
| DBC-009 | integrate_* | error_bounded: Integration error < user tolerance or documented |
| DBC-010 | adapt_step_size | step_size_positive: h > 0 |

### Invariants Required
| ID | Class | Required Invariant |
|----|-------|-------------------|
| DBC-011 | SIMPLE_CALCULUS | tolerance_positive: tolerance > 0 |
| DBC-012 | DERIVATIVE_RESULT | bounds_consistent: lower_bound <= estimate <= upper_bound |
| DBC-013 | INTEGRAL_RESULT | bounds_consistent: lower_bound <= estimate <= upper_bound |

## Constraint Requirements (C)

| ID | Constraint | Type | Immutable | Implication |
|----|-----------|------|-----------|------------|
| C-001 | REAL_64 only | TECHNICAL | YES | No REAL_32 support in Phase 1 |
| C-002 | SCOOP compatible | TECHNICAL | YES | No uncontrolled shared state |
| C-003 | Prefer simple_* | ECOSYSTEM | YES | Build on simple_math, not ISE stdlib |
| C-004 | Use simple_math | ECOSYSTEM | YES | Leverage simple_math.sine, cosine, exp, etc. |
| C-005 | No C libraries | TECHNICAL | YES | Pure Eiffel implementation |
| C-006 | Agent-based API | DESIGN | NO | Can evolve to support other patterns |

## Requirement Traceability Matrix

### FR to Class Features
| FR | Maps To Class | Feature | Method |
|----|---------------|---------|--------|
| FR-001/002/003 | DERIVATIVE_CALCULATOR | compute_forward_difference, compute_backward_difference, compute_central_difference | Eiffel feature calls |
| FR-004 | STEP_SIZE_CALCULATOR | adapt_step_size | Numerical algorithm |
| FR-006/007 | INTEGRAL_CALCULATOR | integrate_trapezoidal, integrate_simpson | Eiffel feature calls |
| FR-012/013 | DERIVATIVE_RESULT, INTEGRAL_RESULT | error_bound, convergence_status | Result classes |
| FR-009/010/011 | GRADIENT_CALCULATOR, JACOBIAN_CALCULATOR | partial_derivative, gradient_vector, jacobian_matrix | Multivariate extensions |

### NFR to Design Choices
| NFR | Implementation Strategy |
|-----|------------------------|
| NFR-001/002 | Use double precision REAL_64; validate on test suite |
| NFR-004 | Compile with void_safety="all" |
| NFR-005 | No shared mutable state; all features are side-effect free |
| NFR-009 | Pure Eiffel; no .c files or external libraries |
| NFR-010 | Depend on simple_math for trig/exp functions |

## Decisions Impacting Requirements

| Decision | Requirement Impact |
|----------|-------------------|
| D-001: Numerical primary | FR-001-007 focus on numerical; symbolic deferred |
| D-002: Adaptive step size | FR-004 drives STEP_SIZE_CALCULATOR design |
| D-003: Trap + Simpson | FR-006/007 are primary integration methods |
| D-004: Agent-based API | NFR-011 drives function parameter design |
| D-005: Skip MML | Simpler postconditions acceptable for scalars |

## Acceptance Criteria Summary

### MVP (Phase 1) Must Have
- [ ] FR-001, 002, 003 (forward/backward/central difference)
- [ ] FR-006, 007 (trapezoidal/Simpson integration)
- [ ] FR-004 (adaptive step size)
- [ ] FR-012, 013, 014 (error estimation and validation)
- [ ] FR-015, 016 (preconditions for smoothness/continuity)
- [ ] NFR-001 through NFR-009 (accuracy, safety, performance, purity)
- [ ] 100% void-safe compilation
- [ ] 50+ test cases with 100% pass rate

### Phase 2 Should Have
- [ ] FR-009, 010, 011 (multivariate operations)
- [ ] FR-005 (step size override)

### Phase 3+ Nice to Have
- [ ] Symbolic differentiation rules
- [ ] Jacobian matrix computation
- [ ] Integration with simple_ode
