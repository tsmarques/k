#include "K.hpp"
#include "KLog.hpp"
#include "Memory.hpp"
#include "TabWidget.hpp"
#include <QtCore/QCoreApplication>
#include <fstream>
#include <iostream>

namespace K
{
  K::K(QWidget* parent, const Arguments& args) :
      QMainWindow(parent),
      m_central_widget(nullptr),
      m_layout(nullptr),
      m_text_edit(nullptr),
      m_tab(),
      m_args(args)
  {
    setupUI();
    loadFiles();
  }

  K::~K()
  {
    Memory::clear(m_central_widget);
    Memory::clear(m_layout);
    Memory::clear(m_text_edit);
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

    QPalette tab_palette = m_tab.palette();
//    tab_palette.setColor(QPalette::Window, QColor::fromRgb(46, 52, 64));
    m_tab.setStyleSheet("QTabWidget::pane { border: 0; }");
//    tab->setAutoFillBackground(true);
    m_tab.setPalette(tab_palette);

    m_layout->addWidget(&m_tab);

    m_text_edit = new Buffer(m_central_widget);
    m_text_edit->setObjectName(QString::fromUtf8("m_text_edit"));
//    m_text_edit->setFrameStyle(QFrame::NoFrame);
    m_layout->addWidget(m_text_edit);
    QPalette p = m_text_edit->palette();
    p.setColor(QPalette::Base, QColor::fromRgb(46, 52, 64));
    p.setColor(QPalette::Text, QColor::fromRgb(216, 222, 233));
    m_text_edit->setPalette(p);

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
  K::loadFiles()
  {
    setWindowTitle(QString::fromUtf8(">= "));
    fs::path home = fs::path(getenv("HOME"));
    std::filesystem::path path(home / ".k-editor/greet.txt");

    std::ifstream ifs(path);
    std::string content( (std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()));

    klog(content);

    std::string window_title = "K [" + m_args.m_curr_dir + "] - " + path.c_str();
    setWindowTitle(QString::fromUtf8(window_title.c_str()));
    m_text_edit->setPlainText(QString::fromUtf8(content.c_str()));

    m_tab.addTab(m_text_edit, path.filename().c_str());
    m_tab.addTab(new QWidget(), "Other");
  }
}