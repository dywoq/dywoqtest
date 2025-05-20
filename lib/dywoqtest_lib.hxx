#ifndef DYWOQTEST_LIB
#define DYWOQTEST_LIB

#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <utility>

#if defined(__cpp_exceptions)
#define DYWOQTEST_LIB_HAS_EXCEPTIONS 1
#elif
#define DYWOQTEST_LIB_HAS_EXCEPTIONS 0
#endif

namespace dywoqtest {

class test_failure : public std::logic_error {
  using std::logic_error::logic_error;
};

template <typename _Rt>
  requires std::equality_comparable<_Rt>
class test {
private:
  using __clean_rt_t = std::decay_t<_Rt>;

  template <typename _Tp> struct __property_data {
    _Tp value;
    bool exists;
  };

  __property_data<__clean_rt_t> __got_data_;
  __property_data<__clean_rt_t> __expected_data_;

  __property_data<const char *> __name_data_;

public:
  using return_type = _Rt;
  using clean_return_type = __clean_rt_t;

  constexpr explicit test(const char *__name, const return_type &__got,
                          const return_type &__expected) noexcept
      : __name_data_{__name, true},
        __got_data_{static_cast<clean_return_type>(__got), true},
        __expected_data_{static_cast<clean_return_type>(__expected), true} {}

  constexpr explicit test(const char *__name,
                          const std::pair<return_type, return_type> __pair) noexcept
      : __name_data_{__name, true},
        __got_data_{static_cast<clean_return_type>(__pair.first), true},
        __expected_data_{static_cast<clean_return_type>(__pair.second), true} {}

  constexpr explicit test(const return_type &__got,
                          const return_type &__expected) noexcept
      : __name_data_{"", false}, __got_data_{static_cast<clean_return_type>(__got), true},
        __expected_data_{static_cast<clean_return_type>(__expected), true} {}

  constexpr explicit test(const std::pair<return_type, return_type> __pair) noexcept
      : __name_data_{"", false},
        __got_data_{static_cast<clean_return_type>(__pair.first), true},
        __expected_data_{static_cast<clean_return_type>(__pair.second), true} {}

  constexpr explicit test(const test<return_type> &__test) noexcept
      : __name_data_(__test.__name_data_), __got_data_(__test.__got_data_),
        __expected_data_(__test.__expected_data_) {}

  constexpr test<_Rt> &operator=(const test<return_type> &__other) noexcept {
    __name_data_ = __other.__name_data_;
    __got_data_ = __other.__got_data_;
    __expected_data_ = __other.__expected_data_;
    return *this;
  }

  constexpr test<_Rt> &
  operator=(const std::pair<return_type, return_type> &__other) noexcept {
    __name_data_.value = "";
    __name_data_.exists = false;
    __got_data_ = __other.first;
    __expected_data_ = __other.second;
    return *this;
  }

  constexpr test<_Rt> &operator=(const char *__name) noexcept {
    __name_data_.value = __name;
    __name_data_.exists = true;
    return *this;
  }

  constexpr return_type got() const noexcept { return __got_data_.value; }

  constexpr return_type expected() const noexcept { return __expected_data_.value; }

  constexpr bool failed() const noexcept {
    return __got_data_.value != __expected_data_.value;
  }
};

} // namespace dywoqtest

#endif