#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QSettings>

class SyntaxHighlighter : public QSyntaxHighlighter
{
private:
    QString highlightedString;
public:
    SyntaxHighlighter(QTextDocument* parent);
    void highlightBlock(const QString& text);
    void setHighlightedString(const QString& str);
    QSettings setting;
};

#endif // SYNTAXHIGHLIGHTER_H
