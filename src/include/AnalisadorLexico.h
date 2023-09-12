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

#ifndef _ANALISADOR_LEXICO_H_
#define _ANALISADOR_LEXICO_H_

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

typedef struct
{
	TAtomo atomo;
	int linha;
	float atributo_numero;
	char atributo_ID[16];
}TInfoAtomo;


TInfoAtomo reconhece_comentario(TInfoAtomo infoAtomo, char *buffer, int *conta_linha, int *pos);
void descartar_delimitadores(char* buffer, int *conta_linha, int *pos);
TInfoAtomo obter_atomo(char* buffer, int *conta_linha, int* pos);
TInfoAtomo reconhece_numero(char* buffer, int* pos);
TInfoAtomo reconhece_id(char* buffer, int* pos);

#endif
