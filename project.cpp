#include <vector>
#include <iostream>

typedef std::vector<std::vector<int>> matrix;

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

  for (int i = 0; i < lines; i++) // print matrix
  {
    for (int j = 0; j < c_values[i]; j++)
    {
      std::cout << m.at(i).at(j) << "|";
    }
    std::cout << "\n";
  }
  std::cout << max_square_dim << std::endl;

  return 0;
}