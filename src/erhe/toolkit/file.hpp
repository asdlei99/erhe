#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace erhe::toolkit
{

// return value will be empty if file does not exist, or is not regular file, or is empty
[[nodiscard]] auto read(
    const std::string_view       description,
    const std::filesystem::path& path
) -> std::optional<std::string>;

// TODO open, save, ...
auto select_file() -> std::optional<std::filesystem::path>;

[[nodiscard]] auto check_is_existing_non_empty_regular_file(
    const std::string_view       description,
    const std::filesystem::path& path,
    bool silent_if_not_exists = false
) -> bool;

} // namespace erhe::toolkit
