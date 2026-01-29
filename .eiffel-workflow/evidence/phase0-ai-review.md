# Phase 0: AI Review Response - simple_calculus

**Reviewer:** Claude Code
**Date:** 2026-01-29 14:30 UTC
**Status:** REVIEW COMPLETE

---

## Probing Questions & Clarifications

### Question 1: Adaptive Step Size Scaling

**Quote:** "Adaptive step size works across scales (tiny x=1e-10 to large x=1e10)"

**Issue:** The formula given is `h = sqrt(ε) × max(|x|, 1.0)`, which handles x scaling, but what about function magnitude? If f(x) is itself very large (f(x) = 1e6) or very small (f(x) = 1e-6), the optimal step size might differ.

**Question:** Should the step size formula also account for the function value magnitude |f(x)|?

**Options:**
A) Include |f(x)|: `h = sqrt(ε) × max(|x|, 1.0) × max(|f(x)|, 1.0)`
B) Keep simple formula but document the assumption (works well for |f(x)| ~ O(1))
C) Let users tune h via Tier 2 API if needed

**Answer:** **Option B** (documented assumption)
**Rationale:** Keeping the formula simple is better. The library will work well for normalized functions (which is standard in numerical analysis). Users who have f(x) with extreme magnitudes can use Tier 2 `derivative_with_options()` to override h.

---

### Question 2: Method Comparison Strategy

**Quote:** "Forward/backward/central methods available for comparison"

**Issue:** How exactly are these results compared? Are all three computed simultaneously? How is the CONVERGENCE_STATUS enum determined?

**Question:** What's the comparison and validation strategy?

**Options:**
A) All three computed, compared pairwise, convergence status based on: all agree (CONVERGED), two agree (WARNING), all differ (FAILED)
B) Compute central, then forward and backward as validation; CONVERGED if within tolerance
C) User picks method (forward/backward/central) explicitly; no automatic comparison

**Answer:** **Option A**
**Rationale:** This enables built-in self-validation. If all three methods agree, result is trustworthy. If only two agree, warning. If all differ, the function is likely not smooth enough. This provides explicit reliability signaling.

**Implementation Detail:** CONVERGENCE_STATUS will have three values:
- CONVERGED: All three methods agree to within tolerance
- WARNING: Two methods agree, one differs
- FAILED: All three methods disagree significantly

---

### Question 3: Error Estimation Method

**Quote:** "Error estimation and convergence validation"

**Issue:** The intent mentions error bounds are returned but doesn't specify the method. Is this Richardson extrapolation? Something else?

**Question:** How are error bounds computed?

**Options:**
A) Richardson extrapolation (compute at h and h/2, estimate error from difference)
B) Analytical error bounds for each method (O(h^p) analysis)
C) Comparison between methods (max difference = error estimate)

**Answer:** **Option C** (comparison between methods)
**Rationale:** Richardson extrapolation requires extra function evaluations. Comparing forward/backward/central is free since all are computed anyway. The difference between results provides a practical error estimate without additional cost.

**Error Bound Formula:**
```
error_bound = max(|f'_forward - f'_central|, |f'_backward - f'_central|)
```

---

### Question 4: Jacobian in Phase 1 or Phase 2?

**Quote:** "Partial derivatives for multi-variable functions" (Phase 1) vs "Jacobian matrix computation" (Phase 2)

**Issue:** Jacobian is just assembled partial derivatives. Is it Phase 1 or Phase 2?

**Question:** Should Jacobian matrix assembly be Phase 1 or Phase 2?

**Options:**
A) Phase 1: Include `jacobian()` that returns MATRIX of all partials
B) Phase 2: Users assemble Jacobians manually from partial derivatives
C) Phase 1 has partial derivatives only; Phase 2 adds Jacobian convenience method

**Answer:** **Option C**
**Rationale:** Phase 1 provides `partial_derivative()` so users can compute each ∂f/∂x_i. Phase 2 adds convenience method `jacobian()` that computes all partials and returns MATRIX. This keeps Phase 1 focused on core differentiation.

---

### Question 5: Tier 3 Expert Access

**Quote:** "Tier 3 (Expert): Direct engine access for research use"

**Issue:** What does this concretely mean?

**Question:** How do users access engine directly?

**Options:**
A) Public method: `engine: DERIVATIVE_CALCULATOR`, user instantiates and calls directly
B) Public method: `create_derivative_calculator(): DERIVATIVE_CALCULATOR`
C) Users don't need this; Tier 2 options are sufficient

**Answer:** **Option B**
**Rationale:** Factory method `create_derivative_calculator()` is cleaner than exposing the class. Advanced users can instantiate engines directly for research. This keeps implementation details abstracted while enabling expert use.

---

### Question 6: Integration with simple_probability

**Quote:** "Seamless integration with simple_probability (Monte Carlo option)"

**Issue:** How is Monte Carlo integration hooked in?

**Question:** What does Monte Carlo integration look like?

**Options:**
A) Tier 2 option: `integrate(f, a, b, method := SIMPSON)` where method can be MONTE_CARLO
B) Separate class: `MONTE_CARLO_INTEGRATOR` uses simple_probability internally
C) Deferred entirely to Phase 2; Phase 1 doesn't mention it

**Answer:** **Option A**
**Rationale:** Tier 2 already has method selection. A MONTE_CARLO option flag makes sense. In Phase 2, this will delegate to simple_probability for sampling. Phase 1 can stub it (document as Phase 2 feature).

---

### Question 7: Acceptance Criteria Clarity

**Quote:** "Derivatives accurate to < 1e-6 relative error on test functions (polynomials, transcendental)"

**Issue:** Relative error of what? On what test functions exactly?

**Question:** What test functions specifically validate the accuracy target?

**Options:**
A) Standard set: f(x) = x^2, x^3, sin(x), cos(x), exp(x), ln(x) at various scales
B) User-provided; acceptance test suite to be designed in Phase 1
C) Polynomial up to degree 5 and 3 transcendental functions

**Answer:** **Option A**
**Rationale:** This is the standard numerical analysis test set. It's comprehensive enough to validate forward/backward/central methods. Accuracy target is relative error of derivative value: |f'_computed - f'_analytical| / |f'_analytical| < 1e-6.

---

## Answers Summary

| Question | Decision | Rationale |
|----------|----------|-----------|
| Adaptive step size formula | Keep simple, document assumption | Standard practice in numerics |
| Method comparison | All three computed, status based on agreement | Built-in self-validation |
| Error estimation | Comparison between methods (free) | No extra function evals needed |
| Jacobian timing | Phase 2 (convenience method) | Phase 1 focuses on partials |
| Tier 3 expert access | Factory method for engine instantiation | Abstraction + capability |
| MC integration | Tier 2 option flag (Phase 2 implementation) | Clean API tier structure |
| Test functions | Standard numerical analysis set | Industry-standard validation |

---

## Intent-v2 Ready

All clarifications captured. Ready to proceed to intent-v2.md generation with these decisions locked in.
