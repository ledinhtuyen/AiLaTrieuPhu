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
    int prize;
    QString question;
    QString a;
    QString b;
    QString c;
    QString d;
    static BackEnd *instance;
    Q_PROPERTY(QString user_name READ getUserName WRITE setUserName NOTIFY userNameChanged);
    Q_PROPERTY(int prize READ getPrize NOTIFY prizeChanged);
    Q_PROPERTY(QString question READ getQuestion NOTIFY questionChanged);
    Q_PROPERTY(QString a READ getA NOTIFY aChanged);
    Q_PROPERTY(QString b READ getB NOTIFY bChanged);
    Q_PROPERTY(QString c READ getC NOTIFY cChanged);
    Q_PROPERTY(QString d READ getD NOTIFY dChanged);
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd();
    QString getUserName() const;
    void setUserName(const QString &value);
    int getPrize();
    QString getQuestion();
    QString getA();
    QString getB();
    QString getC();
    QString getD();
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void disconnectToServer();
    Q_INVOKABLE void signIn(QString username, QString password);
    Q_INVOKABLE void signUp(QString username, QString password);
    Q_INVOKABLE void logOut();
    Q_INVOKABLE void changePassword(QString newPassword);
    Q_INVOKABLE void playAlone();
    Q_INVOKABLE void choiceAnswer(int answer);

signals:
    void userNameChanged();
    void prizeChanged();
    void questionChanged();
    void aChanged();
    void bChanged();
    void cChanged();
    void dChanged();
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