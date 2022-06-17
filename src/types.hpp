#pragma once

#include <optional>
#include <string>

enum class UzTypeId { Void, Int32, Float32, SIZE };

struct UzType {
  UzTypeId id;
};

bool operator==(const UzType &lhs, const UzType &rhs);

std::optional<UzType> toUzType(const std::string &input);
