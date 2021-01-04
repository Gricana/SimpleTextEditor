#include "syntaxhighlighter.h"
#include <QSettings>

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent),
    setting(QSettings::NativeFormat, QSettings::UserScope, "IT", "TextEditor")
{
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    if (highlightedString.isEmpty()) return;

    QTextCharFormat format;
    format.setBackground(Qt::yellow);
    const int length = highlightedString.length();
    setting.beginGroup("/SETTINGS_SEARCH_VIEW");
    bool isCaseSensitive = setting.value("/SETTING_CASE_SENSITIVE").toBool();
    setting.endGroup();
    switch (isCaseSensitive) {
    case true:
        for (int i = text.indexOf(highlightedString, Qt::CaseSensitive); 0 <= i; i = text.indexOf(highlightedString, i + length, Qt::CaseSensitive)) {
            setFormat(i, length, format);
        } break;
    case false:
        for (int i = text.indexOf(highlightedString, 0, Qt::CaseInsensitive); 0 <= i; i = text.indexOf(highlightedString, i + length, Qt::CaseInsensitive)) {
            setFormat(i, length, format);
    } break;
    default: break;
}
}

void SyntaxHighlighter::setHighlightedString(const QString &str)
{
    highlightedString = str;
    rehighlight();
}
