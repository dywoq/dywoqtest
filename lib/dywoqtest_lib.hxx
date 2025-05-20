#ifndef DYWOQTEST_LIB
#define DYWOQTEST_LIB

#include <type_traits>

namespace dywoqtest {

template <typename _Got, typename _Expected> class test {
public:
  using got_t = _Got;
  using expected_t = _Expected;
  using decay_got_t = std::decay_t<_Got>;
  using decay_expected_t = std::decay_t<_Expected>;
};

} // namespace dywoqtest

#endif