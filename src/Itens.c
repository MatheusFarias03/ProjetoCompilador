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
#include "include/Itens.h"

char* strAtomo[][50] = {
	"ALGORITMO",
	"ERRO", 
	"COMENTARIO", 
	"IDENTIFICADOR",
	"VARIAVEL",
	"NUMERO",
	"LOGICO",
	"INTEIRO",
	"PONTO",
	"VIRGULA",
	"PONTO_VIRGULA",
	"DOIS_PONTOS",
	"MENOR",
	"MENOR_IGUAL",
	"MAIOR",
	"MAIOR_IGUAL",
	"IGUAL",
	"CARDINAL",
	"RELACIONAL",
	"FATOR",
	"ABRE_PARENTESES",
	"FECHA_PARENTESES",
	"VERDADEIRO",
	"FALSO",
	"MAIS",
	"MENOS",
	"OU",
	"E",
	"DIV",
	"ASTERISCO",
	"EOS"
};