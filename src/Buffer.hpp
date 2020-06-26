#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;


class Buffer : public QPlainTextEdit
{
Q_OBJECT

public:
    explicit Buffer(QWidget *parent = nullptr);

    void
    lineNumberAreaPaintEvent(QPaintEvent *event);

    int
    lineNumberAreaWidth();

protected:
    void
    resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void
    updateLineNumberAreaWidth(int newBlockCount);

    void
    highlightCurrentLine();

    void
    updateLineNumberArea(const QRect &, int);

private:
    QWidget* linum_area;
};


class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(Buffer*editor) :
            QWidget(editor)
    {
        m_editor = editor;
    }

    QSize
    sizeHint() const Q_DECL_OVERRIDE
    {
        return QSize(m_editor->lineNumberAreaWidth(), 0);
    }

protected:
    void
    paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE
    {
        m_editor->lineNumberAreaPaintEvent(event);
    }

private:
  Buffer* m_editor;
};


#endif