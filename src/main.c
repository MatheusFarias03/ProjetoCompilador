#include <stdio.h>
#include <stdlib.h>
#include "include/TInfoAtomo.h"

int main()
{
	FILE *arquivo;
	arquivo = fopen("src/arquivo_fonte.txt", "r");

	if(arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return 1;
	}

	// Determina o tamanho do arquivo.
	fseek(arquivo, 0, SEEK_END);
	long tamanho = ftell(arquivo);
	fseek(arquivo, 0, SEEK_SET);

	char *buffer = (char*)malloc(tamanho + 1);

	if(buffer == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		fclose(arquivo);
		return 1;
	}

	// Ler caracteres do arquivo para o buffer.
	fread(buffer, sizeof(char), tamanho, arquivo);
	buffer[tamanho] = '\0';

	printf("Realizando analise lexica...");
		
	TInfoAtomo infoAtomo;
	int conta_linha = 1;
	int pos = 0;

	do 
	{
		infoAtomo = obter_atomo(buffer, &conta_linha, &pos);
		if(infoAtomo.atomo == NUMERO)
		{
			printf("#%3d:NUMERO atributo = [%.2f]\n", infoAtomo.linha, infoAtomo.atributo_numero);
		}
		else if(infoAtomo.atomo == IDENTIFICADOR)
		{
			printf("#%3d:IDENTIFICADOR atributo = [%s]\n", infoAtomo.linha, infoAtomo.atributo_ID);
		}
		else if(infoAtomo.atomo == EOS)
		{
			printf("#%3d:Analise Lexica encerrada com sucesso.\n", infoAtomo.linha);
		}
		else if(infoAtomo.atomo == ERRO)
		{
			printf("#%3d:Erro Lexico\n",infoAtomo.linha);
		}

	} while(infoAtomo.atomo != EOS && infoAtomo.atomo != ERRO);

	printf("Fim do programa.");

	free(buffer);
	fclose(arquivo);

	return 0;
}
