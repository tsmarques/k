#include "K.hpp"
#include "KLog.hpp"
#include "Memory.hpp"
#include "TabWidget.hpp"
#include <QtCore/QCoreApplication>
#include <fstream>
#include <iostream>

namespace K
{
  K::K(QWidget* parent, const Options& args) :
      QMainWindow(parent),
      m_central_widget(this),
      m_layout(&m_central_widget),
      m_mx_text_edit(&m_central_widget),
      m_buffers(),
      m_args(args)
  {
    setupUI();
  }

  K::~K()
  { }

  void
  K::setupUI()
  {
    if (this->objectName().isEmpty())
      this->setObjectName(QString::fromUtf8("K"));
    this->resize(800, 600);

    // @fixme not working
//    QPalette main_p = this->palette();
//    main_p.setColor(QPalette::Base, QColor::fromRgb(46, 52, 64));
//    this->setPalette(main_p);
//    this->setAutoFillBackground(true);

    m_central_widget.setObjectName(QString::fromUtf8("centralwidget"));
    QPalette pal = m_central_widget.palette();

    pal.setColor(QPalette::Window, QColor::fromRgb(46, 52, 64));
    m_central_widget.setAutoFillBackground(true);
    m_central_widget.setPalette(pal);

    m_layout.setObjectName(QString::fromUtf8("verticalLayout"));
    m_layout.setSpacing(0);

//    QPalette tab_palette = m_tab.palette();
////    tab_palette.setColor(QPalette::Window, QColor::fromRgb(46, 52, 64));
//    m_tab.setStyleSheet("QTabWidget::pane { border: 0; }");
////    tab->setAutoFillBackground(true);
//    m_tab.setPalette(tab_palette);
//
//    m_layout->addWidget(&m_tab);

    loadBuffers();

    m_mx_text_edit.setWindowTitle(QString::fromUtf8("m-x"));
    m_mx_text_edit.setObjectName(QString::fromUtf8("m_mx_text_edit"));
    m_mx_text_edit.setMaximumSize(QSize(16777215, 30));
    m_mx_text_edit.setUndoRedoEnabled(false);
    m_mx_text_edit.setLineWrapMode(QPlainTextEdit::NoWrap);
    m_mx_text_edit.setPlainText(QString::fromUtf8("> "));
    m_mx_text_edit.setVisible(true);

    QPalette p = m_mx_text_edit.palette();
    p.setColor(QPalette::Base, QColor::fromRgb(46, 52, 64));
    p.setColor(QPalette::Text, QColor::fromRgb(216, 222, 233));
    m_mx_text_edit.setPalette(p);
//
    m_layout.addWidget(&m_mx_text_edit);
    this->setCentralWidget(&m_central_widget);

    setWindowTitle(QCoreApplication::translate("K", "K [] -", nullptr));

    QMetaObject::connectSlotsByName(this);
  }

  void
  K::loadBuffers()
  {
    fs::path home = fs::path(getenv("HOME"));
    std::filesystem::path greet_path(home / ".k-editor/greet.txt");

    std::ifstream ifs(greet_path);
    std::string content( (std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()));

    klog(content);

    m_buffers[greet_path] = std::make_shared<Buffer>();
    m_buffers[greet_path]->setPlainText(QString::fromUtf8(content.c_str()));

    auto bfr_to_display = m_buffers[greet_path];

    std::string window_title;
    if (!m_args.m_files_list.has_value())
      window_title = greet_path.c_str();
    else
    {
      bool first = true;
      for (auto& file_path : m_args.m_files_list.value())
      {
        if (!std::filesystem::exists(file_path))
        {
          klog("can't find ", file_path);
          continue;
        }

        if (std::filesystem::is_directory(file_path))
        {
          klog("can't open directories : ", file_path);
          continue;
        }

        auto text_bfr = std::make_shared<Buffer>();
        std::ifstream f_in(file_path);
        std::string f_content( (std::istreambuf_iterator<char>(f_in)),
                               (std::istreambuf_iterator<char>()));

        text_bfr->setPlainText(QString::fromUtf8(f_content.c_str()));
        m_buffers[file_path] = text_bfr;

        if (first)
        {
          first = false;
          bfr_to_display = text_bfr;
          window_title = file_path;
        }
      }
    }

    // meh
    bfr_to_display->setParent(&m_central_widget);
    m_layout.addWidget(bfr_to_display.get());
    setWindowTitle(QString::fromUtf8(std::string("K[ " + window_title + " ]").c_str()));
  }
}