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


void retornar_erro(TInfoAtomo *InfoAtomo, TAtomo atomo, TAtomo *lookahead)
{
    printf("#%03d: Erro sintatico: esperado [%s] encontrado [%s]\n", 
    InfoAtomo->linha, strAtomo[0][atomo], strAtomo[0][*lookahead]);
    exit(1);
}


int consome(TInfoAtomo *InfoAtomo, TAtomo atomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if (*lookahead == atomo)
    {
        *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        *lookahead = InfoAtomo->atomo;
        return 0;
    }
    return 1;
}


void programa(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if(consome(InfoAtomo, ALGORITMO, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ALGORITMO, lookahead);
    
    if(consome(InfoAtomo, IDENTIFICADOR, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, IDENTIFICADOR, lookahead);
    
    if(consome(InfoAtomo, PONTO_VIRGULA, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, PONTO_VIRGULA, lookahead);
    
    bloco(InfoAtomo, lookahead, buffer, conta_linha, pos);
    
    if(consome(InfoAtomo, PONTO, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, PONTO, lookahead);
}


void bloco(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char* buffer, int *conta_linha, int *pos)
{

}


void tipo(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    int pos_inicial = *pos;

    if(consome(InfoAtomo, LOGICO, lookahead, buffer, conta_linha, pos) == 1)
    {
        /*
         * Volta para onde estava e analisa e analisa mais uma vez para verificar
         * caso seja um atomo INTEIRO e não um LOGICO.
         */
        *pos = pos_inicial; 
        if(consome(InfoAtomo, INTEIRO, lookahead, buffer, conta_linha, pos) == 1)
            retornar_erro(InfoAtomo, INTEIRO, lookahead);
    }
}