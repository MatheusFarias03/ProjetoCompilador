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
#define _ANALISADOR_SINTATICO_H

#include "AnalisadorLexico.h"

void E(TAtomo lookahead, char *buffer, int *conta_linha, int *pos);
void consome(TAtomo atomo, TAtomo lookahead, char *buffer, int *conta_linha, int *pos);

#endif