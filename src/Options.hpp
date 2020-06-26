#ifndef BEE_OPTIONS_HPP
#define BEE_OPTIONS_HPP

#include <filesystem>

#include <Result.hpp>
#include <iostream>

namespace K
{
  class Options
  {
    struct Entry
    {
      char short_name;
      bool is_required;
      bool is_flag;
      std::vector<std::string> values{};
      std::string description;
      bool is_used;
    };

    std::string m_curr_dir;
    std::optional<std::vector<std::filesystem::path>> m_files_list;
    std::map<std::string, Entry> m_loaded_options;

    bool
    process(const std::vector<std::string>& args) const
    {
      auto it = args.begin();
      for (const auto& s : args)
      {
        if (s.at(0) == '-')
        {

        }
      }
      return true;
    }

    void
    printUsage() const
    {
    }

    void
    printVersion() const
    {
      std::cerr << "k: don't have version" << std::endl;
    }

    bool
    hasOption(std::string longName)
    {
      auto ret = m_loaded_options.find(longName);
      if (ret == m_loaded_options.end())
        return false;

      return ret->second.is_used;
    }

  public:
    bool
    parse(int argc, char** argv)
    {
      std::vector<std::string> args(&argv[1], &argv[argc]);
      if (!process(args))
        return false;

      if (hasOption("--help"))
      {
        printUsage();
        return false;
      }

      if (hasOption("--version"))
      {
        printVersion();
        return false;
      }

      return true;
    }

    int
    size() const {
      return m_loaded_options.size();
    }

    Options&
    add(char short_name, const std::string& long_name, bool required, bool is_flag,  const std::string& description)
    {
      Entry e;
      e.short_name = short_name;
      e.is_required = required;
      e.is_flag = is_flag;
      e.description = description;
      e.is_used = false;

      m_loaded_options.insert({long_name, e});
      return *this;
    }
  };
}

#endif
