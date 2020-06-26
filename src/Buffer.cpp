#include <QtWidgets>

#include "Buffer.hpp"

Buffer::Buffer(QWidget *parent) :
    QPlainTextEdit(parent)
{
  linum_area = new LineNumberArea(this);

  QFont f("Source Code Pro");
  f.setStyleHint(QFont::Monospace);
  setFont(f);

  connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
  connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
  connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

  updateLineNumberAreaWidth(0);
  highlightCurrentLine();
}


int
Buffer::lineNumberAreaWidth()
{
  int digits = 1;
  int max = qMax(1, blockCount());
  while (max >= 10) {
    max /= 10;
    ++digits;
  }

  int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

  return space;
}



void
Buffer::updateLineNumberAreaWidth(int)
{
  setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void
Buffer::updateLineNumberArea(const QRect &rect, int dy)
{
  if (dy)
    linum_area->scroll(0, dy);
  else
    linum_area->update(0, rect.y(), linum_area->width(), rect.height());

  if (rect.contains(viewport()->rect()))
    updateLineNumberAreaWidth(0);
}



void
Buffer::resizeEvent(QResizeEvent *e)
{
  QPlainTextEdit::resizeEvent(e);

  QRect cr = contentsRect();
  linum_area->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}



void
Buffer::highlightCurrentLine()
{
  QList<QTextEdit::ExtraSelection> extra_selection;

  if (!isReadOnly()) {
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



void
Buffer::lineNumberAreaPaintEvent(QPaintEvent *event)
{
  QPainter painter(linum_area);
  painter.fillRect(event->rect(), QColor::fromRgb(46, 52, 64));


  QTextBlock block = firstVisibleBlock();
  int blockNumber = block.blockNumber();
  int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
  int bottom = top + (int) blockBoundingRect(block).height();

  while (block.isValid() && top <= event->rect().bottom())
  {
    if (block.isVisible() && bottom >= event->rect().top())
    {
      QString number = QString::number(blockNumber + 1);
      painter.setPen(QColor::fromRgb(216, 222, 233));
      painter.drawText(0, top, linum_area->width(),
                       fontMetrics().height(),
                       Qt::AlignCenter, number);
    }

    block = block.next();
    top = bottom;
    bottom = top + (int) blockBoundingRect(block).height();
    ++blockNumber;
  }
}