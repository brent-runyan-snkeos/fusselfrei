#include <cassert>
#include <functional>
#include <memory>
#include <utility>

void foo(std::unique_ptr<int>&)
{
  // Don't modify an lvalue
}

void foo(std::unique_ptr<int>&& ptr)
{
  // Consume an rvalue because we can
  ptr.reset();
}

template <typename T>
class foo_forwarder
{
public:
  explicit foo_forwarder(T&& arg)
    : argument_{std::forward<T>(arg)} // SonarQube suggests std::move() here which would move from an lvalue reference
  {
  }

  foo_forwarder(const foo_forwarder& that) = delete;
  foo_forwarder(foo_forwarder&& that) = delete;

  ~foo_forwarder() = default;

  foo_forwarder& operator=(const foo_forwarder& that) = delete;
  foo_forwarder& operator=(foo_forwarder&& that) = delete;

  void operator()() &&
  {
    foo(std::forward<T>(argument_));
  }

private:
  T argument_;
};

template <typename T>
void bar(T&& arg) // T is deduced here
{
  std::invoke(foo_forwarder<T>{std::forward<T>(arg)});
}

int forward_object_main()
{
  bar(std::make_unique<int>(1));

  auto ptr = std::make_unique<int>(2);

  bar(ptr);

  assert(ptr != nullptr);

  return 0;
}
