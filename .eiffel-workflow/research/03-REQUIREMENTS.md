# REQUIREMENTS: simple_calculus

## Functional Requirements
| ID | Requirement | Priority | Acceptance Criteria |
|----|-------------|----------|---------------------|
| FR-001 | Compute numerical derivative using forward difference | MUST | error < 1e-5 for polynomial f(x)=x^2 |
| FR-002 | Compute numerical derivative using backward difference | MUST | error < 1e-5 for polynomial f(x)=x^2 |
| FR-003 | Compute numerical derivative using central difference | MUST | error < 1e-6 for polynomial f(x)=x^2 |
| FR-004 | Compute numerical integral using trapezoidal rule | MUST | error < 1e-4 for ∫x^2 dx from 0 to 1 |
| FR-005 | Compute numerical integral using Simpson's rule | MUST | error < 1e-6 for ∫x^2 dx from 0 to 1 |
| FR-006 | Compute partial derivative ∂f/∂x for f(x,y) | SHOULD | multi-variable support with variable selection |
| FR-007 | Compute gradient vector ∇f for f(x,y,z) | SHOULD | all partial derivatives at once |
| FR-008 | Compute Jacobian matrix for vector function | SHOULD | matrix of all first partial derivatives |
| FR-009 | Estimate error in numerical differentiation | SHOULD | error bounds for all methods |
| FR-010 | Estimate error in numerical integration | SHOULD | adaptive quadrature with error control |

## Non-Functional Requirements
| ID | Requirement | Category | Measure | Target |
|----|-------------|----------|---------|--------|
| NFR-001 | Accuracy of numerical derivatives | ACCURACY | Relative error | < 1e-6 on test suite |
| NFR-002 | Accuracy of numerical integration | ACCURACY | Relative error | < 1e-5 on test suite |
| NFR-003 | Void safety | SAFETY | void_safety setting | "all" |
| NFR-004 | SCOOP compatibility | CONCURRENCY | concurrency support | "scoop" |
| NFR-005 | Performance | PERFORMANCE | Calls per second | > 1,000,000 |
| NFR-006 | No external dependencies | DEPENDENCY | C libraries needed | 0 |

## Constraints
| ID | Constraint | Type | Immutable? |
|----|-----------|------|------------|
| C-001 | Must use REAL_64 (double precision) | TECHNICAL | YES |
| C-002 | Must be SCOOP-compatible | TECHNICAL | YES |
| C-003 | Must prefer simple_* over ISE stdlib | ECOSYSTEM | YES |
| C-004 | Must use simple_math for basic operations | ECOSYSTEM | YES |
| C-005 | No external C library dependencies | TECHNICAL | YES |
