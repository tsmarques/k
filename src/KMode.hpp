#ifndef K_EDITOR_KMODE_HPP
#define K_EDITOR_KMODE_HPP

namespace K::Mode
{
  class KMode
  {
  public:
    virtual const char* name() = 0;

    virtual void onOpen() = 0;

    virtual void onClose() = 0;

    virtual void onRegisterKeymap()
    { }
  };
}

#endif// K_EDITOR_KMODE_HPP
