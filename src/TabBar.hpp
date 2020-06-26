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

#ifndef CASSINI_TABBAR_HPP
#define CASSINI_TABBAR_HPP

#include <QtWidgets/QStyleOptionTab>
#include <QtWidgets/QStylePainter>
#include <QtWidgets/QTabBar>

namespace K
{
  class TabBar : public QTabBar
  {
    QVector<int> unsaved;

  public:
    void
    setUnsaved(int index)
    {
      if (index >= count() || index < 0)
        return;
      unsaved << index;
      update();
    }
    void
    setSaved(int index)
    {
      if (!unsaved.contains(index))
        return;
      unsaved.remove(unsaved.indexOf(index));
      update();
    }

  protected:
    void
    paintEvent(QPaintEvent*) Q_DECL_OVERRIDE
    {
      QStylePainter painter(this);
      QStyleOptionTab opt;

      for (int i = 0; i < count(); i++)
      {
        initStyleOption(&opt, i);
        opt.palette.setColor(QPalette::Button, Qt::red);
        painter.save();
        if (unsaved.contains(i))
          painter.setFont(QFont("Source Code Pro", 10, QFont::Bold));

        painter.drawControl(QStyle::CE_TabBarTabShape, opt);
        painter.drawControl(QStyle::CE_TabBarTabLabel, opt);
        painter.restore();
      }
    }
  };
}

#endif
