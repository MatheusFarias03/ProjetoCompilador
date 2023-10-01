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
			printf("#%03d: %s \n", *conta_linha, strAtomo[0][COMENTARIO]);
			do
			{
				(*pos)++;
			} while (buffer[*pos] != '\n');
			descartar_delimitadores(buffer, conta_linha, pos);
			infoAtomo.atomo = COMENTARIO;
		}

		// Se for comentario de multiplas linhas.
		else if(buffer[*pos] == '*')
		{
			printf("#%03d: %s \n", *conta_linha, strAtomo[0][COMENTARIO]);
			do
			{
				(*pos)++;
				if(buffer[*pos]=='\n')
				{
					(*conta_linha)++;
					printf("#%03d: %s \n", *conta_linha, strAtomo[0][COMENTARIO]);
				}
			} while (buffer[*pos] != '*' && buffer[(*pos)+1] != '/');
			(*pos) += 2;
			descartar_delimitadores(buffer, conta_linha, pos);
			infoAtomo.atomo = COMENTARIO;
		}
		// Se nao for nenhum dos dois, ERRO.
		else
		{
			infoAtomo.atomo = ERRO;
		}
	}
	// Se nao for '/', atomo recebe ERRO.
	else 
	{
		infoAtomo.atomo = ERRO;
	}
	infoAtomo.linha = *conta_linha;
	return infoAtomo;
}


TInfoAtomo obter_atomo(char *buffer, int *conta_linha, int *pos)
{
	TInfoAtomo infoAtomo = {ERRO, 0, 0.0, ""};
	
	descartar_delimitadores(buffer, conta_linha, pos);

	// Checar comentarios.
	infoAtomo = reconhece_comentario(infoAtomo, buffer, conta_linha, pos);
	while (infoAtomo.atomo == COMENTARIO)
	{
		infoAtomo = reconhece_comentario(infoAtomo, buffer, conta_linha, pos);
	}
	

	if(isdigit(buffer[*pos]))
		infoAtomo = reconhece_numero(buffer, pos);
	
	else if(isalpha(buffer[*pos]))
		infoAtomo = reconhece_id(buffer, pos);
	
	else if(buffer[*pos] == ';')
	{
		infoAtomo.atomo = PONTO_VIRGULA;
		(*pos)++;
	}

	else if(buffer[*pos] == ':')
	{
		infoAtomo.atomo = DOIS_PONTOS;
		(*pos)++;

		if(buffer[*pos] == '=')
		{
			infoAtomo.atomo = ATRIBUICAO;
			(*pos)++;
		}
	}

	else if(buffer[*pos] == ',')
	{
		infoAtomo.atomo = VIRGULA;
		(*pos)++;
	}
	
	else if(buffer[*pos] == '.')
	{
		infoAtomo.atomo = PONTO;
		(*pos)++;
	}

	else if(buffer[*pos] == '<')
	{
		infoAtomo.atomo = MENOR;
		(*pos)++;
		
		if(buffer[*pos] == '=')
		{
			infoAtomo.atomo = MENOR_IGUAL;
			(*pos)++;
		}
	}

	else if(buffer[*pos] == '>')
	{
		infoAtomo.atomo = MAIOR;
		(*pos)++;
		
		if(buffer[*pos] == '=')
		{
			infoAtomo.atomo = MAIOR_IGUAL;
			(*pos)++;
		}
	}

	else if(buffer[*pos] == '=')
	{
		infoAtomo.atomo = IGUAL;
		(*pos)++;
	}

	else if(buffer[*pos] == '#')
	{
		infoAtomo.atomo = CARDINAL;
		(*pos)++;
	}

	else if(buffer[*pos] == '(')
	{
		infoAtomo.atomo = ABRE_PARENTESES;
		(*pos)++;
	}

	else if(buffer[*pos] == ')')
	{
		infoAtomo.atomo = FECHA_PARENTESES;
		(*pos)++;
	}

	else if(buffer[*pos] == '+')
	{
		infoAtomo.atomo = MAIS;
		(*pos)++;
	}

	else if(buffer[*pos] == '-')
	{
		infoAtomo.atomo = MENOS;
		(*pos)++;
	}

	else if(buffer[*pos] == '*')
	{
		infoAtomo.atomo = ASTERISCO;
		(*pos)++;
	}

	else if(buffer[*pos] == '/')
	{
		infoAtomo.atomo = DIV;
		(*pos)++;
	}
	
	else if(buffer[*pos] == '\x0')
		infoAtomo.atomo = EOS;
	
	else
		infoAtomo.atomo = ERRO;

	printf("#%03d: %s \n", *conta_linha, strAtomo[0][infoAtomo.atomo]);

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
    if(isalpha(buffer[*pos]))
	{
		// Retorna o infoAtomo com erro.
		return infoAtomo;
	}
	if(buffer[*pos] == 'E' || buffer[*pos] == 'e')
	{
		(*pos)++;
		goto q2;
	}
	goto final;

q2:
	if(buffer[*pos] == '+' || buffer[*pos] == '-')
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

final:
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

    if(isalpha(buffer[*pos]))
	{
		(*pos)++;
        goto q1;
    }
    return infoAtomo;

q1:
	if(isalpha(buffer[*pos]) || isdigit(buffer[*pos]) || buffer[*pos] == '_')
	{
        (*pos)++;
        goto q1;
    }
    
	// Se houver uma letra maiuscula ou houver mais de 15 caracteres, retorna infoAtomo com erro. 
	if((*pos) - init_id > 15)
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

	if(strcmp(infoAtomo->atributo_ID, "inteiro") == 0)
		infoAtomo->atomo = INTEIRO;
	
	if(strcmp(infoAtomo->atributo_ID, "logico") == 0)
		infoAtomo->atomo = LOGICO;

	if(strcmp(infoAtomo->atributo_ID, "variavel") == 0)
		infoAtomo->atomo = VARIAVEL;
	
	if(strcmp(infoAtomo->atributo_ID, "verdadeiro") == 0)
		infoAtomo->atomo = VERDADEIRO;

	if(strcmp(infoAtomo->atributo_ID, "falso") == 0)
		infoAtomo->atomo = FALSO;

	if(strcmp(infoAtomo->atributo_ID, "OU") == 0)
		infoAtomo->atomo = OU;

	if(strcmp(infoAtomo->atributo_ID, "E") == 0)
		infoAtomo->atomo = E;

	if(strcmp(infoAtomo->atributo_ID, "leia") == 0)
		infoAtomo->atomo = LEIA;

	if(strcmp(infoAtomo->atributo_ID, "enquanto") == 0)
		infoAtomo->atomo = ENQUANTO;

	if(strcmp(infoAtomo->atributo_ID, "faca") == 0)
		infoAtomo->atomo = FACA;

	if(strcmp(infoAtomo->atributo_ID, "se") == 0)
		infoAtomo->atomo = SE;

	if(strcmp(infoAtomo->atributo_ID, "senao") == 0)
		infoAtomo->atomo = SENAO;

	if(strcmp(infoAtomo->atributo_ID, "entao") == 0)
		infoAtomo->atomo = ENTAO;

	if(strcmp(infoAtomo->atributo_ID, "escreva") == 0)
		infoAtomo->atomo = ESCREVA;

	if(strcmp(infoAtomo->atributo_ID, "inicio") == 0)
		infoAtomo->atomo = INICIO;

	if(strcmp(infoAtomo->atributo_ID, "fim") == 0)
		infoAtomo->atomo = FIM;
}