#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <QElapsedTimer>
#include <QProcess>
#include <QTextEdit>

#include <QTimer>

class Console : public QTextEdit
{
    Q_OBJECT
public:
    Console(const QString &program, const QStringList &arguments = {},QWidget *parent = nullptr);
    void appendText(const QString &text);
    ~Console();
private:
    void handleProcessError(QProcess::ProcessError error);
private slots:
    void printTerminationResult(int exit_code, QProcess::ExitStatus status);
private:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
private:
    QString m_input;
    QProcess m_process;
    QElapsedTimer m_timer;
    bool m_finished;
    int m_reachable_pos;
    bool m_manually_terminated;
};

#endif // WIDGET_HPP
