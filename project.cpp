#include <vector>
#include <iostream>

typedef std::vector<std::vector<int>> matrix;

int nofways(int n, int m, int d, int c_values[], int i_line, int count, int comb_sum[]) {
  
  if(d == 1) { 
    return count;
  }
  else if(d == c_values[i_line] && i_line + 1 == d) { //caso em q um quadrado preenche a primeira linha toda e chega ao fundo da matriz
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
  /////////////////////////////////////////////////////////////////

  else if(d < c_values[i_line]) { // casos em q ha mais q um quadrado na primeira linha
    
    if(i_line + 1 == d) { //casos em q o quadrado n preenche a linha toda mas chega ao fundo da matriz
      
      if(c_values[i_line] - d >= d) { //se der pra fzr da mesma dimensao ao lado direito 
        int aux_value = 0;
        for(int i = d-1; i <=(c_values[i_line] -d);i++) {
          int c_aux_values[n];
          int line_counter = 0;
          for(int j = 0; j <= i_line; j++) { // mete os valores que sobram de cada linha no novo array
            c_aux_values[j] = c_values[j] - d -(i-1);
            line_counter++;
          }
          aux_value = i;
          count += 1 + nofways(n, c_aux_values[i_line],std::min(d,c_aux_values[i_line]), c_aux_values, i_line, 0, comb_sum);
          if(c_aux_values[i_line] == 1) {count++;}
        }
        int c_aux_values[n];
        int line_counter = 0;
        int i = aux_value +1;
        for(int j = 0; j <= i_line; j++) { // mete os valores que sobram de cada linha no novo array
          c_aux_values[j] = c_values[j] - d -(i-1);
          line_counter++;
        }
        count+= nofways(n, c_aux_values[i_line] - i, d, c_aux_values, i_line, 0, comb_sum);

      }
      else if(c_values[i_line]-d > 0){// nao da pra fzr outro da mesma dimensao mas da pra continuar a calcular
        int c_aux_values[n];
        for(int i = 0; i <= i_line; i++) { // mete os valores que sobram de cada linha no novo array
          c_aux_values[i] = c_values[i] - d;
        }
        count += 1 + c_values[i_line] - d +  nofways(n, c_aux_values[0], std::min(d,c_aux_values[i_line]),c_aux_values , i_line, 0, comb_sum);
      }
      //nao existe o caso de c_values[i_line]-d = 0 , pois vai a um if de cima quando o quadrado preenche a linha na totalidade e chega ao fundo da matriz 
    
    }
  
      
    else if(i_line + 1 > d ) {//caso em q n preenche a linha toda e n chega ao fundo da matriz
      if(c_values[i_line] == d +1) { //caso de haver dois quadrados em cima
        //std::cout << d << " " << i_line << std::endl;
        int c_aux_values[n];
        int cl_aux_values[n];
        int line_counter = 0;
        for(int i = 0; i < i_line; i++) { // mete os valores que sobram de cada linha no novo array
          if(i >= ((i_line-d)+1) && i != i_line) {
            c_aux_values[i] = c_values[i] - d;
            cl_aux_values[i] = c_values[i] - d - 1;
            line_counter++;
          }
          else if(i <= ((i_line-d)+1) && i!= i_line) {
            c_aux_values[i] = c_values[i];
            cl_aux_values[i] = c_values[i];
            line_counter++;
          }
        }

        count += 1 + nofways(line_counter,m,std::min(line_counter, m), c_aux_values, line_counter-1, 0, comb_sum); //primeiro quadrado da esq em cima, o count vai a zero pois estamos a somar restos
        count += 1 + nofways(line_counter,m,std::min(line_counter, m), cl_aux_values, line_counter-1, 0, comb_sum); // quadrado de cima da direita
      }
      else {
        int rest_columns = c_values[i_line] - d;
        if(c_values[i_line] - d == d) {count++;}////////////falta contar combinaçoes possiveis em baixo tmb 
        for(int i = 0; i <= rest_columns; i++) {
          int c_aux_values[n];
          int line_counter = 0;
          for(int j = 0; j < i_line; j++) { // mete os valores que sobram de cada linha no novo array
            if(j >= ((i_line-d)+1) && j != i_line) {
              c_aux_values[j] = c_values[j] - d- i;
              line_counter++;
            }
            else if(j <= ((i_line-d)+1) && j!= i_line) {
              c_aux_values[j] = c_values[j];
              line_counter++;
            }
          }

          count += 1 + nofways(line_counter,m,std::min(line_counter, m), c_aux_values, line_counter-1, 0, comb_sum); 
          if(i >= d ) {                /////////lado 
            int cl_aux_values[n]; //os q sobram do lado esq
            int line_counter = 0;
            for(int j = 0; j <= i_line; j++) { // mete os valores que sobram de cada linha no novo array
              cl_aux_values[j] = i;
              line_counter++;
              
            }
            count += 1 +  nofways(line_counter, i, std::min(line_counter, i), cl_aux_values, i-1, 0, comb_sum);
          }
        }
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////
  else if(d == c_values[i_line] && i_line + 1 > d) {  //caso em q um quadrado preenche a primeira linha toda mas n chega ao fundo da matriz
    int verify = 0;
    for(int i = i_line-1; i > i_line-d; i--){
      if(c_values[i] == c_values[i_line]) {
        verify = 1;
        break;
      }
      else {
        verify = 0;
      }
    }
    if(verify == 1) { //caso em q ao "tirar" o quadrado da primeira linha obtemos uma forma perfeita em baixo ja calculada
      count += comb_sum[i_line-d];
    }
    else {
      int c_aux_values[n];
      int line_counter = 0;
      for(int i = 0; i < i_line; i++) { // mete os valores que sobram de cada linha no novo array
        if(i >= ((i_line-d)+1) && i != i_line) {
          c_aux_values[i] = c_values[i] - d;
          line_counter++;
        }
        else if(i <= ((i_line-d)+1) && i!= i_line) {
          c_aux_values[i] = c_values[i];
          line_counter++;
        }
      }
      count += 1 + nofways(line_counter,m,std::min(line_counter, m), c_aux_values, line_counter-1, 0, comb_sum); //primeiro quadrado da esq em cima, o count vai a zero pois estamos a somar restos
    }
  }

  
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
  else if(d == 1 && i_line != 0) {
    comb = 0;
  }
  else if(d > 2) {
    for(int i = d; i >= 2; i--) {
      comb += nofways(n , m, i, c_values, i_line, 0, comb_sum);
    }
  }
  else {
    comb += nofways(n, m, d, c_values, i_line, 0, comb_sum);
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