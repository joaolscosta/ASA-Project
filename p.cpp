#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<long int, long int> map_values;
typedef std::vector<std::vector<int>> matrix;


matrix zero_matrix(matrix m, int d, int i_max, int col_max)
{
    for (int i = i_max; i < i_max + d; i++)
    {
        for (int j = col_max; j > col_max - d; j--)
        {
            m.at(i).at(j) = 0;
        }
    }
    return m;
}

long int convert(int arr[], int lines)
{
    long int number = 0;
    for (int i = 0; i < lines; i++)
    {
        number *= 10;
        number += arr[i];
        if (arr[i] > 0)
        {
            number++;
        }
        number += i; //trata colisoes
    }
    return number;
}

int find_max_dim(matrix m, int c_values[], int lines, int columns, int i_max, int col_max)
{
    if (i_max == 0 && col_max == 0)
    {
        return 0;
    }
    int max_dim = 0;
    int minimum = min(lines - i_max, col_max);
    for (int i = 1; i <= minimum; i++)
    {
        if (m.at(i_max + i).at(col_max) == 0 || m.at(i_max).at(col_max - i) == 0)
        {
            max_dim = i;
            break;
        }
    }
    return max_dim;
}

int find_col_max(int c_values[], int lines, int columns, int i_max, matrix m)
{
    int col_max = 0;
    for (int j = columns + 1; j >= 0; j--)
    {
        if (m.at(i_max).at(j) == 1)
        {
            col_max = j;
            break;
        }
    }
    return col_max;
}
int find_i_max(int c_values[], int lines, int columns, matrix m)
{
    int i_max = 0;
    for (int i = 0; i < lines; i++) // input c values of each line
    {
        if (c_values[i] > c_values[i_max])
        {
            i_max = i;
        }
    }
    return i_max;
}

long int combinations(matrix m, int i_max, int col_max, int max_dim, int lines, int columns, long int count)
{
    if (max_dim == 0)
    {
        return 1;
    }

    int c_values[lines] = {};
    for (int i = 0; i < lines; i++)
    {
        for (int j = 1; j < columns + 1; j++)
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

    long int key1 = convert(c_values, lines);
    if (map_values.count(key1) == 1)
    {
        return map_values[key1];
    }

    for (int i = max_dim; i > 0; i--)
    {
        matrix new_m = zero_matrix(m, i, i_max, col_max);
        int new_c_values[lines] = {};
        for (int i = 0; i < lines; i++)
        {
            for (int j = 1; j < columns + 1; j++)
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

        int new_i_max = find_i_max(new_c_values, lines, columns, new_m);
        int new_col_max = find_col_max(new_c_values, lines, columns, new_i_max, new_m);
        int new_max_dim = find_max_dim(new_m, new_c_values, lines, col_max, new_i_max, new_col_max);

        count += combinations(new_m, new_i_max, new_col_max, new_max_dim, lines, columns, 0);
    }
    map_values.insert(pair<long int, int>(key1, count));

    return count;
}

int main()
{

    int lines = 0, columns = 0;
    long int total_combinations = 0;

    cin >> lines;
    cin >> columns;

    int c_values[lines];
    for (int i = 0; i < lines; i++) // input c values of each line
    {
        cin >> c_values[i];
    }

    matrix m = {};

    for (int i = 0; i <= lines; i++) // initialize matrix
    {
        vector<int> vector = {};
        for (int j = 0; j <= columns + 1; j++)
        {
            vector.push_back(0);
        }
        m.push_back(vector);
    }

    for (int i = 0; i < lines; i++) // fill colored squares
    {
        for (int j = 1; j <= c_values[i]; j++)
        {

            m.at(i).at(j) = 1;
        }
    }

    int i_max = find_i_max(c_values, lines, columns, m);
    int col_max = find_col_max(c_values, lines, columns, i_max, m);
    int max_dim = find_max_dim(m, c_values, lines, columns, i_max, col_max);
    if (max_dim == 0)
    {
        total_combinations = 0;
    }
    else
    {
        total_combinations = combinations(m, i_max, col_max, max_dim, lines, columns, 0);
    }


    cout << total_combinations << endl;

    return 0;
}