#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, ushort> map_values;
typedef std::vector<std::vector<ushort>> matrix;

matrix zero_matrix(matrix m, ushort d, ushort i_max, ushort col_max)
{
    for (ushort i = i_max; i < i_max + d; i++)
    {
        for (ushort j = col_max; j > col_max - d; j--)
        {
            m.at(i).at(j) = 0;
        }
    }
    return m;
}
string convert(ushort arr[], ushort lines)
{
    ushort number = 0;
    for (ushort i = 0; i < lines; i++)
    {
        number *= 10;
        number += arr[i];
        
    }
    return to_string(number);
}

ushort find_max_dim(matrix m, ushort c_values[], ushort lines, ushort columns, ushort i_max, ushort col_max)
{
    // n vale a pena ver à direita , ve à esq e em baixo
    if (i_max == 0 && col_max == 0)
    {
        return 0;
    }
    ushort max_dim = 0;
    ushort minimum = min(lines - i_max, col_max);
    for (ushort i = 1; i <= minimum; i++)
    {
        if (m.at(i_max + i).at(col_max) == 0 || m.at(i_max).at(col_max - i) == 0)
        {
            max_dim = i;
            break;
        }
    }
    return max_dim;
}

ushort find_col_max(ushort c_values[], ushort lines, ushort columns, ushort i_max, matrix m)
{
    ushort col_max = 0;
    for (ushort j = columns + 1; j >= 0; j--)
    {
        if (m.at(i_max).at(j) == 1)
        {
            col_max = j;
            break;
        }
    }
    return col_max;
}
ushort find_i_max(ushort c_values[], ushort lines, ushort columns, matrix m)
{
    ushort i_max = 0;
    for (ushort i = 0; i < lines; i++) // input c values of each line
    {
        if (c_values[i] > c_values[i_max])
        {
            i_max = i;
        }
    }
    return i_max;
}

ushort combinations(matrix m, ushort i_max, ushort col_max, ushort max_dim, ushort lines, ushort columns, ushort count)
{
    if (max_dim == 0)
    {
        return 1;
    }

    ushort c_values[lines] = {};
    for (ushort i = 0; i < lines; i++)
    {
        for (ushort j = 1; j < columns + 1; j++)
        {
            if (m.at(i).at(j) > 0)
            {
                c_values[i]++;
            }
            else
            {
                break;
            }
        }
    }

    for (ushort i = max_dim; i > 0; i--)
    {
        matrix new_m = zero_matrix(m, i, i_max, col_max);
        ushort new_c_values[lines] = {};
        for (ushort i = 0; i < lines; i++)
        {
            for (ushort j = 1; j < columns + 1; j++)
            {
                if (new_m.at(i).at(j) > 0)
                {
                    new_c_values[i]++;
                }
                else
                {
                    break;
                }
            }
        }

        /////////////////////
        string key = convert(c_values, lines);
        if (map_values[key] != 0)
        {
            return map_values[key];
        }
        else
        {
            ushort new_i_max = find_i_max(new_c_values, lines, columns, new_m);
            ushort new_col_max = find_col_max(new_c_values, lines, columns, new_i_max, new_m);
            ushort new_max_dim = find_max_dim(new_m, new_c_values, lines, col_max, new_i_max, new_col_max);
            key = convert(new_c_values, lines);
            count += combinations(new_m, new_i_max, new_col_max, new_max_dim, lines, columns, 0);

            map_values.insert(pair<string, ushort>(key, count));
        }
    }

    return count;
}

int main()
{

    ushort lines = 0, columns = 0;
    long int total_combinations = 0;

    std::cin >> lines;
    std::cin >> columns;

    ushort c_values[lines];
    for (ushort i = 0; i < lines; i++) // input c values of each line
    {
        std::cin >> c_values[i];
    }

    matrix m = {};

    for (ushort i = 0; i <= lines; i++) // initialize matrix
    {
        std::vector<ushort> vector = {};
        for (ushort j = 0; j <= columns + 1; j++)
        {   
            vector.push_back(0);
        }
        m.push_back(vector);
    }

    for (ushort i = 0; i < lines; i++) // fill colored squares
    {
        for (ushort j = 1; j <= c_values[i]; j++)
        {

            m.at(i).at(j) = 1;
        }
    }



    ushort i_max = find_i_max(c_values, lines, columns, m);
    ushort col_max = find_col_max(c_values, lines, columns, i_max, m);
    ushort max_dim = find_max_dim(m, c_values, lines, columns, i_max, col_max);
    if (max_dim == 0)
    {
        total_combinations = 0;
    }
    else
    {
        total_combinations = combinations(m, i_max, col_max, max_dim, lines, columns, 0);
    }




    cout << total_combinations << std::endl;

    return 0;
}