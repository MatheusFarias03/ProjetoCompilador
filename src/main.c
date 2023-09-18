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
#include "include/Itens.h"

int main()
{
	// Variaveis.

	FILE *arquivo;
	char *buffer; // Contem o arquivo em uma unica string.
	TInfoAtomo infoAtomo; // Informacoes do atomo.
	TAtomo lookahead;
	int conta_linha = 1;
	int pos = 0; // Posicao do caractere no buffer.

	ler_arquivo(arquivo, &buffer);

	printf("\nAnalisando arquivo...\n");

	infoAtomo = obter_atomo(buffer, &conta_linha, &pos);
	lookahead = infoAtomo.atomo; 

	//programa(&infoAtomo, &lookahead, buffer, &conta_linha, &pos);
	tipo(&infoAtomo, &lookahead, buffer, &conta_linha, &pos);
	consome(&infoAtomo, EOS, &lookahead, buffer, &conta_linha, &pos);

	printf("\nAnalise finalizada com sucesso.\n");

	free(buffer);

	return 0;
}
