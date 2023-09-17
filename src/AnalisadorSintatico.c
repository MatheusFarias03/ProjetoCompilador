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
#include "include/Itens.h"
#include "include/AnalisadorSintatico.h"
#include "include/AnalisadorLexico.h"

void consome(TInfoAtomo *InfoAtomo, TAtomo atomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if (*lookahead == atomo)
    {
        *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        *lookahead = InfoAtomo->atomo;
    }
    else
    {
        printf("#%03d: Erro sintatico: esperado [%s] encontrado [%s]\n", 
        InfoAtomo->linha, *strAtomo[atomo], *strAtomo[*lookahead]);
        exit(1);
    }
}

void programa(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    consome(InfoAtomo, ALGORITMO, lookahead, buffer, conta_linha, pos);
    consome(InfoAtomo, IDENTIFICADOR, lookahead, buffer, conta_linha, pos);
    consome(InfoAtomo, PONTO_VIRGULA, lookahead, buffer, conta_linha, pos);
    consome(InfoAtomo, PONTO, lookahead, buffer, conta_linha, pos);
}
