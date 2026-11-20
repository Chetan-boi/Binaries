#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "runBinary.hpp"

TEST_CASE("shellQuote wraps plain text in single quotes") {
    CHECK(shellQuote("hello") == "'hello'");
}

TEST_CASE("shellQuote escapes embedded single quotes") {
    CHECK(shellQuote("it's") == "'it'\\''s'");
}

TEST_CASE("shellQuote leaves shell characters literal") {
    CHECK(shellQuote("$HOME;ls") == "'$HOME;ls'");
}
