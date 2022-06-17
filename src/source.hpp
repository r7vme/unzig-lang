#pragma once

#include <memory>
#include <string>

class SourceObject {
  const std::string rawSource;

  SourceObject(const SourceObject &other) = delete;
  SourceObject &operator=(const SourceObject &other) = delete;

public:
  SourceObject(const std::string &rawSource);
  const std::string &getRawSource() const;
  std::string getHightlightedPosition(const size_t position) const;
};

using Source = std::shared_ptr<SourceObject>;

Source createSource(const std::string &input);
