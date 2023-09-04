#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/TInfoAtomo.h"

TInfoAtomo obter_atomo(char* buffer, int conta_linha)
{
		TInfoAtomo infoAtomo;
		// Descartando os delimitadores.
		while(*buffer==' ' || *buffer=='\n' || *buffer=='\t' || *buffer=='\r')
		{
				if(*buffer=='\n')
				{
						conta_linha++;
				}
				buffer++;
		}

		if(isdigit(*buffer))
		{
				infoAtomo = reconhece_numero(buffer);
		}
		else if(islower(*buffer))
		{
				infoAtomo = reconhece_id(buffer);
		}
		else if(*buffer == '\x0')
		{
				infoAtomo.atomo = EOS;
		}
		else
		{
				infoAtomo.atomo = ERRO;
		}

		infoAtomo.linha = conta_linha;
		return infoAtomo;
}


TInfoAtomo reconhece_numero(char *buffer)
{
		char *p_ini_num = buffer;
		TInfoAtomo infoAtomo;
		infoAtomo.atomo = ERRO;

		if(isdigit(*buffer))
		{
				buffer++;
				goto q1;
		}
		return infoAtomo;

q1:
		if(isdigit(*buffer))
		{
       		buffer++;
        	goto q1;
    	}
    	if( *buffer=='.' )
		{
        	buffer++;
        	goto q2;
    	}
    	// Erro: nao pertence ao alfabeto do analisador lexico.
    	return infoAtomo;

q2:
		if(isdigit(*buffer))
		{
				buffer++;
				goto q3;
		}
		// Erro: nao pertence ao alfabeto do analisador lexico.
		return infoAtomo;

q3:
		if(isdigit(*buffer))
		{
				buffer++;
        		goto q3;
    	}
    	if(isalpha(*buffer))
		{
				// Retorna o infoAtomo com erro.
				return infoAtomo;
		}
		strncpy(infoAtomo.atributo_ID, p_ini_num, buffer - p_ini_num);
    	infoAtomo.atributo_ID[buffer-p_ini_num] = '\x0';
    	infoAtomo.atributo_numero = atof(infoAtomo.atributo_ID);
    	infoAtomo.atomo = NUMERO;
    	return infoAtomo;
}

TInfoAtomo reconhece_id(char* buffer)
{
		char *pIniID = buffer;
    	TInfoAtomo infoAtomo;
    	infoAtomo.atomo = ERRO;

    	if(islower(*buffer))
		{
				buffer++;
        		goto q1;
    	}
    	return infoAtomo;

q1:
		if(islower(*buffer)||isdigit(*buffer))
		{
        		buffer++;
        		goto q1;
    	}
    	
		if(isupper(*buffer))
        return infoAtomo;

    	strncpy(infoAtomo.atributo_ID,pIniID,buffer-pIniID);
    	infoAtomo.atributo_ID[buffer-pIniID] = '\x0';
    	infoAtomo.atomo  = IDENTIFICADOR;
    	return infoAtomo;
}
