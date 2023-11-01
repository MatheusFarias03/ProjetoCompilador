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

#ifndef _ANALISADOR_SEMANTICO_H_
#define _ANALISADOR_SEMANTICO_H_

#include "Itens.h"

// IDENTIFICADOR:

// Aloca dinamicamente na memoria um espaco para criar a lista de variaveis.
void criar_lista_variavel(int tamanho);

// Aumenta o tamanaho da lista_variaveis.
void aumentar_lista(int tamanho);

// Insere uma variavel na lista_variaveis.
void inserir_variavel_na_lista(TInfoAtomo *atomo_variavel);

// Checa todas as variáveis para verificar se não há nenhuma repitida na lista.
void checar_variaveis();

/*
* Checa se uma determinada variável, passada como argumento, existe na lista
* lista_variaveis.
*/
int checar_variavel_existe(TInfoAtomo *atomo_variavel);

// Liberar a memória alocada dinamicamente para lista_variaveis
void free_lista_variavel();

// --------------------------------------------------------------------------------------

// EXPRESSAO:

// // Aloca dinamicamente na memoria um espaco para criar a lista para a expressao.
void criar_lista_expressao(int tamanho);

// Aumenta o tamanho da lista_expressao.
void aumentar_lista_expressao(int tamanho);

// Insere um InfoAtomo na lista.
void inserir_InfoAtomo_lista_expressao(TInfoAtomo *info_atomo);

// Liberar a memória alocada dinamicamente para lista_expressao
void free_lista_expressao();

/*
* Checar se não ocorre a mistura entre soma, subtracao e divisao com booleano em
* uma expressao.
*/
void avaliar_expressao();

#endif
