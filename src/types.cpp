#include "types.hpp"

#include <array>
#include <utility>

bool operator==(const UzType &lhs, const UzType &rhs) { return lhs.id == rhs.id; }

std::optional<UzType> toUzType(const std::string &input) {
  using UzTypeName = std::pair<std::string, UzTypeId>;
  using UzTypeNames = std::array<UzTypeName, static_cast<size_t>(UzTypeId::SIZE)>;
  static const UzTypeNames typeNames = {std::make_pair("void", UzTypeId::Void),
                                        std::make_pair("i32", UzTypeId::Int32),
                                        std::make_pair("f32", UzTypeId::Float32)};
  for (auto &t : typeNames) {
    if (t.first == input) {
      return UzType{t.second};
    }
  }
  return std::nullopt;
}
