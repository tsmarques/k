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
      m_central_widget(nullptr),
      m_layout(nullptr),
      m_buffers(),
      m_args(args)
  {
    setupUI();
  }

  K::~K()
  {
    Memory::clear(m_central_widget);
    Memory::clear(m_layout);
  }

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

    m_central_widget = new QWidget(this);
    m_central_widget->setObjectName(QString::fromUtf8("centralwidget"));
    QPalette pal = m_central_widget->palette();

    pal.setColor(QPalette::Window, QColor::fromRgb(46, 52, 64));
    m_central_widget->setAutoFillBackground(true);
    m_central_widget->setPalette(pal);

    m_layout = new QVBoxLayout(m_central_widget);
    m_layout->setObjectName(QString::fromUtf8("verticalLayout"));
    m_layout->setSpacing(0);

//    QPalette tab_palette = m_tab.palette();
////    tab_palette.setColor(QPalette::Window, QColor::fromRgb(46, 52, 64));
//    m_tab.setStyleSheet("QTabWidget::pane { border: 0; }");
////    tab->setAutoFillBackground(true);
//    m_tab.setPalette(tab_palette);
//
//    m_layout->addWidget(&m_tab);

    loadBuffers();

    m_mx_text_edit = new QPlainTextEdit(m_central_widget);
    m_mx_text_edit->setObjectName(QString::fromUtf8("m_mx_text_edit"));
    m_mx_text_edit->setMaximumSize(QSize(16777215, 25));
    m_mx_text_edit->setFocusPolicy(Qt::NoFocus);
    m_mx_text_edit->setUndoRedoEnabled(false);
    m_mx_text_edit->setLineWrapMode(QPlainTextEdit::NoWrap);
    m_mx_text_edit->setReadOnly(true);
    m_mx_text_edit->setPlainText(QString::fromUtf8(">= "));
    m_mx_text_edit->setFrameStyle(QFrame::NoFrame);
    m_mx_text_edit->setVisible(false);

    m_layout->addWidget(m_mx_text_edit);
    this->setCentralWidget(m_central_widget);

    setWindowTitle(QCoreApplication::translate("K", "K [] -", nullptr));

    QMetaObject::connectSlotsByName(this);
  }

  void
  K::loadBuffers()
  {
    setWindowTitle(QString::fromUtf8(">= "));
    fs::path home = fs::path(getenv("HOME"));
    std::filesystem::path greet_path(home / ".k-editor/greet.txt");

    std::ifstream ifs(greet_path);
    std::string content( (std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()));

    klog(content);

    m_buffers[greet_path] = std::make_shared<Buffer>(m_central_widget);
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
        auto text_bfr = std::make_shared<Buffer>(m_central_widget);
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
    m_layout->addWidget(bfr_to_display.get());
    setWindowTitle(QString::fromUtf8(std::string("K[ " + window_title + " ]").c_str()));
  }
}