# Eiffel Contract Review Request - simple_calculus (Claude)

**Project:** simple_calculus - Numerical Calculus Library
**Phase:** 2 - Adversarial Contract Review (Round 2)
**Reviewer:** Claude
**Previous Reviewer:** Ollama QwenCoder

---

## Ollama Review Results (Summary)

Ollama identified 8 issues:
1. **HIGH**: Missing postcondition in DERIVATIVE_RESULT.make - error_bound semantics
2. **MEDIUM**: Missing infinite check in step_size_calculator
3. **HIGH**: Unrealistic postcondition in compute_step_size (result < 1.0e-5 violated when x=1e10)
4. **MEDIUM**: Missing tolerance semantics in CONVERGENCE_ANALYZER
5. **MEDIUM**: Missing frame conditions on DERIVATIVE_CALCULATOR attributes
6. **LOW**: Silent fallback in CONVERGENCE_STATUS.to_string
7. **HIGH**: Incomplete postcondition in compute_adaptive (iterations_positive may fail if tolerance huge)
8. **MEDIUM**: Missing error bound semantics documentation in INTEGRAL_RESULT

**Critical Issues Requiring Fix:**
- Issue #2: Add `not x.is_infinite` precondition
- Issue #3: Fix or remove `result_reasonable` postcondition
- Issue #7: Change `iterations_positive` to `iterations_non_negative`

---

## Your Task: Claude Deeper Review

You are reviewing Eiffel contracts for **technical correctness, SCOOP safety, and consistency**. Assume Ollama's identified issues are valid. Your job:

1. **Validate Ollama's findings** - Are they technically correct?
2. **Check MML/Frame conditions** - Are frame conditions properly specified for SCOOP?
3. **Verify mathematical semantics** - Do contracts match numerical analysis reality?
4. **Check consistency** - Do related postconditions agree?
5. **Find additional issues** Ollama may have missed

**Additional Focus Areas:**
- SCOOP: Are results properly immutable? Can step_calculator/analyzer be safely shared?
- Mathematical: Does error_bound definition make sense numerically?
- Type Safety: Are preconditions sufficient to prevent invalid state?
- Consistency: Do Tier 1/2/3 APIs have consistent contracts?

---

## Key Contracts (Abbreviated)

### STEP_SIZE_CALCULATOR.compute_step_size

```eiffel
compute_step_size (x: REAL_64): REAL_64
	require
		x_valid: not x.is_nan
	ensure
		result_positive: Result > 0.0
		result_not_nan: not Result.is_nan
		result_reasonable: Result > 1.0e-15 and Result < 1.0e-5
	end
```

**Ollama Issue #3:** If x = 1e10, Result = sqrt(2.2e-16) * 1e10 ≈ 1.5e2, violates Result < 1.0e-5.

**Your analysis needed:**
- Is Ollama correct? (Yes, mathematically obvious)
- How should this be fixed?
- Does formula documentation match postcondition?

---

### INTEGRAL_CALCULATOR.compute_adaptive

```eiffel
compute_adaptive (...): INTEGRAL_RESULT
	require
		tolerance_positive: tolerance > 0.0
	ensure
		...
		iterations_positive: Result.iterations > 0
	end
```

**Ollama Issue #7:** If tolerance = 1000.0, Simpson's rule meets it on first call. l_iterations stays 0. Postcondition violated.

**Your analysis:**
- Is precondition weak? (tolerance_positive doesn't prevent 1000)
- Should postcondition be iterations_non_negative?
- What tolerance range makes sense?

---

### DERIVATIVE_RESULT (Immutability)

```eiffel
make (a_value: REAL_64; a_error_bound: REAL_64; a_status: INTEGER)
	ensure
		value_set: value = a_value
		error_bound_set: error_bound = a_error_bound
		convergence_status_set: convergence_status = a_status
	end
```

**Ollama Issue #5 (Frame Conditions):** No explicit invariant that value/error_bound/convergence_status don't change after creation.

**Your analysis:**
- In Eiffel, are these implicitly immutable (no setter)?
- Should an invariant enforce immutability?
- For SCOOP, is explicit frame condition needed?

---

## Contracts to Review (Full)

[SAME CONTRACT TEXT AS OLLAMA PROMPT - All 9 classes with full code]

**Classes:**
1. CONVERGENCE_STATUS (enum)
2. STEP_SIZE_CALCULATOR (utility)
3. CONVERGENCE_ANALYZER (utility)
4. CONVERGENCE_RESULT (data)
5. DERIVATIVE_RESULT (data)
6. INTEGRAL_RESULT (data)
7. DERIVATIVE_CALCULATOR (engine)
8. INTEGRAL_CALCULATOR (engine)
9. SIMPLE_CALCULUS (facade)

---

## Claude-Specific Review Checklist

- [ ] **Ollama's 8 issues**: Are they valid? Any false positives?
- [ ] **Step size bounds**: Should postcondition scale with x?
- [ ] **Iterations postcondition**: Should be >= 0?
- [ ] **Infinite/NaN propagation**: What should happen if x=Infinity?
- [ ] **SCOOP immutability**: Are implicit immutable fields OK?
- [ ] **Frame conditions**: Needed for concurrent use?
- [ ] **MML usage**: Should data classes use MML model queries?
- [ ] **Error semantics**: Is error_bound absolute or relative?
- [ ] **Tolerance validation**: Upper bounds needed?
- [ ] **Tier consistency**: Do Tier 1/2/3 postconditions align?

---

## Output Format

For **validated** Ollama issues:
```
**OLLAMA ISSUE #N - VALIDATED** [description]
**CONTEXT**: [why it's correct]
**PRIORITY**: [Critical/High/Medium]
```

For **additional** issues found:
```
**NEW ISSUE**: [description]
**LOCATION**: [Class.feature]
**ROOT CAUSE**: [analysis]
**FIX**: [suggestion]
```

For **false positives** (if any):
```
**OLLAMA ISSUE #N - DISPUTED**
**REASON**: [why Ollama is wrong]
**CORRECT INTERPRETATION**: [what actually holds]
```

---

## Proceed with Review

Analyze the contracts above using the Ollama findings as starting point. Validate, add, or dispute as needed.

**Return:** Organized list of all issues (Ollama validated + new + disputed) with priorities.
