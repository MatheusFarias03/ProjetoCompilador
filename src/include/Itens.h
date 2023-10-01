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

#ifndef _ITENS_H_
#define _ITENS_H_

/*
 * Enumeração que representa os diferentes tipos de átomos que podem ser 
 * encontrados no analisador léxico. Cada valor neste enum corresponde a 
 * um tipo específico de átomo.
*/
typedef enum
{
	ALGORITMO,
	ERRO,
	COMENTARIO,
	IDENTIFICADOR,
	VARIAVEL,
	NUMERO,
	LOGICO,
	INTEIRO,
	PONTO,
	VIRGULA,
	PONTO_VIRGULA,
	DOIS_PONTOS,
	MENOR,
	MENOR_IGUAL,
	MAIOR,
	MAIOR_IGUAL,
	IGUAL,
	CARDINAL,
	RELACIONAL,
	FATOR,
	ABRE_PARENTESES,
	FECHA_PARENTESES,
	VERDADEIRO,
	FALSO,
	MAIS,
	MENOS,
	OU,
	E,
	DIV,
	ASTERISCO,
	ATRIBUICAO,
	LEIA,
	ENQUANTO,
	FACA,
	SE,
	SENAO,
	ENTAO,
	ESCREVA,
	INICIO,
	FIM,
	COMANDO,
	EOS
}TAtomo;

/* 
 * Contem as strings que representam os diferentes tipos de atomo em TAtomo.
 * Devem ser as mesmas e estar na mesma que as especificadas no enumerador.
 */
extern char* strAtomo[][50];

/*
* Struct utilizada para armazenar as informacões associadas a um atomo
* identificado durante a analize léxica do programa.
*/
typedef struct
{
	TAtomo atomo; // Tipo de átomo.
	int linha; // Linha em que o átomo foi encontrado.
	float atributo_numero; // Valor do átomo se for um número.
	char atributo_ID[16]; // Identificador, se for uma string.
}TInfoAtomo;

#endif