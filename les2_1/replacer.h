#ifndef REPLACER_H
#define REPLACER_H

#include <QString>
#include <optional>
#include <tuple>

class Replacer
{
public:
    Replacer() = default;
public:
    std::optional<std::tuple<QString, int, int>> GetReplacement(const QString& line) const;
    QString Replace(const QString& line, const std::tuple<QString, int, int>& replacement) const;
};

#endif // REPLACER_H
