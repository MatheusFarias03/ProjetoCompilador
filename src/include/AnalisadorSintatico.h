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
* Esta função imprime uma mensagem de erro indicando a linha onde ocorreu o erro,
* o token esperado e o token encontrado. Em seguida, encerra o programa.
*/
void retornar_erro(TInfoAtomo *InfoAtomo, TAtomo atomo, TAtomo *lookahead);

/*
 * Esta função compara o átomo atual (lookahead) com um átomo esperado (atomo).
 * Se eles forem iguais, a função obtém um novo átomo do buffer e atualiza a 
 * estrutura TInfoAtomo com as informações do novo átomo. O lookahead também é 
 * atualizado. Caso contrário, a função imprime uma mensagem de erro sintático 
 * indicando o átomo esperado e o átomo encontrado, e retorna 1, que deve ser
 * interpretado como 'exit(1)' ao sair da funcão.
 */
int consome(TInfoAtomo *InftoAtomo, TAtomo atomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <programa>::= "algoritmo identificador" ";" <bloco> "."
void programa(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <bloco>::= [ <declaracao_de_variaveis> ] <comando_composto>
void bloco(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`declaracao_de_variaveis`> ::= **variavel** {<`lista_variavel`> “:” <`tipo`> “;”}+
void declaracao_de_variaveis(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`lista_variavel`> ::= **identificador** { “,” **identificador** }
void lista_variavel(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <tipo> ::= "inteiro" | "logico"
void tipo(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <comando_composto> ::= inicio <comando> { “;” <comando>} fim
void comando_composto(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`comando`> ::= <`comando_atribuicao`> | <`comando_se`> | <`comando_enquanto`> | <`comando_entrada`> | <`comando_saida`> | <`comando_composto`>
void comando(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`comando_atribuicao`> ::= **identificador** “:=” <`expressao`>
void comando_atribuicao(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`comando_entrada`> ::= **leia** “(“ <`lista_variavel`> “)”
void comando_entrada(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`comando_enquanto`> ::= **enquanto** “(” <`expressao`> “)” **faca** <`comando`>
void comando_enquanto(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`comando_se`> ::= se “(” <`expressao`> “)” **entao** <`comando`> [**senao** <`comando`>]
void comando_se(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <comando_saida> ::= escreva “(“ <expressao> { “,” <expressao> } “)”
void comando_saida(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`expressao`> ::= <`expressao_simples`> [<`relacional`> <`expressao_simples`> ]
void expressao(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`relacional`> ::= “<” | “<=” | “=” | “#” | “>” | “>=”
void relacional(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`expressao_simples`> ::= [“+” | “−”] <`termo`> { (“+” | “−” | **ou** ) <`termo`> }
void expressao_simples(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`termo`> ::= <`fator`> { ( “`*`” | **div** | **e** ) <`fator`> }
void termo(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

// <`fator`> ::= **identificador** | **numero** | **verdadeiro** | **falso** | “(” <`expressao`> “)”
void fator(TInfoAtomo *InfoAtomo, TAtomo *lookahead, char *buffer, int *conta_linha, int *pos);

#endif