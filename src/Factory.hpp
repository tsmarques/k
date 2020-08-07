#ifndef K_EDITOR_FACTORY_HPP
#define K_EDITOR_FACTORY_HPP

#include "Buffer.hpp"
#include "LinumMode.hpp"
#include "KMode.hpp"

#include <memory>

namespace K::Mode::Factory
{
  std::unique_ptr<Mode::KMode> create(const std::string& mode_name, std::shared_ptr<Buffer> parent)
  {
    return std::make_unique<Mode::LinumMode>(parent);
  }
}

#endif// K_EDITOR_FACTORY_HPP
