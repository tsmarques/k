#ifndef K_EDITOR_LINUMMODE_HPP
#define K_EDITOR_LINUMMODE_HPP

#include "Buffer.hpp"
#include "KMode.hpp"

namespace K::Mode
{
  class LinumMode : public KMode
  {
    //! Linum area
    QWidget* linum_area;
    //! Buffer to apply this mode to
    std::shared_ptr<Buffer> buffer;

    int linumWidth();

    void onEvent(QPaintEvent* event);

    void onEvent(QResizeEvent* event);

  private slots:
    void updateLinumWidth(int newBlockCount);

    void updateLinumArea(const QRect& rect, int dy);

  public:
    LinumMode(std::shared_ptr<Buffer> bfr);

    const char*
    name() override
    {
      return "linum-mode";
    }

    void onOpen() override;

    void onClose() override;

    void onRegisterKeymap() override;
  };
}
#endif// K_EDITOR_LINUMMODE_HPP
