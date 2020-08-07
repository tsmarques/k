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
#include <src/Buffer/BufferActions.hpp>
#include <src/Buffer/DefaultActions.hpp>

namespace fs = std::filesystem;

namespace K
{
  constexpr const char* c_greet_screen = "~/.k/greet.txt";

  class K : public QMainWindow
  {
  Q_OBJECT
    QWidget m_central_widget;
    QVBoxLayout m_layout;
    QPlainTextEdit m_mx_text_edit;
    //! Existing buffers
    std::map<std::filesystem::path, std::shared_ptr<Buffer>> m_buffers;
    //! Buffer actions
    std::map<std::filesystem::path, std::unique_ptr<BufferActions>> m_buffer_actions;

    const Options& m_args;

    void
    setupUI();

    void
    loadBuffers();

    void loadModes(std::shared_ptr<Buffer> parent_buffer);


  public:
    K(QWidget* parent, const Options& options);
  };
}
#endif // BEE_HPP
