
#include "nlohmann/json.hpp"
#include <benchmark/benchmark.h>
#include <json/json.h>
#include <cstddef>

// https://github.com/open-source-parsers/jsoncpp
// https://github.com/nlohmann/json


/*
{
    "name" : "zhangyuge",
    "age" : 10,
    "sex" : "male"
}
*/

const static std::string jsonStr =
    "{\
					\"name\":\"Cain\",\
					\"age\":23,\
					\"sex\":\"man\"\
					}";

struct Person
{
    std::string name;
    int age{};
    std::string sex;
};


static void BM_JsonCPP_encode(benchmark::State& state)
{
    for (auto _ : state)
    {
        Json::Value j;
        j["name"] = "zhangyuge";
        j["age"] = 12;
        j["sex"] = "male";

        auto s = j.toStyledString();
        benchmark::DoNotOptimize(s);
        benchmark::DoNotOptimize(j);
    }
}

static void BM_JsonCPP_decode(benchmark::State& state)
{
    for (auto _ : state)
    {
        Json::Reader reader;
        Json::Value value;

        Person person;
        if (reader.parse(jsonStr, value))
        {
            person.name = value["name"].asString();
            person.age = value["age"].asInt();
            person.sex = value["sex"].asString();

            benchmark::DoNotOptimize(reader);
            benchmark::DoNotOptimize(value);
            benchmark::DoNotOptimize(person);
        }
    }
}


static void BM_nlohmannJson_encode(benchmark::State& state)
{
    for (auto _ : state)
    {
        nlohmann::json j;
        j["name"] = "zhangyuge";
        j["age"] = 12;
        j["sec"] = "male";

        auto s = j.dump();

        benchmark::DoNotOptimize(s);
        benchmark::DoNotOptimize(j);
    }
}

static void BM_nlohmannJson_decode(benchmark::State& state)
{
    for (auto _ : state)
    {
        Person person;
        nlohmann::json j = nlohmann::json::parse(jsonStr, nullptr, false);

        person.name = j["name"];
        person.age = j["age"];
        person.sex = j["sex"];

        benchmark::DoNotOptimize(j);
        benchmark::DoNotOptimize(person);
    }
}


// Register the function as a benchmark
BENCHMARK(BM_JsonCPP_encode);
BENCHMARK(BM_JsonCPP_decode);
BENCHMARK(BM_nlohmannJson_encode);
BENCHMARK(BM_nlohmannJson_decode);