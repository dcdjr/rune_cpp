#include "rune/file_utils.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <optional>

std::optional<std::string> rune::load_program(const std::string& program_path) {
    std::ifstream ifs(program_path);
    if (!ifs.is_open()) 
        return std::nullopt;
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}
