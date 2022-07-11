#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

using namespace std;

int main(int argc, char **argv) {
	char filepath[255] = "relatorios/mainrightloop/";
	strcat(filepath, argv[1]);
	ofstream outfile;
	outfile.open(filepath, ios::app);	

	auto start = std::chrono::system_clock::now();
	int nImages = atoi(argv[1]), i;

	for(i = 0; i < nImages; i++){
		int width, height, channels;
		int lin, col, chan;
		
		//Carregadno imagem
		char path[255] = "imagens/input/textura", index[2];
		if(i >= 10) {
			path[21] = i/10 + 48;
			path[22] = i%10 + 48;
		}
		else {
			path[21] = i+48;
		}
		strcat(path,".jpg");
		
		unsigned char *img = stbi_load(path, &width, &height, &channels, 0);
		if(img == NULL) {
			printf("Error in loading the image\n");
			continue;
		}
	
		//Transformacao de array para matriz
		unsigned char img_mat[width][height][channels];
		unsigned char *p = img;
		for(lin = 0; lin < width; lin++){
			for(col = 0; col < height; col++){
				for(chan = 0; chan < channels; chan++){
					img_mat[lin][col][chan] = *(p++);
				}			
			}
		}	
		
		//Negativo
		for(lin = 0; lin < width; lin++){
			for(col = 0; col < height; col++){
				for(chan = 0; chan < channels; chan++){
					img_mat[lin][col][chan] =  255 - img_mat[lin][col][chan];
				}
			}
		}
		
		//Controle de brilho
		int c  = rand() % 256;;
		for(lin = 0; lin < width; lin++){
			for(col = 0; col < height; col++){
				for(chan = 0; chan < channels; chan++){
					img_mat[lin][col][chan] = img_mat[lin][col][chan] + c;
					img_mat[lin][col][chan] = (img_mat[lin][col][chan] > 255) ? 255 : img_mat[lin][col][chan];
				}
			}
		}
		
		//Limiarizacao
		int upLim = rand() %256, downLim = rand() %256;
		for(lin = 0; lin < width; lin++){
			for(col = 0; col < height; col++){
				for(chan = 0; chan < channels; chan++){
					if(img_mat[lin][col][chan] > upLim){
						img_mat[lin][col][chan] = 255;
					} else if (img_mat[lin][col][chan] < downLim){
						img_mat[lin][col][chan] = 0;
					}
				}
			}
		}
		
		//Filtro de media
		for(lin = 0; lin < width; lin++){
			for(col = 0; col < height; col++){
				for(chan = 0; chan < channels; chan++){
					unsigned char valores[9];
					int index = 0;
					
					for (int j = lin - 1; j <= lin + 1; j++) {
						for (int k = col - 1; k <= col + 1; k++){
							if (j < 0 || j >= width ){
								valores[index++] = 0;
							} 
							else if (k < 0 || k >= height ){
								valores[index++] = 0;
							} else {
								valores[index++] = img_mat[j][k][chan];	
							}
						}
					}

					int sum = 0;
					for (int j = 0; j < 9; j++) {
						sum += valores[j];
					}
					
					img_mat[lin][col][chan] = sum / 9;
				}
			}
		}
		
		//Volta para array
		p = img;
		for(lin = 0; lin < width; lin++){
			for(col = 0; col < height; col++){
				for(chan = 0; chan < channels; chan++){
					*(p++) = img_mat[lin][col][chan];
				}
			}
		}
				
		//Salvando imagem
		char outpath[255] ="imagens/output/texture";
		if(i >= 10) {
			outpath[21] = i/10 + 48;
			outpath[22] = i%10 + 48;
		}
		else {
			outpath[21] = i +48;
		}
		strcat(outpath,".jpg");
		stbi_write_jpg(outpath, width, height, channels, img, width*height);
	}

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end-start;
	outfile << elapsed_seconds.count() << "\n";

	return 0;
}
