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
	ERRO,
	COMENTARIO,
	IDENTIFICADOR,
	NUMERO,
	OP_SOMA,
	OP_MULT,
	EOS
}TAtomo;

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