//**************************************************************************************************
// Copyright (C) 2020 OceanScan - Marine Systems & Technology, Lda.                                *
//**************************************************************************************************
//                                                                                                 *
// All information contained herein is, and remains the property of OceanScan - Marine             *
// Systems & Technology, Lda. Dissemination of this information or reproduction of this material   *
// is strictly forbidden unless prior written permission is obtained from OceanScan - Marine       *
// Systems & Technology, Lda.                                                                      *
//                                                                                                 *
// This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part   *
// of this source code package.                                                                    *
//                                                                                                 *
//**************************************************************************************************

#ifndef CASSINI_TABWIDGET_HPP
#define CASSINI_TABWIDGET_HPP

#include "TabBar.hpp"
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
namespace K
{
  class TabWidget :
      public QTabWidget
  {
    TabBar* mTabBar;

  public:
    explicit TabWidget(QWidget* parent = nullptr) :
        QTabWidget(parent)
    {
      mTabBar = new TabBar;
      setTabBar(mTabBar);
    }
  };
}
#endif
