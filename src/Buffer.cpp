#include <QtWidgets>

#include "Buffer.hpp"

namespace K
{
  Buffer::Buffer(QWidget* parent) :
    QPlainTextEdit(parent)
  {
    setObjectName(QString::fromUtf8("m_text_edit"));
    QPalette p = palette();
    p.setColor(QPalette::Base, QColor::fromRgb(46, 52, 64));
    p.setColor(QPalette::Text, QColor::fromRgb(216, 222, 233));
    setPalette(p);

    QFont f("Source Code Pro");
    f.setStyleHint(QFont::Monospace);
    setFont(f);

    connect(this, SIGNAL(cursorPositionChanged()), this,
            SLOT(highlightCurrentLine()));

    highlightCurrentLine();
  }

  void
  Buffer::setModes(std::vector<std::unique_ptr<Mode::KMode>>& modes)
  {
    m_active_modes.swap(modes);
  }

  void
  Buffer::resizeEvent(QResizeEvent* e)
  {
    QPlainTextEdit::resizeEvent(e);
    // @todo
  }

  void
  Buffer::highlightCurrentLine()
  {
    QList<QTextEdit::ExtraSelection> extra_selection;

    if (!isReadOnly())
    {
      QTextEdit::ExtraSelection selection;

      QColor lineColor = QColor::fromRgb(18, 66, 82);

      selection.format.setBackground(lineColor);
      selection.format.setProperty(QTextFormat::FullWidthSelection, true);
      selection.cursor = textCursor();
      selection.cursor.clearSelection();
      extra_selection.append(selection);
    }

    setExtraSelections(extra_selection);
  }

  QRectF Buffer::getBlockBoundingGeometry(const QTextBlock &block) const
  {
    return blockBoundingGeometry(block);
  }

  QPointF Buffer::getContentOffset() const
  {
    return contentOffset();
  }

  QRectF Buffer::getBlockBoundingRect(const QTextBlock &block) const
  {
    return blockBoundingRect(block);
  }

  void
  Buffer::setMargins(int left, int top, int right, int bottom)
  {
    setMargins(left, top, right, bottom);
  }

  QTextBlock
  Buffer::getFirstVisibleBlock()
  {
    return firstVisibleBlock();
  }
}