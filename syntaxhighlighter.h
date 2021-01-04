#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SyntaxHighlighter : public QSyntaxHighlighter
{
private:
    QString highlightedString;
public:
    SyntaxHighlighter(QTextDocument* parent);
    void highlightBlock(const QString& text);
    void setHighlightedString(const QString& str);
};

#endif // SYNTAXHIGHLIGHTER_H
