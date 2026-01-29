# RISKS: simple_calculus

## Risk Register

| ID | Risk | Likelihood | Impact | Mitigation |
|----|------|------------|--------|-----------|
| RISK-001 | Numerical instability on ill-conditioned functions | MEDIUM | MEDIUM | Preconditions warn about smoothness; error estimates flag instability |
| RISK-002 | Performance overhead from adaptive step size | LOW | MEDIUM | Cache step size for repeated evaluations |
| RISK-003 | Users expect symbolic differentiation | MEDIUM | LOW | Clear documentation that we provide numerical methods |
| RISK-004 | Integration divergence on unbounded domains | MEDIUM | HIGH | Preconditions require bounded [a,b]; document limitations |
| RISK-005 | REAL_64 precision insufficient for some physics | LOW | MEDIUM | Target use cases validate accuracy; defer extended precision to Phase 2 |

## Technical Risks

### RISK-001: Numerical Instability on Ill-Conditioned Functions
**Description:** Some functions (e.g., nearly flat near extrema) cause numerical derivative to become unreliable
**Likelihood:** MEDIUM (users will accidentally use unsuitable functions)
**Impact:** MEDIUM (silent failure - wrong answer delivered)
**Indicators:**
- Derivative estimate changes significantly with tiny step size changes
- Multiple methods give wildly different results

**Mitigation:**
- Precondition: "function_sufficiently_smooth" documenting expectations
- Postcondition: Return error bound - user can check if result is trustworthy
- Compare multiple methods internally, flag divergence

**Contingency:**
- Throw exception if methods disagree beyond threshold
- Document which function classes are supported

### RISK-002: Performance on High-Order Derivatives
**Description:** Computing 3rd or 4th derivatives through finite differences amplifies numerical error
**Likelihood:** MEDIUM (advanced users may attempt this)
**Impact:** MEDIUM (unusable results)
**Indicators:** Error estimate explodes for higher orders

**Mitigation:**
- Focus Phase 1 on 1st derivatives (most common in physics)
- Defer higher derivatives to Phase 2 or recommend combination approach

**Contingency:**
- Document limitations clearly
- Suggest using automatic differentiation for higher orders

### RISK-003: Integration Accuracy on Discontinuous Functions
**Description:** Numerical integration assumes smoothness; discontinuities cause divergence
**Likelihood:** MEDIUM
**Impact:** HIGH (silently wrong answer)
**Indicators:** Simpson's rule error estimate doesn't decrease with finer grid

**Mitigation:**
- Precondition: "function_continuous_on_interval"
- Error estimation detects and flags suspicious results
- Document that users must split integrals at discontinuities

**Contingency:**
- Throw exception if convergence stalls
- Suggest breaking integral at known discontinuities

## Ecosystem Risks

### RISK-004: Conflict with future symbolic differentiation
**Description:** Later symbolic library might have incompatible API
**Likelihood:** LOW
**Impact:** MEDIUM (API redesign needed)

**Mitigation:**
- Design numerical API to be compatible with symbolic
- Use function agents that work with both
- Document extension points for symbolic later

## Resource Risks

### RISK-005: Insufficient Eiffel expertise for optimization
**Description:** Pure Eiffel numerical code might be slower than needed
**Likelihood:** LOW (modern compilers are good)
**Impact:** MEDIUM (poor adoption)

**Mitigation:**
- Phase 1: Correctness over performance
- Profile before optimizing
- If needed, use inline C for hottest paths (following simple_* pattern)

**Contingency:**
- Phase 2 can add C-optimized versions of core operations
