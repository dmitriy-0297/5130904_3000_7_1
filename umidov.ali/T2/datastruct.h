#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>

namespace umidov {
    struct DataStruct;

    struct DelimiterIO;

    struct LIT;

    struct OCT;

    struct StringIO;

    class iofmtguard;

    std::istream& readDelimiter(std::istream& input, DelimiterIO&& destination);

    std::istream& readString(std::istream& input, StringIO&& destination);

    std::istream& readULongLiteral(std::istream& input, LIT&& destination);

    std::istream& readULongBinaryLiteral(std::istream& input, OCT&& destination);

    std::istream& operator>>(std::istream& input, DelimiterIO&& destination);

    std::istream& operator>>(std::istream& input, StringIO&& destination);

    std::istream& operator>>(std::istream& input, LIT&& destination);

    std::istream& operator>>(std::istream& input, OCT&& destination);

    std::istream& operator>>(std::istream& input, DataStruct& destination);

    std::ostream& operator<<(std::ostream& output, const DataStruct& source);
}

#endif
