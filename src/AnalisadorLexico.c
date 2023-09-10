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
#include <string.h>
#include <ctype.h>
#include "include/AnalisadorLexico.h"

TInfoAtomo obter_atomo(char* buffer, int *conta_linha, int *pos)
{
	TInfoAtomo infoAtomo;
	
	// Descartando os delimitadores.
	while(buffer[*pos]==' ' || buffer[*pos]=='\n' || buffer[*pos]=='\t' || buffer[*pos]=='\r')
	{
		if(buffer[*pos]=='\n')
		{
			(*conta_linha)++;
		}
		(*pos)++;
	}

	if(isdigit(buffer[*pos]))
	{
		infoAtomo = reconhece_numero(buffer, pos);
	}
	else if(islower(buffer[*pos]))
	{
		infoAtomo = reconhece_id(buffer, pos);
	}
	else if(buffer[*pos] == '+')
	{
		infoAtomo.atomo = OP_SOMA;
	}
	else if(buffer[*pos] == '*')
	{
		infoAtomo.atomo = OP_MULT;
	}
	else if(buffer[*pos] == '\x0')
	{
		infoAtomo.atomo = EOS;
	}
	else
	{
		infoAtomo.atomo = ERRO;
	}

	infoAtomo.linha = *conta_linha;
	return infoAtomo;
}


TInfoAtomo reconhece_numero(char *buffer, int *pos)
{
	int ini_num = *pos;
	TInfoAtomo infoAtomo;
	infoAtomo.atomo = ERRO;

	if(isdigit(buffer[*pos]))
	{
		(*pos)++;
		goto q1;
	}
	return infoAtomo;

q1:
	if(isdigit(buffer[*pos]))
	{
    	(*pos)++;
        goto q1;
    }
    if( buffer[*pos]=='.' )
	{
        (*pos)++;
        goto q2;
    }
    // Erro: nao pertence ao alfabeto do analisador lexico.
    return infoAtomo;

q2:
	if(isdigit(buffer[*pos]))
	{
		(*pos)++;
		goto q3;
	}
	// Erro: nao pertence ao alfabeto do analisador lexico.
	return infoAtomo;

q3:
	if(isdigit(buffer[*pos]))
	{
		(*pos)++;
        goto q3;
    }
    if(isalpha(buffer[*pos]))
	{
		// Retorna o infoAtomo com erro.
		return infoAtomo;
	}
	strncpy(infoAtomo.atributo_ID, buffer + ini_num, (*pos) - ini_num);
    infoAtomo.atributo_ID[(*pos) - ini_num] = '\x0';
    infoAtomo.atributo_numero = atof(infoAtomo.atributo_ID);
    infoAtomo.atomo = NUMERO;
    return infoAtomo;
}

TInfoAtomo reconhece_id(char* buffer, int *pos)
{
	int init_id = *pos;
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = ERRO;

    if(islower(buffer[*pos]))
	{
		(*pos)++;
        goto q1;
    }
    return infoAtomo;

q1:
	if(islower(buffer[*pos])||isdigit(buffer[*pos]))
	{
        (*pos)++;
        goto q1;
    }
    
	// Se houver uma letra maiuscula ou houver mais de 15 caracteres, retorna infoAtomo com erro. 
	if(isupper(buffer[*pos]) || (*pos) - init_id > 15)
    	return infoAtomo;

    strncpy(infoAtomo.atributo_ID, buffer + init_id, (*pos) - init_id);
    infoAtomo.atributo_ID[(*pos) - init_id] = '\x0';
    infoAtomo.atomo  = IDENTIFICADOR;
    return infoAtomo;
}
