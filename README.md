# nanoid-cpp

[![License](https://img.shields.io/badge/license-MIT%20License-blue.svg)](LICENSE)

Header-only C++ implementation of [ai's](https://github.com/ai) [nanoid](https://github.com/ai/nanoid)
<
## Usage

### Normal

The default method uses URL-friendly symbols (`A-Za-z0-9_~`) and returns an ID
with 21 characters.

```cpp
auto id = nanoid::generate();
```

If you want to reduce ID length (and increase collisions probability),
you can pass the size as an argument:

```cpp
auto id = nanoid::generate(10);
```

### Custom Alphabet or Length

If you want to change the ID's alphabet or length
you can pass alphabet and size.

```cpp
auto id = nanoid::generate("1234567890abcdef", 10);
```

Alphabet must contain 256 symbols or less.

### Custom Random Bytes Generator

You can replace the default safe random generator with a callable object that accepts two 
`std::vector<std::uint8_t>::iterator` iterators.
For instance, to use a generator based on std::rand().

```cpp
auto random = [](std::vector<std::uint8_t>::iterator begin, std::vector<std::uint8_t>::iterator end)
{
    std::generate(begin, end, []{ return std::rand(); });
};
auto id = nanoid::generate(random, nanoid::alphabets::NUMBERS, 10);
```

### Predefined alphabets
`nanoid-cpp` comes with a predefined set of alphabets, they're included in `nanoid::alphabets` namespace

* `nanoid::alphabets::DEFAULT_ALPHABET` -> default alphabet used in `nanoid-cpp`
* `nanoid::alphabets::NUMBERS` -> Only numbers (0 to 9)
* `nanoid::alphabets::UPPERCASE` -> Uppercase english letters
* `nanoid::alphabets::LOWERCASE` -> Lowercase english letters
* `nanoid::alphabets::NO_LOOK_ALIKES` -> Numbers and english alphabet without lookalikes: 1, l, I, 0, O, o, u, v, 5, S, s

## Credits

- [ai](https://github.com/ai) - [nanoid](https://github.com/ai/nanoid)

## License

The MIT License (MIT). Please see [License File](LICENSE) for more information.