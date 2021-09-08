#include "Console.hpp"
#include <QKeyEvent>
#include <QPushButton>

Console::Console(const QString &program, const QStringList &arguments, QWidget *parent)
    :
      QTextEdit(parent),
      m_finished(false)
{
    setStyleSheet("background-color:black;color:white;");
    setContextMenuPolicy(Qt::NoContextMenu);    //disable menu
    connect(&m_process,&QProcess::readyReadStandardOutput,[&](){
        appendText(m_process.readAllStandardOutput());
    });
    connect(&m_process,&QProcess::readyReadStandardError,[&](){
        appendText(m_process.readAllStandardError());
    });
    connect(&m_process,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished), this, &Console::printTerminationResult);
    connect(&m_process,&QProcess::errorOccurred,this,&Console::handleProcessError);
    m_process.setProgram(program);
    m_process.setArguments(arguments);
    m_timer.start();
    m_process.start();
}

void Console::appendText(const QString &text)
{
    moveCursor(QTextCursor::End);
    insertPlainText(text);
    m_reachable_pos = textCursor().position();
}

Console::~Console()
{
    qDebug("this was called!");
    m_process.kill();
}

void Console::handleProcessError(QProcess::ProcessError error)
{
    QString error_string;
    switch(error)
    {
        case QProcess::ProcessError::FailedToStart:
            error_string = QString("Failed to start program %1").arg(m_process.program());
            break;
        case QProcess::ProcessError::Crashed:
            error_string = QString("Program %1 crashed!").arg(m_process.program());
            break;
        default:
            return;     //do not react on other errors
    }
    setTextColor(Qt::red);

    append(error_string);
    setTextColor(Qt::yellow);
    append("Press any key to exit!");
    m_finished = true;
}

void Console::printTerminationResult(int exit_code, QProcess::ExitStatus status)
{
    Q_UNUSED(status);
    setTextColor(Qt::yellow);
    append(QString("\nProgram %1 finished in %2 ms.").arg(m_process.program()).arg(m_timer.elapsed()));
    if(exit_code == 0)
        setTextColor(Qt::green);
    else
        setTextColor(Qt::red);
    append(QString("Program exited with exit code %1.").arg(exit_code));
    setTextColor(Qt::yellow);
    append("Press any key to exit!");
    m_finished = true;
}

void Console::keyPressEvent(QKeyEvent *e)
{
    if(m_finished)
    {
        e->ignore();
        close();
    }
    int key = e->key();
    if(((key == Qt::Key_Left || key == Qt::Key_Backspace) && textCursor().position() <= m_reachable_pos)
            || key == Qt::Key_Up
            || key == Qt::Key_Down)
    {
        e->ignore();
        return;
    }

    bool is_ctrl = e->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier);
    if(is_ctrl)
    {
        if(key == Qt::Key_C)       //ctrl + c (terminate program)
        {
            e->accept();
            m_process.kill();
        }
        else
        {
            e->ignore();
        }
        return;
    }
    if(key == Qt::Key_Return || key == Qt::Key_Enter)
    {
        moveCursor(QTextCursor::End);
    }
    if(key == Qt::Key_Backspace)
    {
        QTextCursor cursor = textCursor();
        int actual_pos = cursor.position();
        cursor.movePosition(QTextCursor::End);
        int last_pos = cursor.position();
        m_input.remove(m_input.length() - (last_pos - actual_pos) - 1,1);
    }
    else if(key == Qt::Key_Delete)
    {
        QTextCursor cursor = textCursor();
        int actual_pos = cursor.position();
        cursor.movePosition(QTextCursor::End);
        int last_pos = cursor.position();
        m_input.remove(m_input.length() - (last_pos - actual_pos),1);
    }
    else{
        m_input += e->text();
    }

    QTextEdit::keyPressEvent(e);
    if(key == Qt::Key_Return || key == Qt::Key_Enter)
    {
        m_process.write(m_input.toLocal8Bit());
        m_input.clear();
        m_reachable_pos = textCursor().position();
    }
}

void Console::mousePressEvent(QMouseEvent *e)
{
    e->ignore();
}


void Console::mouseReleaseEvent(QMouseEvent *e)
{
    e->ignore();
}

void Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    e->ignore();
}
