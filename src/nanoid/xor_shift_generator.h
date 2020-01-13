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

#ifndef NANOID_XOR_SHIFT_GENERATOR_H
#define NANOID_XOR_SHIFT_GENERATOR_H

#include <vector>
#include <cstdint>

namespace nanoid
{
    /**
     * Non secure RNG
     */
    class xor_shift_generator
    {
        std::uint32_t x;
        std::uint32_t y;
        std::uint32_t z;
        std::uint32_t w;
    public:

        xor_shift_generator() : x(0x193A6754), y(0xA8A7D469), z(0x97830E05), w(0x113BA7BB)
        {
        }

        uint32_t generate_random_number()
        {
            auto t = x ^(x << 11);
            x = y;
            y = z;
            z = w;
            auto w_ = w;
            w = w_ ^ (w_ >> 19) ^ (t ^ (t >> 8));
            return w;
        }

        /**
         * Fills a vector with random values provided by mt19937 random engine
         * @param begin vector begin
         * @param end vector end
         */
        inline void operator()(std::vector<std::uint8_t>::iterator begin, std::vector<std::uint8_t>::iterator end)
        {
            std::generate(begin, end, [this]()
            { return generate_random_number(); });
        }

    };
}

#endif //NANOID_XOR_SHIFT_GENERATOR_H
