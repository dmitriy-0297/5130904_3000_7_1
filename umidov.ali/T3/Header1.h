        #ifndef HEADER1_H
        #define HEADER1_H

        #include <vector>
        #include "Header2.h"

        namespace cmd
        {
            int validStringToInt(std::string str);
            void area(std::vector<geometry::Polygon>& value, const std::string str);
            void max(std::vector<geometry::Polygon>& value, const std::string str);
            void min(std::vector<geometry::Polygon>& value, const std::string str);
            void count(std::vector<geometry::Polygon>& value, const std::string str);
            void lessArea(std::vector<geometry::Polygon>& value);
            void maxSeq(std::vector<geometry::Polygon>& value);
            void echo(std::vector<geometry::Polygon>& value);
            void inFrame(std::vector<geometry::Polygon>& value);
        }

        #endif
