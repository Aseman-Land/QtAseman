#ifndef ASEMANOBJECTIVECLAYER_H
#define ASEMANOBJECTIVECLAYER_H

#include <QString>
#include <QVariantList>
#include <QObject>

#include <functional>

class AsemanObjectiveCLayer: public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal keyboardHeight READ keyboardHeight WRITE setKeyboardHeight NOTIFY keyboardHeightChanged)
public:
    AsemanObjectiveCLayer(QObject *parent = nullptr);
    virtual ~AsemanObjectiveCLayer();

    static qreal statusBarHeight();
    static qreal navigationBarHeight();
    static bool saveToCameraRoll(const QString &filePath);
    static void getContactList(std::function<void(const QVariantList &res)> asyncCallback = Q_NULLPTR);
    static void sharePaper(const QString &text);
    static QString deviceId();
    static bool openUrlInSafari(const QString &str);
    static void triggerVibrateFeedback();

    static bool hasBiometric();
    static bool biometricCheck();

    qreal keyboardHeight() const;
    void setKeyboardHeight(const qreal &keyboardHeight);

Q_SIGNALS:
    void keyboardHeightChanged();

private:
    qreal mKeyboardHeight = 0;
};

typedef AsemanObjectiveCLayer QAsemanObjectiveCLayer;

#endif // ASEMANOBJECTIVECLAYER_H
