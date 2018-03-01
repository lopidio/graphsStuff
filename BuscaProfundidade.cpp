/* *********************************************/
/********************************************  /
//
// @date -
//
// Project -
//
//  if (!bug)
//	@author Lopídio (I love America)
//  else
//	@author Unkwonn
//
//
//  Good Luck!
** *********************************/
/* *******************************/


#include "BuscaProfundidade.h"

BuscaProfundidade::BuscaProfundidade()
{
}

BuscaProfundidade::~BuscaProfundidade()
{
        //dtor
}

/** @brief execute
  *
  * @todo: document this function
  */
Grafo* BuscaProfundidade::execute()
{
        if (stepExecute(origem->getId())) //Achou a busca
        {
                Grafo* novoGrafo = new Grafo();
                int tam = pilha.size();
                printf("1\n");
                Vertice** minhaListaVertices = new Vertice*[tam];
                int id = tam -1;
                printf("2\n");
                while(pilha.size()) //Criando os vértices do novo grafo
                {
                        Vertice* novoVertice = new Vertice(id, pilha.top());
                        minhaListaVertices[id] = novoVertice;
                        novoGrafo->addVertice(novoVertice); //Criando todos os vértices
                        --id;
                        pilha.pop();
                }
                printf("3\n");
                for (int i = 1; i < tam; i++) //Criando as arestas do novo grafo
                {
                        novoGrafo->addAresta(new Aresta(minhaListaVertices[i-1], minhaListaVertices[i]));
                }
                printf("4\n");
                delete[] minhaListaVertices;
                return novoGrafo;
        }
        else
                return NULL;
}

void printPilha(stack<Vertice*> p)
{
        printf("Pilha: --> ");
        while (p.size() > 0)
        {
                printf("%d  ", p.top()->getId());
                p.pop();
        }
        printf("\n");
}

/** @brief stepExecute
  *
  * @todo: document this function
  */
bool BuscaProfundidade::stepExecute(int id) //Retorna caso tenha encontrado
{
        visitados.push_back(id);
        Vertice* verticeAtual = grafo->findVerticeById(id);
        pilha.push(verticeAtual);
        printPilha(pilha);
        verticeAtual->selecionar(); //Gera a animação
        //animacao->addStep( verticeAtual ,eA_select); // Gera a animação
        if (id == destino->getId())
                return true;
        bool fim = false;
        for (int i = 0; i < numVertices; i++)
        {
                if (matriz[id][i] != SEM_ARESTA && !verificaExistenciaNaLista(i))
                {
                        fim = stepExecute(i);
                }
                if (fim)
                        return true;
        }
        pilha.pop();
        verticeAtual->desselecionar();
        //animacao->addStep( verticeAtual,eA_deselect); // Gera a animação
        return false;
}

/** @brief verificaExistenciaNaLista
  *
  * @todo: document this function
  */
bool BuscaProfundidade::verificaExistenciaNaLista(int i)
{
        for (std::list<int>::iterator it = visitados.begin(); it != visitados.end(); it++)
        {
                if ( *it == i)
                        return true;
        }
        return false;
}



/** @brief getNome
  *
  * @todo: document this function
  */
std::string const  BuscaProfundidade::getNome() const
{
        return "Busca em Profundidade";
}

/** @brief needRalo
  *
  * @todo: document this function
  */
bool BuscaProfundidade::needDestino() const
{
        return true;
}

/** @brief needFonte
  *
  * @todo: document this function
  */
bool BuscaProfundidade::needOrigem() const
{
        return true;
}
