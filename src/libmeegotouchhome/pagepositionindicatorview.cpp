/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libmeegotouch.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include "pagepositionindicatorview.h"

#include <MScalableImage>
#include "pagepositionindicator.h"
#include "pagepositionindicatormodel.h"

#include <QDebug>

PagePositionIndicatorView::PagePositionIndicatorView(PagePositionIndicator *controller) :
    MWidgetView(controller)
{
}

PagePositionIndicatorView::~PagePositionIndicatorView()
{
}

void PagePositionIndicatorView::updateData(const QList<const char *>& modifications)
{
    MWidgetView::updateData(modifications);

    const char *member;
    foreach(member, modifications) {
        if (member == PagePositionIndicatorModel::FocusedPage
            || member == PagePositionIndicatorModel::PageCount) {
            update();
        }
    }
}

void PagePositionIndicatorView::drawContents(QPainter *painter, const QStyleOptionGraphicsItem *option) const
{
    Q_UNUSED(option);

    int pageCount = model()->pageCount();

    if (pageCount > 1) {
        int focusedPage = model()->focusedPage();
        int viewCenter = size().width() / 2;

        const MScalableImage *focusedIcon = style()->focusedIndicatorImage();
        const MScalableImage *unfocusedIcon = style()->unfocusedIndicatorImage();

        int iconWidth = style()->iconSize().width();
        int iconHeight = style()->iconSize().height();

        int indicatorBarWidth = iconWidth * pageCount + style()->spacing() * (pageCount - 1);

        int indicatorBarYpos = 0;
        // center the indicator bar in viewport
        int indicatorBarXpos = viewCenter - (indicatorBarWidth / 2);

        int iconPositionInIndicatorBar = indicatorBarXpos;
        for (int i = 0; i < pageCount; i++) {
            if (focusedPage == i) {
                focusedIcon->draw(iconPositionInIndicatorBar, indicatorBarYpos, iconWidth, iconHeight, painter);
            } else {
                unfocusedIcon->draw(iconPositionInIndicatorBar, indicatorBarYpos, iconWidth, iconHeight, painter);
            }
            iconPositionInIndicatorBar += iconWidth + style()->spacing();
        }
    }
}

M_REGISTER_VIEW_NEW(PagePositionIndicatorView, PagePositionIndicator)