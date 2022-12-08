#include <vector>
#include <iostream>

typedef std::vector<std::vector<int>> matrix;

int nofways(int n, int m, int d, int count) {
  if(d == 1) { return count; }
  else if(n == d && m == d) { 
    count += 1 + nofways(n, m, d - 1, count); 
  }
  

  else if(d < n && d < m) {
    count += (m - d + 1)*(n - d + 1);

  }
  else if(n >= d && m > n) { 
    if(m - d < d) {
      count += (1 + nofways(n, m - d, m - d, count))*2;
      if(((m-d)-1) > 0) {
          for(int i = 1; i <= (m - d)-1; i++) {
            if((m - i - d) == 1 && (m - 1- d) == 1 ) {count++;}
            else {
              if((m - i - d) == 1 ) {count++;}
              if((m - 1- d) == 1) {count++;}
              count += nofways(n, m - d - (m - i - d), m - i - d, count) + nofways(n, m - i - d, m - 1- d, count);
            }
          }
      } 
    }
  }
  else if(m >= d && n > m) { 
      if(n - d < d) {
        count += (1 + nofways(n - d, m, n - d, count))*2;
        if(((n - d)-1) > 0) {
          for(int i = 1; i <= (n - d)-1; i++) {
            if((n - i - d) == 1 && (n - 1- d) == 1) {count++;}
            else {
              if((n - i - d) == 1 ) {count++;}
              if((n - 1- d) == 1) {count++;}
              count += nofways(n - d - (n - i - d), m, n - i - d, count) + nofways(n - i - d, m, n - 1- d, count);
            }
          }
        }
      }
  }

  return count;

}

int main()
{
  int lines = 0, columns = 0;
  int max_square_dim = 0;
  // int total_combinations = 0;

  std::cin >> lines;
  std::cin >> columns;

  int c_values[lines];

  for (int i = 0; i < lines; i++) // input c values of each line
  {
    std::cin >> c_values[i];
  }

  // percorrer c_values para ver a maior dimensão possivel

  for (int i = columns; i > 0; i--)
  {
    int cont = 0;
    for (int j = columns; j > 0; j--)
    {
      if (c_values[j - 1] >= i)
      {
        cont++;
        if (cont == i)
        {
          max_square_dim = i;
        }
      }
    }
    if (max_square_dim != 0)
    {
      break;
    }
  }

  matrix m = {};

  for (int i = 0; i < lines; i++) // initialize matrix
  {
    std::vector<int> vector = {};
    for (int j = 0; j < columns; j++)
    {
      vector.push_back(0);
    }
    m.push_back(vector);
  }

  for (int i = 0; i < lines; i++) // fill colored squares
  {
    for (int j = 0; j < c_values[i]; j++)
    {
      m.at(i).at(j) = 1;
    }
  }

  /*for (int i = 0; i < lines; i++) // print matrix
  {
    for (int j = 0; j < c_values[i]; j++)
    {
      std::cout << m.at(i).at(j) << "|";
    }
    std::cout << "\n";
  }*/
  ///std::cout << max_square_dim << std::endl;
  int count = 0;
  std::cout << nofways(lines, columns, max_square_dim, count) << std::endl;

  return 0;
}