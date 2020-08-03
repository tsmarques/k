#ifndef K_EDITOR_BUFFERACTIONS_HPP
#define K_EDITOR_BUFFERACTIONS_HPP

#include <filesystem>

#include <Buffer.hpp>
namespace K
{
  class BufferActions
  {
  public:
    virtual void load(const std::filesystem::path& file_path, Buffer& bfr) = 0;
    virtual void save(const std::filesystem::path& file_path, const Buffer& bfr) = 0;
  };
}

#endif// K_EDITOR_BUFFERACTIONS_HPP
