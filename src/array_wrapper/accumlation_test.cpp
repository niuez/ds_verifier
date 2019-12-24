#include <array_wrapper/accumulation.hpp>
#include <unit_test/test.hpp>
#include <vector>

TEST_START() {
  ds::array_wrapper<int, ds::accumulation<int>> vec(std::vector<int>{ 0, 1, 2, 3, 4, 5 });
  TEST_ASSERT(vec.accum_from0(4) == 6, "accum_from0 failure");
  TEST_ASSERT(vec.accum_from0(6) == 15, "accum_from0 failure");
}
TEST_END()
