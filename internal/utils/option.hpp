#ifndef OPTION_HPP
#define OPTION_HPP

#include "try.hpp"
#include <cstddef>
#include <string>

template<class T>
class Option;

namespace types {
    template<class T>
    class Some {
    public:
        explicit Some(T val) : val_(val) {}

        Some(const Some &other) {
            *this = other;
        }

        ~Some() {}

        Some &operator=(const Some &other) {
            if (*this != other) {
                val_ = other.val_;
            }
            return *this;
        }

        operator Option<T>() const { // NOLINT(google-explicit-constructor)
            return Option<T>(new Some<T>(val_));
        }

        T val() const {
            return val_;
        }

        bool operator==(const Some &other) const {
            return val_ == other.val_;
        }

        bool operator!=(const Some &other) const {
            return val_ != other.val_;
        }

    private:
        T val_;
    };

    class None {
    public:
        bool operator==(const None &other) const {
            (void) other;
            return true;
        }

        bool operator!=(const None &other) const {
            (void) other;
            return false;
        }

        template<class T>
        operator Option<T>() const { // NOLINT(google-explicit-constructor)
            return Option<T>(NULL);
        }
    };
} // namespace types

template<class T>
types::Some<T> Some(T val) { // NOLINT(readability-identifier-naming)
    return types::Some<T>(val);
}

// NOLINTNEXTLINE(readability-identifier-naming)
const types::None None = types::None();

template<class T>
class Option {
public:
    explicit Option(types::Some<T> *some) : some_(some) {}

    explicit Option(types::None none) : some_(NULL) {
        (void) none;
    }

    Option(const Option &other) : some_(other.some_) {}

    ~Option() {
        delete some_;
    }

    Option &operator=(const Option &other) {
        if (this != &other) {
            if (other.isSome()) {
                if (some_ != NULL) {
                    *some_ = *other.some_;
                } else {
                    some_ = new types::Some<T>(*other.some_);
                }
            } else {
                some_ = NULL;
            }
        }
        return *this;
    }

    bool operator==(const Option &other) const {
        if (isSome() != other.isSome()) {
            return false;
        }
        if (isNone()) {
            return true;
        }
        return *some_ == *other.some_;
    }

    bool operator!=(const Option &other) const {
        if (isSome() != other.isSome()) {
            return true;
        }
        if (isNone()) {
            return false;
        }
        return *some_ != *other.some_;
    }

    bool isSome() const {
        return some_ != NULL;
    }

    bool isNone() const {
        return some_ == NULL;
    }

    T unwrap() const {
        return some_->val();
    }

    T unwrapOr(T val) const {
        if (isSome())
            return some_->val();
        return val;
    }

    bool canUnwrap() const {
        return isSome();
    }

private:
    types::Some<T> *some_;
};

#endif
