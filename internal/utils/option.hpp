#ifndef OPTION_HPP
#define OPTION_HPP

#include <cstddef>

namespace types {
    template<class T>
    class Some;
}

template<class T>
class Option {
public:
    explicit Option(types::Some<T> *some) : some_(some) {}

    Option(const Option &other) {
        *this = other;
    }

    ~Option() {
        delete some_;
    }

    Option &operator=(const Option &other) {
        if (this != &other) {
            some_ = other.some_;
        }
        return *this;
    }

    bool operator==(const Option &other) {
        if (isSome() != other.isSome())
            return false;
        if (isNone())
            return true;
        return *some_ == *other.some_;
    }

    bool operator!=(const Option &other) {
        if (isSome() != other.isSome())
            return true;
        if (isNone())
            return false;
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

private:
    types::Some<T> *some_;
};

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

        operator Option<T>() { // NOLINT(google-explicit-constructor)
            return Option<T>(new Some<T>(val_));
        }

        T val() {
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
        operator Option<T>() { // NOLINT(google-explicit-constructor)
            return Option<T>(NULL);
        }
    };
} // namespace types

template<class T>
types::Some<T> Some(T val) { // NOLINT
    return types::Some<T>(val);
}

types::None None = types::None(); // NOLINT

#endif
