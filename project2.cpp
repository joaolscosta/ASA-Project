#include <iostream>
#include <unordered_map>
#include <vector>
#include <string> 


using namespace std;

unordered_map<string, int> map_values;
typedef std::vector<std::vector<int>> matrix;


matrix zero_matrix(matrix m, int d, int i_max, int col_max) {
    for(int i = i_max; i < i_max+d; i++) {
        for(int j = col_max; j>col_max-d;j--) {
            m.at(i).at(j) = 0;
        }
    }
    return m;
}
string convert(int arr[], int lines) {
    int number = 0;
    for (int i = 0; i < lines; i++) {
        number*=10;
        number+=arr[i];
    }
    return to_string(number);
}

int find_max_dim(matrix m,int c_values[], int lines, int columns,int  i_max, int col_max) {
//n vale a pena ver à direita , ve à esq e em baixo 
    if(i_max ==0 && col_max == 0) {
        return 0;
    }
    int max_dim = 0;
    int minimum = min(lines-i_max, col_max);
    //cout<<"minimuuuuuuuuu"<<minimum<<"i_max"<<i_max<<"col"<<col_max<<endl;
    for(int i = 1; i<=minimum;i++) {
        if(m.at(i_max+i).at(col_max) == 0 || m.at(i_max).at(col_max-i) == 0) {
            max_dim = i;
            break;
        }
    }
    return max_dim;
}

int find_col_max(int c_values[], int lines, int columns, int i_max, matrix m) {
    int col_max = 0;
    for(int j= columns+1; j >=0 ;j--) {
        if(m.at(i_max).at(j) == 1) {
            col_max = j;
            break;
        }

    }
    return col_max;
}
int find_i_max(int c_values[], int lines, int columns, matrix m) {
    int i_max = 0;
    for (int i = 0; i < lines; i++) // input c values of each line
    {   
        if(c_values[i]>c_values[i_max]) {
            i_max = i;
        }
    }
    return i_max;
}

int combinations(matrix m, int i_max, int col_max, int max_dim, int lines, int columns, int count) {
    if(max_dim == 0) {
        return 1;
    }

    int c_values[lines] = {};
    for (int i = 0; i < lines; i++) 
    {
        for (int j = 1; j < columns+1; j++)
        {
            if(m.at(i).at(j) > 0) {
                c_values[i]++;
            }
            else {
                break;
            }
        }
    }
    
    for(int i = max_dim; i>0;i--) {
        //cout<<i<<endl;
        matrix new_m = zero_matrix(m, i, i_max, col_max);
        //////////corrigir c_values///////
        int new_c_values[lines] = {};
        for (int i = 0; i < lines; i++) 
        {
            for (int j = 1; j < columns+1; j++)
            {
                if(new_m.at(i).at(j) > 0) {
                    new_c_values[i]++;
                }
                else {
                    break;
                }
            }
        }

        /////////////////////
        string key = convert(c_values, lines);
        if(map_values.find(key)==map_values.end()) {
            int new_i_max = find_i_max(new_c_values, lines, columns, new_m);
            int new_col_max = find_col_max(new_c_values, lines, columns, new_i_max, new_m);
            int new_max_dim = find_max_dim(new_m, new_c_values, lines, col_max, new_i_max, new_col_max);
            key = convert(new_c_values, lines);
            count+= combinations(new_m, new_i_max, new_col_max, new_max_dim, lines, columns, 0);
            map_values.insert(pair<string, int>(key, count));


        }
        else {
            return map_values[key];

        }
    }
    return count;


}

int main()
{

    int lines = 0, columns = 0;
    int total_combinations = 0;

    std::cin >> lines;
    std::cin >> columns;


    int c_values[lines];
    for (int i = 0; i < lines; i++) // input c values of each line
    {   
        std::cin >> c_values[i];

    }

    matrix m = {};

    for (int i = 0; i <= lines; i++) // initialize matrix
    {
        std::vector<int> vector = {};
        for (int j = 0; j <= columns+1; j++)
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



    /*for (int i = 0; i <= lines; i++) // print matrix
    {
        for (int j = 0; j <= columns+1; j++)
        {

            std::cout << m.at(i).at(j) << "|";
        }
        
        std::cout << "\n";
    } */
    
    int i_max = find_i_max(c_values, lines, columns, m);
    int col_max = find_col_max(c_values, lines, columns, i_max, m);
    int max_dim = find_max_dim(m, c_values, lines, columns, i_max, col_max);
    if(max_dim == 0) {
        total_combinations = 0;
    }
    else {
        total_combinations= combinations(m, i_max, col_max, max_dim, lines, columns, 0);
    }
    
   /* matrix m2 = zero_matrix(m, 2,i_max,col_max);
    for (int i = 0; i <= lines; i++) // print matrix
    {
        for (int j = 0; j <= columns+1; j++)
        {

            std::cout << m2.at(i).at(j) << "|";
        }
        
        std::cout << "\n";
    } */


    cout <<total_combinations << std::endl;

  return 0;
}