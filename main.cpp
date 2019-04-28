#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>

struct S
{
  std::string first_;
  std::string last_;
};

bool operator==(const S& a, const S& b) { return a.first_ == b.first_ && a.last_ == b.last_; }

namespace std
{
template <> struct hash<S>
{
  size_t operator()(S const& s) const
  {
    size_t h1 = std::hash<std::string>{}(s.first_);
    size_t h2 = std::hash<std::string>{}(s.first_);
    return h1 ^ (h2 << 1);
  }
};
}  // namespace std

int main()
{
  std::string str = "hello hush";
  std::cout << "hash(" << str << ") = " << std::hash<std::string>{}(str) << '\n';

  S obj = {"Hubert", "Farnsworth"};
  std::cout << "hash(" << std::quoted(obj.first_) << ',' << std::quoted(obj.last_)
            << ") = " << std::hash<S>{}(obj) << '\n';

  std::unordered_set<S> objs{obj, {"Bender", "Rodriguez"}, {"Leela", "Turanga"}};
  for (auto s : objs)
  {
    std::cout << "hash(" << std::quoted(s.first_) << ',' << std::quoted(s.last_)
              << ") = " << std::hash<S>{}(s) << '\n';
  }
  return 0;
}