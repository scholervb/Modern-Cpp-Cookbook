#pragma once

// std::conditional that enables us to choose between several types at compile time, based
// on a compile-time Boolean expression.

#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>

namespace recipe_6_11 {
  using namespace std::string_literals;

  // In a type alias or typedef, to select between a 32-bit and 64-bit integer type, based
  // on the platform:
  using long_type = std::conditional<sizeof(void*) <= 4, long, long long>::type;

  // In an alias template, to select between a 8-, 16-, 32-, or 64-bit integer type, based
  // on the user specification:
  template <int size>
  using number_type = typename std::conditional<
    size <= 1, std::int8_t,
    typename std::conditional<size <= 2, std::int16_t,
                              typename std::conditional<size <= 4, std::int32_t,
                                                        std::int64_t>::type>::type>::type;

  // In a type template parameter, to select between integer and real uniform
  // distribution:
  // To help simplify the use of std::conditional, C++14 provides an alias template called std::conditional_t and that is defined as follows:

  /*
  template<bool Test, class T1, class T2>
  using conditional_t = typename conditional<Test,T1,T2>::type;
  */

  template <typename T,
            typename D = std::conditional_t<std::is_integral<T>::value,
                                            std::uniform_int_distribution<T>,
                                            std::uniform_real_distribution<T>>,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
  std::vector<T> GenerateRandom(T const min, T const max, size_t const size)
  {
    std::vector<T> v(size);

    std::random_device rd{};
    std::mt19937 mt{ rd() };

    D dist{ min, max };

    std::generate(std::begin(v), std::end(v), [&dist, &mt] { return dist(mt); });

    return v;
  }

  void execute()
  {
    std::cout << "\nRecipe 6.11: Using std::conditional to choose between types."
              << "\n------------------------------------------------------------\n";

    {
      auto n = long_type{ 42 };
    }

    {
      auto n1 = number_type<1>{ 42 };
      auto n2 = number_type<2>{ 42 };
      auto n3 = number_type<3>{ 42 };
      auto n4 = number_type<4>{ 42 };
      auto n5 = number_type<5>{ 42 };
      auto n6 = number_type<6>{ 42 };
      auto n7 = number_type<7>{ 42 };
      auto n8 = number_type<8>{ 42 };
      auto n9 = number_type<9>{ 42 };

      static_assert(sizeof(n1) == 1);
      static_assert(sizeof(n2) == 2);
      static_assert(sizeof(n3) == 4);
      static_assert(sizeof(n4) == 4);
      static_assert(sizeof(n5) == 8);
      static_assert(sizeof(n6) == 8);
      static_assert(sizeof(n7) == 8);
      static_assert(sizeof(n8) == 8);
      static_assert(sizeof(n9) == 8);

      static_assert(sizeof(number_type<1>) == 1);
      static_assert(sizeof(number_type<2>) == 2);
      static_assert(sizeof(number_type<3>) == 4);
      static_assert(sizeof(number_type<4>) == 4);
      static_assert(sizeof(number_type<5>) == 8);
      static_assert(sizeof(number_type<6>) == 8);
      static_assert(sizeof(number_type<7>) == 8);
      static_assert(sizeof(number_type<8>) == 8);
      static_assert(sizeof(number_type<9>) == 8);
    }

    {
      auto lprint = [](auto const& v) {
        for (auto const n : v) {
          std::cout << n << " ";
        }
        std::cout << std::endl;
      };

      std::cout << "Integer uniform distribution:\n";
      auto v1 = GenerateRandom(1, 10, 10);
      lprint(v1);

      std::cout << "\nReal uniform distribution:\n";
      auto v2 = GenerateRandom(1.0, 10.0, 10);
      lprint(v2);

      // auto v3 = GenerateRandom("1.0"s, "10.0"s, 10); // error
    }

    std::cout << "---------------------------------\n\n";
  }
}
