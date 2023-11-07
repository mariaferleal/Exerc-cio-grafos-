#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 99999  // Infinito (um valor grande para representar ausência de conexão)

typedef int TIPOPESO;

typedef struct adjacencia
{
  int vertice;
  TIPOPESO peso;
  struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
  ADJACENCIA *cab;
} VERTICE;

typedef struct grafo
{
  int vertices;
  int arestas;
  VERTICE *adj;
} GRAFO;

GRAFO *criaGrafo(int v)
{
  int i;
  GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));

  for (i = 0; i < v; i++)
  {
    g->adj[i].cab = NULL;
  }
  return (g);
}

ADJACENCIA *criaAdj(int v, int peso)
{
  ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
  temp->vertice = v;
  temp->peso = peso;
  temp->prox = NULL;

  return (temp);
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p)
{
  if (!gr)
    return (false);
  if (vf < 0 || vf >= gr->vertices)
    return (false);
  if (vi < 0 || vi >= gr->vertices)
    return (false);

  ADJACENCIA *novo = criaAdj(vf, p);

  novo->prox = gr->adj[vi].cab;
  gr->adj[vi].cab = novo;
  gr->arestas++;
  return (true);
}

void imprime(GRAFO *gr)
{
  printf("Vértices: %d. Arestas: %d. \n", gr->vertices, gr->arestas);
  int i;

  for (i = 0; i < gr->vertices; i++)
  {
    printf("v%d: ", i);
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad)
    {
      printf("v%d(%d) ", ad->vertice, ad->peso);
      ad = ad->prox;
    }
    printf("\n");
  }
}

int main()
{
  int numVertices = 6;  // Número de vértices no grafo
  GRAFO *grafo = criaGrafo(numVertices);

  // Adicione as arestas e seus pesos
  criaAresta(grafo, 0, 1, 5);
  criaAresta(grafo, 1, 2, 2);
  criaAresta(grafo, 2, 3, 7);
  criaAresta(grafo, 3, 4, 3);
  criaAresta(grafo, 4, 5, 1);

  imprime(grafo);

  int origem = 1;
  int destino = 5;

  // Calcular o valor total do caminho entre {1, 5}
  int valorTotalCaminho = 0;
  ADJACENCIA *ad = grafo->adj[origem].cab;
  while (ad)
  {
    if (ad->vertice == destino)
    {
      valorTotalCaminho += ad->peso;
      break;
    }
    ad = ad->prox;
  }

  if (valorTotalCaminho == 0)
  {
    printf("Não há caminho entre %d e %d.\n", origem, destino);
  }
  else
  {
    printf("O valor total do caminho entre {%d, %d} é %d.\n", origem, destino, valorTotalCaminho);
  }

  return 0;
}
