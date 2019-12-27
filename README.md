# ds\_verifier

## 目標

- データ構造のverifyはそれよりより下位のデータ構造でverifyするべき.
- 例えば, セグ木の`fold`は合っているが, `at`が実は間違っていますみたいな事故を減らしたい. より多くの種類のクエリを簡単にverifyしたい.

## Example

累積和のライブラリである`ds::accumlation`をverifyするとする.

`ds::verifier`は

```cpp
template<
  class Target, // verifyするデータ構造
  class Checker, // Targetが正しく動いているかを確かめるデータ構造
  class Gen, // std::mt19937などの乱数生成器
  class InitMethod, // データ構造の初期化の方法
  const std::size_t Q, // クエリの回数
  class Query // verifyしたいクエリの種類
>
class verifier { /* ... */ }
```

という定義になっている.

```cpp
VERIFY_START() {
  using i32 = ds::int32; // 乱数で初期化できるようにしたintのラッパ
  using accum_verify = ds::verifier<
    ds::array_wrapper<i32, ds::accumulation<i32>>, // accumulationのラッパ (最初に累積和を計算する)
    ds::array_wrapper<i32, std::vector<i32>>, // std::vectorのラッパ (forで毎回, 累積和を計算する)
    std::mt19937,
    ds::random_init_vector<i32, 100>, // データ構造を要素100個のランダムなintで初期化する
    300, // クエリは300回
    ds::accum_from0<i32> // [0, r)の累積和を計算するクエリをverifyする
    >;

  std::mt19937 gen(1);
  VERIFY(accum_verify()(gen, "accumulation_example1")); // verify
}
VERIFY_END();
```

このソースコードを実行すると, verifyした結果をjsonで出力する.

## verify自動化

現段階なので, よりよくしていきたい

1. verifyしたいコードが入っているディレクトリの`CMakeLists.txt`にこれを書く

```cmake
file(GLOB_RECURSE verify_source_list *_verify.cpp)

set(verify_list)
file(REMOVE "${CMAKE_BINARY_DIR}/verify_list")

foreach(verify_source IN LISTS verify_source_list)
  file(RELATIVE_PATH relative_source "${CMAKE_SOURCE_DIR}" "${verify_source}")
  message("verify_source: ${relative_source}")
  get_filename_component(verify_target "${verify_source}" NAME_WE)
  add_executable("${verify_target}" "${verify_source}")
  target_link_libraries("${verify_target}" ds_verifier)
  list(APPEND verify_list "${verify_target}")
  file(APPEND "${CMAKE_BINARY_DIR}/verify_list" "${CMAKE_CURRENT_BINARY_DIR}/${verify_target}:${relative_source}\n")
endforeach()

```

2. ソースコードをビルド

out-of-sourceで

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

3. `$ python3 verify.py build`でverify

`$ python3 verify.py build --all`をすると, すべてverify済みのときにverifyをスキップします.

4. `$ python3 generate.py`でGitHub Pages用のHTMLソースを生成
