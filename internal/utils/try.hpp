#ifndef INTERNAL_UTILS_TRY_HPP
#define INTERNAL_UTILS_TRY_HPP

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TRY(expr) TRY_OR(expr, types::convertToNoneOrErr(expr))

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TRY_OR(expr, defaultValue) ({             \
    if (!(expr).canUnwrap()) return defaultValue; \
    (expr).unwrap();                              \
})

#endif
