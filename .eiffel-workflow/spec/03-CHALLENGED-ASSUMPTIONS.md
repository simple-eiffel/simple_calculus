# 03-CHALLENGED-ASSUMPTIONS: simple_calculus

## Executive Summary
This document challenges assumptions from the research phase using OOSC2 critical thinking. By questioning each assumption, we ensure design robustness and identify hidden requirements.

---

## Research Assumptions Under Challenge

### A-1: "Numerical methods sufficient for most use cases"

**Original Assumption (from SCOPE.md):**
> Scientists and engineers will accept numerical derivatives and integrals without symbolic computation.

**Challenge Questions:**
1. **What if the application domain is symbolic?** (e.g., computer algebra, symbolic physics)
2. **What if accuracy requirements exceed floating-point precision?** (e.g., finance, cryptography)
3. **What if users need derivative expressions, not just values?**

**Analysis:**
- Numerical methods give point values, not expressions
- Symbolic methods would return f'(x) = 2x for f(x) = x^2
- Research validated physics/optimization primary use; these DO work numerically
- But financial and symbolic domains will fail silently

**Mitigation Strategy:**
1. **Document scope boundary clearly** - "Phase 1: Numerical only"
2. **Add explicit precondition** - "function_suitable_for_numerical_differentiation"
3. **Error estimation** - Let error_bound reveal when result untrustworthy
4. **Plan Phase 2** - Design API extensible to symbolic layer (D-001 reversible)

**Updated Requirement:**
```
NFR-012: Numerical limitations documented
  - Postcondition must include estimated error
  - Users can detect unsuitable functions by large error_bound
  - Documentation must state: "This library is for numerical methods only"
```

**OOSC2 Application:** Explicit statement of scope boundary (Principle 2: DBC)

---

### A-2: "Floating-point arithmetic (REAL_64) adequate for physics"

**Original Assumption (from SCOPE.md):**
> Double precision (IEEE 754) sufficient for physics simulations.

**Challenge Questions:**
1. **What defines "physics simulations"?** Different domains have wildly different accuracy needs
2. **What about ill-conditioned functions?** (e.g., derivatives of nearly-flat curves)
3. **What if numerical derivatives degrade rapidly?** (RISK-001: Numerical instability)
4. **What if cascading computations compound rounding errors?**

**Examples That Break This:**
- Atmospheric modeling: 64-bit can drift over weeks of simulation
- Quantum mechanics: Interference effects require careful precision management
- Stiff differential equations: Numerical errors amplify

**Analysis:**
- Standard physics (mechanics, electromagnetics): REAL_64 works fine
- Advanced physics (many-body, quantum): May need extended precision
- Research validated "target 1e-6 to 1e-9 relative error" - achievable with REAL_64
- BUT: This is application-dependent, not universal

**Mitigation Strategy:**
1. **Precondition: Document function suitability** - Add `function_smooth` precondition
2. **Postcondition: Always return error_bound** - User can detect insufficient precision
3. **Phase 2 extensibility** - Design to support extended precision later
4. **Test with ill-conditioned functions** - Reveal limitations early

**Updated Requirement:**
```
NFR-013: Precision awareness
  - Error estimation must detect when REAL_64 insufficient
  - Documentation: "For functions with dynamic range > 1e6, results unreliable"
  - Convergence status should flag high error estimates
```

**OOSC2 Application:** Explicit postconditions reveal limitations (Principle 2: DBC)

---

### A-3: "Simple interface preferred over feature-rich API"

**Original Assumption (from SCOPE.md):**
> Users want SIMPLE_CALCULUS.derivative(f, x) not GSL_style_with_50_parameters

**Challenge Questions:**
1. **What if advanced users need fine-grained control?** (e.g., algorithm selection, error tolerance, step size)
2. **What if simple API masks important options?** (violates OOSC2 openness)
3. **How do we extend simple API without breaking existing code?**
4. **Is "simple" at odds with "scientifically correct"?**

**Analysis:**
- Research shows NumPy/SciPy have both: `diff()` (simple) and `gradient()` with options
- "Simple by default, powerful by option" is proven pattern
- But overcomplexity leads to misuse and errors
- D-004 (agent-based API) already adds complexity; need careful ergonomics

**Examples:**
- Simple: `derivative(agent f, x)`
- Powerful: `derivative_with_options(agent f, x, algorithm=CENTRAL, step_size=1e-8, tolerance=1e-9)`

**Mitigation Strategy:**
1. **Tiered API design:**
   - **Tier 1 (Simple):** `derivative(f, x)` - Auto h, returns result
   - **Tier 2 (Control):** `derivative_with_options(f, x, options)` - User h, tolerance, method
   - **Tier 3 (Engine):** `DERIVATIVE_CALCULATOR` - Direct engine access
2. **Backward compatibility** - Tier 1 remains stable; Tier 2/3 can evolve
3. **Documentation** - Make Tier 1 the primary documented interface
4. **Example code** - Show Tier 1 exclusively until advanced use needed

**Updated Requirement:**
```
NR-014: Tiered API design
  - Tier 1 (simple): Must work with no options beyond function and point
  - Tier 2 (control): Optional parameter class for advanced users
  - Tier 3 (engine): Direct class instantiation for library implementers
  - Design must allow extension without modifying Tier 1
```

**OOSC2 Application:** Openness to extension (Principle 4: Reusability)

---

### D-001: "Numerical primary, symbolic deferred"

**Original Decision (from DECISIONS.md):**
> MVP ships faster with numerical only, symbolic added in Phase 2+

**Challenge Questions:**
1. **What if symbolic derivatives would actually be easier?** (chain rule rules, not finite differences)
2. **What if symbolic enables symbolic integration?** (impossible with numerical alone)
3. **What if users expect derivatives like mathematics teaches?**
4. **Is deferring symbolic delaying critical features?**

**Analysis:**
- Symbolic differentiation: Algorithm (apply rules) vs numerics (compute values)
- Symbolic IS conceptually simpler, but requires expression parsing
- Research shows physics/optimization DON'T need expressions; just values
- True gap: no symbolic library in Eiffel ecosystem
- Deferring symbolic is correct for MVP, but API must anticipate it

**Mitigation Strategy:**
1. **API compatibility** - Functions (agents) work same way in numerical or symbolic layer
2. **Don't expose method choice** - Hide whether derivative computed numerically or symbolically
3. **Error estimates remain** - Even symbolic benefits from error bounds
4. **Document scope** - "Phase 1: Numerical methods for real-valued functions"

**Challenge Verdict:** ACCEPTED - Deferring symbolic is correct

---

### D-002: "Adaptive h based on machine epsilon"

**Original Decision (from DECISIONS.md):**
> h = sqrt(epsilon) * max(|x|, 1.0)

**Challenge Questions:**
1. **Is sqrt(epsilon) optimal for all functions?** Theorem says yes for smooth f
2. **What about non-smooth functions?** Where is precondition validated?
3. **What if user function is "thin" (derivative changes very slowly)?** h might be too large
4. **Is machine epsilon alone sufficient?** Or need function properties?

**Analysis:**
- Classic formula: h = sqrt(ε) minimizes truncation + rounding error
- Assumes f is sufficiently smooth (C3 continuous for central difference)
- If f not smooth: Error estimate explodes, convergence_status = DIVERGED
- Precondition must state smoothness requirement
- User override (FR-005) allows adjustment if auto-selection fails

**Mitigation Strategy:**
1. **Precondition: function_sufficiently_smooth** - Explicit: at least C2 continuous
2. **Postcondition: error_estimate_provided** - Return error_bound so user can check
3. **Adaptive refinement option** - If error large, suggest halving h and retrying
4. **Test coverage** - Test on ill-conditioned functions to validate error estimates

**Challenge Verdict:** ACCEPTED - Formula is correct, but precondition must enforce smoothness

---

### D-003: "Trapezoidal + Simpson primary; adaptive quadrature deferred"

**Original Decision (from DECISIONS.md):**
> These two methods sufficient for most integrals; fancy adaptive methods phase 2+

**Challenge Questions:**
1. **What about discontinuous integrands?** Where both methods fail
2. **What about near-singularities?** Oscillatory integrands?
3. **Is Simpson's rule actually better than Gaussian quadrature?**
4. **What if users integrate pathological functions?**

**Analysis:**
- Trapezoidal rule: Assumes f is smooth; error ~ O(h^2)
- Simpson's rule: Better accuracy for smooth f; error ~ O(h^4)
- Both FAIL on discontinuous, oscillatory, or singular integrands
- Gaussian quadrature IS more sophisticated but harder to implement
- Research says "good balance of simplicity and accuracy" - correct for MVP
- RISK-003 (discontinuous functions) exists but precondition mitigates: "function_continuous_on_interval"

**Mitigation Strategy:**
1. **Precondition: function_continuous_on_interval** - Explicit requirement in DBC
2. **Postcondition: convergence_status flags divergence** - If methods disagree greatly
3. **Error estimate** - Simpson error ~ (b-a)^5 / 180 / n^4 * f''''(ξ) - bounds must reflect this
4. **Documentation** - "If integration diverges, function may be discontinuous; split interval manually"
5. **Phase 2: Adaptive quadrature** - Can handle discontinuities by auto-detecting and recursing

**Challenge Verdict:** ACCEPTED - Methods sufficient for smooth functions; preconditions enforce assumption

---

### D-004: "Agent-based function passing"

**Original Decision (from DECISIONS.md):**
> Users write: `calculus.derivative(agent sin_function, x_value)`

**Challenge Questions:**
1. **Are agents idiomatic in user code?** Or confusing to non-Eiffel programmers?
2. **What about partial application?** (agent (x: REAL_64): REAL_64 do ... end)
3. **Can agents be passed to simple_* libraries?** (ecosystem consistency)
4. **What about performance of agent calls?**

**Analysis:**
- Eiffel agents are closures; only idiomatic function passing mechanism
- NumPy uses functions/lambdas; Boost uses templates
- Agents in Eiffel are powerful but have learning curve
- Performance: Agent call ≈ virtual function call; negligible overhead
- Research shows agents natural for black-box function evaluation

**Mitigation Strategy:**
1. **Documentation and examples** - Show agent syntax explicitly
2. **Provide wrapper functions** - For common functions (sin, cos, exp) via simple_math integration
3. **Alias syntax** - Consider helper creation methods (future)
4. **Ecosystem consistency** - Ensure simple_* libraries all accept agents consistently

**Challenge Verdict:** ACCEPTED - Agents are correct choice; mitigate learning curve with docs

---

### D-005: "Skip MML; simple postconditions acceptable"

**Original Decision (from DECISIONS.md):**
> Calculus works on scalars mostly; MML (specification notation) overkill

**Challenge Questions:**
1. **Is simplifying postconditions actually safer?** Or does it hide contracts?
2. **What if future extensions need MML?** (multivariate, matrices)
3. **Is this principle extensible?** Or does it create design debt?

**Analysis:**
- MML (Mathematical Modeling Language) provides formal notation for frame conditions
- For scalar operations (DERIVATIVE, INTEGRAL): Not much benefit
- For collections/arrays: MML becomes necessary (see simple_array, simple_list)
- Decision is correct for Phase 1; Phase 2 may need MML for matrices

**Mitigation Strategy:**
1. **Document design choice** - "Phase 1 uses informal postconditions"
2. **Prepare for MML** - Structure classes to accommodate formal specs later
3. **Test coverage compensates** - Comprehensive tests validate what specs don't formally state
4. **Evolutionary design** - Phase 2 can introduce MML gradually for Jacobian/Gradient

**Challenge Verdict:** ACCEPTED - Correct for MVP; documented as Phase 1 limitation

---

## Summary of Challenge Resolutions

| Assumption | Challenged? | Outcome | Impact on Design |
|-----------|-----------|---------|------------------|
| A-1: Numerical sufficient | YES | Revised: Add error estimation and preconditions | Postcondition must return error_bound |
| A-2: REAL_64 adequate | YES | Revised: Adaptive error reporting | Postcondition reveals precision limits |
| A-3: Simple > feature-rich | YES | Revised: Tiered API design | Tier 1 simple, Tier 2/3 for control |
| D-001: Numerical primary | YES | Accepted: API anticipates symbolic | Design facades for future extension |
| D-002: Adaptive h | YES | Accepted: Enforce smoothness precondition | Add `function_sufficiently_smooth` |
| D-003: Trap + Simpson | YES | Accepted: Add continuity precondition | Add `function_continuous_on_interval` |
| D-004: Agent-based API | YES | Accepted: Mitigate learning curve | Comprehensive docs + wrapper helpers |
| D-005: Skip MML | YES | Accepted: Prepare for evolution | Structure classes for MML-ready Phase 2 |

---

## Updated Requirements from Challenge Process

### New Preconditions Identified
1. `function_sufficiently_smooth` - At least C2 continuous (for derivatives)
2. `function_continuous_on_interval` - No discontinuities in [a,b] (for integration)
3. `point_in_domain` - x within valid computation range
4. `function_suitable_for_numerical` - Not pathological (oscillatory, singular)

### New Postconditions Identified
1. `error_bound_provided` - Always return convergence_status and error estimate
2. `numerical_limitations_documented` - User aware this is numerical, not symbolic
3. `extension_points_present` - API designed to add symbolic, extended precision later

### New Constraints Identified
1. `C-007: Tier 1 stability` - Simple API never breaks; only add Tier 2/3
2. `C-008: Precondition enforcement` - Validate smoothness, continuity at call time
3. `C-009: Error transparency` - Every result includes confidence indicator

---

## Design Decisions Confirmed

All research decisions are CONFIRMED, with added preconditions:
- D-001: Numerical primary → Add precondition `function_suitable_for_numerical`
- D-002: Adaptive h → Add precondition `function_sufficiently_smooth`
- D-003: Trap + Simpson → Add precondition `function_continuous_on_interval`
- D-004: Agent-based API → Add documentation and wrapper helpers
- D-005: Skip MML → Prepare architecture for Phase 2 MML migration

