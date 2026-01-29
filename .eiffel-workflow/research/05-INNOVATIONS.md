# INNOVATIONS: simple\_calculus

## What Makes This Different

### I-001: Design by Contract for Numerical Methods

**Problem Solved:** Numerical algorithms have implicit error bounds and convergence assumptions
**Approach:** Explicit preconditions (function smoothness, interval bounds) and postconditions (error estimates)
**Novelty:** Most numerical libraries don't formally specify convergence guarantees
**Design Impact:** Users know exactly what accuracy to expect, when methods will fail

Example:

```eiffel
derivative: REAL\_64
    -- Numerical derivative of function at point
    require
        function\_smooth: -- precondition about smoothness
        point\_in\_domain: x >= a and x <= b
    ensure
        error\_estimated: error <= estimated\_error\_bound
```

### I-002: Adaptive Step Size with Machine Epsilon

**Problem Solved:** Fixed step sizes fail on different function scales
**Approach:** Automatic h selection based on: machine epsilon, function magnitude, derivative estimate
**Novelty:** Transparent to user, prevents under/overflow automatically
**Design Impact:** Single API call works across different problem scales

### I-003: Multiple Method Comparison for Validation

**Problem Solved:** How do users know if result is accurate?
**Approach:** Provide forward/backward/central difference, let user compare results
**Novelty:** Built-in self-validation without requiring external references
**Design Impact:** SIMPLE\_CALCULUS has operation that returns (derivative, error\_estimate, comparison\_status)

### I-004: Integration with simple\_probability for Monte Carlo

**Problem Solved:** Some integrals impossible with deterministic methods
**Approach:** Design API compatible with simple\_probability for Monte Carlo integration
**Novelty:** Seamless handoff between deterministic and stochastic integration
**Design Impact:** User can switch integration methods with single parameter change

## Differentiation from Existing Solutions

|Aspect|Existing (NumPy/GSL)|Our Approach|Benefit|
|-|-|-|-|
|Error handling|Return NaN or infinity|Preconditions prevent invalid calls|Fail-fast, predictable|
|Accuracy control|User guesses step size|Automatic adaptive h|Better results by default|
|API simplicity|Many parameters|Single facade SIMPLE\_CALCULUS|Easier to use|
|Eiffel integration|Non-existent|Pure Eiffel with DBC|Native language idioms|
|SCOOP ready|Not applicable|Fully concurrent|Future-proof|



