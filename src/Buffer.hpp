#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

#include "KMode.hpp"

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

namespace K
{
  class Buffer : public QPlainTextEdit
  {
    Q_OBJECT

    std::vector<std::unique_ptr<Mode::KMode>> m_active_modes;
    void highlightCurrentLine();

  public:
    Buffer(QWidget* parent = nullptr);

    void setModes(std::vector<std::unique_ptr<Mode::KMode>>& modes);

    int linumWidth();

    //! Public access to setViewportMargins
    void setMargins(int left, int top, int right, int bottom);

    //! Public access to firstVisibleBlock()
    QTextBlock getFirstVisibleBlock();

    //! Public access to blockBoundingGeometry
    QRectF getBlockBoundingGeometry(const QTextBlock &block) const;

    //! Public access to blockBoundingRect
    QRectF getBlockBoundingRect(const QTextBlock &block) const;

    //! Public access to contentOffset
    QPointF getContentOffset() const;

  protected:
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
  };
}


#endif