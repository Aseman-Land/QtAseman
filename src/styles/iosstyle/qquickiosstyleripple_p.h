/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKIOSSTYLERIPPLE_P_H
#define QQUICKIOSSTYLERIPPLE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQuick/qquickitem.h>
#include <QtGui/qcolor.h>

QT_BEGIN_NAMESPACE

class QQuickIOSStyleRipple : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL)
    Q_PROPERTY(qreal clipRadius READ clipRadius WRITE setClipRadius FINAL)
    Q_PROPERTY(bool pressed READ isPressed WRITE setPressed FINAL)
    Q_PROPERTY(bool active READ isActive WRITE setActive FINAL)
    Q_PROPERTY(QQuickItem *anchor READ anchor WRITE setAnchor FINAL)
    Q_PROPERTY(Trigger trigger READ trigger WRITE setTrigger FINAL)

public:
    QQuickIOSStyleRipple(QQuickItem *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    qreal clipRadius() const;
    void setClipRadius(qreal radius);

    bool isActive() const;
    void setActive(bool active);

    bool isPressed() const;
    void setPressed(bool pressed);

    enum Trigger { Press, Release };
    Q_ENUM (Trigger)

    Trigger trigger() const;
    void setTrigger(Trigger trigger);

    QPointF anchorPoint() const;

    QQuickItem *anchor() const;
    void setAnchor(QQuickItem *anchor);

    qreal diameter() const;

protected:
    void itemChange(ItemChange change, const ItemChangeData &data) override;
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
    void timerEvent(QTimerEvent *event) override;

    void prepareWave();
    void enterWave();
    void exitWave();

private:
    bool m_active = false;
    bool m_pressed = false;
    int m_waves = 0;
    int m_enterDelay = 0;
    Trigger m_trigger = Press;
    qreal m_clipRadius = 0.0;
    QColor m_color;
    QQuickItem *m_anchor = nullptr;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickIOSStyleRipple)

#endif // QQUICKIOSSTYLERIPPLE_P_H
