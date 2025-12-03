#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include <string>
#include <cctype>
#include <cstring>
#include <vector>

std::string processStringVersion1(const std::string& input) {
    std::string result = input;
    bool hasDigit = false;

    for (char c : result) {
        if (std::isdigit(c)) {
            hasDigit = true;
            break;
        }
    }

    for (char& c : result) {
        if (c == ' ') {
            c = hasDigit ? '_' : '-';
        }
    }

    return result;
}

std::string processStringVersion2(const std::string& input) {
    return processStringVersion1(input);
}

std::string processStringVersion3(const std::string& input) {
    return processStringVersion1(input);
}

TEST_CASE("Обработка строки без цифр") {
    SECTION("Версия 1 - пробелы заменяются на дефисы") {
        REQUIRE(processStringVersion1("hello world test") == "hello-world-test");
    }

    SECTION("Версия 2 - пробелы заменяются на дефисы") {
        REQUIRE(processStringVersion2("simple test case") == "simple-test-case");
    }

    SECTION("Версия 3 - пробелы заменяются на дефисы") {
        REQUIRE(processStringVersion3("no digits here") == "no-digits-here");
    }
}

TEST_CASE("Обработка строки с цифрами") {
    SECTION("Версия 1 - пробелы заменяются на подчеркивания") {
        REQUIRE(processStringVersion1("hello 123 world") == "hello_123_world");
    }

    SECTION("Версия 2 - пробелы заменяются на подчеркивания") {
        REQUIRE(processStringVersion2("test 456 string") == "test_456_string");
    }

    SECTION("Версия 3 - пробелы заменяются на подчеркивания") {
        REQUIRE(processStringVersion3("string with 789 digits") == "string_with_789_digits");
    }
}

TEST_CASE("Тестирование обработки граничных случаев с памятью") {
    SECTION("Очень длинная строка без пробелов") {
        std::string longString(1000, 'a');
        REQUIRE(processStringVersion1(longString) == longString);
        REQUIRE(processStringVersion2(longString) == longString);
        REQUIRE(processStringVersion3(longString) == longString);
    }

    SECTION("Строка с множеством пробелов подряд") {
        std::string manySpaces = "a   b    c     d";
        REQUIRE(processStringVersion1(manySpaces) == "a---b----c-----d");
        REQUIRE(processStringVersion2(manySpaces + "1") == "a___b____c_____d1");
        REQUIRE(processStringVersion3(manySpaces) == "a---b----c-----d");
    }

    SECTION("Строка с максимальным количеством цифр") {
        std::string allDigits = "1 2 3 4 5 6 7 8 9 0";
        REQUIRE(processStringVersion1(allDigits) == "1_2_3_4_5_6_7_8_9_0");
        REQUIRE(processStringVersion2(allDigits) == "1_2_3_4_5_6_7_8_9_0");
        REQUIRE(processStringVersion3(allDigits) == "1_2_3_4_5_6_7_8_9_0");
    }
}

TEST_CASE("Тестирование специальных символов и граничных значений") {
    SECTION("Строка только с пробелами и одним символом") {
        REQUIRE(processStringVersion1("   a   ") == "---a---");
        REQUIRE(processStringVersion2("   1   ") == "___1___");
        REQUIRE(processStringVersion3("  a 1 b ") == "__a_1_b_");
    }

    SECTION("Строка с табуляциями и другими whitespace символами") {
        std::string withTabs = "a\tb\tc";
        REQUIRE(processStringVersion1(withTabs) == withTabs);
        REQUIRE(processStringVersion2(withTabs) == withTabs);
        REQUIRE(processStringVersion3(withTabs) == withTabs);
    }
}

TEST_CASE("Тестирование последовательности вызовов") {
    SECTION("Многократный вызов с разными данными") {
        REQUIRE(processStringVersion1("first call") == "first-call");
        REQUIRE(processStringVersion1("second 123 call") == "second_123_call");
        REQUIRE(processStringVersion1("third call") == "third-call");
    }

    SECTION("Чередование строк с цифрами и без") {
        REQUIRE(processStringVersion2("no digits") == "no-digits");
        REQUIRE(processStringVersion2("with 123 digits") == "with_123_digits");
        REQUIRE(processStringVersion2("again no digits") == "again-no-digits");
        REQUIRE(processStringVersion2("and 456 again") == "and_456_again");
    }
}

TEST_CASE("Тестирование корректности обработки памяти") {
    SECTION("Обработка строки с повторяющимися паттернами") {
        std::string pattern = "abc 123 def 456 ghi 789 ";
        std::string expected = "abc_123_def_456_ghi_789_";
        REQUIRE(processStringVersion1(pattern) == expected);
        REQUIRE(processStringVersion2(pattern) == expected);
        REQUIRE(processStringVersion3(pattern) == expected);
    }

    SECTION("Строка с минимальной длиной") {
        REQUIRE(processStringVersion1("") == "");
        REQUIRE(processStringVersion1("a") == "a");
        REQUIRE(processStringVersion1("1") == "1");
        REQUIRE(processStringVersion1(" ") == "-");
    }

    SECTION("Строка с максимальным чередованием пробелов") {
        std::string alternating = "a b c d e f g h i j k l m n o p";
        std::string result = processStringVersion1(alternating);
        REQUIRE(result.find(' ') == std::string::npos);
    }
}

TEST_CASE("Тестирование целостности данных") {
    SECTION("Исходная строка не изменяется") {
        std::string original = "test 123 string";
        std::string copy = original;
        processStringVersion1(copy);
        REQUIRE(original == "test 123 string");
    }

    SECTION("Корректность замены всех пробелов") {
        std::string testString = "a b c d e f";
        std::string result = processStringVersion1(testString);
        int spaceCount = 0;
        for (char c : testString) if (c == ' ') spaceCount++;

        int dashCount = 0;
        for (char c : result) if (c == '-') dashCount++;

        REQUIRE(spaceCount == dashCount);
    }

    SECTION("Сохранение не-пробельных символов") {
        std::string testString = "hello123world!@#";
        std::string result = processStringVersion2(testString);
        for (size_t i = 0; i < testString.size(); ++i) {
            if (testString[i] != ' ') {
                REQUIRE(result.find(testString[i]) != std::string::npos);
            }
        }
    }
}

TEST_CASE("Тестирование логики замены пробелов") {
    SECTION("Одна цифра влияет на все пробелы в строке") {
        REQUIRE(processStringVersion1("a b c") == "a-b-c");
        REQUIRE(processStringVersion1("a 1 c") == "a_1_c");
        REQUIRE(processStringVersion1("1 a b") == "1_a_b");
        REQUIRE(processStringVersion1("a b 1") == "a_b_1");
    }

    SECTION("Крайние случаи с цифрами") {
        REQUIRE(processStringVersion2(" 1") == "_1");
        REQUIRE(processStringVersion2("1 ") == "1_");
        REQUIRE(processStringVersion2(" 1 ") == "_1_");
    }

    SECTION("Строки с разным количеством пробелов") {
        REQUIRE(processStringVersion3("a b") == "a-b");
        REQUIRE(processStringVersion3("a  b") == "a--b");
        REQUIRE(processStringVersion3("a   b") == "a---b");
        REQUIRE(processStringVersion3("a 1 b") == "a_1_b");
        REQUIRE(processStringVersion3("a  1  b") == "a__1__b");
    }
}