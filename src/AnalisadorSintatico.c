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
#include "include/AnalisadorSemantico.h"


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
    if(*lookahead == VARIAVEL)
    {
        declaracao_de_variaveis(InfoAtomo, lookahead, buffer, conta_linha, pos);
    }

    comando_composto(InfoAtomo, lookahead, buffer, conta_linha, pos);
}


void declaracao_de_variaveis(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    int pos_inicial = *pos;
    if(consome(InfoAtomo, VARIAVEL, lookahead, buffer, conta_linha, pos) == 0)
    {

verifica_variaveis:
        
        // Cria a lista de variaveis.
        if (lista_variaveis == NULL)
        {
            criar_lista_variavel(1);
        }
        // Adicionar elemento na lista de variaveis.
        inserir_variavel_na_lista(InfoAtomo);

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
        // Verifica se nao existem variaveis com o mesmo nome.
        checar_variaveis();

        // Liberar o espaco alocado para a lista de variaveis.
        free_lista_variavel();
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
            // Adicionar elemento na lista de variaveis.
            inserir_variavel_na_lista(InfoAtomo);

            pos_inicial = *pos;
            if(consome(InfoAtomo, IDENTIFICADOR, lookahead, buffer, conta_linha, pos) == 1)
            {
                *pos = pos_inicial;
                retornar_erro(InfoAtomo, IDENTIFICADOR, lookahead);
            }
            // Adicionar elemento na lista de variaveis.
            inserir_variavel_na_lista(InfoAtomo);
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
            
            expressao(InfoAtomo, lookahead, buffer, conta_linha, pos);
            
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

    if( *lookahead == IGUAL || *lookahead == MENOR_IGUAL || *lookahead == MAIOR_IGUAL ||
        *lookahead == MENOR || *lookahead == MAIOR || *lookahead == CARDINAL)
    {
        relacional(InfoAtomo, lookahead, buffer, conta_linha, pos);
        expressao_simples(InfoAtomo, lookahead, buffer, conta_linha, pos);
    }
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


void comando_composto(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if(consome(InfoAtomo, INICIO, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, INICIO, lookahead);
    
    comando(InfoAtomo, lookahead, buffer, conta_linha, pos);

loop_cmd_compst:
    if(*lookahead == PONTO_VIRGULA)
    {
        *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        *lookahead = InfoAtomo->atomo;
        comando(InfoAtomo, lookahead, buffer, conta_linha, pos);
        goto loop_cmd_compst;
    }

    if(consome(InfoAtomo, FIM, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, FIM, lookahead);
}


void comando(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    switch (*lookahead)
    {
    case IDENTIFICADOR:
        comando_atribuicao(InfoAtomo, lookahead, buffer, conta_linha, pos);
        break;

    case SE:
        comando_se(InfoAtomo, lookahead, buffer, conta_linha, pos);
        break;

    case ENQUANTO:
        comando_enquanto(InfoAtomo, lookahead, buffer, conta_linha, pos);
        break;

    case LEIA:
        comando_entrada(InfoAtomo, lookahead, buffer, conta_linha, pos);
        break;

    case ESCREVA:
        comando_saida(InfoAtomo, lookahead, buffer, conta_linha, pos);
        break;

    case INICIO:
        comando_composto(InfoAtomo, lookahead, buffer, conta_linha, pos);
        break;
    
    default:
        retornar_erro(InfoAtomo, COMANDO, lookahead);
        break;
    }
    if( *lookahead == IDENTIFICADOR || *lookahead == SE || *lookahead == ENQUANTO ||
        *lookahead == LEIA || *lookahead == ESCREVA || *lookahead == INICIO)
    {

    }
}


void comando_atribuicao(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if(consome(InfoAtomo, IDENTIFICADOR, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, IDENTIFICADOR, lookahead);
    
    if(consome(InfoAtomo, ATRIBUICAO, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ATRIBUICAO, lookahead);

    expressao(InfoAtomo, lookahead, buffer, conta_linha, pos);
}


void comando_entrada(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if(consome(InfoAtomo, LEIA, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, LEIA, lookahead);
    
    if(consome(InfoAtomo, ABRE_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ABRE_PARENTESES, lookahead);
    
    lista_variavel(InfoAtomo, lookahead, buffer, conta_linha, pos);

    if(consome(InfoAtomo, FECHA_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, FECHA_PARENTESES, lookahead);
}


void comando_enquanto(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if(consome(InfoAtomo, ENQUANTO, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ENQUANTO, lookahead);

    if(consome(InfoAtomo, ABRE_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ABRE_PARENTESES, lookahead);

    expressao(InfoAtomo, lookahead, buffer, conta_linha, pos);

    if(consome(InfoAtomo, FECHA_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, FECHA_PARENTESES, lookahead);
    
    if(consome(InfoAtomo, FACA, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, FACA, lookahead);

    comando(InfoAtomo, lookahead, buffer, conta_linha, pos);
}


void comando_se(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if(consome(InfoAtomo, SE, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, SE, lookahead);

    if(consome(InfoAtomo, ABRE_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ABRE_PARENTESES, lookahead);

    expressao(InfoAtomo, lookahead, buffer, conta_linha, pos);

    if(consome(InfoAtomo, FECHA_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, FECHA_PARENTESES, lookahead);
    
    if(consome(InfoAtomo, ENTAO, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ENTAO, lookahead);

    comando(InfoAtomo, lookahead, buffer, conta_linha, pos);

    if(*lookahead == SENAO)
    {
        if(consome(InfoAtomo, SENAO, lookahead, buffer, conta_linha, pos) == 1)
            retornar_erro(InfoAtomo, SENAO, lookahead);

        comando(InfoAtomo, lookahead, buffer, conta_linha, pos);
    }
}


void comando_saida(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos)
{
    if(consome(InfoAtomo, ESCREVA, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ESCREVA, lookahead);
    
    if(consome(InfoAtomo, ABRE_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, ABRE_PARENTESES, lookahead);
    
    expressao(InfoAtomo, lookahead, buffer, conta_linha, pos);

loop_cmd_saida:
    if(*lookahead == VIRGULA)
    {
        *InfoAtomo = obter_atomo(buffer, conta_linha, pos);
        *lookahead = InfoAtomo->atomo;

        expressao(InfoAtomo, lookahead, buffer, conta_linha, pos);
        goto loop_cmd_saida;
    }

    if(consome(InfoAtomo, FECHA_PARENTESES, lookahead, buffer, conta_linha, pos) == 1)
        retornar_erro(InfoAtomo, FECHA_PARENTESES, lookahead);
}