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
#include <QtWidgets/QPlainTextEdit>

namespace fs = std::filesystem;

namespace K
{
  constexpr const char* c_greet_screen = "~/.k/greet.txt";

  struct Arguments
  {
    std::string m_curr_dir;
    std::optional<std::vector<std::filesystem::path>> m_files_list;
  };

  class K : public QMainWindow
  {
  Q_OBJECT
    QWidget* m_central_widget;
    QVBoxLayout* m_layout;
    Buffer* m_text_edit;
    QPlainTextEdit* m_mx_text_edit;
    QTabWidget m_tab;

    const Arguments& m_args;

    void
    setupUI();

    void
    loadFiles();


  public:
    K(QWidget* parent, const Arguments& options);
    ~K() override;
  };
}
#endif // BEE_HPP
