#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QVariantMap>
#include <QQmlApplicationEngine>
#include "iservice.h"
class FarmersFridgeClient;
class EventWatcher;
class CartModel;
class TableModel;
class ColorModel;
class MessageModel;

class Controller : public QObject, public IService
{
    Q_OBJECT
    Q_PROPERTY(QString currentNetworkIP READ currentNetworkIP WRITE setCurrentNetworkIP NOTIFY currentNetworkIPChanged)
    Q_PROPERTY(QObject *cartModel READ cartModel NOTIFY cartModelChanged)
    Q_PROPERTY(QString currentCategory READ currentCategory WRITE setCurrentCategory NOTIFY currentCategoryChanged)
    Q_PROPERTY(QString currentFilter READ currentFilter WRITE setCurrentFilter NOTIFY currentFilterChanged)
    Q_PROPERTY(QStringList saladAssets READ saladAssets NOTIFY saladAssetsChanged)
    Q_PROPERTY(QString offLinePath READ offLinePath NOTIFY offLinePathChanged)

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

    // Set item count:
    Q_INVOKABLE void setItemCount(int count, const QString &vendItemName);

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

    // To local file:
    Q_INVOKABLE QString toLocalFile(const QString &filePath);

    // From local file:
    Q_INVOKABLE QString fromLocalFile(const QString &filePath);

    // Set current menu item for category:
    Q_INVOKABLE void setCurrentMenuItemForCategory(const QVariant &menuItem);

    // Retur current menu item for category:
    Q_INVOKABLE QVariant getCurrentMenuItemForCategory(const QString &category);

    // Restore default settings:
    Q_INVOKABLE void restoreDefaultSettings();

    // Save settings:
    Q_INVOKABLE void saveSettings();

    // Return file base name:
    Q_INVOKABLE QString fileBaseName(const QString &sFullPath) const;

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

    // Read salad assets:
    void readSaladAssets();

    // Return current network IP:
    const QString &currentNetworkIP() const;

    // Set current network IP:
    void setCurrentNetworkIP(const QString &currentNetworkIP);

    // Return cart model:
    QObject *cartModel() const;

    // Return current category:
    const QString &currentCategory() const;

    // Set current category:
    void setCurrentCategory(const QString &categoryName);

    // Return current filter:
    const QString &currentFilter() const;

    // Set current filter:
    void setCurrentFilter(const QString &filterName);

    // Return offline path:
    const QString &offLinePath() const;

    // Use hard coded settings:
    void useHardCodedSettings();

    // Save download report:
    void saveDownloadReport();

private:
    // Salad assets:
    QStringList mSaladAssets;

    // QML application engine:
    QQmlApplicationEngine mEngine;

    // Farmers fridge client:
    FarmersFridgeClient *mFarmersClient;

    // Event watcher:
    EventWatcher *mEventWatcher;

    // Cart model:
    CartModel *mCartModel;

    // Table model:
    TableModel *mTableModel;

    // Color model:
    ColorModel *mColorModel;

    // Message model:
    MessageModel *mMessageModel;

    // Current category:
    QString mCurrentCategory;

    // Current filter:
    QString mCurrentFilter;

    // Current network IP:
    QString mCurrentNetworkIP;

    // Offline path:
    QString mOffLinePath;

    // Current item for category:
    QMap<QString, QVariant> mCurrentItemForCategory;

public slots:
    // Update colors:
    void onUpdateColors();

    // Data ready:
    void onDataReady();

signals:
    // Current network IP changed:
    void currentNetworkIPChanged();

    // Cart model changed:
    void cartModelChanged();

    // Current category changed:
    void currentCategoryChanged();

    // Current filter changed:
    void currentFilterChanged();

    // Salad assets changed:
    void saladAssetsChanged();

    // Off line path changed:
    void offLinePathChanged();

    // Current menu item for category changed:
    void currentMenuItemForCategoryChanged();
};

#endif // CONTROLLER_H
