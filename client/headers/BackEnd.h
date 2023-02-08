#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>
#include <string>

extern "C" {
  #include "Utils.h"
}

class BackEnd : public QObject
{
    Q_OBJECT
public:
    static std::string server_ip;
    static int server_port;
    Q_PROPERTY(QString user_name READ getUserName WRITE setUserName NOTIFY userNameChanged)
    explicit BackEnd(QObject *parent = nullptr);
    QString getUserName() const;
    void setUserName(const QString &value);
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void disconnectToServer();
    Q_INVOKABLE void signIn(QString username, QString password);
    Q_INVOKABLE void signUp(QString username, QString password);
    Q_INVOKABLE void logOut();
    Q_INVOKABLE void changePassword(QString newPassword);

signals:
    void userNameChanged();
    void connectSuccess();
    void connectFail();
    void loginSuccess();
    void loggedIn();
    void accountBlocked();
    void accountNotExist();
    void wrongPassword();
    void signupSuccess();
    void accountExist();
    void changePasswordSuccess();
    void sameOldPassword();
private:
    QString user_name;
};
#endif // BACKEND_H