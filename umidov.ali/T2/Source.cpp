#include "item_data.h"

namespace umidov {
    std::string binaryNull(unsigned long long ref) {
        std::stringstream ss;
        ss << "0b" << std::setfill('0') << std::setw(2) << std::to_string(ref);
        std::string out = ss.str();
        size_t i = out.find('b');
        if (out[i + 1] == '0' and out[i + 2] == '0') {
            out.erase(i + 2, 1);
        }
        return out;
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LIT&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        return in >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, OCT&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        return in >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        DataStruct input;
        {
            using sep = DelimiterIO;
            using lit = LIT;
            using oct = OCT;
            using str = StringIO;

            in >> sep{ '(' };
            bool flag1 = false;
            bool flag2 = false;
            bool flag3 = false;
            while (true) {
                if (flag1 && flag2 && flag3) {
                    break;
                }
                std::string key;
                char c;
                in >> c;
                if (!in) {
                    break;
                }

                if (c == ':' && (in >> key)) {
                    if (key == "key1") {
                        in >> lit{ input.key1 } >> sep{ 'u' } >> sep{ 'l' } >> sep{ 'l' };
                        flag1 = true;
                    }
                    else if (key == "key2") {
                        in >> sep{ '0' } >> sep{ 'b' } >> oct{ input.key2 };
                        flag2 = true;
                    }
                    else if (key == "key3") {
                        in >> str{ input.key3 };
                        flag3 = true;
                    }
                }
            }
            in >> sep{ ':' } >> sep{ ')' };
        }
        if (in) {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(";
        out << ":key1 " << src.key1 << "ull";
        out << ":key2 " << binaryNull(src.key2);
        out << ":key3 " << "\"" << src.key3 << "\"";
        out << ":)";
        return out;
    }

    bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1) {
            return a.key1 < b.key1;
        }
        else if (a.key2 != b.key2) {
            return a.key2 < b.key2;
        }
        else {
            return a.key3.length() < b.key3.length();
        }
    }

    iofmtguard::iofmtguard(std::basic_ios<char>& stream) :
        stream_(stream),
        fill_(stream.fill()),
        precision_(stream.precision()),
        flags_(stream.flags()) {}

    iofmtguard::~iofmtguard() {
        stream_.fill(fill_);
        stream_.precision(precision_);
        stream_.flags(flags_);
    }
}
