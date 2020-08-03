#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class Linum;

namespace K
{
  class Buffer : public QPlainTextEdit
  {
    Q_OBJECT

  public:
    Buffer(QWidget* parent = nullptr);

    void linumPaintEvent(QPaintEvent* event);

    int linumWidth();

  protected:
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

  private slots:
    void updateLinumWidth(int newBlockCount);

    void highlightCurrentLine();

    void updateLinumArea(const QRect& rect, int dy);

  private:
    QWidget* linum_area;
  };

  class Linum : public QWidget
  {
  public:
    explicit Linum(Buffer* editor) : QWidget(editor) { m_editor = editor; }

    QSize
    sizeHint() const Q_DECL_OVERRIDE
    {
      return QSize(m_editor->linumWidth(), 0);
    }

  protected:
    void
    paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE
    {
      m_editor->linumPaintEvent(event);
    }

  private:
    Buffer* m_editor;
  };
}


#endif