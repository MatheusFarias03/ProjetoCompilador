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

char* strAtomo[][30] = {
	"ALGORITMO",
	"ERRO", 
	"COMENTARIO", 
	"IDENTIFICADOR",
	"NUMERO",
	"LOGICO",
	"INTEIRO",
	"PONTO",
	"PONTO_VIRGULA",
	"EOS"
};