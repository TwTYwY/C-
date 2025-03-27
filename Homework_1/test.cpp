#include <catch2/catch_test_macros.hpp>
#include "LongArithmetic.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Plus operation works correctly, when both positive and no fractional part", "[arithmetic]") {
    // given
    const LongNum num1("10");
    const LongNum num2("10");

    // when
    const LongNum result = num1 + num2;

    // then
    const LongNum expected("20");
    REQUIRE(result == expected);
}

TEST_CASE("Plus operation works correctly, when both positive and no integer part", "[arithmetic]") {
    // given
    const LongNum num1("0.1");
    const LongNum num2("0.1");

    // when
    const LongNum result = num1 + num2;

    // then
    const LongNum expected("0.2");
    REQUIRE(result == expected);
}

TEST_CASE("Plus operation works correctly, when both positive", "[arithmetic]") {
    // given
    const LongNum num1("10.5");
    const LongNum num2("10.75");

    // when
    const LongNum result = num1 + num2;

    // then
    const LongNum expected("21.25");
    REQUIRE(result == expected);
}

TEST_CASE("Plus operation works correctly, when one negative", "[arithmetic]") {
    // given
    const LongNum num1("-10.15");
    const LongNum num2("10.75");

    // when
    const LongNum result = num1 + num2;

    // then
    const LongNum expected("0");
    REQUIRE(result == expected);
}

TEST_CASE("Plus operation works correctly, when one negative and number is really long", "[arithmetic]") {
    // given
    const LongNum num1(
        "-10000000000000000000000000000000000000000000000000000000000000000000001"
        ".5"
    );
    const LongNum num2(
        "10000000000000000000000000000000000000000000000000000000000000000000000"
        ".5"
    );

    // when
    const LongNum result = num1 + num2;

    // then
    const LongNum expected("-1");
    REQUIRE(result == expected);
}

TEST_CASE("Minus operation works correctly", "[arithmetic]") {
    // given
    const LongNum num1(
        "15.84375"
    );
    const LongNum num2(
        "11.8125"
    );

    // when
    const LongNum result_positive = num1 - num2;

    // then
    const LongNum expected_positive("4.03125");
    CHECK(result_positive == expected_positive);

    // when
    const LongNum result_negative = num2 - num1;

    // then
    const LongNum expected_negative("-4.03125");
    REQUIRE(result_negative == expected_negative);
}

TEST_CASE("Multiply operation works correctly, when both positive", "[arithmetic]") {
    // given
    const LongNum num1(
        "15.84375"
    );
    const LongNum num2(
        "11.8125"
    );

    // when
    const LongNum result = num1 * num2;

    // then
    const LongNum expected("187.154296875");
    REQUIRE(result == expected);
}

TEST_CASE("Multiply operation works correctly, when one negative", "[arithmetic]") {
    // given
    const LongNum num1(
        "-15.84375"
    );
    const LongNum num2(
        "11.8125"
    );

    // when
    const LongNum result = num1 * num2;

    // then
    const LongNum expected("-187.154296875");
    REQUIRE(result == expected);
}

TEST_CASE("Multiply operation works correctly, when both negative", "[arithmetic]") {
    // given
    const LongNum num1(
        "-15.84375"
    );
    const LongNum num2(
        "-11.8125"
    );

    // when
    const LongNum result = num1 * num2;

    // then
    const LongNum expected("187.154296875");
    REQUIRE(result == expected);
}

TEST_CASE("Greater operation works correctly, when both positive", "[arithmetic]") {
    // given
    const LongNum num1(
        "10.01"
    );
    const LongNum num2(
        "11.02"
    );

    // when
    const bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    const bool result_true = num1 < num2;

    // then
    REQUIRE(result_true);
}

TEST_CASE("Greater operation works correctly, when one negative", "[arithmetic]") {
    // given
    const LongNum num1(
        "-10.01"
    );
    const LongNum num2(
        "11.02"
    );

    // when
    const bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    const bool result_true = num1 < num2;

    // then
    REQUIRE(result_true);
}

TEST_CASE("Greater operation works correctly, when both negative", "[arithmetic]") {
    // given
    const LongNum num1(
        "-11.01"
    );
    const LongNum num2(
        "-10.02"
    );

    // when
    const bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    const bool result_true = num1 < num2;

    // then
    REQUIRE(result_true);
}
