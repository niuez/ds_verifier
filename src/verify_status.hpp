#ifndef VERIFY_STATUS_HPP
#define VERIFY_STATUS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <random>

namespace ds {

  template<class Gen>
  const char* gen_name() { return "unknown gen"; }

  template<>
  const char* gen_name<std::mt19937>() { return "std::mt19937"; }

  struct fail_at {
    const std::string query;
    const std::string info;
    fail_at() {}
    fail_at(const std::string& query, const std::string& info)
      : query(query), info(info) {}
  };
  
  template<
    class Target,
    class Checker,
    class Gen,
    class InitMethod,
    const std::size_t Q,
    class Query
  >
  struct verify_status {
    const std::string test_case;
    const std::string timestamp;
    const bool verified;
    const fail_at failat;

    static verify_status success(const std::string& test_case) {
      return verify_status {
        test_case,
        "[ -- timestamp here -- ]",
        true,
        fail_at()
      };
    }
    static verify_status failure(const std::string& test_case, const fail_at& failat) {
      return verify_status {
        test_case,
        "[ --timestamp here-- ]",
        false,
        failat
      };
    }

    void detail() const {
      std::cout << "----- verify status -----" << std::endl;
      std::cout << "test_case: " << test_case << std::endl;
      std::cout << "timestamp: " << timestamp << std::endl;
      std::cout << "target: " << Target::name() << std::endl;
      std::cout << "checker: " << Checker::name() << std::endl;
      std::cout << "gen: " << gen_name<Gen>() << std::endl;
      std::cout << "init_method: " << InitMethod::name() << std::endl;
      std::cout << "queri count: " << Q << std::endl;
      std::cout << "stauts: " << (verified ? "verified" : "failure") << std::endl;
      std::cout << "Query: " << Query::name() << std::endl;
      if(!verified) {
        std::cout << failat.query << std::endl;
        std::cout << failat.info << std::endl;
      }
    }
  };
}

#endif

