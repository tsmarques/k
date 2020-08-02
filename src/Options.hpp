#ifndef K_EDITOR_OPTIONS_HPP
#define K_EDITOR_OPTIONS_HPP

#include <stdlib.h>
#include <string>
#include <vector>
#include <optional>
#include <filesystem>

namespace K
{
  struct Options
  {
    std::string m_curr_dir;
    //! --help option
    std::optional<std::string> m_help_str;
    //! --version option
    std::optional<std::string> m_version_str;
    //! -f option
    std::optional<std::vector<std::filesystem::path>> m_files_list;
  };
}

#endif
