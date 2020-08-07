#include "LinumMode.hpp"

#include "KLog.hpp"
#include <QtGui/QPainter>
#include <QtGui/QTextBlock>


namespace K::Mode
{
  LinumMode::LinumMode(std::shared_ptr<Buffer> bfr) :
      KMode(),
      buffer(bfr)
  {
    buffer->connect(buffer.get(), SIGNAL(blockCountChanged(int)), buffer.get(),
                    SLOT(updateLinumWidth(int)));

    buffer->connect(buffer.get(), SIGNAL(updateRequest(QRect, int)), buffer.get(),
                    SLOT(updateLinumArea(QRect, int)));
  }

  int
  LinumMode::linumWidth()
  {
    int digits = 1;
    int max = qMax(1, buffer->blockCount());
    while (max >= 10)
    {
      max /= 10;
      ++digits;
    }

    int space = 3 + buffer->fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
  }

  void
  LinumMode::updateLinumWidth(int)
  {
    buffer->setMargins(linumWidth(), 0, 0, 0);
  }

  void
  LinumMode::updateLinumArea(const QRect& rect, int dy)
  {
    if (dy)
      linum_area->scroll(0, dy);
    else
      linum_area->update(0, rect.y(), linum_area->width(), rect.height());

    if (rect.contains(buffer->viewport()->rect()))
      updateLinumWidth(0);
  }

  void
  LinumMode::onOpen()
  {
    klog("init linum-mode at ", buffer->objectName().toStdString());
  }

  void LinumMode::onClose()
  {
    klog("closing linum-mode at ", buffer->objectName().toStdString());
  }

  void LinumMode::onRegisterKeymap()
  {  }

  void
  LinumMode::onEvent(QPaintEvent* event)
  {
    QPainter painter(linum_area);
    painter.fillRect(event->rect(), QColor::fromRgb(121, 125, 133));

    QTextBlock block = buffer->getFirstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top =
        (int)buffer->getBlockBoundingGeometry(block).translated(buffer->getContentOffset()).top();
    int bottom = top + (int)buffer->getBlockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
      if (block.isVisible() && bottom >= event->rect().top())
      {
        QString number = QString::number(blockNumber + 1);
        painter.setPen(QColor::fromRgb(216, 222, 233));
        painter.drawText(0, top, linum_area->width(), buffer->fontMetrics().height(),
                         Qt::AlignCenter, number);
      }

      block = block.next();
      top = bottom;
      bottom = top + (int)buffer->getBlockBoundingRect(block).height();
      ++blockNumber;
    }
  }

  void LinumMode::onEvent(QResizeEvent* event)
  {
    (void) event;

    QRect cr = buffer->contentsRect();
    linum_area->setGeometry(
        QRect(cr.left(), cr.top(), linumWidth(), cr.height()));
  }
}