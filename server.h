#ifndef SERVER_H
#define SERVER_H

#include <nzmqt/nzmqt.hpp>

#include <QQuickItem>
#include <QByteArray>
#include <QThread>
#include <QQueue>

#include <stdexcept>

using namespace nzmqt;

class Server : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString updateAddress READ updateAddress WRITE setUpdateAddress NOTIFY updateAddressChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

public:
    explicit Server(QQuickItem* parent = 0);

    static QString adjustPath(const QString &path);

    // Property accessors
    QString address() const;
    void setAddress(QString arg);
    bool running() const;


    QString updateAddress() const;
    void setUpdateAddress(QString arg);

signals:
//    void requestReceived(const QString &request);
    void requestReceived(QVariant request);
    void replySent(const QList<QByteArray>& reply);
    void updateSent(const QList<QByteArray>& update);
    void failure(const QString& tag);
    void finished();
    void createFigure(const QString &handle, const QString &qml);

    // Properties
    void addressChanged(QString arg);
    void runningChanged(bool arg);

    void updateAddressChanged(QString arg);

public slots:
    void processRequest(const QList<QByteArray>& request);
    void updateRequest(const QList<QByteArray>& request);
    void sendReply(QVariant reply);
    void parameterChanged(QString figurehandle, QString parameter, QVariant update);
    void parameterUpdated(QString figureHandle, QString parameter);
    void start();
    void stop();

protected:
    static void sleep(unsigned long msecs);
    void setRunning(bool arg);
    void startServer();
    void sendUpdate(QVariant update);
    bool sendPendingUpdate();

private:
    // Allow sleeping
    class ThreadTools : private QThread
    {
    public:
        using QThread::msleep;

    private:
        ThreadTools() {}
    };


    ZMQSocket* m_socket;
    ZMQSocket* m_updateSocket;
    QMap<QString, QVariant> m_updateMap;
    QList<QString> m_updatesToSend;
    QList<QString> m_updatesToReceive;
    bool m_updateReady;

    // Properties
    QString m_address;
    bool m_running;

//    static ZMQContext* m_context;

    QString m_updateAddress;
};

#endif // SERVER_H