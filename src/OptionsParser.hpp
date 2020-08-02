#ifndef BEE_OPTIONS_HPP
#define BEE_OPTIONS_HPP

#include <filesystem>

#include <Options.hpp>
#include <Result.hpp>
#include <iostream>

namespace K
{
  class OptionsParser
  {
  public:
    struct Entry
    {
      char short_name;
      std::string long_name;
      bool is_required;
      bool is_flag;
      std::vector<std::string> values_str{};
      std::string entry_description;
      bool is_used;

      Entry(char short_n, std::string long_n) :
          short_name(short_n),
          long_name(long_n)
      { }

      Entry&
      isRequired(bool value)
      {
        is_required = value;
        return *this;
      }

      Entry&
      isFlag(bool value)
      {
        is_flag = value;
        return *this;
      }

      Entry&
      description(const char* desc)
      {
        entry_description = desc;
        return *this;
      };

      Entry&
      values(std::vector<std::string> v)
      {
        values_str = v;
        return *this;
      }
    };

    bool
    parse(K::Options& kargs, int argc, char** argv)
    {
      std::vector<std::string> args(&argv[1], &argv[argc]);
      if (!process(args))
        return false;

      auto ret = getOption("--help");
      if (ret.has_value())
      {
        kargs.m_help_str = getUsage();
        return true;
      }

      ret = getOption("--version");
      if (ret.has_value())
      {
        kargs.m_version_str = getVersion();
        return true;
      }

      ret = getOption("--files");
      if (ret.has_value())
      {
        std::vector<std::filesystem::path> to_load_files;
        auto file_paths = ret.value();

        for (auto& file_path_str : file_paths)
          to_load_files.push_back(std::filesystem::path(file_path_str));

        kargs.m_files_list = to_load_files;
      }

      return true;
    }

    int
    size() const {
      return m_available_options.size();
    }

    OptionsParser&
    add(const Entry& e)
    {
      m_available_options.insert({e.long_name, e});
      return *this;
    }

    std::map<std::string, Entry> m_available_options;
    //! Map of used option and values strings
    std::map<std::string, std::vector<std::string>> m_used_options;

    bool
    process(const std::vector<std::string>& args)
    {
      std::string curr = "";
      for (const auto& s : args)
      {
        if (s.at(0) == '-')
        {
          curr = s;
          m_used_options[s] = std::vector<std::string>();
        }
        else
        {
          if (curr.empty() || m_used_options.find(curr) == m_used_options.end())
          {
            std::cerr << s << " is not an option" << std::endl;
            return false;
          }

          m_used_options.at(curr).push_back(s);
        }
      }

      return true;
    }

    std::string
    getUsage() const
    {
      return "Use it as you want...";
    }

    std::string
    getVersion() const
    {
      return "v0.0.1";
    }

    std::optional<std::vector<std::string>>
    getOption(std::string longName)
    {
      std::optional<std::vector<std::string>> ret;
      auto it = m_used_options.find(longName);
      // doesn't exist
      if (it == m_used_options.end())
        return ret;

      ret = it->second;
      return ret;
    }
  };
}

#endif
