# Otimização de Algoritmos Mal Construídos

## Main-Wrong

Esta é a versão  mais ineficiente do programa pois não otimiza o acesso a memória cache. Os elementos das matrizes que representam as imagens são acessados de forma ineficiente como pode ser visto a seguir:

```C++
int c = rand() % 256;;
for(chan = 0; chan < channels; chan++){ //CANAL
	for(col = 0; col < height; col++){ //COLUNA
		for(lin = 0; lin < width; lin++){ //LINHA
			img_mat[lin][col][chan] = img_mat[lin][col][chan] + c;  //ADICAO DE BRILHO
			img_mat[lin][col][chan] = (img_mat[lin][col][chan] > 255) ? 255 : img_mat[lin][col][chan];
		}
	}
}
```

## Main-LoopFusion

Esta versão é um pouco mais otimizado que a primeira pois utiliza fusão de loops agrupando várias operações num mesmo loop fazendo com que o tempo de execução diminua:

```C++
int c = rand() % 256, upLim = rand() %256, downLim = rand() %256;	
for( chan = 0; chan < channels; chan++){ //CANAL
	for(col = 0; col < height; col++){ //COLUNA
		for(lin = 0; lin < width; lin++){ //LINHA
			img_mat[lin][col][chan] =  255 - img_mat[lin][col][chan]; //NEGATIVO
					 
			img_mat[lin][col][chan] = img_mat[lin][col][chan] + c;  //ADICAO DE BRILHO
			img_mat[lin][col][chan] = (img_mat[lin][col][chan] > 255) ? 255 : img_mat[lin][col][chan];

			if(img_mat[lin][col][chan] > upLim){     //LIMIARIZAÇÃO
				img_mat[lin][col][chan] = 255;
			} else if (img_mat[lin][col][chan] < downLim){
				img_mat[lin][col][chan] = 0;
			}
		}			
	}
} 
```

## Main-RightLoop

Esta versão é um pouco mais eficiente que as primeiras apesar de não estar otimizada. Essa eficiência vem simplesmente pelo fato de acessar as matrizes que representam as imagens de forma correta:

```C++
int c  = rand() % 256;;
for(lin = 0; lin < width; lin++){ //LINHA
	for(col = 0; col < height; col++){ //COLUNA
		for(chan = 0; chan < channels; chan++){ //CANAL
			img_mat[lin][col][chan] = img_mat[lin][col][chan] + c; //ADICAO DE BRILHO
			img_mat[lin][col][chan] = (img_mat[lin][col][chan] > 255) ? 255 : img_mat[lin][col][chan];
		}
	}
}
```

## Main-RightLoopFusion

Esta é a versão mais eficiente sem utilizar paralelismo pois, além de acessar corretamente as matrizes das imagens, também utiliza a técnica de fusão de loops:

```C++
unsigned char img_mat[width][height][channels];
unsigned char *p = img;
int c = rand() % 256, upLim = rand() %256, downLim = rand() %256;	
for(lin = 0; lin < width; lin++){ //LINHA
	for(col = 0; col < height; col++){ //COLUNA
		for(chan = 0; chan < channels; chan++){ //CANAL
			img_mat[lin][col][chan] = *(p++); //TRANSFORMACAO DA IMAGEM DE PONTEIRO PARA MATRIZ
					
			img_mat[lin][col][chan] =  255 - img_mat[lin][col][chan];  //NEGATIVO
					
			img_mat[lin][col][chan] = img_mat[lin][col][chan] + c; //ADICAO DE BRILHO
			img_mat[lin][col][chan] = (img_mat[lin][col][chan] > 255) ? 255 : img_mat[lin][col][chan];
					
			if(img_mat[lin][col][chan] > upLim) { //LIMIARIZACAO
				img_mat[lin][col][chan] = 255;
			} else if (img_mat[lin][col][chan] < downLim) {
				img_mat[lin][col][chan] = 0;
			}
					
		}			
	}
} 
```
## Main-RightLoopFusionParallel

O paralelismo foi usado na versão final do programa para realizar toda a parte do processamento que poderia ser paralelizada. A parte do código utilizando o OpenMP é apresentado abaixo:

```C++
int c = rand() % 255, upLim = rand() % 255, downLim = rand() % 255;	
#pragma omp parallel for collapse(3) // PARALELISMO
for(lin = 0; lin < width; lin++){ //LINHA
	for(col = 0; col < height; col++){ //COLUNA
		for(chan = 0; chan < channels; chan++){	//CANAL
			img_mat[lin][col][chan] =  255 - img_mat[lin][col][chan]; //NEGATIVO
				 
			img_mat[lin][col][chan] = img_mat[lin][col][chan] + c; //ADICAO DE BRILHO
			img_mat[lin][col][chan] = (img_mat[lin][col][chan] > 255) ? 255 : img_mat[lin][col][chan];
					
			if(img_mat[lin][col][chan] > upLim){ //LIMIARIZACAO
				img_mat[lin][col][chan] = 255;
			} else if (img_mat[lin][col][chan] < downLim){
				img_mat[lin][col][chan] = 0;
			}
						
		}			
	}
}
```

# Resultados

Os testes realizados com as versões não otimizadas e sem paralelismo foram feitos com 2, 4, 8 e 16 imagens. E os testes
realizados com a versão paralela do programa foram feitos com 16 imagens e com 2, 4, 8 e 32 threads. O resultados do desempenho 
de cada versão do código sem paralelismo pode ser vista no gráfico abaixo.

<img src="/graficos/N° de imagens X Tempo médio de execução.png" align="middle" >

É possível perceber que o tempo médio de execução de cada uma das versões sem paralelismo aumenta quase que linearmente em 
relação ao número de imagens processadas. Na versão com paralelismo, percebemos que o efeito é um pouco diferente, para um número pequeno de threads temos um tempo de execução médio maior para 16 imagens, mas quando aumentamos o número de threads o tempo 
médio de execução diminui até se torna praticamente constante.

<img src="/graficos/N° de threads X Tempo de execução médio.png" align="middle" >

Uma possível causa para a versão do programa que possui paralelismo ser menos eficiente quando utilizadas poucas threads é a de 
que o custo para gerenciar a poucas threads somado ao custo de cada uma das threads de realizar o sua execução contribui para que resultado final não seja o mais eficiente.