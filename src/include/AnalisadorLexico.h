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
 * Lê o conteúdo de um arquivo ("arquivo_fonte.txt") e o armazena em um buffer
 * alocado dinamicamente. O tamanho do arquivo é determinado e o buffer é alocado
 * de acordo. Certifique-se de liberar a memória alocada para o buffer após o uso.
 */
void ler_arquivo(FILE *arquivo, char **buffer);

/* Verifica se o caractere atual no buffer indica um comentário. Se for um 
 * comentário de uma linha ou de múltiplas linhas, a função avança a posição 
 * no buffer adequadamente e atualiza a estrutura TInfoAtomo com a informação 
 * do tipo de átomo (COMENTARIO) e a linha onde foi encontrado.
 */
TInfoAtomo reconhece_comentario(TInfoAtomo infoAtomo, char *buffer, int *conta_linha, int *pos);

/*
 * Avança a posição no buffer para ignorar delimitadores, como espaços em branco, 
 * quebras de linha, tabulações e retornos de carro. Ela também atualiza o contador 
 * de linha conforme necessário.
 */
void descartar_delimitadores(char* buffer, int *conta_linha, int *pos);

/*
 * Analisa o conteúdo do buffer na posição atual e reconhece o tipo de átomo (token)
 * presente no código-fonte. Descarta delimitadores e chama funções específicas 
 * para identificar números, identificadores e comentários. A função atualiza a estrutura
 * TInfoAtomo com informações sobre o átomo e a linha onde foi encontrado.
 */
TInfoAtomo obter_atomo(char* buffer, int *conta_linha, int* pos);

/*
 * Reconhece e analisa números no buffer a partir da posição atual. Identifica 
 * números inteiros e números de ponto flutuante, atualiza a estrutura TInfoAtomo 
 * com informações sobre o número encontrado e retorna o tipo do átomo.
 */
TInfoAtomo reconhece_numero(char* buffer, int* pos);

/*
 * Reconhece e analisa identificadores (nomes de variáveis, funções, etc.) no buffer 
 * a partir da posição atual. Verifica se o identificador começa com uma letra minúscula 
 * e contém apenas letras minúsculas, dígitos ou underscores. Se o identificador tiver 
 * mais de 15 caracteres ou começar com uma letra maiúscula, a função retorna um erro.
 * Caso contrário, ela atualiza a estrutura TInfoAtomo com informações sobre o identificador
 * encontrado e retorna o tipo do átomo (IDENTIFICADOR).
 */
TInfoAtomo reconhece_id(char* buffer, int* pos);


void reconhece_palavra_reservada(TInfoAtomo *infoAtomo);

#endif
