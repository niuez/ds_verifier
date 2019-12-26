#ifndef VERIFY_STATUS_HPP
#define VERIFY_STATUS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <json11/json11.h>

namespace ds {

  template<class Gen>
  const char* gen_name() { return "unknown gen"; }

  template<>
  const char* gen_name<std::mt19937>() { return "std::mt19937"; }


  std::string get_timestamp() {
    auto timestamp = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    std::time_t t = std::chrono::system_clock::to_time_t(timestamp);
    const std::tm* lt = std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(lt, "%Y-%m-%d %H:%M:%S");
    return ss.str();
  }

  

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
        get_timestamp(),
        true,
        fail_at()
      };
    }
    static verify_status failure(const std::string& test_case, const fail_at& failat) {
      return verify_status {
        test_case,
        get_timestamp(),
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

    json11::Json to_json() const {
      return json11::Json::object({
            { "test_case", test_case },
            { "timestamp", timestamp },
            { "target", Target::name() },
            { "checker", Checker::name() },
            { "gen", gen_name<Gen>() },
            { "init_method", InitMethod::name() },
            { "query_count", (int)Q },
            { "status", (verified ? "verified" : "failure") },
            { "query", Query::name() },
            { "fail_at", (verified ? json11::Json::object() : json11::Json::object({ { "fail_query", failat.query }, { "fail_info", failat.info } })) }
          });
    }
  };

}

#endif

