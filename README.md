# simple_calculus

[Documentation](https://simple-eiffel.github.io/simple_calculus/) •
[GitHub](https://github.com/simple-eiffel/simple_calculus) •
[Issues](https://github.com/simple-eiffel/simple_calculus/issues)

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Eiffel 25.02](https://img.shields.io/badge/Eiffel-25.02-purple.svg)
![DBC: Contracts](https://img.shields.io/badge/DBC-Contracts-green.svg)

Numerical calculus library: derivatives, integrals, and partial derivatives with verified accuracy.

Part of the [Simple Eiffel](https://github.com/simple-eiffel) ecosystem.

## Status

✅ **Production Ready** — v1.0.0
- 45 tests passing, 100% pass rate
- Adaptive step size computation, convergence analysis
- Design by Contract throughout

## Quick Start

```eiffel
local
    l_calc: SIMPLE_CALCULUS
    l_f: FUNCTION [REAL_64, REAL_64]
do
    create l_calc
    l_f := agent (x: REAL_64): REAL_64 do Result := x * x end
    Result := l_calc.derivative (l_f, 1.0)
end
```

For complete documentation, see [our docs site](https://simple-eiffel.github.io/simple_calculus/).

## Features

- **Tier 1 API** — Simple interface for derivatives, integrals, partial derivatives
- **Tier 2 API** — Advanced control with method selection and error bounds
- **Tier 3 API** — Expert access to computation engines for research use
- **Adaptive Algorithms** — Automatic step size and tolerance management
- **Convergence Analysis** — Three-method comparison for derivative accuracy
- **SCOOP Compatible** — Immutable results enable concurrent use

For details, see the [User Guide](https://simple-eiffel.github.io/simple_calculus/user-guide.html).

## Installation

```bash
# Add to your ECF:
<library name="simple_calculus" location="$SIMPLE_EIFFEL/simple_calculus/simple_calculus.ecf"/>
```

## License

MIT License - See LICENSE file

## Support

- **Docs:** https://simple-eiffel.github.io/simple_calculus/
- **GitHub:** https://github.com/simple-eiffel/simple_calculus
- **Issues:** https://github.com/simple-eiffel/simple_calculus/issues
