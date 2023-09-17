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
#include "include/Itens.h"

void ler_arquivo(FILE *arquivo, char **buffer)
{
	// Leitura do "arquivo_fonte.txt".
	arquivo = fopen("src/arquivo_fonte.txt", "r");

	if(arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	// Determina o tamanho do arquivo.
	fseek(arquivo, 0, SEEK_END);
	long tamanho = ftell(arquivo);
	fseek(arquivo, 0, SEEK_SET);

	*buffer = (char*)malloc(tamanho + 1);

	if(*buffer == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		fclose(arquivo);
		exit(1);
	}

	// Ler caracteres do arquivo para o buffer.
	fread(*buffer, sizeof(char), tamanho, arquivo);
	(*buffer)[tamanho] = '\0';

	fclose(arquivo);
}

void descartar_delimitadores(char* buffer, int *conta_linha, int *pos)
{
	while(buffer[*pos]==' ' || buffer[*pos]=='\n' || buffer[*pos]=='\t' || buffer[*pos]=='\r')
	{
		if(buffer[*pos]=='\n')
			(*conta_linha)++;
		
		(*pos)++;
	}
}


TInfoAtomo reconhece_comentario(TInfoAtomo infoAtomo, char *buffer, int *conta_linha, int *pos)
{
	// Checar comentarios.
	if(buffer[*pos] == '/')
	{
		(*pos)++;
		
		// Se for comentario de apenas uma linha.
		if(buffer[*pos] == '/')
		{
			do
			{
				(*pos)++;
			} while (buffer[*pos] != '\n');
			descartar_delimitadores(buffer, conta_linha, pos);
		}

		// Se for comentario de multiplas linhas.
		else if(buffer[*pos] == '*')
		{
			do
			{
				(*pos)++;
				if(buffer[*pos]=='\n')
					(*conta_linha)++;
				
			} while (buffer[*pos] != '*' && buffer[(*pos)+1] != '/');
			descartar_delimitadores(buffer, conta_linha, pos);
			(*pos) += 2;
		}

		infoAtomo.atomo = COMENTARIO;
		infoAtomo.linha = *conta_linha;
	}
	return infoAtomo;
}


TInfoAtomo obter_atomo(char *buffer, int *conta_linha, int *pos)
{
	TInfoAtomo infoAtomo = {ERRO, 0, 0.0, ""};
	
	descartar_delimitadores(buffer, conta_linha, pos);

	// Checar comentarios.
	infoAtomo = reconhece_comentario(infoAtomo, buffer, conta_linha, pos);
	if(infoAtomo.atomo == COMENTARIO)
		return infoAtomo;

	if(isdigit(buffer[*pos]))
		infoAtomo = reconhece_numero(buffer, pos);
	
	else if(islower(buffer[*pos]))
		infoAtomo = reconhece_id(buffer, pos);
	
	else if(buffer[*pos] == ';')
	{
		infoAtomo.atomo = PONTO_VIRGULA;
		(*pos)++;
	}
	
	else if(buffer[*pos] == '.')
	{
		infoAtomo.atomo = PONTO;
		(*pos)++;
	}
	
	else if(buffer[*pos] == '\x0')
		infoAtomo.atomo = EOS;
	
	else
		infoAtomo.atomo = ERRO;

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
	if(islower(buffer[*pos]) || isdigit(buffer[*pos]) || buffer[*pos] == '_')
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

	reconhece_palavra_reservada(&infoAtomo);

    return infoAtomo;
}


void reconhece_palavra_reservada(TInfoAtomo *infoAtomo)
{
	if(strcmp(infoAtomo->atributo_ID, "algoritmo") == 0)
		infoAtomo->atomo = ALGORITMO;
}