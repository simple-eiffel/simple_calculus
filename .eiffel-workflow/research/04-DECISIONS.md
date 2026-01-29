# DECISIONS: simple_calculus

## Decision Log

### D-001: Numerical vs Symbolic Differentiation
**Question:** Should we implement symbolic differentiation (knowing derivative rules) or numerical differentiation (approximating with finite differences)?

**Options:**
1. Numerical only: Simple, fast, works for any function
2. Symbolic only: Exact answers, but requires expression parsing
3. Both: Complex but most powerful

**Decision:** Numerical primary, symbolic rules deferred
**Rationale:** MVP ships faster, works with black-box functions (important for physics where function is computed, not parsed)
**Implications:** Accuracy limited by floating-point precision, but sufficient for physics
**Reversible:** YES - can add symbolic layer later

### D-002: Step Size Strategy
**Question:** How should we choose the optimal step size h for numerical differentiation?

**Options:**
1. Fixed h (e.g., 1e-8)
2. Adaptive h based on machine epsilon and f(x)
3. User-specified h

**Decision:** Adaptive h with user override
**Rationale:** Prevents under/overflow, works across different scales
**Implications:** Automatic step size computation adds slight overhead
**Reversible:** YES

### D-003: Integration Rule Selection
**Question:** What integration methods should be primary?

**Options:**
1. Just trapezoidal rule
2. Trapezoidal + Simpson's rule
3. Adaptive quadrature (Gaussian, etc.)

**Decision:** Trapezoidal and Simpson's primary, adaptive quadrature deferred
**Rationale:** Good balance of simplicity and accuracy for MVP
**Implications:** Some use cases may need more accuracy later
**Reversible:** YES

### D-004: Function Representation
**Question:** How should users pass functions to our calculus operations?

**Options:**
1. Function pointers
2. Agent objects (Eiffel closures)
3. Inherit from FUNCTION class

**Decision:** Agent objects (Eiffel's closure pattern)
**Rationale:** Most natural Eiffel pattern, enables lambda-like syntax
**Implications:** Users write: `agent math.compute_derivative (agent f, x_value)`
**Reversible:** YES

### D-005: MML Model Queries
**Question:** Should we use simple_mml for precise postconditions?

**Options:**
1. Skip MML (simple postconditions)
2. Full MML with frame conditions

**Decision:** Full MML for collection operations, skip for pure numerical
**Rationale:** Calculus works on scalars mostly; MML overkill
**Implications:** Lighter weight, easier to understand
**Reversible:** NO - design choice

