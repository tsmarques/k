#ifndef K_EDITOR_DEFAULTACTIONS_HPP
#define K_EDITOR_DEFAULTACTIONS_HPP

#include "BufferActions.hpp"
#include <fstream>

namespace K
{
  class DefaultActions : public BufferActions
  {
    std::fstream f_stream;

  public:
    void
    load(const std::filesystem::path& file_path, Buffer& bfr) override
    {
      f_stream.open(file_path, std::ios::in | std::ios::out);
      std::string f_content( (std::istreambuf_iterator<char>(f_stream)),
                             (std::istreambuf_iterator<char>()));

      bfr.setPlainText(QString::fromUtf8(f_content.c_str()));
    }

    void
    save(const std::filesystem::path& file_path, const Buffer& bfr) override
    {
      f_stream.seekg(0);
      std::string text = bfr.toPlainText().toStdString();
      f_stream.write(text.c_str(), text.size());
    }

    ~DefaultActions()
    {
      f_stream.close();
    }
  };
}
#endif
