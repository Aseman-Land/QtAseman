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

#include "qquickiosstyleripple_p.h"

#include <QtCore/qmath.h>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qsgadaptationlayer_p.h>
#include <QtQuickControls2/private/qquickanimatednode_p.h>
#include <QtQuickTemplates2/private/qquickabstractbutton_p.h>
#include <QtQuickTemplates2/private/qquickabstractbutton_p_p.h>

QT_BEGIN_NAMESPACE

namespace {
    enum WavePhase { WaveEnter, WaveExit };
}

static const int RIPPLE_ENTER_DELAY = 80;
static const int OPACITY_ENTER_DURATION_FAST = 120;
static const int WAVE_OPACITY_DECAY_DURATION = 333;
static const qreal WAVE_TOUCH_DOWN_ACCELERATION = 1024.0;

class QQuickIOSStyleRippleWaveNode : public QQuickAnimatedNode
{
public:
    QQuickIOSStyleRippleWaveNode(QQuickIOSStyleRipple *ripple);

    void exit();
    void updateCurrentTime(int time) override;
    void sync(QQuickItem *item) override;

private:
    qreal m_from = 0;
    qreal m_to = 0;
    qreal m_value = 0;
    WavePhase m_phase = WaveEnter;
    QPointF m_anchor;
    QRectF m_bounds;
};

QQuickIOSStyleRippleWaveNode::QQuickIOSStyleRippleWaveNode(QQuickIOSStyleRipple *ripple)
    : QQuickAnimatedNode(ripple)
{
    start(qRound(1000.0 * qSqrt(ripple->diameter() / 2.0 / WAVE_TOUCH_DOWN_ACCELERATION)));

    QSGOpacityNode *opacityNode = new QSGOpacityNode;
    appendChildNode(opacityNode);

    QQuickItemPrivate *d = QQuickItemPrivate::get(ripple);
    QSGInternalRectangleNode *rectNode = d->sceneGraphContext()->createInternalRectangleNode();
    rectNode->setAntialiasing(true);
    opacityNode->appendChildNode(rectNode);
}

void QQuickIOSStyleRippleWaveNode::exit()
{
    m_phase = WaveExit;
    m_from = m_value;
    setDuration(WAVE_OPACITY_DECAY_DURATION);
    restart();
    connect(this, &QQuickAnimatedNode::stopped, this, &QObject::deleteLater);
}

void QQuickIOSStyleRippleWaveNode::updateCurrentTime(int time)
{
    qreal p = 1.0;
    if (duration() > 0)
        p = time / static_cast<qreal>(duration());

    m_value = m_from + (m_to - m_from) * p;
    p = m_value / m_to;

    const qreal dx = (1.0 - p) * (m_anchor.x() - m_bounds.width() / 2);
    const qreal dy = (1.0 - p) * (m_anchor.y() - m_bounds.height() / 2);

    QMatrix4x4 m;
    m.translate(qRound((m_bounds.width() - m_value) / 2 + dx),
                qRound((m_bounds.height() - m_value) / 2 + dy));
    setMatrix(m);

    QSGOpacityNode *opacityNode = static_cast<QSGOpacityNode *>(firstChild());
    Q_ASSERT(opacityNode->type() == QSGNode::OpacityNodeType);
    qreal opacity = 1.0;
    if (m_phase == WaveExit)
        opacity -= static_cast<qreal>(time) / WAVE_OPACITY_DECAY_DURATION;
    opacityNode->setOpacity(opacity);

    QSGInternalRectangleNode *rectNode = static_cast<QSGInternalRectangleNode *>(opacityNode->firstChild());
    Q_ASSERT(rectNode->type() == QSGNode::GeometryNodeType);
    rectNode->setRect(QRectF(0, 0, m_value, m_value));
    rectNode->setRadius(m_value / 2);
    rectNode->update();
}

void QQuickIOSStyleRippleWaveNode::sync(QQuickItem *item)
{
    QQuickIOSStyleRipple *ripple = static_cast<QQuickIOSStyleRipple *>(item);
    m_to = ripple->diameter();
    m_anchor = ripple->anchorPoint();
    m_bounds = ripple->boundingRect();

    QSGOpacityNode *opacityNode = static_cast<QSGOpacityNode *>(firstChild());
    Q_ASSERT(opacityNode->type() == QSGNode::OpacityNodeType);

    QSGInternalRectangleNode *rectNode = static_cast<QSGInternalRectangleNode *>(opacityNode->firstChild());
    Q_ASSERT(rectNode->type() == QSGNode::GeometryNodeType);
    rectNode->setColor(ripple->color());
}

class QQuickIOSStyleRippleBackgroundNode : public QQuickAnimatedNode
{
    Q_OBJECT

public:
    QQuickIOSStyleRippleBackgroundNode(QQuickIOSStyleRipple *ripple);

    void updateCurrentTime(int time) override;
    void sync(QQuickItem *item) override;

private:
    bool m_active = false;
};

QQuickIOSStyleRippleBackgroundNode::QQuickIOSStyleRippleBackgroundNode(QQuickIOSStyleRipple *ripple)
    : QQuickAnimatedNode(ripple)
{
    setDuration(OPACITY_ENTER_DURATION_FAST);

    QSGOpacityNode *opacityNode = new QSGOpacityNode;
    opacityNode->setOpacity(0.0);
    appendChildNode(opacityNode);

    QQuickItemPrivate *d = QQuickItemPrivate::get(ripple);
    QSGInternalRectangleNode *rectNode = d->sceneGraphContext()->createInternalRectangleNode();
    rectNode->setAntialiasing(true);
    opacityNode->appendChildNode(rectNode);
}

void QQuickIOSStyleRippleBackgroundNode::updateCurrentTime(int time)
{
    qreal opacity = time / static_cast<qreal>(duration());
    if (!m_active)
        opacity = 1.0 - opacity;

    QSGOpacityNode *opacityNode = static_cast<QSGOpacityNode *>(firstChild());
    Q_ASSERT(opacityNode->type() == QSGNode::OpacityNodeType);
    opacityNode->setOpacity(opacity);
}

void QQuickIOSStyleRippleBackgroundNode::sync(QQuickItem *item)
{
    QQuickIOSStyleRipple *ripple = static_cast<QQuickIOSStyleRipple *>(item);
    if (m_active != ripple->isActive()) {
        m_active = ripple->isActive();
        setDuration(m_active ? OPACITY_ENTER_DURATION_FAST : WAVE_OPACITY_DECAY_DURATION);
        restart();
    }

    QSGOpacityNode *opacityNode = static_cast<QSGOpacityNode *>(firstChild());
    Q_ASSERT(opacityNode->type() == QSGNode::OpacityNodeType);

    QSGInternalRectangleNode *rectNode = static_cast<QSGInternalRectangleNode *>(opacityNode->firstChild());
    Q_ASSERT(rectNode->type() == QSGNode::GeometryNodeType);

    const qreal w = ripple->width();
    const qreal h = ripple->height();
    const qreal sz = qSqrt(w * w + h * h);

    QMatrix4x4 matrix;
    if (qFuzzyIsNull(ripple->clipRadius())) {
        matrix.translate(qRound((w - sz) / 2), qRound((h - sz) / 2));
        rectNode->setRect(QRectF(0, 0, sz, sz));
        rectNode->setRadius(sz / 2);
    } else {
        rectNode->setRect(QRectF(0, 0, w, h));
        rectNode->setRadius(ripple->clipRadius());
    }

    setMatrix(matrix);
    rectNode->setColor(ripple->color());
    rectNode->update();
}

QQuickIOSStyleRipple::QQuickIOSStyleRipple(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents);
}

bool QQuickIOSStyleRipple::isActive() const
{
    return m_active;
}

void QQuickIOSStyleRipple::setActive(bool active)
{
    if (active == m_active)
        return;

    m_active = active;
    update();
}

QColor QQuickIOSStyleRipple::color() const
{
    return m_color;
}

void QQuickIOSStyleRipple::setColor(const QColor &color)
{
    if (m_color == color)
        return;

    m_color = color;
    update();
}

qreal QQuickIOSStyleRipple::clipRadius() const
{
    return m_clipRadius;
}

void QQuickIOSStyleRipple::setClipRadius(qreal radius)
{
    if (qFuzzyCompare(m_clipRadius, radius))
        return;

    m_clipRadius = radius;
    setClip(!qFuzzyIsNull(radius));
    update();
}

bool QQuickIOSStyleRipple::isPressed() const
{
    return m_pressed;
}

void QQuickIOSStyleRipple::setPressed(bool pressed)
{
    if (pressed == m_pressed)
        return;

    m_pressed = pressed;

    if (!isEnabled()) {
        exitWave();
        return;
    }

    if (pressed) {
        if (m_trigger == Press)
            prepareWave();
        else
            exitWave();
    } else {
        if (m_trigger == Release)
            enterWave();
        else
            exitWave();
    }
}

QQuickIOSStyleRipple::Trigger QQuickIOSStyleRipple::trigger() const
{
    return m_trigger;
}

void QQuickIOSStyleRipple::setTrigger(Trigger trigger)
{
    m_trigger = trigger;
}

QPointF QQuickIOSStyleRipple::anchorPoint() const
{
    const QRectF bounds = boundingRect();
    const QPointF center = bounds.center();
    if (!m_anchor)
        return center;

    QPointF anchorPoint = bounds.center();
    if (QQuickAbstractButton *button = qobject_cast<QQuickAbstractButton *>(m_anchor))
        anchorPoint = QQuickAbstractButtonPrivate::get(button)->pressPoint;
    anchorPoint = mapFromItem(m_anchor, anchorPoint);

    // calculate whether the anchor point is within the ripple circle bounds,
    // that is, whether waves should start expanding from the anchor point
    const qreal r = qSqrt(bounds.width() * bounds.width() + bounds.height() * bounds.height()) / 2;
    if (QLineF(center, anchorPoint).length() < r)
        return anchorPoint;

    // if the anchor point is outside the ripple circle bounds, start expanding
    // from the intersection point of the ripple circle and a line from its center
    // to the the anchor point
    const qreal p = qAtan2(anchorPoint.y() - center.y(), anchorPoint.x() - center.x());
    return QPointF(center.x() + r * qCos(p), center.y() + r * qSin(p));
}

QQuickItem *QQuickIOSStyleRipple::anchor() const
{
    return m_anchor;
}

void QQuickIOSStyleRipple::setAnchor(QQuickItem *item)
{
    m_anchor = item;
}

qreal QQuickIOSStyleRipple::diameter() const
{
    const qreal w = width();
    const qreal h = height();
    return qSqrt(w * w + h * h);
}

void QQuickIOSStyleRipple::itemChange(ItemChange change, const ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);
}

QSGNode *QQuickIOSStyleRipple::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QQuickItemPrivate *d = QQuickItemPrivate::get(this);
    QQuickDefaultClipNode *clipNode = d->clipNode();
    if (clipNode) {
        // TODO: QTBUG-51894
        // clipNode->setRadius(m_clipRadius);
        clipNode->setRect(boundingRect());
        clipNode->update();
    }

    QSGNode *container = oldNode;
    if (!container)
        container = new QSGNode;

    QQuickIOSStyleRippleBackgroundNode *backgroundNode = static_cast<QQuickIOSStyleRippleBackgroundNode *>(container->firstChild());
    if (!backgroundNode) {
        backgroundNode = new QQuickIOSStyleRippleBackgroundNode(this);
        backgroundNode->setObjectName(objectName());
        container->appendChildNode(backgroundNode);
    }
    backgroundNode->sync(this);

    // enter new waves
    int i = m_waves;
    QQuickIOSStyleRippleWaveNode *enterNode = static_cast<QQuickIOSStyleRippleWaveNode *>(backgroundNode->nextSibling());
    while (i-- > 0) {
        if (!enterNode) {
            enterNode = new QQuickIOSStyleRippleWaveNode(this);
            container->appendChildNode(enterNode);
        }
        enterNode->sync(this);
        enterNode = static_cast<QQuickIOSStyleRippleWaveNode *>(enterNode->nextSibling());
    }

    // exit old waves
    int j = container->childCount() - 1 - m_waves;
    while (j-- > 0) {
        QQuickIOSStyleRippleWaveNode *exitNode = static_cast<QQuickIOSStyleRippleWaveNode *>(backgroundNode->nextSibling());
        if (exitNode) {
            exitNode->exit();
            exitNode->sync(this);
        }
    }

    return container;
}

void QQuickIOSStyleRipple::timerEvent(QTimerEvent *event)
{
    QQuickItem::timerEvent(event);

    if (event->timerId() == m_enterDelay)
        enterWave();
}

void QQuickIOSStyleRipple::prepareWave()
{
    if (m_enterDelay <= 0)
        m_enterDelay = startTimer(RIPPLE_ENTER_DELAY);
}

void QQuickIOSStyleRipple::enterWave()
{
    if (m_enterDelay > 0) {
        killTimer(m_enterDelay);
        m_enterDelay = 0;
    }

    ++m_waves;
    update();
}

void QQuickIOSStyleRipple::exitWave()
{
    if (m_enterDelay > 0) {
        killTimer(m_enterDelay);
        m_enterDelay = 0;
    }

    if (m_waves > 0) {
        --m_waves;
        update();
    }
}

QT_END_NAMESPACE

#include "qquickiosstyleripple.moc"
