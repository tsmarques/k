#ifndef BEE_HPP
#define BEE_HPP

#include <QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "Buffer.hpp"
#include <Options.hpp>
#include <OptionsParser.hpp>
#include <QtWidgets/QPlainTextEdit>

namespace fs = std::filesystem;

namespace K
{
  constexpr const char* c_greet_screen = "~/.k/greet.txt";

  class K : public QMainWindow
  {
  Q_OBJECT
    QWidget* m_central_widget;
    QVBoxLayout* m_layout;
    std::map<std::filesystem::path, std::shared_ptr<Buffer>> m_buffers;
    QPlainTextEdit* m_mx_text_edit;
//    QTabWidget m_tab;

    const Options& m_args;

    void
    setupUI();

    void
    loadBuffers();


  public:
    K(QWidget* parent, const Options& options);
    ~K() override;
  };
}
#endif // BEE_HPP
