#include <memory>
#include <type_traits>
#include <utility>

void foo(std::unique_ptr<int>)
{
}

template <typename T>
concept foo_argument =
  // T is not deduced here ...
  requires (T&& arg) {
    foo(std::forward<T>(arg)); // SonarQube suggests std::move() which is wrong (see static assertions below)
  };

static_assert(foo_argument<std::unique_ptr<int>&&>);
static_assert(!foo_argument<std::unique_ptr<int>&>);

struct bar
{
  template <foo_argument T> // ... T is deduced here
  void operator()(T&& arg) const
  {
    foo(std::forward<T>(arg));
  }
};

static_assert(std::is_invocable_v<const bar&, std::unique_ptr<int>&&>);
static_assert(!std::is_invocable_v<const bar&, std::unique_ptr<int>&>);

int forward_concept_main()
{
  bar{}(std::make_unique<int>(42));

  return 0;
}
