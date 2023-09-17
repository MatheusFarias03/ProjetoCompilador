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

#ifndef _ANALISADOR_SINTATICO_H_
#define _ANALISADOR_SINTATICO_H_

#include "AnalisadorLexico.h"
#include "Itens.h"

/*
 * Esta função compara o átomo atual (lookahead) com um átomo esperado (atomo).
 * Se eles forem iguais, a função obtém um novo átomo do buffer e atualiza a 
 * estrutura TInfoAtomo com as informações do novo átomo. O lookahead também é 
 * atualizado. Caso contrário, a função imprime uma mensagem de erro sintático 
 * indicando o átomo esperado e o átomo encontrado, e encerra o programa.
 */
void consome(TInfoAtomo *InftoAtomo, TAtomo atomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <programa>::= "algoritmo identificador" ";" <bloco> "."
void programa(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

#endif