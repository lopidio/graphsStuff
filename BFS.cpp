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


#include "BFS.h"

BFS::BFS()
{
        //ctor
}

BFS::~BFS()
{
        //dtor
}

/** @brief listSearch
  *
  * @todo: document this function
  */
bool BFS::listsSearch(int x) const
{
        std::list<int>::const_iterator it;
        for (it = verticesAvisitar.begin(); it != verticesAvisitar.end(); it++)
                if (*(it) == x)
                        return true;

        for (it = verticesVisitados.begin(); it != verticesVisitados.end(); it++)
                if (*(it) == x)
                        return true;
        return false;
}

/** @brief stepExecute
  *
  * @todo: document this function
  */
bool BFS::stepExecute()
{
        int id = verticesAvisitar.front();
        verticesVisitados.push_back(id);
        if (id == destino->getId())
                return true;
        verticesAvisitar.pop_front();
        for (int i = 0; i < numVertices; i++)
        {
                if (matriz[id][i] != SEM_ARESTA && !listsSearch(i)) //Se existe a ligação, e o vértice não consta em nenhuma das listas
                {
                        verticesAvisitar.push_back(i);
                        grafo->findVerticeById(i)->selecionar();
                }
        }
        grafo->findVerticeById(id)->desselecionar();
        if (verticesAvisitar.size() > 0) //Enquanto houver vértice a visitar, retorna isso
                return stepExecute();
        return false;
}

/** @brief execute
  *
  * @todo: document this function
  */
Grafo* BFS::execute()
{
        verticesAvisitar.push_back(origem->getId());
        grafo->findVerticeById(origem->getId())->selecionar();
        if (stepExecute())
                return createNewGraph();
        AMBIENTE->addMessageBox(L"Busca em largura executada", L"Nao ha retorno no algoritmo");
        return NULL;
}

/** @brief needDestino
  *
  * @todo: document this function
  */
bool BFS::needDestino() const
{
        return true;
}

/** @brief needOrigem
  *
  * @todo: document this function
  */
bool BFS::needOrigem() const
{
        return true;
}

/** @brief getNome
  *
  * @todo: document this function
  */
const std::string BFS::getNome() const
{
        return "Busca Largura";
}

/** @brief createNewGraph
  *
  * @todo: document this function
  */
Grafo* BFS::createNewGraph()
{
        Grafo* novoGrafo = new Grafo();
        novoGrafo->addVertice(new Vertice(0, grafo->findVerticeById(verticesVisitados.front())));
        novoGrafo->addVertice(new Vertice(1, grafo->findVerticeById(verticesVisitados.back())));
        return novoGrafo;
}

