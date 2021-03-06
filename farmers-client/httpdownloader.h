#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

// Application:
#include "httpworker.h"

// Qt:
#include <QObject>
#include <QDir>

class HttpDownLoader : public QObject
{
    Q_OBJECT

public:
    friend class FarmersFridgeClient;

    // Destructor:
    ~HttpDownLoader();

    // Download:
    Q_INVOKABLE void download();

    // Download:
    void download(const QUrl &uRemoteUrl, const QDir &dstDir, const QString &x_api_key="", const HttpWorker::RequestType &requestType=HttpWorker::GET);

    // Return dst dir:
    const QDir &dstDir() const;

    // Return url:
    const QUrl &remoteUrl() const;

    // Return local file path:
    const QString &localFilePath() const;

    // Set local file path:
    void setLocalFilePath(const QString &sLocalFilePath);

    // Return header info:
    const QVariantMap &headerInfo() const;

    // Return reply:
    const QByteArray &reply() const;

    // Get header info:
    QString getHeaderInfo(const QString &sKey) const;

protected:
    // Default constructor:
    HttpDownLoader(QObject *parent=0);

private:
    // Interface:
    QDir m_dstDir;
    QUrl m_uRemoteUrl;
    QString m_x_api_key;
    QString m_sLocalFilePath;
    QVariantMap m_mHeaderInfo;
    HttpWorker::RequestType m_requestType;
    QByteArray m_bReply;

public slots:
    // Data downloaded:
    void onFinished();

signals:
    // Data ready:
    void ready();

    // Time out:
    void timeOut();
};

#endif // HTTPDOWNLOADER_H
