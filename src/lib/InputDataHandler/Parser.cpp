#include "InputDataHandler/Parser.hpp"
#include "InputDataHandler/Polygon.hpp"
#include "InputDataHandler/InputData.hpp"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>

void Parser::read_file(InputData &rawInput, char *argv[])
{
    rawInput.setConflictD(atof(argv[1]));
    std::ifstream input_file(argv[2], std::ifstream::in);
    std::string read_line;
    std::vector<Polygon::Polygon> row;
    Polygon::Polygon *poly = NULL;
    int polyIndex = 0;
    while (getline(input_file, read_line))
    {
        boost::erase_all(read_line, "\t");
        std::vector<std::string> splited_string;
        boost::split(splited_string, read_line, boost::is_any_of(" "), boost::token_compress_on);
        if (splited_string.size() > 1)
        {
            if (splited_string[0] == "ROW")
            {
                std::vector<double> tmp;
                tmp.emplace_back(std::stof(splited_string[2]));
                tmp.emplace_back(std::stof(splited_string[3]));
                rawInput.insertRowInfo(tmp);
            }
            if (splited_string[0] == "POLYGON")
            {
                poly = new Polygon::Polygon;
                poly->setId(polyIndex);
                polyIndex++;
            }
            else if (splited_string[0] == "MASK")
            {
                poly->setMask(int(splited_string[1][0]));
            }
            else if (splited_string[0] == "RECT")
            {
                poly->setRect(std::stof(splited_string[1]), std::stof(splited_string[2]), std::stof(splited_string[3]), std::stof(splited_string[4]));
            }
            else if (splited_string[0] == "END")
            {
                if (splited_string[1][0] == 'P')
                {
                    row.push_back(*poly);
                    delete poly;
                    poly = NULL;
                }
                if (splited_string[1][0] == 'R')
                {
                    rawInput.addRow(row);
                    row.clear();
                }
            }
        }
    }
}
void Parser::output_file(InputData &Input, char *argv[])
{
    std::ofstream myfile(argv[3]);
    auto getrowInfo = Input.getRowInfo();
    if (myfile.is_open())
    {
        auto layout = Input.getLayout();
        int rowIndex = 0, polyIndex = 0;
        for (const auto &row : layout)
        {
            myfile << "ROW R" << rowIndex <<" "<<getrowInfo[rowIndex][0]<<" "<<getrowInfo[rowIndex][1]<<" \n";
            for (const auto &poly : row)
            {
                myfile<<"\tPOLYGON P" << polyIndex <<"\n";
                int mask = poly.getMask();
                auto rect = poly.getRect();
                if(mask == 0)
                    myfile<<"\t\tMASK A\n";
                else if(mask == 1)
                    myfile<<"\t\tMASK B\n";
                else if(mask == 2)
                    myfile<<"\t\tMASK C\n";
                else if(mask == 3)
                    myfile<<"\t\tMASK E\n";
                myfile<<"\t\tLAYER M1\n";
                for(auto &r : rect){
                    auto c1 = r.getC1();
                    auto c2 = r.getC2();
                    myfile<<"\t\t\tRECT "<<c1.first<<" "<<c1.second<<" "<<c2.first<<" "<<c2.second<<"\n";
                }
                myfile<<"\t\tEND\n";
                myfile<<"\tEND P" << polyIndex <<"\n";
                polyIndex++;
            }
            myfile<<"END R" << rowIndex <<"\n";
            rowIndex++;
        }
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
    return;
}