## Verify Report Json(TODO)

```json

[
  {
    "test_case" : "accumlation_ex0",
    "timestamp" : "2019-12-25 09:00:00",
    "verified" : true,
    "target" : "accumulation",
    "checker" : "std::vector",
    "init_method" : "random vector",
    "query_count" : 200,
    "queries" : [
      "accumulate from index 0"
    ],
  },
  {
    "test_case" : "accumlation_ex1",
    "timestamp" : "2019-12-25 09:00:00",
    "verified" : false,
    "target" : "accumulation",
    "checker" : "std::vector",
    "init_method" : "random vector",
    "query_count" : 200,
    "queries" : [
      "accumulate from index 0"
    ],
    "fail_at" : {
      "q" : 50,
      "query" : "accumulate from index 0",
      "info" : "r = 5 : target return 5 but checker return 6."
    }
  }
]

```
