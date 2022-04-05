#include "replacer.h"

#include <QHash>

namespace
{
    QHash<QString, QString> hexHash
    {
        {"#@P@",   u8"\u2117"},
        {"#@EUR@", u8"\u20AC"},
        {"#@DOL@", u8"\u0024"},
        {"#@C@",   u8"\u00A9"},
        {"#@POU@", u8"\u00A3"},
        {"#@R@",   u8"\u00AE"},
        {"#@TM@",  u8"\u2122"},
        {"#@RUB@", u8"\u20BD"},
        {"#@DEG@", u8"\u2070"},
        {"#@PRO@", u8"\u2030"},
    };
}

std::optional<std::tuple<QString, int, int>> Replacer::GetReplacement(const QString& line) const
{
    QHash<QString, QString>::const_iterator i = hexHash.constBegin();
    while (i != hexHash.constEnd())
    {
        if(int index = line.indexOf(i.key()); index != -1)
        {
            return std::make_tuple(i.value(), index, i.key().length());
        }
        ++i;
    }
    return std::nullopt;
}

QString Replacer::Replace(const QString& line, const std::tuple<QString, int, int>& replacement) const
{
    QString formattedText {line};
    const auto& [lexeme, pos, length] = replacement;

    formattedText.replace(pos, length, lexeme);
    return formattedText;
}
