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
    std::time_t t = std::time(nullptr);
    const std::tm* lt = std::gmtime(&t);
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

    void detail(std::ostream& os) const {
      os << "----- verify status -----" << std::endl;
      os << "test_case: " << test_case << std::endl;
      os << "timestamp: " << timestamp << std::endl;
      os << "target: " << Target::name() << std::endl;
      os << "checker: " << Checker::name() << std::endl;
      os << "gen: " << gen_name<Gen>() << std::endl;
      os << "init_method: " << "" << std::endl;
      os << "query count: " << "" << std::endl;
      os << "stauts: " << (verified ? "verified" : "failure") << std::endl;
      os << "Query: " << Query::name() << std::endl;
      if(!verified) {
        os << failat.query << std::endl;
        os << failat.info << std::endl;
      }
    }

    json11::Json to_json() const {
      return json11::Json::object({
            { "test_case", test_case },
            { "timestamp", timestamp },
            { "target", Target::name() },
            { "checker", Checker::name() },
            { "gen", gen_name<Gen>() },
            { "init_method", "" },
            { "query_count", 0 },
            { "status", (verified ? "verified" : "failure") },
            { "query", Query::name() },
            { "fail_at", (verified ? json11::Json::object() : json11::Json::object({ { "fail_query", failat.query }, { "fail_info", failat.info } })) }
          });
    }
  };

}

#endif

