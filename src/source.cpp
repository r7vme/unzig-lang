#include "source.hpp"
#include <stdexcept>

SourceObject::SourceObject(const std::string &rawSource) : rawSource(rawSource) {}

const std::string &SourceObject::getRawSource() const { return rawSource; };

std::string SourceObject::getHightlightedPosition(const size_t position) const {
  if (position >= rawSource.size()) {
    throw std::out_of_range("position is out of range");
  }

  std::size_t lineBegin = rawSource.rfind('\n', position);
  if (lineBegin == std::string::npos) {
    lineBegin = 0;
  } else {
    lineBegin += 1;
  }

  std::size_t lineEnd = rawSource.find('\n', position);
  if (lineEnd == std::string::npos) {
    lineEnd = (rawSource.size() - 1);
  }

  auto line = rawSource.substr(lineBegin, lineEnd - lineBegin);
  auto relativeTokenPosition = position - lineBegin;
  std::string highlightLine(line.size(), ' ');
  highlightLine.at(relativeTokenPosition) = '^';
  const std::string prefix = " | ";
  return prefix + line + '\n' + prefix + highlightLine;
}

Source createSource(const std::string &input) { return std::make_shared<SourceObject>(input); }
