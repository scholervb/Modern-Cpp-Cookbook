#pragma once

#include <iostream>

namespace recipe_3_06_1 {

// only works with Clang 3.9

#ifdef __clang__
  template <typename... Ts>
  auto add(Ts... args)
  {
    return (... + args);
  }

  template <typename... Ts>
  auto addr(Ts... args)
  {
    return (args + ...);
  }

  template <typename... Ts>
  auto all_of(Ts... args)
  {
    return (... && args);
  }

  template <typename... Ts>
  auto any_of(Ts... args)
  {
    return (... || args);
  }

  template <typename T>
  struct wrapper_min {
    T const& value;
  };

  template <typename T>
  constexpr auto operator<(wrapper_min<T> const& lhs, wrapper_min<T> const& rhs)
  {
    return wrapper_min<T>{ lhs.value < rhs.value ? lhs.value : rhs.value };
  }

  template <typename... Ts>
  constexpr auto min(Ts&&... args)
  {
    return (wrapper_min<Ts>{ args } < ...).value;
  }
#endif

  void execute()
  {
    std::cout << "\nRecipe 3.06.1: Using fold expressions to simplify variadic function "
                 "templates."
              << "\n---------------------------------------------------------------------"
                 "---------"
              << "\nRight now only works with CLang.\n";

#ifdef __clang__
    std::cout << min(10, 2, 3, 4, 5) << std::endl;

    std::cout << add() << std::endl;
    std::cout << add(1, 2, 3, 4, 5) << std::endl;
    std::cout << addr(1, 2, 3, 4, 5) << std::endl;

    std::cout << all_of(true, true, true) << std::endl;
    std::cout << all_of(false, false, false) << std::endl;
    std::cout << all_of(true, false, true) << std::endl;

    std::cout << any_of(true, true, true) << std::endl;
    std::cout << any_of(false, false, false) << std::endl;
    std::cout << any_of(true, false, true) << std::endl;
#endif
  }
}
