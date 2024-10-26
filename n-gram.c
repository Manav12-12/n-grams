#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void ngram_Generator(float K[27][27]){

  //open the file to read from
  FILE *file = fopen("names.txt", "r");
  char line[100];
  line[0] = '!';
  while(fgets(line + 1 , 99 , file)){
    int len = strlen(line);
    line[len - 2] = '\0';
    for(int i = 1; line[i]!= '\0'; i++){
        K[line[i - 1] - 'a' + 1][line[i] - 'a' + 1]++;
      
    }


  }
    fclose(file);

}

//normalizing the matrix

void normalize(float K[27][27]){
  for(int i = 1; i < 27; i++){
    float sum = 0;
    for(int j = 1; j < 27; j++){
      sum += K[i][j];
    }
    for(int j = 1; j < 27; j++){
      K[i][j] /= sum;
    }
  }
}

//generating the next character

char next_Char(float K[27][27], char c){

  float r = (float)rand() / RAND_MAX;
  float sum = 0;
  for(int i = 1; i < 27; i++){
    sum += K[c - 'a' + 1][i];
    if(sum > r){
      return i + 'a' - 1;
    }
  }
  return '!';
}

//generating the next name depending on your task you may alter this generator function 

void next_Name(float K[27][27], char name[100]){
  name[0] = 'a' + (rand() % 26);
  int length = 3 + (rand() % 6);
  for(int i = 1; i < length; i++){
    name[i] = next_Char(K, name[i - 1]);
    
    }
    name[length] = '\0';
  }


//the main function 

int main(){
    srand(time(NULL));
    float K[27][27] = {0};
    

    ngram_Generator(K);
    normalize(K);
    char name[100];
    for(int i = 0; i < 30; i++){
      next_Name(K, name);
      printf("%s\n", name);
  }
  return 0;
}

