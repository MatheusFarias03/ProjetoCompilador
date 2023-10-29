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
#include "include/Itens.h"

void criar_lista_variavel(int tamanho)
{
    if (lista_variaveis == NULL)
    {
        lista_variaveis = (TInfoAtomo*)malloc(tamanho * sizeof(TInfoAtomo));
        if (lista_variaveis == NULL)
        {
            fprintf(stderr, "Falha na alocacao de memoria para a lista de variaveis.\n");
            exit(1);
        }
        lv_t_atual = 0;
        lv_t_max = tamanho;
    }
    else
    {
        fprintf(stderr, "Lista de variaveis previamente declarada.\n");
        exit(1);
    }
}

void aumentar_lista(int tamanho)
{
    lv_t_max += tamanho;
    lista_variaveis = (TInfoAtomo*)realloc(lista_variaveis, lv_t_max * sizeof(TInfoAtomo));
}

void inserir_variavel_na_lista(TInfoAtomo *atomo_variavel)
{
    // Checar se a lista está cheia. Caso esteja, aumentar.
    if (lv_t_atual == lv_t_max)
    {
        aumentar_lista(1);
    }
    lista_variaveis[lv_t_atual] = *atomo_variavel;
    lv_t_atual++;
}

void checar_variaveis()
{
    for (int i = 0; i < lv_t_atual; i++)
    {
        for (int j = i + 1; j < lv_t_atual; j++)
        {
            // Comparar o atributo_ID entre os elementos i e j.
            if (strcmp(lista_variaveis[i].atributo_ID, lista_variaveis[j].atributo_ID) == 0)
            {
                // Encontrado elementos com o mesmo atributo_ID.
                fprintf(stderr, "Erro: Variaveis %s e %s possuem o mesmo identificador.\n",
                        lista_variaveis[i].atributo_ID, lista_variaveis[j].atributo_ID);
                exit(1);
            }
        }
    }
}

void free_lista_variavel()
{
    free(lista_variaveis);

    // Resetar lv_t_max e lv_t_atual para indicar uma lista vazia
    lv_t_max = 0;
    lv_t_atual = 0;

}
