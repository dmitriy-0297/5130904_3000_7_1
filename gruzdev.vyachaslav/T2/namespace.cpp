#include "namespace.h"

namespace gruzdev
{
    struct UnsignedLongLongIO
    {
        unsigned long long& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char character = '0';
        in >> character;
        if (in && (character != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, CMPDoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        double real_part = 0.0;
        double imag_part = 0.0;

        in >> DelimiterIO{ '(' } >> real_part >> imag_part >> DelimiterIO{ ')' };
        if (in)
        {
            dest.ref = std::complex<double>(real_part, imag_part);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.num;
    }

    std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> std::hex >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            using Delimiter = DelimiterIO;
            using ULL = UnsignedLongLongIO;
            using CMPDouble = CMPDoubleIO;
            using String = StringIO;

            in >> Delimiter{ '(' };
            bool flag1 = false, flag2 = false, flag3 = false;
            while (true) {
                if (flag1 && flag2 && flag3) break;
                std::string key;
                char character;
                in >> character;
                if (!in) break;

                if (character == ':' && (in >> key))
                {
                    if (key == "key1")
                    {
                        in >> ULL{ input.key1 };
                        flag1 = true;
                    }
                    else if (key == "key2")
                    {
                        in >> Delimiter{ '#' } >> Delimiter{ 'c' } >> CMPDouble{ input.key2 };
                        flag2 = true;
                    }
                    else if (key == "key3")
                    {
                        in >> String{ input.key3 };
                        flag3 = true;
                    }
                }
            }
            in >> Delimiter{ ':' } >> Delimiter{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(";
        out << ":key1 " << std::uppercase << std::hex << "0x" << src.key1;
        out << ":key2 " << std::fixed << std::setprecision(1) << "#c(" << src.key2.real() << " " << src.key2.imag() << ")";
        out << ":key3 \"" << src.key3 << "\"";
        out << ":)";
        return out;
    }

    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second)
    {
        double Real_first = ds_first.key2.real(),
            Real_second = ds_second.key2.real(),
            Imaginary_first = ds_first.key2.imag(),
            Imaginary_second = ds_second.key2.imag(),
            Magnitude_first = 0.0,
            Magnitude_second = 0.0;
        Magnitude_first = sqrt(pow(Real_first, 2) + pow(Imaginary_first, 2));
        Magnitude_second = sqrt(pow(Real_second, 2) + pow(Imaginary_second, 2));

        if (ds_first.key1 < ds_second.key1)
        {
            return true;
        }
        else if (ds_first.key1 == ds_second.key1)
        {
            if (Magnitude_first < Magnitude_second)
            {
                return true;
            }
            else if (Magnitude_first == Magnitude_second)
            {
                return ds_first.key3.length() < ds_second.key3.length();
            }
        }
        return false;
    }

    iofmtguard::iofmtguard(std::basic_ios< char >& stream) :
        s_(stream),
        fill_(stream.fill()),
        precision_(stream.precision()),
        fmt_(stream.flags())
    {}

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}

