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
    QString call_phone_answer;
    int voteA;
    int voteB;
    int voteC;
    int voteD;
    int correct_answer;
    int reward;
    static BackEnd *instance;
    Q_PROPERTY(QString user_name READ getUserName WRITE setUserName NOTIFY userNameChanged);
    Q_PROPERTY(QString enemy_name READ getEnemyName WRITE setEnemyName NOTIFY enemyNameChanged);
    Q_PROPERTY(int prize READ getPrize WRITE setPrize NOTIFY prizeChanged);
    Q_PROPERTY(QString question READ getQuestion NOTIFY questionChanged);
    Q_PROPERTY(QString a READ getA NOTIFY aChanged);
    Q_PROPERTY(QString b READ getB NOTIFY bChanged);
    Q_PROPERTY(QString c READ getC NOTIFY cChanged);
    Q_PROPERTY(QString d READ getD NOTIFY dChanged);
    Q_PROPERTY(QString call_phone_answer READ getCallPhoneAnswer NOTIFY callPhoneAnswerChanged);
    Q_PROPERTY(int voteA READ getVoteA NOTIFY voteAChanged);
    Q_PROPERTY(int voteB READ getVoteB NOTIFY voteBChanged);
    Q_PROPERTY(int voteC READ getVoteC NOTIFY voteCChanged);
    Q_PROPERTY(int voteD READ getVoteD NOTIFY voteDChanged);
    Q_PROPERTY(int correct_answer READ getCorrectAnswer);
    Q_PROPERTY(int reward READ getReward WRITE setReward NOTIFY rewardChanged);

    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd();
    QString getUserName() const;
    void setUserName(const QString &value);
    QString getEnemyName() const;
    void setEnemyName(const QString &value);
    int getPrize();
    void setPrize(int value);
    QString getQuestion();
    QString getA();
    QString getB();
    QString getC();
    QString getD();
    QString getCallPhoneAnswer();
    int getReward();
    void setReward(int value);
    int getCorrectAnswer();
    int getVoteA();
    int getVoteB();
    int getVoteC();
    int getVoteD();

    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void disconnectToServer();
    Q_INVOKABLE void signIn(QString username, QString password);
    Q_INVOKABLE void signUp(QString username, QString password);
    Q_INVOKABLE void logOut();
    Q_INVOKABLE void changePassword(QString newPassword);
    Q_INVOKABLE void playAlone();
    Q_INVOKABLE void choiceAnswer(int answer);
    Q_INVOKABLE void fiftyFifty();
    Q_INVOKABLE void callPhone();
    Q_INVOKABLE void vote();
    Q_INVOKABLE void changeQuestion();
    Q_INVOKABLE void stopGame();
    Q_INVOKABLE void overTime();
    Q_INVOKABLE void playPvP();

signals:
    void userNameChanged();
    void enemyNameChanged();
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
    void callPhoneAnswerChanged();
    void voteAChanged();
    void voteBChanged();
    void voteCChanged();
    void voteDChanged();
    void correctAnswer();
    void rewardChanged();
    void lose();
    void lose2();
    void foundPlayer();
    void openVote();
    void openCallPhone();

private:
    QString user_name;
    QString enemy_name;
};
#endif // BACKEND_H