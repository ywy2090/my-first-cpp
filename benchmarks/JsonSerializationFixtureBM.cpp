
#include "nlohmann/json.hpp"
#include <benchmark/benchmark.h>
#include <json/json.h>
#include <cstddef>

// https://github.com/open-source-parsers/jsoncpp
// https://github.com/nlohmann/json

struct Person
{
    std::string name;
    int age{};
    std::string sex;
};


class JsonSerializationFixture : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State& state) override {}

    void TearDown(const ::benchmark::State& state) override {}

public:
    const std::string m_jsonStr =
        "{\
					\"name\":\"Cain\",\
					\"age\":23,\
					\"sex\":\"man\"\
					}";
};


BENCHMARK_DEFINE_F(JsonSerializationFixture, BM_JsonCppEncodeTest)(benchmark::State& state)
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

BENCHMARK_DEFINE_F(JsonSerializationFixture, BM_JsonCppDecodeTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        Json::Reader reader;
        Json::Value value;

        Person person;
        if (reader.parse(m_jsonStr, value))
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

BENCHMARK_DEFINE_F(JsonSerializationFixture, BM_NlohmannJsonEncodeTest)(benchmark::State& state)
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

BENCHMARK_DEFINE_F(JsonSerializationFixture, BM_NlohmannJsonDecodeTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        Person person;
        nlohmann::json j = nlohmann::json::parse(m_jsonStr, nullptr, false);

        person.name = j["name"];
        person.age = j["age"];
        person.sex = j["sex"];

        benchmark::DoNotOptimize(j);
        benchmark::DoNotOptimize(person);
    }
}


// Register the function as a benchmark
BENCHMARK_REGISTER_F(JsonSerializationFixture, BM_JsonCppEncodeTest);
BENCHMARK_REGISTER_F(JsonSerializationFixture, BM_JsonCppDecodeTest);
BENCHMARK_REGISTER_F(JsonSerializationFixture, BM_NlohmannJsonEncodeTest);
BENCHMARK_REGISTER_F(JsonSerializationFixture, BM_NlohmannJsonDecodeTest);