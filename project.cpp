#include <vector>
#include <iostream>

typedef std::vector<std::vector<int>> matrix;

int nofways(int n, int m, int d, int c_values[], int i_line, int count, int comb_sum[]) {
  
  /*std::cout << n << " " << m << " " << d  << " " << c_values[i_line] << std::endl;*/
  if(d == 1) { 
    //count++;
    return count;
  }
  else if(d == c_values[i_line] && i_line + 1 == d) { //caso em q um quadradao preenche a primeira linha toda e chega ao fundo da matriz
    int c_aux_values[n];
    int line_counter = 0;
    for(int i = 0; i <= i_line; i++) { // mete os valores que sobram de cada linha no novo array
      c_aux_values[i] = c_values[i] - d;
      if(c_aux_values[i] > 0) {
        line_counter++;
      }
    }
    if(c_aux_values[0] != 0) {
      count += 1 + nofways(line_counter ,c_aux_values[0], std::min(c_aux_values[line_counter-1], line_counter), c_aux_values, line_counter-1, count, comb_sum);
    }
    else {
      count += 1;
    }

  }

  else if(d < c_values[i_line]) { // casos em q ha mais q um quadrado na primeira linha
    
    if(i_line + 1 == d) { //caso em q o quadrado n preenche a linha toda mas chega ao fundo da matriz
    
      if(c_values[i_line] - d >= d) { //se der pra fzr da mesma dimensao ao lado direito 
        int c_aux_values[n];
        //int lc_values[n];
        int lc_aux_values[n];
        int line_counter = 0;
        for(int i = 0; i <= i_line; i++) { // mete os valores que sobram de cada linha no novo array
          c_aux_values[i] = c_values[i] - d;
          lc_aux_values[i] = c_values[i] - d -1;
          //lc_values[i] = c_values[i] - 1;
          line_counter++;
        }
        
        count += 1 + nofways(n, c_values[i_line]-d, d, c_aux_values, i_line, count, comb_sum) + 
        nofways(line_counter, c_values[i_line]-d, d -1, c_aux_values, i_line, count, comb_sum) +
                 nofways(n, c_values[i_line]-d-1, (std::min(c_values[i_line]-d-1,d)), lc_aux_values, i_line, count, comb_sum) + //caso em q o quadrado grande avança pra direita e deixa vazio pra tras
        nofways(n, c_values[i_line]-d-1, d-1, lc_aux_values, i_line, count, comb_sum) + 
        c_values[i_line] - d; // o resto sao os isolados
      }
      else if(c_values[i_line]-d > 0){// nao da pra fzr o isolado com outro da mesma dimensao mas da pra continuar a calcular
        
        int c_aux_values[n];
        int line_counter = 0;
        for(int i = 0; i <= i_line; i++) { // mete os valores que sobram de cada linha no novo array
          c_aux_values[i] = c_values[i] - 1;
          line_counter++;
        }
        count += 1 + nofways(n, c_values[i_line]-1, d, c_aux_values, i_line, count, comb_sum);
      }
      //nao existe o caso de c_values[i_line]-d = 0 , pois vai a um if de cima quando o quadrado preenche a linha na totalidade e chega ao fundo da matriz 
    
    }


  }
  else if(d == c_values[i_line] && i_line + 1 > d) {  //caso em q um quadrado preenche a primeira linha toda mas n chega ao fundo da matriz
    int i_line_re = i_line-d;
    count+= (comb_sum[i_line_re]);
    int c_aux_values[n];
    int line_counter = 0;
    for(int i = 0; i <= i_line; i++) { 
      if(c_values[i] > c_values[i_line]) {
        c_aux_values[i] = c_values[i] - d;
        line_counter++;
      }
    }
    int d_aux = c_values[i_line-d+1] - d;
    int i_line_aux = (i_line-d+1) - d_aux +1;
    count += 1 + nofways(n , c_values[0] - d, d_aux, c_aux_values, i_line_aux, count, comb_sum);
  }
  else if(d < c_values[i_line] && i_line + 1 > d) { //casos em q ha mais q um quadrado na primeira linha e n chega até ao fundo da matriz
    int i_line_re = i_line-d;
    count+= (comb_sum[i_line_re]) * ((c_values[i_line])-d+1); //pode aproveitar as linhas q ja foram calculadas

  }
  
  
  /*
  

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
  } */

  return count;

}

int recursive_comb(int n , int m, int d, int c_values[], int comb_sum[], int i_line) {
  int comb = 0;
  if(d == 1 && i_line == 0) {
    comb_sum[i_line] = 1;
  }
  else if(comb_sum[i_line-1] == 1 && d == 1) {
    comb_sum[i_line] = 1;
  }
  else if(d == 1) {comb = 0;}
  else if(d > 2) {
    int count = 0;
    for(int i = d; i >= 2; i--) {
      comb += nofways(n , m, i, c_values, i_line, count, comb_sum);
    }
  }
  else {
    int count = 0;
    comb += nofways(n, m, d, c_values, i_line, count, comb_sum);
  }
  if(i_line != 0) {
    comb_sum[i_line] = comb_sum[i_line-1] + comb;
  }

  return comb_sum[i_line];
}

int main()
{
  int lines = 0, columns = 0;
  int total_combinations = 0;

  std::cin >> lines;
  std::cin >> columns;

  int c_values[lines];
  int comb_sum[lines]; //sum of combinations per line
  for (int i = lines; i > 0; i--) // initialize array
  {
    comb_sum[i] = 0;
  }
  
  for (int i = lines; i > 0; i--) // input c values of each line
  {
    std::cin >> c_values[i-1];
  }
  


  /* percorrer c_values para ver a maior dimensão possivel

  for (int i = columns; i > 0; i--)
  {
    int cont = 0;
    for (int j = lines; j > 0; j--)
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
  }*/

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
/*
  for (int i = lines -1; i >= 0; i--) // print matrix
  {
    for (int j = 0; j < c_values[i]; j++)
    {
      std::cout << m.at(i).at(j) << "|";
    }
    std::cout << "\n";
  }
*/

  
  for(int i = 0; i < lines; i++) {
    if(i == 0 && c_values[i] != 0) { 
      comb_sum[0] = 1;
      total_combinations = 1;
    }
    else if(c_values[i] == 0) {break;}
    else {
      int d = std::min(c_values[i], i+1);
      total_combinations = recursive_comb(lines, columns, d, c_values, comb_sum, i);
      
      
    }
  }
  std::cout << total_combinations << std::endl;

  return 0;
}