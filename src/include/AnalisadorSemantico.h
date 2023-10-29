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

// Aloca dinamicamente na memoria um espaco para criar a lista de variaveis.
void criar_lista_variavel(int tamanho);

void aumentar_lista(int tamanho);

void inserir_variavel_na_lista(TInfoAtomo *atomo_variavel);

void checar_variaveis();

// Liberar a memória alocada dinamicamente para lista_variaveis
void free_lista_variavel();

#endif
