# 02-DOMAIN-MODEL: simple_calculus

## Executive Summary
This document identifies the core domain concepts for simple_calculus library using OOSC2 principles. Each concept is mapped to proposed Eiffel classes with their key responsibilities and relationships.

## Core Domain Concepts

### 1. FUNCTION
**What it is:** A mathematical function that accepts real inputs and produces real outputs.

**In simple_calculus context:**
- Represented as an Eiffel agent (D-004: Agent-based API)
- Not a class but a behavioral contract: `agent (x: REAL_64): REAL_64`
- Encapsulates black-box computability (crucial for physics simulations)

**Responsibilities:**
- Accept real input parameters
- Return real output values
- May represent physical phenomena (not parsed expressions)

**Relationships:**
- Input to DERIVATIVE_CALCULATOR
- Input to INTEGRAL_CALCULATOR
- Input to GRADIENT_CALCULATOR (for multivariate)

**Design Decision Rationale:**
- Agents allow lambda-like closures: `agent math.sin_wrapper (agent f, ...)`
- Supports black-box functions (physics engines compute f(x), don't describe it)
- More idiomatic Eiffel than explicit FUNCTION interface

**Example Usage:**
```eiffel
my_function: FUNCTION [REAL_64, REAL_64]
create {FUNCTION [REAL_64, REAL_64]} my_function.make
    (agent (x: REAL_64): REAL_64 do Result := x * x end)
```

---

### 2. DERIVATIVE
**What it is:** The rate of change of a function at a point.

**Mathematical Definition:**
```
f'(x) = lim(h→0) [f(x+h) - f(x)] / h
```

**In simple_calculus context:**
- Computed numerically using finite differences (D-001: Numerical primary)
- Multiple methods: forward, backward, central difference (FR-001, 002, 003)
- Includes error bounds (I-003: Multiple method comparison)

**Responsibilities:**
- Estimate derivative value at point x
- Validate smoothness assumptions (I-001: DBC for numerical methods)
- Provide error bound estimate (FR-012)

**Key Properties:**
- `derivative_value: REAL_64` - Estimated f'(x)
- `error_bound: REAL_64` - Upper bound on |estimated - actual|
- `convergence_status: DERIVATIVE_STATUS` - Indicates reliability

**Relationships:**
- Computed by DERIVATIVE_CALCULATOR
- Returned as DERIVATIVE_RESULT
- Forms basis for GRADIENT (multivariate case)

---

### 3. STEP_SIZE (h)
**What it is:** The finite difference interval used in numerical differentiation.

**Mathematical Role:**
```
Forward difference: f'(x) ≈ [f(x+h) - f(x)] / h
Central difference: f'(x) ≈ [f(x+h) - f(x-h)] / (2h)
```

**In simple_calculus context:**
- Adaptive selection based on machine epsilon (D-002: Adaptive h)
- Formula: `h = sqrt(epsilon) * max(|x|, 1.0)`
- User override allowed (FR-005)

**Responsibilities:**
- Balance truncation error (too large h) and rounding error (too small h)
- Prevent underflow/overflow automatically
- Scale with function magnitude

**Key Properties:**
- `initial_h: REAL_64` - Starting guess
- `optimal_h: REAL_64` - Machine-adaptive selection
- `user_h: REAL_64` - Optional user override

**Relationships:**
- Managed by STEP_SIZE_CALCULATOR
- Consumed by DERIVATIVE_CALCULATOR
- Cached for repeated evaluations (NFR-008)

**Risk Mitigation:**
- RISK-001: Smoothness assumption detected when methods disagree
- RISK-002: Adaptive h prevents over/underflow

---

### 4. INTEGRAL
**What it is:** The accumulated sum (area under curve) for a function over an interval.

**Mathematical Definition:**
```
∫[a,b] f(x) dx ≈ sum of rectangles/trapezoids/curves
```

**In simple_calculus context:**
- Computed numerically using quadrature rules (D-003: Trap + Simpson)
- Two primary methods: trapezoidal rule, Simpson's rule (FR-006, 007)
- Methods provide self-validation through comparison

**Responsibilities:**
- Approximate definite integral value
- Ensure domain [a,b] is bounded and finite (RISK-004)
- Detect discontinuities and flag unreliable results

**Key Properties:**
- `integral_value: REAL_64` - Estimated ∫[a,b] f(x) dx
- `error_bound: REAL_64` - Upper bound on error
- `convergence_status: INTEGRAL_STATUS` - Convergence indicator

**Relationships:**
- Computed by INTEGRAL_CALCULATOR
- Returned as INTEGRAL_RESULT
- Foundation for Monte Carlo integration (future I-004)

**Preconditions (Risk Mitigation):**
- Interval must be bounded: `a < b and a.is_finite and b.is_finite`
- Function must be continuous on [a,b]
- No unbounded domains (RISK-004 mitigation)

---

### 5. ERROR_BOUND
**What it is:** Upper limit on numerical error in derivative or integral computation.

**In simple_calculus context:**
- Postcondition for every numerical operation (I-001: DBC for numerical methods)
- Allows users to decide if result is trustworthy
- Based on method-specific error theory

**Responsibilities:**
- Provide pessimistic estimate (always >= true error)
- React to:
  - Function smoothness violations
  - Rounding errors from small h
  - Integration grid coarseness
  - Discontinuities or singularities

**Key Properties:**
- `absolute_error: REAL_64` - Error in result units
- `relative_error: REAL_64` - Error as fraction of result
- `confidence_level: REAL_64` - How certain the bound is

**Relationships:**
- Included in DERIVATIVE_RESULT
- Included in INTEGRAL_RESULT
- Drives decision: "is result usable?"

**DBC Integration:**
```eiffel
ensure
    result_valid: not (result.derivative_value.is_nan or result.derivative_value.is_infinite)
    error_reasonable: result.error_bound >= 0.0
    accuracy_achieved: result.error_bound < tolerance
```

---

### 6. CONVERGENCE_STATUS
**What it is:** Indicator of numerical stability and reliability for the computed result.

**Possible Values:**
- `CONVERGED` - Methods agree, error bound small, result trustworthy
- `CONVERGED_WITH_WARNING` - Result acceptable but near boundary of reliability
- `DIVERGED` - Methods disagree strongly, discontinuity detected, result untrustworthy
- `FAILED` - Computation aborted due to precondition violation

**In simple_calculus context:**
- Generated by method comparison (I-003: Multiple method comparison)
- Signals user that error estimation may be unreliable

**Responsibilities:**
- Detect numerical instability
- Flag smoothness violations (RISK-001)
- Warn of method divergence

**Example Logic:**
```
Compare forward and central difference results:
if |forward - central| > tolerance:
    status := CONVERGED_WITH_WARNING
if |forward - central| > 10 * tolerance:
    status := DIVERGED
```

**Relationships:**
- Computed by DERIVATIVE_CALCULATOR
- Included in DERIVATIVE_RESULT
- Included in INTEGRAL_RESULT
- User examines before trusting result

---

## Domain Concept Hierarchy

```
NUMERICAL_OPERATION (abstract)
├── DERIVATIVE
│   ├── derivative_value: REAL_64
│   ├── error_bound: REAL_64
│   └── convergence_status: CONVERGENCE_STATUS
│
└── INTEGRAL
    ├── integral_value: REAL_64
    ├── error_bound: REAL_64
    └── convergence_status: CONVERGENCE_STATUS

FUNCTION (agent-based, not a class)
├── Input: REAL_64 (possibly vector for multivariate)
└── Output: REAL_64

STEP_SIZE
├── initial_estimate: REAL_64
├── adaptive_h: REAL_64
└── user_override: REAL_64

ERROR_BOUND
├── absolute_error: REAL_64
├── relative_error: REAL_64
└── confidence: REAL_64

CONVERGENCE_STATUS
├── CONVERGED
├── CONVERGED_WITH_WARNING
├── DIVERGED
└── FAILED
```

---

## Domain Relationships

### Call Dependencies
```
User Code
    ↓
SIMPLE_CALCULUS (Facade)
    ├→ DERIVATIVE_CALCULATOR
    │   ├→ STEP_SIZE_CALCULATOR (for h selection)
    │   └→ CONVERGENCE_VALIDATOR (for method comparison)
    │
    └→ INTEGRAL_CALCULATOR
        ├→ STEP_SIZE_CALCULATOR (for grid refinement)
        └→ CONVERGENCE_VALIDATOR (for error control)
```

### Data Flow
```
Agent Function ──┐
                 ├→ DERIVATIVE_CALCULATOR ──→ DERIVATIVE_RESULT
Point x ─────────┤    (uses STEP_SIZE_CALCULATOR)
                 └→ CONVERGENCE_VALIDATOR
```

---

## Key Domain Invariants (OOSC2 Principle 1: Explicit Data Invariant)

1. **Error bound monotonicity:** As method improves (finer grid, more iterations), error_bound should decrease or stay constant.

2. **Result consistency:** Multiple invocations with same inputs must return results within error_bound of each other.

3. **Convergence monotonicity:** If convergence_status is DIVERGED, user should not trust result; CONVERGED guarantees error_bound < tolerance.

4. **Step size positivity:** All step sizes (h) must be positive: h > 0.

5. **Tolerance consistency:** All tolerances used must be positive and consistent: tolerance > 0 across library.

---

## Multivariate Extensions (Phase 2)

### PARTIAL_DERIVATIVE
- Extension of DERIVATIVE to single variable in multivariate function
- Computed using chain rule numerically: ∂f/∂x_i ≈ [f(..., x_i+h, ...) - f(..., x_i-h, ...)] / (2h)
- Returns DERIVATIVE_RESULT with same structure

### GRADIENT
- Vector of all partial derivatives ∇f = [∂f/∂x, ∂f/∂y, ∂f/∂z, ...]
- Dimensions: n-dimensional input → n-component gradient vector
- Each component is a DERIVATIVE with its own error_bound

### JACOBIAN
- Matrix of all partial derivatives for vector-valued functions
- Input: R^n → R^m function
- Output: m×n matrix J where J_ij = ∂f_i/∂x_j
- Each element is a DERIVATIVE

---

## Design Principles Applied

### OOSC2 Principle 1: Explicit Data Invariant
Each domain concept has explicit invariants:
- ERROR_BOUND: `absolute_error >= 0`
- DERIVATIVE: `error_bound >= |forward - central|`
- STEP_SIZE: `h > 0`

### OOSC2 Principle 2: Design by Contract
Each numerical operation has:
- **Precondition:** Validates input assumptions (smoothness, continuity, boundedness)
- **Postcondition:** Guarantees output correctness and error bounds
- **Invariant:** Maintains consistency across repeated operations

### OOSC2 Principle 3: Abstraction
Domain concepts abstracted away from implementation:
- DERIVATIVE hides forward/backward/central difference choice
- INTEGRAL hides trapezoidal/Simpson rule choice
- CONVERGENCE_STATUS abstracts method agreement detection

### OOSC2 Principle 4: Reusability
All domain concepts designed to extend:
- DERIVATIVE → PARTIAL_DERIVATIVE (multivariate)
- INTEGRAL → MULTIPLE_INTEGRAL (multidimensional)
- Agent-based functions work with any numeric type in future

---

## Mapping to Proposed Classes

| Domain Concept | Class Name | Type | Responsibility |
|---|---|---|---|
| FUNCTION | (Agent only) | - | Represent callable functions |
| DERIVATIVE | DERIVATIVE_RESULT | Data class | Hold derivative, error, status |
| INTEGRAL | INTEGRAL_RESULT | Data class | Hold integral, error, status |
| STEP_SIZE | (Within STEP_SIZE_CALCULATOR) | Algorithm | Compute optimal h |
| ERROR_BOUND | (Within result classes) | Attribute | Track error information |
| CONVERGENCE_STATUS | CONVERGENCE_STATUS enum | Enumeration | Signal computation reliability |
| Computation Logic | DERIVATIVE_CALCULATOR | Engine | Implement numerical differentiation |
| Computation Logic | INTEGRAL_CALCULATOR | Engine | Implement numerical integration |
| High-level API | SIMPLE_CALCULUS | Facade | User-facing interface |

