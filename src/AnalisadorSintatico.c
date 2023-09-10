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
#include "include/AnalisadorSintatico.h"
#include "include/AnalisadorLexico.h"

void consome(TAtomo atomo, TAtomo lookahead, char *buffer, int *conta_linha, int *pos)
{
    if (lookahead == atomo)
    {
        InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        lookahead = InfoAtomo.atomo = IDENTIFICADOR;
    }
    else
    {
        printf("#%03d: Erro sintatico: esperado [%s] encontrado [%s]\n", InfoAtomo.linha, strAtomo[atomo], strAtomo[lookahead]);
        exit(1);
    }
}

void E(TAtomo lookahead, char *buffer, int *conta_linha, int *pos)
{
    switch (lookahead)
    {
    case OP_SOMA:
        consome(OP_SOMA, buffer, conta_linha, pos);
        break;

    case OP_MULT:
        consome(OP_MULT, buffer, conta_linha, pos);
        break;

    case IDENTIFICADOR:
        consome(IDENTIFICADOR, buffer, conta_linha, pos);
        break;
    
    default:
        consome(NUMERO, buffer, conta_linha, pos);
        break;
    }
}