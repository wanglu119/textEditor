#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QKeyEvent>

#include "texteditor.h"

TextEditor::TextEditor(QWidget* parent):QTextEdit(parent)
{
    clear();
}

bool TextEditor::readFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("TextEditor"),
                             tr("Cannot read file %1.\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    setPlainText(in.readAll());

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return true;
}

bool TextEditor::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("TextEditor"),
                             tr("Cannot write file %1.\n%2")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    out << this -> toPlainText();

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return true;
}

void TextEditor::keyPressEvent(QKeyEvent *ev)
{
    if( Qt::Key_Insert == ev->key())
    {
        // 置反当前写入模式
        setOverwriteMode(!overwriteMode());
        emit overwriteModeChanged();
        return ;
    }
    QTextEdit::keyPressEvent(ev);
}


void TextEditor::find()
{

}
