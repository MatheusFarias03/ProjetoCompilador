#ifndef _T_INFO_ATOMO_H_
#define _T_INFO_ATOMO_H_

typedef enum
{
	ERRO,
	IDENTIFICADOR,
	NUMERO,
	EOS
}TAtomo;

typedef struct
{
	TAtomo atomo;
	int linha;
	float atributo_numero;
	char atributo_ID[16];
}TInfoAtomo;

// Funcoes que retornam TInfoAtomo.
TInfoAtomo obter_atomo(char* buffer, int *conta_linha, int* pos);
TInfoAtomo reconhece_numero(char* buffer, int* pos);
TInfoAtomo reconhece_id(char* buffer, int* pos);

#endif
