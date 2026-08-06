#ifndef RUNE_FILE_UTILS_HPP
#define RUNE_FILE_UTILS_HPP

#include <string>
#include <optional>

namespace rune 
{

std::optional<std::string> load_program(const std::string& program_path);

} // namespace rune

#endif
