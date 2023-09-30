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


void declaracao_de_variaveis(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    int pos_inicial = *pos;
    if(consome(InfoAtomo, VARIAVEL, lookahead, buffer, conta_linha, pos) == 0)
    {

verifica_variaveis:
        lista_variavel(InfoAtomo, lookahead, buffer, conta_linha, pos);
        if(consome(InfoAtomo, DOIS_PONTOS, lookahead, buffer, conta_linha, pos) == 1)
            retornar_erro(InfoAtomo, DOIS_PONTOS, lookahead);
        tipo(InfoAtomo, lookahead, buffer, conta_linha, pos);
        if(consome(InfoAtomo, PONTO_VIRGULA, lookahead, buffer, conta_linha, pos) == 1)
            retornar_erro(InfoAtomo, PONTO_VIRGULA, lookahead);
        
        pos_inicial = *pos;
        if(consome(InfoAtomo, IDENTIFICADOR, lookahead, buffer, conta_linha, pos) == 0)
        {
            *pos = pos_inicial;
            InfoAtomo->atomo = IDENTIFICADOR;
            *lookahead = IDENTIFICADOR;
            goto verifica_variaveis;
        }
        else
        {
            *pos = pos_inicial;
        }
    }
    else
    {
        retornar_erro(InfoAtomo, VARIAVEL, lookahead);
    }
}


void lista_variavel(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    int pos_inicial = *pos;
    if(consome(InfoAtomo, IDENTIFICADOR, lookahead, buffer, conta_linha, pos) == 0)
    {
        pos_inicial = *pos;
        while(consome(InfoAtomo, VIRGULA, lookahead, buffer, conta_linha, pos) == 0)
        {
            pos_inicial = *pos;
            if(consome(InfoAtomo, IDENTIFICADOR, lookahead, buffer, conta_linha, pos) == 1)
            {
                *pos = pos_inicial;
                retornar_erro(InfoAtomo, IDENTIFICADOR, lookahead);
            }
        }
    }
    else
    {
        *pos = pos_inicial;
        retornar_erro(InfoAtomo, IDENTIFICADOR, lookahead);
    }
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


void relacional(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    switch (*lookahead)
    {
    case IGUAL:
        break;
    
    case MENOR:
        break;

    case MENOR_IGUAL:
        break;

    case MAIOR:
        break;
    
    case MAIOR_IGUAL:
        break;

    case CARDINAL:
        break;
    
    default:
        retornar_erro(InfoAtomo, RELACIONAL, lookahead);
        break;
    }
    
    *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
    *lookahead = InfoAtomo->atomo;
}


void fator(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    int fechou_parenteses = 1;

    switch (*lookahead)
    {
    case IDENTIFICADOR:
        break;
    
    case NUMERO:
        break;
    
    case VERDADEIRO:
        break;

    case FALSO:
        break;
    
    case ABRE_PARENTESES:
        {
            *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
            *lookahead = InfoAtomo->atomo;
            
            // TODO: expressao();
            
            if(consome(InfoAtomo, FECHA_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
                retornar_erro(InfoAtomo, FECHA_PARENTESES, lookahead);
            fechou_parenteses = 0;
        }
        break;
    
    default:
        retornar_erro(InfoAtomo, FATOR, lookahead);
        break;
    }

    if (fechou_parenteses != 0)
    {
        *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        *lookahead = InfoAtomo->atomo;
    }
    
}


void expressao(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    expressao_simples(InfoAtomo, lookahead, buffer, conta_linha, pos);
    // TODO: relacional();
    // TODO: expressao_simples();
}


void expressao_simples(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if(*lookahead == MAIS || *lookahead == MENOS)
    {
        *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        *lookahead = InfoAtomo->atomo;
    }

    termo(InfoAtomo, lookahead, buffer, conta_linha, pos);

loop_ex_simp:
    if (*lookahead == MAIS || *lookahead == MENOS || *lookahead == OU)
    {
        *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        *lookahead = InfoAtomo->atomo;

        termo(InfoAtomo, lookahead, buffer, conta_linha, pos);

        goto loop_ex_simp;
    }
}


void termo(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    fator(InfoAtomo, lookahead, buffer, conta_linha, pos);

termo_loop:
    if (*lookahead == ASTERISCO || *lookahead == DIV || *lookahead == E)
    {
        *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        *lookahead = InfoAtomo->atomo;
        fator(InfoAtomo, lookahead, buffer, conta_linha, pos);
        goto termo_loop;
    }
    
}