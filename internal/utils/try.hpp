#ifndef TRY_HPP
#define TRY_HPP

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TRY(expr) TRY_OR(expr, expr)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TRY_OR(expr, defaultValue) ({             \
    if (!(expr).canUnwrap()) return defaultValue; \
    (expr).unwrap();                              \
})

#endif
