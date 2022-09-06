#include <vector>
#include <Calculator/PermuteCalculator.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

void getPermute_dup(const std::vector<int> color, std::vector<int> permute, std::vector<std::vector<int>> &permuteset, const int n, const int length)
{
    for (int i = 0; i < n; i++)
    {
        std::vector<int> per;
        per = permute;
        per.emplace_back(color[i]);
        if (length == 1)
            permuteset.emplace_back(per);
        else
            getPermute_dup(color, per, permuteset, n, length - 1);
    }
}
void getPermute(std::vector<std::vector<bool>> &valid_color, std::vector<std::vector<bool>> &conflict, std::vector<int> permute, std::vector<std::vector<int>> &permuteset, const int n, const int length, const int l,int print)
{
    int now_index = l - length;
    for (int i = 0; i < n; i++)
    {
        std::vector<int> per;
        per = permute;
        if (!valid_color[now_index][i])
            continue;
        int c_size = conflict[now_index].size();
        bool flag = false;
        if (now_index > 0)
        {
            for (int ind = 0; ind < now_index; ind++)
            {
                if (conflict[ind][now_index-(ind+1)])
                {
                    if (per[ind] == i)
                        flag = true;
                }
            }
        }
        per.emplace_back(i);
        if (length == 1 && !flag)
            permuteset.emplace_back(per);
        else if(!flag)
            getPermute(valid_color, conflict, per, permuteset, n, length - 1, l,print);
    }
}
void getPermute2(const std::vector<int> color, std::string permute, std::unordered_map<std::string, int> &permuteset, const int n, const int length)
{
    for (int i = 0; i < n; i++)
    {
        std::string per = permute;
        per += std::to_string(color[i]);
        if (length == 1)
            permuteset[per] = -1;
        else
            getPermute2(color, per, permuteset, n, length - 1);
    }
}

std::vector<std::vector<int>> PermuteCalculator::calculate_same(std::vector<bool> valid_color, int cutsize)
{
    std::vector<std::vector<int>> permuteset;
    std::vector<int> per;
    std::vector<int> color_lib = {0, 1, 2, 3};
    std::vector<int> color;
    for (int i = 0; i < 3; i++)
    {
        if (valid_color[i])
        {
            color.emplace_back(color_lib[i]);
        }
    }
    color.emplace_back(3);
    getPermute_dup(color, per, permuteset, color.size(), cutsize);
    return permuteset;
}
std::vector<std::vector<int>> PermuteCalculator::calculate(std::vector<std::vector<bool>> valid_color, std::vector<std::vector<bool>> &conflict, int cutsize,int print)
{
    std::vector<std::vector<int>> permuteset;
    std::vector<int> per;
    getPermute(valid_color, conflict, per, permuteset, 4, cutsize, cutsize,print);
    return permuteset;
}
void PermuteCalculator::calculate2(std::unordered_map<int, std::unordered_map<std::string, int>> &permuteSets, std::vector<bool> &cutset_num)
{
    int index = 0;
    for (auto cutsetsize : cutset_num)
    {
        if (cutsetsize)
        {
            if (permuteSets.find(index) == permuteSets.end())
            {
                std::unordered_map<std::string, int> permuteset;
                std::vector<int> color = {0, 1, 2, 3};
                std::string per = "";
                std::vector<bool> used(3, false);
                getPermute2(color, per, permuteset, 4, index);
                permuteSets[index] = permuteset;
            }
        }
        index++;
    }
}