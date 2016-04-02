#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QVariantMap>
#include <QQmlApplicationEngine>
#include "iservice.h"
class EventWatcher;
class CartModel;

class Controller : public QObject, public IService
{
    Q_OBJECT
    Q_PROPERTY(QString currentRoute READ currentRoute NOTIFY currentRouteChanged)
    Q_PROPERTY(QString currentIP READ currentIP NOTIFY currentIPChanged)
    Q_PROPERTY(QObject *cartModel READ cartModel NOTIFY cartModelChanged)
    Q_PROPERTY(QString currentCategory READ currentCategory WRITE setCurrentCategory NOTIFY currentCategoryChanged)
    Q_PROPERTY(QStringList saladAssets READ saladAssets NOTIFY saladAssetsChanged)

public:
    friend class MenuViewer;

    // Destructor:
    virtual ~Controller();

    // Startup:
    virtual bool startup();

    // Shutdown:
    virtual void shutdown();

    // Return salad assets:
    const QStringList &saladAssets() const;

    // Increment item count:
    Q_INVOKABLE void incrementItemCount(const QString &vendItemName);

    // Decrement item count:
    Q_INVOKABLE void decrementItemCount(const QString &vendItemName);

    // Add item:
    Q_INVOKABLE void addItem(const QString &vendItemName, const QString &icon,
        const QString &nutrition, const QString &category, const QString &price);

    // Remove item:
    Q_INVOKABLE void removeItem(const QString &vendItemName);

    // Clear cart:
    Q_INVOKABLE void clearCart();

    // Validate email address:
    Q_INVOKABLE bool validateEmailAddress(const QString &emailAddress);

    // Validate coupon:
    Q_INVOKABLE bool validateCoupon(const QString &coupon);

protected:
    // Constructor:
    explicit Controller(QObject *parent = 0);

private:
    // Register types:
    void registerTypes();

    // Set context properties:
    void setContextProperties();

    // Start GUI:
    void startGUI();

    // Load application parameters:
    void loadApplicationParameters();

    // Save application parameters:
    void saveApplicationParameters();

    // Set default parameters:
    void setDefaultParameters();

    // Read salad assets:
    void readSaladAssets();

    // Return current route:
    QString currentRoute() const;

    // Return current IP:
    QString currentIP() const;

    // Return cart model:
    QObject *cartModel() const;

    // Return current category:
    const QString &currentCategory() const;

    // Set current category:
    void setCurrentCategory(const QString &categoryName);

private:
    // Application keys:
    QStringList mAppKeys;

    // Application parameters:
    QVariantMap mAppParameters;

    // Salad assets:
    QStringList mSaladAssets;

    // QML application engine:
    QQmlApplicationEngine mEngine;

    // Event watcher:
    EventWatcher *mEventWatcher;

    // Cart model:
    CartModel *mCartModel;

    // Current category:
    QString mCurrentCategory;

signals:
    // Current route changed:
    void currentRouteChanged();

    // Current IP changed:
    void currentIPChanged();

    // Cart model changed:
    void cartModelChanged();

    // Current category changed:
    void currentCategoryChanged();

    // Salad assets changed:
    void saladAssetsChanged();
};

#endif // CONTROLLER_H
