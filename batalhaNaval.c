#include <stdio.h>
#define TAMANHO_TABULEIRO 10 // tamanho do tabuleiro 10x10
#define POSICAO_HORIZONTAL 0 // representa a posição (navio) horizontal
#define POSICAO_VERTICAL 1 // representa a posição (navio) vertical
#define POSICAO_DIAGONAL 2 // representa a posição (navio) diagonal
#define POSICAO_DIAGONAL_SECUNDARIA 3 // representa a posição (navio) diagonal secundária
#define TAMANHO_NAVIO 3 // tamanho do vetor que representa o navio
#define QUANT_LINHAS_HABILIDADE 3 // quantidade de linhas da matriz de habilidade
#define QUANT_COLUNAS_HABILIDADE 5 // quantidade de colunas da matriz de habilidade


/*
 VARIÁVEIS
*/
int tabuleiro[10][10] =                         // inicializa a matrix 10x10 (tabuleiro) com valor 0 (água)
{
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int navioA[TAMANHO_NAVIO] = {3, 3, 3};  // representa o Navio A que fica na horizontal
int navioB[TAMANHO_NAVIO] = {3, 3, 3};  // Representa o Navio B que fica na vertical
int navioC[TAMANHO_NAVIO] = {3, 3, 3};  // Representa o Navio C que fica na diagonal
int navioD[TAMANHO_NAVIO] = {3, 3, 3};  // Representa o Navio D que fica na diagonal secundária

// coordenadas iniciais do navio A (horizontal)
int coordYnavioA = 9; // eixo y - vertical
int coordXnavioA = 0; // eixo x - horizontal

// posicionando navio B (vertical)
int coordYnavioB = 0; // eixo y - vertical
int coordXnavioB = 9; // eixo x - horizontal

// posicionando navio C (diagonal)
int coordYnavioC = 3; // eixo y - vertical
int coordXnavioC = 7; // eixo x - horizontal

int coordYnavioD = 0; // eixo y - vertical
int coordXnavioD = 8; // eixo x - horizontal

int habilidadeCone[QUANT_LINHAS_HABILIDADE][QUANT_COLUNAS_HABILIDADE]; // matriz que representa a habilidade Cone
int habilidadeCruz[QUANT_LINHAS_HABILIDADE][QUANT_COLUNAS_HABILIDADE]; // matriz que representa a habilidade Cruz
int habilidadeOctaedro[QUANT_LINHAS_HABILIDADE][QUANT_COLUNAS_HABILIDADE]; // matriz que representa a habilidade Octaedro

/*
Posiciona um navio dentro do tabuleiro
PARAMETROS:
  coordY: coordenada inicial do navio no eixo Y
  coordX: coordenada inicial do navio no eixo X
  posicao: vertical, horizontal, diagonal ou diagonal inversa
  navio: o array de 3 posições que representa o navio
RETORNOS:
  Retorna 0 se está tudo certo, 
  Retorna 1 se o navio não sobrepõe nenhum outro que já está no tabuleiro
*/
int posicionarNavio(int coordY, int coordX, int posicao, int navio[]){
  int valorAtual = 0;
  int foraDosLimites = verificarLimitesNavio(coordY, coordX, posicao); // verifica se coordenadas do navio dentro dos limites do tabuleiro, considerando a posição
  if(foraDosLimites == 1){ // se a função 'verificar limites' retorna 1, quer dizer que a coordenada do navio testado é inválida
    printf("Erro: Na coordenada atual Y: %d e X: %d, o navio extrapola os limites do tabuleiro!\n", coordY, coordX);
    return 1;
  }

  for(int i=0; i < TAMANHO_NAVIO; i++){ // percorre cada "peça" do navio para posicioná-la
    if(posicao == POSICAO_HORIZONTAL){  // se o navio está na horizontal, a peça deve ser colocada à direita
      valorAtual = tabuleiro[coordY][coordX+i]; // pega o valor atual daquela posição do tabuleiro para verificar se há sobreposição
      if(valorAtual == 3){  // se há sobreposição...
        printf("Erro: Sobreposição detectada nas coordendas Y: %d e X: %d\n", coordY, coordX+i);
        return 1; // sai da função com erro (1)
      }

      tabuleiro[coordY][coordX+i] = navio[i]; // o valor 3 é colocado em cada posição avançando pra direita (eixo x), visto que o navio está na horizontal
    } else if (posicao == POSICAO_VERTICAL) {
      valorAtual = tabuleiro[coordY+i][coordX];
      if(valorAtual == 3){
        printf("Erro: Sobreposição detectada nas coordendas Y: %d e X: %d\n", coordY+i, coordX);
        return 1;
      }
      tabuleiro[coordY+i][coordX] = navio[i]; // o valor 3 é colocado em cada posição avançando pra baixo (eixo y), visto que o navio está na vertical
    } else if (posicao == POSICAO_DIAGONAL) {
      valorAtual = tabuleiro[coordY+i][coordX+i];
      if(valorAtual == 3){
        printf("Erro: Sobreposição detectada nas coordendas Y: %d e X: %d\n", coordY+i, coordX+i);
        return 1;
      }
      tabuleiro[coordY+i][coordX+i] = navio[i]; // o valor 3 é colocado em cada posição avançando pra baixo e pra direita visto que o navio está na diagonal primária
    } else if (posicao == POSICAO_DIAGONAL_SECUNDARIA) {
      valorAtual = tabuleiro[coordY+i][coordX-i];
      if(valorAtual == 3){
        printf("Erro: Sobreposição detectada nas coordendas Y: %d e X: %d\n", coordY+i, coordX-i);
        return 1;
      }
      tabuleiro[coordY+i][coordX-i] = navio[i]; // o valor 3 é colocado em cada posição avançando pra baixo e pra esquerda visto que o navio está na diagonal secundária
    }
  }

  return 0;
}

/*
Verifica se as coordenadas iniciais dos navios estão dentro do limite do tabuleiro
PARAMETROS:
  coordY: coordenada inicial do navio no eixo Y
  coordX: coordenada inicial do navio no eixo X
  posicao: vertical, horizontal, diagonal ou diagonal inversa
RETORNOS:
  Retorna 0 se está tudo certo, dentro do limite
  Retorna 1 se está fora do limite
*/
int verificarLimitesNavio(int coordY, int coordX, int posicao){
  // se a coordenada x ou y for maior que 10 ou menor que 0 já retorna 1 (erro)
  if(coordX < 0 || coordY < 0 || coordX >= TAMANHO_TABULEIRO || coordY >= TAMANHO_TABULEIRO) {
    return 1;
  }

  if(posicao == POSICAO_HORIZONTAL && 
      coordX +TAMANHO_NAVIO > TAMANHO_TABULEIRO  // verifica se a parte do navio avançou o lado direito do tabuleiro
  ){
    return 1; // retorna erro
  } else if (posicao == POSICAO_VERTICAL &&
      coordY +TAMANHO_NAVIO > TAMANHO_TABULEIRO // verifica se a parte do navio avançou o lado de baixo do tabuleiro
  ){
    return 1;
  } else if (posicao == POSICAO_DIAGONAL){
    for(int i=0; i < TAMANHO_NAVIO; i++){
      if(coordX+i >= TAMANHO_TABULEIRO){ // verifica se a parte do navio avançou o lado direito do tabuleiro
        return 1; // retorna erro
      } else if(coordY+i >= TAMANHO_TABULEIRO){  // verifica se a parte do navio avançou o lado de baixo do tabuleiro
        return 1; // retorna erro
      }
    }
  } else if (posicao == POSICAO_DIAGONAL_SECUNDARIA){
    for(int i=0; i < TAMANHO_NAVIO; i++){
      if(coordX-i < 0){ // verifica se a parte do navio avançou o lado esquerdo do tabuleiro
        return 1; // retorna erro
      } else if(coordY+i >= TAMANHO_TABULEIRO){ // verifica se a parte do navio avançou o lado de baixo do tabuleiro
        return 1; // retorna erro
      }
    }
  }
        
  return 0; // se não deu erro em nenhum checagem acima, então as coordenadas estão dentro do limite do tabuleiro
}

/*
Posiciona uma habilidade dentro do tabuleiro
PARAMETROS:
  habilidade: matriz que representa a habilidade
  coordCentralY: coordenada central onde ficará o centro da habilidade no tabuleiro (eixo Y)
  coordCentralX: coordenada central onde ficará o centro da habilidade no tabuleiro (eixo X)
RETORNOS:
  Retorna 0 se a habilidade foi posicionada com sucesso, dentro do limite
  Retorna 1 se a habilidade está fora do limite e não pode ser posicionada
*/
int posicionarHabilidade(int habilidade[QUANT_LINHAS_HABILIDADE][QUANT_COLUNAS_HABILIDADE], int coordCentralY, int coordCentralX){
  int coordInicialY = coordCentralY - 1; // coordenada Y do tabuleiro em que a primeira posição da habilidade será colocada
  int coordInicialX = coordCentralX - 2; // coordenada X do tabuleiro em que a primeira posição da habilidade será colocada
  int coordFinalY = coordCentralY + 1; // coordenada Y do tabuleiro em que a primeira posição da habilidade será colocada
  int coordFinalX = coordCentralX + 2; // coordenada X do tabuleiro em que a primeira posição da habilidade será colocada

  // verifica limites
  if(coordInicialX < 0 ||                                   // verifica se a primeira posição da habilidade está além do limite esquerdo do tabuleiro
      coordFinalX >= TAMANHO_TABULEIRO ||        // verifica se última posição da habilidade está além do limite direito do tabuleiro
      coordInicialY < 0 ||                                  // verifica se primeira posição da habilidade está além do limite superior do tabuleiro
      coordFinalY >= TAMANHO_TABULEIRO             // verifica se última posição da habilidade está além do limite inferior do tabuleiro
  ){
    return 1; // em qualquer um dos casos acima a habilidade está fora dos limites, então a função sai com retorno 1
  }

  // Posiciona a habilidade no tabuleiro
  int valorAtual;
  for (int i = 0; i < QUANT_LINHAS_HABILIDADE; i++) // percorre as colunas da matriz que representa a habilidade
  {
    for (int j = 0; j < QUANT_COLUNAS_HABILIDADE; j++){  // percorre as linhas da matriz que representa a habilidade
      valorAtual = tabuleiro[coordInicialY+i][coordInicialX+j]; 
      if(habilidade[i][j] == 5){  // só posiciona a habilidade na coordenada se o valor dela for 5 (área de efeito). Dessa forma evita-se colocar 0 em cima de um navio ou outra habilidade
        tabuleiro[coordInicialY+i][coordInicialX+j] = habilidade[i][j];
      } else {
        continue; // se na posição atual da habilidade o valor é 0 (sem efeito), então evitamos colocá-lo no tabuleiro e prosseguimos para a próxima iteração do loop
      }
    }
  }

  return 0; // retorna sucesso após posicionar a habilidade
}

int main(){
  /*
  CONSTRUINDO MATRIZ DAS HABILIDADES
  */
  // constrói a matriz para o Cone
  int colunaMeio = QUANT_COLUNAS_HABILIDADE / 2;
  for (int i = 0; i < QUANT_LINHAS_HABILIDADE; i++) {
    for (int j = 0; j < QUANT_COLUNAS_HABILIDADE; j++) {
      if(j >= colunaMeio-i && j <= colunaMeio +i){
        habilidadeCone[i][j] = 5;
      } else {
        habilidadeCone[i][j] = 0;
      }
    }
  }

  // constrói a matriz para a Cruz
  for (int i = 0; i < QUANT_LINHAS_HABILIDADE; i++) {
    for (int j = 0; j < QUANT_COLUNAS_HABILIDADE; j++) {
      if(i != 1 && j == colunaMeio){
        habilidadeCruz[i][j] = 5;
      } else if(i == 1){
        habilidadeCruz[i][j] = 5;
      } else {
        habilidadeCruz[i][j] = 0;
      }
    }
  }

  // constrói a matriz para o Octaedro
  // 
  for (int i = 0; i < QUANT_LINHAS_HABILIDADE; i++) {
    for (int j = 0; j < QUANT_COLUNAS_HABILIDADE; j++) {
      if(i != 1 && j == colunaMeio){
        habilidadeOctaedro[i][j] = 5;
      } else if(i == 1 && j > 0 && j != QUANT_COLUNAS_HABILIDADE-1){
        habilidadeOctaedro[i][j] = 5;
      } else {
        habilidadeOctaedro[i][j] = 0;
      }
    }
  }

  /*
  POSICIONANDO NAVIOS
  */
  int erroAoPosicionar = 0; // essa variável irá guardar o valor 0 ou 1 conforme o retorno da função 'posicionar navio'. 0 se a funcao retornou com sucesso e 1 se retornou com erro

  // posiciona navio A no tabuleiro
  erroAoPosicionar = posicionarNavio(coordYnavioA, coordXnavioA, POSICAO_HORIZONTAL, navioA); // posiciona o navio A nas coordenadas indicadas e na posição horizontal
  
  if(erroAoPosicionar == 1 ){
    printf("Erro: O navio A não pode ser posicionado!\n");
    return 1; // sai do jogo se deu algumm erro ao posicionar o navio
  }

  // posicionando navio B no tabuleiro
  erroAoPosicionar = posicionarNavio(coordYnavioB, coordXnavioB, POSICAO_VERTICAL, navioB); // posiciona o navio B nas coordenadas indicadas e na posição vertical

  if(erroAoPosicionar == 1 ){
    printf("Erro: O navio B não pode ser posicionado!\n");
    return 1; // sai do jogo se deu algumm erro ao posicionar o navio
  }

  // posiciona navio C no tabuleiro
  erroAoPosicionar = posicionarNavio(coordYnavioC, coordXnavioC, POSICAO_DIAGONAL, navioC); // posiciona o navio C nas coordenadas indicadas e na posição diagonal primária

  if(erroAoPosicionar == 1 ){
    printf("Erro: O navio C não pode ser posicionado!\n");
    return 1; // sai do jogo se deu algumm erro ao posicionar o navio
  }

  // posiciona navio D no tabuleiro
  erroAoPosicionar = posicionarNavio(coordYnavioD, coordXnavioD, POSICAO_DIAGONAL_SECUNDARIA, navioD); // posiciona o navio D nas coordenadas indicadas e na posição diagonal secundária

  if(erroAoPosicionar == 1 ){
    printf("Erro: O navio D não pode ser posicionado!\n");
    return 1; // sai do jogo se deu algumm erro ao posicionar o navio
  }

  /*
  POSICIONANDO HABILIDADES
  */
  int foraDosLimites = 0; // guarda o valor 0 ou 1 conforme o retorno da função 'posicionarHabilidade'. 0 se está dentro dos limites, 1 se está fora dos limites
  
  // posiciona cone
  foraDosLimites = posicionarHabilidade(habilidadeCone, 1, 2);
  if(foraDosLimites == 1){
    printf("Habilidade Cone está fora dos limites do tabuleiro!\n");
    return 1;
  }

  // posiciona cruz
  foraDosLimites = posicionarHabilidade(habilidadeCruz, 5, 2);
  if(foraDosLimites == 1){
    printf("Habilidade Cruz está fora dos limites do tabuleiro!\n");
    return 1;
  }

  foraDosLimites = posicionarHabilidade(habilidadeOctaedro, 8, 7);
  if(foraDosLimites == 1){
    printf("Habilidade Octaedro está fora dos limites do tabuleiro!\n");
    return 1;
  }


  /*
  IMPRIME TABULEIRO
  */
  printf("\n");
  for(int i=0; i < TAMANHO_TABULEIRO; i++){  // imprime da posição 0 até a posição 9 (eixo y / linhas)
    printf("%d - ", i);
    for(int j=0; j < TAMANHO_TABULEIRO; j++){  // imprime da posição 0 até a posição 9 (eixo x / colunas)
      printf("%d ", tabuleiro[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}