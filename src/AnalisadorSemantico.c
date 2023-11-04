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
    // Checar atomo correto (IDENTIFICADOR).
    if (atomo_variavel->atomo == IDENTIFICADOR)
    {
        // Checar se a lista está cheia. Caso esteja, aumentar.
        if (lv_t_atual == lv_t_max)
        {
            aumentar_lista(1);
        }
        lista_variaveis[lv_t_atual] = *atomo_variavel;
        lv_t_atual++;
    }
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
    lista_variaveis = NULL;

    // Resetar lv_t_max e lv_t_atual para indicar uma lista vazia
    lv_t_max = 0;
    lv_t_atual = 0;

}

int checar_variavel_existe(TInfoAtomo *atomo_variavel)
{
    for (int i = 0; i < lv_t_atual; i++)
    {
        if (strcmp(lista_variaveis[i].atributo_ID, atomo_variavel->atributo_ID) == 0)
        {
            // Encontrado elemento com o mesmo atributo_ID
            return 0;
        }
    }
    // Elemento ausente na lista_variaveis
    return 1;
}

// TODO: Alguma coisa de errado acontece aqui quando '(' ou ')' está na expressão.
void criar_lista_expressao(int tamanho)
{
    if (lista_expressao == NULL)
    {
        lista_expressao = (TInfoAtomo*)malloc(tamanho * sizeof(TInfoAtomo));
        if (lista_expressao == NULL)
        {
            fprintf(stderr, "Falha na alocacao de memoria para a <<lista_expressao>>.\n");
            exit(1);
        }
        le_t_atual = 0;
        le_t_max = tamanho;
    }
    else
    {
        // fprintf(stderr, "<<lista_expressao>> previamente declarada.\n");
        // exit(1);
    }
}

void avaliar_expressao()
{
    /*
    * Algoritmo "Shunting Yard", do Dijkstra.
    * Primeirament cria-se duas variaveis que servirão de pilha para guardar os InfoAtomos:
    * pilha_saida e pilha_operadores. 
    */
    TInfoAtomo *pilha_saida = (TInfoAtomo*)malloc(le_t_max * sizeof(TInfoAtomo));
    TInfoAtomo *pilha_operadores = (TInfoAtomo*)malloc(le_t_max * sizeof(TInfoAtomo));
    
    TInfoAtomo atomo_atual;
    TInfoAtomo atomo_ant;
    TInfoAtomo atomo_vazio = {0};

    int pos_saida = 0;
    int pos_operadores = 0;
    int pos_ant = 0;

    for (int i = 0; i < le_t_max - 1; i++)
    {
        atomo_atual = lista_expressao[i];

        // Se for um identificador, numero ou booleano: adicionar na pilha_saida.
        if (
            atomo_atual.atomo == IDENTIFICADOR || atomo_atual.atomo == NUMERO ||
            atomo_atual.atomo == VERDADEIRO || atomo_atual.atomo == FALSO
        )
        {
            pilha_saida[pos_saida] = atomo_atual;
            pos_saida++;
        }
        // Caso seja mais ou menos...
        else if (atomo_atual.atomo == MAIS || atomo_atual.atomo == MENOS)
        {
            // Caso não seja o primeiro operador na pilha_operadores...
            if (pos_operadores > 0)
            {
                pos_ant = pos_operadores - 1;
                atomo_ant = pilha_operadores[pos_ant];
                
                // Verificar se o InfoAtomo na posicao anterior é de igual ou maior valor.
                if (
                    atomo_ant.atomo == DIV || atomo_ant.atomo == ASTERISCO ||
                    atomo_ant.atomo == MENOS || atomo_ant.atomo == MAIS
                )
                {
                    /*
                    * Caso seja, remover o InfoAtomo anterior da pilha_operadores e colocá-lo
                    * na pilha_saida.
                    */
                    pilha_saida[pos_saida] = atomo_ant;
                    pos_saida++;
                    pilha_operadores[pos_ant] = atomo_atual;
                }
                // Caso não for de maior ou igual valor, apenas adicionar na lista.
                else
                {
                    pilha_operadores[pos_operadores] = atomo_atual;
                    pos_operadores++;
                }

            }
            // Caso seja o primeiro operador, apenas adicioná-lo na pilha_operadores.
            else
            {
                pilha_operadores[pos_operadores] = atomo_atual;
                pos_operadores++;
            }
        }
        // Caso seja divisão ou multiplicacão...
        else if (atomo_atual.atomo == DIV || atomo_atual.atomo == ASTERISCO)
        {
            // Caso não seja o primeiro operador na pilha_operadores...
            if (pos_operadores > 0)
            {
                pos_ant = pos_operadores - 1;
                atomo_ant = pilha_operadores[pos_ant];
                
                // Verificar se o InfoAtomo na posicao anterior é de igual ou maior valor.
                if (atomo_ant.atomo == DIV || atomo_ant.atomo == ASTERISCO)
                {
                    /*
                    * Caso seja, remover o InfoAtomo anterior da pilha_operadores e colocá-lo
                    * na pilha_saida.
                    */
                    pilha_saida[pos_saida] = atomo_ant;
                    pos_saida++;
                    pilha_operadores[pos_ant] = atomo_atual;
                }
                // Caso não for de maior ou igual valor, apenas adicionar na lista.
                else
                {
                    pilha_operadores[pos_operadores] = atomo_atual;
                    pos_operadores++;
                }
            }
            // Caso seja o primeiro operador, apenas adicioná-lo na pilha_operadores.
            else
            {
                pilha_operadores[pos_operadores] = atomo_atual;
                pos_operadores++;
            }
        }
        // Caso seja um fecha parenteses...
        else if (atomo_atual.atomo == FECHA_PARENTESES)
        {
            // Percorrer a lista, de tras para frente, até encontrar o abre parenteses.
            while (pilha_operadores[pos_operadores-1].atomo != ABRE_PARENTESES)
            {
                // Enquanto não, mover os atomos da pilha de operadores para a de saída.
                if (pos_operadores != 0)
                {
                    pilha_saida[pos_saida] = pilha_operadores[pos_operadores-1];
                    pos_saida++;
                    pilha_operadores[pos_operadores-1] = atomo_vazio;
                    pos_operadores -= 1;
                }
                else
                {
                    printf("ERRO (ln.%d): Há fecha-parenteses, mas não abre-parenteses.", atomo_atual.linha);
                    exit(1);
                }
            }
            // Apenas para confirmar se estamos no atomo com ABRE_PARENTESES.
            if (pilha_operadores[pos_operadores].atomo == ABRE_PARENTESES)
            {
                pilha_operadores[pos_operadores] = atomo_vazio;
                if (pos_operadores > 0)
                {
                    pos_operadores -= 1;
                }
            }
        }
        // Abre-parenteses e operadores de comparacao possuem a menor prioridade.
        else if (
            atomo_atual.atomo == ABRE_PARENTESES || atomo_atual.atomo == MENOR ||
            atomo_atual.atomo == MAIOR || atomo_atual.atomo == MENOR_IGUAL ||
            atomo_atual.atomo == MAIOR_IGUAL || atomo_atual.atomo == IGUAL
        )
        {
            pilha_operadores[pos_operadores] = atomo_atual;
            pos_operadores++;
        }
    }

    // Mover a galera toda dos operadores pra saída.
    for (int i = pos_operadores-1; i >= 0; i -= 1)
    {
        pilha_saida[pos_saida] = pilha_operadores[i];
        pos_saida++;
        pilha_operadores[i] = atomo_vazio;
        pos_operadores -= 1;
    }

    for (int i = 0; i < pos_saida; i++)
    {
        if (pilha_saida[i].atomo == IDENTIFICADOR)
        {
            printf("\npilha_saida[%d]: %s", i, pilha_saida[i].atributo_ID);
        }
        else if (pilha_saida[i].atomo == NUMERO)
        {
            printf("\npilha_saida[%d]: %f", i, pilha_saida[i].atributo_numero);
        }
        else
        {
            printf("\npilha_saida[%d]: %d", i, pilha_saida[i].atomo);
        }
    }
    printf("\n\n");

    // Limpar a memória para as pilhas.
    free(pilha_operadores);
    free(pilha_saida);

    pos_saida = 0;
    pos_operadores = 0;
    pos_ant = 0;
}

void aumentar_lista_expressao(int tamanho)
{
    le_t_max += tamanho;
    lista_expressao = (TInfoAtomo*)realloc(lista_expressao, le_t_max * sizeof(TInfoAtomo));
}

void inserir_InfoAtomo_lista_expressao(TInfoAtomo *info_atomo)
{
    // Checar se a lista está cheia. Caso esteja, aumentar.
    if (le_t_atual == le_t_max)
    {
        aumentar_lista_expressao(1);
    }
    lista_expressao[le_t_atual] = *info_atomo;
    le_t_atual++;
}

void free_lista_expressao()
{
    free(lista_expressao);
    lista_expressao = NULL;

    // Resetar lv_t_max e lv_t_atual para indicar uma lista vazia
    le_t_max = 0;
    le_t_atual = 0;
}