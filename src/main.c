/*
 *  Autor: Matheus Farias de Oliveira Matsumoto
 *  TIA: 32138271
 * 
 *  Nao eh permitido o uso deste arquivo para outros alunos que estao cursando a materia de
 *  compiladores do sexto semestre do curso de Ciencia da Computacao, 2023, na Universidade
 *  Presbiteriana Mackenzie.
 * 
 *  Link: https://github.com/MatheusFarias03/ProjetoCompilador 
 */

#include <stdio.h>
#include <stdlib.h>
#include "include/AnalisadorLexico.h"
#include "include/AnalisadorSintatico.h"

int main()
{
	// Variaveis.
	FILE *arquivo;
	char *buffer; // Contem o arquivo em uma unica string.
	TInfoAtomo infoAtomo; // Informacoes do atomo.
	TAtomo lookahead;
	int conta_linha = 1;
	int pos = 0; // Posicao do caractere no buffer.

	// Leitura do "arquivo_fonte.txt".
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

	buffer = (char*)malloc(tamanho + 1);

	if(buffer == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		fclose(arquivo);
		return 1;
	}

	// Ler caracteres do arquivo para o buffer.
	fread(buffer, sizeof(char), tamanho, arquivo);
	buffer[tamanho] = '\0';

	printf("Realizando analise lexica...\n");

	do 
	{
		infoAtomo = obter_atomo(buffer, &conta_linha, &pos);
		lookahead = infoAtomo.atomo;

		if(infoAtomo.atomo == NUMERO)
			printf("#%3d:NUMERO atributo = [%.2f]\n", infoAtomo.linha, infoAtomo.atributo_numero);
		
		else if(infoAtomo.atomo == IDENTIFICADOR)
			printf("#%3d:IDENTIFICADOR atributo = [%s]\n", infoAtomo.linha, infoAtomo.atributo_ID);
		
		else if(infoAtomo.atomo == EOS)
			printf("#%3d:Analise Lexica encerrada com sucesso.\n", infoAtomo.linha);
		
		else if(infoAtomo.atomo == ERRO)
			printf("#%3d:Erro Lexico\n",infoAtomo.linha);

	} while(infoAtomo.atomo != EOS && infoAtomo.atomo != ERRO);

	printf("Fim do programa.");

	free(buffer);
	fclose(arquivo);

	return 0;
}
