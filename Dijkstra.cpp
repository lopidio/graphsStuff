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


#include "Dijkstra.h"

Dijkstra::Dijkstra()
{
        //ctor
}

Dijkstra::~Dijkstra()
{
        //dtor
}

void printVector(int* v, int n)
{
        for (int i = 0; i < n; i++)
                printf("%d  ", v[i]);
        printf("\n");
}

void printVector(bool* v, int n)
{
        for (int i = 0; i < n; i++)
                printf("%d  ", v[i]);
        printf("\n");
}

/** @brief execute
  *
  * @todo: document this function
  */
Grafo* Dijkstra::execute() //S origem, t destino
{

        Caminho primeiro(-1, 0, origem->getId());
        verticesParaVisitar.push_back(primeiro);
        stepExecute();

        return createGraph();
}


/** @brief createGraph
  *
  * @todo: document this function
  */
Grafo* Dijkstra::createGraph()
{
        Grafo* novoGrafo = new Grafo();
        for (int i = 0; i < (int)verticesVisitados.size(); i++) //Criando os vértices
        {
                int idAtual = verticesVisitados[i].id;
                Vertice* novo = new Vertice(i, grafo->findVerticeById(idAtual));
                //printf("Id: %d       pai: %d     custo: %d\n", verticesVisitados[i].id, verticesVisitados[i].pai, verticesVisitados[i].custoTotal);
                novoGrafo->addVertice(novo);
        }

        for (int i = 1; i < (int)verticesVisitados.size(); i++) //Criando as arestas
        {
                int origemAtual = verticesVisitados[i].pai;
                int destinoAtual = verticesVisitados[i].id;
                Aresta* nova = new Aresta(grafo->findVerticeById(origemAtual), grafo->findVerticeById(destinoAtual));
                novoGrafo->addAresta(nova);
                Aresta* antiga = grafo->findArestaByVerticesID(origemAtual, destinoAtual);
                nova->editarValor(antiga->getValor());
                if (antiga->isBidirecional())
                        nova->mudarTipo();
        }
        return novoGrafo;
}



/** @brief searchAndReturnAVisitar
  *
  * @todo: document this function
  */
Dijkstra::Caminho* Dijkstra::searchAndReturnAVisitar(int x)
{
        for (std::list<Caminho>::iterator it = verticesParaVisitar.begin(); it != verticesParaVisitar.end(); it++)
                if (it->id == x)
                        return &(*it);
        return NULL;
}

/** @brief verificaVisitados
  *
  * @todo: document this function
  */
bool Dijkstra::verificaVisitados(int x) const
{
        for (unsigned int i = 0; i < verticesVisitados.size(); i++)
                if (verticesVisitados[i].id == x)
                        return true;
        return false;
}



int Dijkstra::compareCaminho(const Caminho& a, const Caminho& b)
{
        return a.custoTotal < b.custoTotal;
}


void Dijkstra::stepExecute()
{
        verticesParaVisitar.sort(Dijkstra::compareCaminho); //Ordena a lista
        Caminho atual = verticesParaVisitar.front(); //Pega o menor caminho
        verticesParaVisitar.pop_front();
        verticesVisitados.push_back(atual);
        int id = atual.id;
        grafo->findVerticeById(id)->selecionar();
        for (int i = 0; i < numVertices; i++)
        {
                int custoTotalAtual = atual.custoTotal + matriz[id][i];
                if (matriz[id][i] != SEM_ARESTA && !verificaVisitados(i)) //Se existir a aresta e ainda não tiver sido visitado
                {
                        Caminho* novo = searchAndReturnAVisitar(i);
                        if (novo) //Se ele já tiver na lista de espera, eu só atualizo caso necessário
                        {
                                if (novo->custoTotal > custoTotalAtual) //O caminho achado anteriormente até esse vértice é mais eficiente
                                {
                                        grafo->findArestaByVerticesID(novo->pai, novo->id)->desselecionar();
                                        grafo->findArestaByVerticesID(id, i)->selecionar();
                                        novo->pai = id;
                                        novo->custoTotal = custoTotalAtual;
                                }
                        }
                        else //Se não tiver na lista ainda, eu insiro
                        {
                                grafo->findArestaByVerticesID(id, i)->selecionar();
                                Caminho add(id, custoTotalAtual, i);
                                verticesParaVisitar.push_back(add);
                        }
                }
        }
        if (verticesParaVisitar.size() > 0)
                return stepExecute();
}

/** @brief needOrigem
  *
  * @todo: document this function
  */
bool Dijkstra::needOrigem() const
{
        return true;
}


/** @brief especificCondition
  *
  * @todo: document this function
  */
bool Dijkstra::especificCondition() const
{
        vector<Aresta*> arestas = grafo->getArestas();
        for (unsigned int i = 0; i < arestas.size(); i++)
        {
                if (arestas[i]->getFloatValor() < 0)
                {
                        AMBIENTE->addMessageBox(L"Algoritmo de Dijkstra", L"O algoritmo nao aceita pesos negativos");
                        return false;
                }
        }
        return true;
}

/** @brief Caminho
  *
  * @todo: document this function
  */
Dijkstra::Caminho::Caminho(int pai_, int custoTotal_, int id_):pai(pai_), custoTotal(custoTotal_), id(id_)
{

}


const std::string Dijkstra::getNome() const
{
        return "Dijkstra";
}
