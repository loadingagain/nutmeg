#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmlwindow.h"
#include <QQuickView>
#include <QSystemTrayIcon>
#include "src/server.h"

class Server;
class MainWindow : public QmlWindow
{
    Q_OBJECT
    Q_PROPERTY(Server* server READ server WRITE setServer NOTIFY serverChanged)
    Q_PROPERTY(QmlWindow* settingsWindow READ settingsWindow WRITE setSettingsWindow NOTIFY settingsWindowChanged)

public:
    explicit MainWindow(QUrl qmlSource, QWidget *parent = 0);

    Server* server() const;
    void setServer(Server* arg);

    QmlWindow* settingsWindow() const;
    void setSettingsWindow(QmlWindow *arg);

signals:
    void serverChanged(Server* arg);
    void settingsWindowChanged(QmlWindow* arg);

protected slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showSettings();

public slots:
    void notify(const QString &title, const QString &msg);

private:
    void createSystemTray();
    QSystemTrayIcon *m_trayIcon;

    Server* m_server;
    QmlWindow* m_settingsWindow;
};

#endif // MAINWINDOW_H
