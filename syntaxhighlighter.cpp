#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    if (highlightedString.isEmpty()) return;

    QTextCharFormat format;
    format.setBackground(Qt::green);

    const int length = highlightedString.length();
    for (int i = text.indexOf(highlightedString); 0 <= i; i = text.indexOf(highlightedString, i + length))
    {
        setFormat(i, length, format);
    }
}

void SyntaxHighlighter::setHighlightedString(const QString &str)
{
    highlightedString = str;
    rehighlight();
}
