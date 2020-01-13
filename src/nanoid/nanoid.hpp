/*
The MIT License (MIT)

Copyright 2020 Alan Ramírez Herrera <alan5142@hotmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef NANOID_H
#define NANOID_H

#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <functional>

#if __cplusplus >= 201703L
#include <string_view>
#else

#include <string>

#endif

namespace nanoid
{
    // use string view in C++17
    #if __cplusplus >= 201703L
    using string_alphabet = std::string_view;
    using string_alphabet_parameter = std::string_view;
    #else
    using string_alphabet = std::string const;
    using string_alphabet_parameter = string_alphabet &;
    #endif

    /**
     * Contains a set of useful alphabets
     */
    namespace alphabets
    {
        /**
         * Default alphabet
         */
        string_alphabet DEFAULT_ALPHABET = "_-0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        /**
         * Only numbers (0 to 9)
         */
        string_alphabet NUMBERS = "0123456789";

        /**
         * Uppercase english letters
         */
        string_alphabet UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        /**
         * Lowercase english letters
         */
        string_alphabet LOWERCASE = "abcdefghijklmnopqrstuvwxyz";

        /**
         * Numbers and english alphabet without lookalikes: 1, l, I, 0, O, o, u, v, 5, S, s
         */
        string_alphabet NO_LOOK_ALIKES = "2346789ABCDEFGHJKLMNPQRTUVWXYZabcdefghijkmnpqrtwxyz";
    }

    namespace details
    {
        inline void generate_random_bytes(std::vector<std::uint8_t>::iterator begin, std::vector<std::uint8_t>::iterator end)
        {
            static std::random_device device;
            std::generate(begin, end, []()
            { return device(); });
        }

        template<typename F>
        struct is_invocable :
                std::is_constructible<
                        std::function<void(std::vector<std::uint8_t>::iterator, std::vector<std::uint8_t>::iterator)>,
                        std::reference_wrapper<typename std::remove_reference<F>::type>
                >
        {
        };
    }

    /**
     * Generates a random id
     * @tparam RandomGenerator random numeric generator, it must be a callable object with two arguments of type std::vector<uint8_t>::iterator: begin and end
     * @param random_device random device callable object
     * @param alphabet set of characters to be used to generate the random id
     * @param length id length
     * @return string with random id
     */
    template<class RandomGenerator, class = typename std::enable_if<details::is_invocable<RandomGenerator>::value>>
    inline std::string generate(
            RandomGenerator &random_device,
            string_alphabet_parameter alphabet = alphabets::DEFAULT_ALPHABET,
            int length = 21)
    {
        if (alphabet.empty() || alphabet.size() >= 256)
        {
            throw std::invalid_argument("Alphabet must contain between 1 and 255 sybols.");
        }
        if (length <= 0)
        {
            throw std::invalid_argument("Size must be greater than zero.");
        }

        auto mask = (2 << static_cast<int>(std::floor(std::log(alphabet.size() - 1) / std::log(2)))) - 1;
        auto step = static_cast<int>(std::ceil(1.6 * mask * length / alphabet.size()));

        auto id_builder = std::string();
        id_builder.reserve(length);
        auto count = 0;

        auto bytes = std::vector<std::uint8_t>(step);

        while (true)
        {
            random_device(std::begin(bytes), std::end(bytes));
            for (auto i = 0; i < step; ++i)
            {
                auto alphabet_index = bytes[i] & mask;
                if (alphabet_index >= alphabet.length()) continue;

                id_builder.push_back(alphabet[alphabet_index]);
                if (++count == length)
                {
                    return id_builder;
                }
            }
        }
    }

    /**
     * Generates a random id
     * @details it uses class "nanoid::random_number_generator" as id generator
     * @param alphabet set of characters to be used to generate the random id
     * @param length id length
     * @return string with random id
     */
    inline std::string generate(string_alphabet_parameter alphabet = alphabets::DEFAULT_ALPHABET, int length = 21)
    {
        return generate(details::generate_random_bytes, alphabet, length);
    }

    /**
     * Generates a random id
     * @details it uses class "nanoid::random_number_generator" as id generator
     * @param alphabet set of characters to be used to generate the random id
     * @param length id length
     * @return string with random id
     */
    inline std::string generate(char const *const alphabet, int length = 21)
    {
        return generate(string_alphabet_parameter(alphabet), length);
    }

    /**
     * Generates a random id of given length
     * @param size random id length
     * @return string with random id
     */
    inline std::string generate(int size)
    {
        return generate(alphabets::DEFAULT_ALPHABET, size);
    }
}

#endif //NANOID_H
