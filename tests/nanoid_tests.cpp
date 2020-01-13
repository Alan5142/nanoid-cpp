#include "gtest/gtest.h"
#include "nanoid/nanoid.hpp"
#include "nanoid/xor_shift_generator.h"
#include <unordered_map>

constexpr auto DEFAULT_SIZE = 21;

TEST(nanoid_tests, test_default)
{
    auto result = nanoid::generate();
    ASSERT_EQ(21, result.size());
}

TEST(nanoid_tests, test_different_ids)
{
    auto result1 = nanoid::generate();
    auto result2 = nanoid::generate();
    ASSERT_NE(result1, result2);
}

TEST(nanoid_tests, test_custom_size)
{
    auto result = nanoid::generate(10);
    ASSERT_EQ(10, result.length());
}

TEST(nanoid_tests, test_custom_alphabet)
{
    auto result = nanoid::generate(nanoid::alphabets::NUMBERS);
    ASSERT_EQ(DEFAULT_SIZE, result.size());
}

TEST(nanoid_tests, test_custom_literal_alphabet)
{
    auto result = nanoid::generate("abcdefghijk");
    ASSERT_EQ(DEFAULT_SIZE, result.size());
}

TEST(nanoid_tests, test_custom_alphabet_and_size)
{
    auto result = nanoid::generate(nanoid::alphabets::LOWERCASE, 5);
    ASSERT_EQ(5, result.size());
}

TEST(nanoid_tests, test_class_random_generator)
{
    auto generator = nanoid::xor_shift_generator();
    auto result = nanoid::generate(generator);
    ASSERT_EQ(DEFAULT_SIZE, result.size());
}

TEST(nanoid_tests, test_lamba_random_generator)
{
    auto generator = [](std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end)
    {
        static std::random_device device;
        static std::mt19937 engine(device());
        std::generate(begin, end, []
        {
            return engine();
        });
    };
    auto result = nanoid::generate(generator);
    ASSERT_EQ(DEFAULT_SIZE, result.size());
}

TEST(nanoid_tests, test_id_uses_only_chars_from_alphabet)
{
    auto &alphabet = nanoid::alphabets::DEFAULT_ALPHABET;
    auto result = nanoid::generate();
    for (auto chr : result)
    {
        ASSERT_NE(alphabet.find(chr), nanoid::string_alphabet::npos);
    }
}

TEST(nanoid_tests, test_no_collisions)
{
    constexpr auto count = 100 * 1000;
    auto lookup = std::unordered_map<std::string, bool>();
    lookup.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        auto result = nanoid::generate();
        ASSERT_EQ(lookup.find(result), std::end(lookup));
        lookup[result] = true;
    }
}
