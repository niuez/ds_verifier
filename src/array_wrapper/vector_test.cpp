#include <array_wrapper/vector.hpp>
#include <unit_test/test.hpp>
#include <vector>

TEST_START() {
  ds::array_wrapper<int, std::vector<int>> vec(std::vector<int>{ 0, 1, 2 });
  TEST_ASSERT(vec.access_index(1) == 1, "access_index failure");
  TEST_ASSERT(vec.accum_from0(2) == 1, "accum_from0 failure");
}
TEST_END()
