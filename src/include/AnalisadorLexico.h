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

#ifndef _ANALISADOR_LEXICO_H_
#define _ANALISADOR_LEXICO_H_

#include "Itens.h"
/*
 * Esta função lê o conteúdo de um arquivo ("arquivo_fonte.txt") e o armazena
 * em um buffer alocado dinamicamente. O tamanho do arquivo é determinado e
 * o buffer é alocado de acordo. Certifique-se de liberar a memória alocada
 * para o buffer após o uso.
 */
void ler_arquivo(FILE *arquivo, char **buffer);

TInfoAtomo reconhece_comentario(TInfoAtomo infoAtomo, char *buffer, int *conta_linha, int *pos);

void descartar_delimitadores(char* buffer, int *conta_linha, int *pos);

TInfoAtomo obter_atomo(char* buffer, int *conta_linha, int* pos);

TInfoAtomo reconhece_numero(char* buffer, int* pos);

TInfoAtomo reconhece_id(char* buffer, int* pos);

#endif
