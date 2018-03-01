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


#include "Prim.h"

Prim::Prim()
{
        //ctor
}

Prim::~Prim()
{
        //dtor
}


/** @brief verificaVertice
  *
  * @todo: document this function
  */
bool Prim::verificaVertice(int id)
{
        for (std::list<int>::iterator it = verticesInclusos.begin(); it != verticesInclusos.end(); it++)
        {
                if ( *it == id)
                        return true;
        }
        return false;
}

/** @brief execute
  *
  * @todo: document this function
  */
Grafo* Prim::execute()
{
        printf("Prim::execute selecionarArestas\n");
        selecionarArestas();
        printf("Prim::execute criarNovoGrafo\n");
        return criarNovoGrafo();
}

/** @brief especificCondition
  *
  * @todo: document this function
  */
bool Prim::especificCondition() const
{
        bool conexo = grafo->isConexo();
        bool bidirecional = grafo->isBidirecional();
        bool retorno = conexo && bidirecional;
        printf("isConexoOrientadoFrom %d?\n", origem->getId());
        if (!retorno)
                AMBIENTE->addMessageBox(L"Instancia incompleta", L"A instancia nao cumpre as exigencias do algoritmo");
        return retorno;
}

/** @brief needOrigem
  *
  * @todo: document this function
  */
bool Prim::needOrigem() const
{
        return true;
}

/** @brief getNome
  *
  * @todo: document this function
  */
const std::string Prim::getNome() const
{
        return "Prim";
}


/** @brief selecionarArestas
  *
  * @todo: document this function
  */
void Prim::selecionarArestas()
{
        grafo->ordenarArestasPorPeso();
        verticesInclusos.push_back(origem->getId());
        origem->selecionar();
        vector<Aresta*> arestasCandidatas = grafo->getArestas();
        for (int i = 0; (int)verticesInclusos.size() < numVertices; i++) //Selecionei todas as arestas!
        {
                int origemId = arestasCandidatas[i]->getVerticeOrigem()->getId();
                int destinoId = arestasCandidatas[i]->getVerticeDestino()->getId();
                bool origemIdJaIncluso = verificaVertice(origemId);
                bool destinoIdJaIncluso = verificaVertice(destinoId);
                arestasCandidatas[i]->selecionar();
                if ((origemIdJaIncluso ^ destinoIdJaIncluso))// || //Se a origem já consta na lista
                     //(arestasCandidatas[i]->isBidirecional() && !origemIdJaIncluso && destinoIdJaIncluso) )
                {

                        arestasSelecionadas.push_back(arestasCandidatas[i]);
                        if (!origemIdJaIncluso)
                        {
                                grafo->findVerticeById(origemId)->selecionar();
                                verticesInclusos.push_back(origemId);
                        }
                        else
                        {
                                grafo->findVerticeById(destinoId)->selecionar();
                                verticesInclusos.push_back(destinoId);
                        }
                        arestasCandidatas.erase(arestasCandidatas.begin() + i);
                        i = -1;
                }
                else
                        arestasCandidatas[i]->desselecionar();

        }
}


/** @brief criarNovoGrafo
  *
  * @todo: document this function
  */
Grafo* Prim::criarNovoGrafo()
{
        Grafo* novoGrafo = new Grafo();
        for (std::list<int>::iterator it = verticesInclusos.begin(); it != verticesInclusos.end(); it++) //Criando os vértices
        {
                novoGrafo->addVertice(new Vertice(*it, grafo->findVerticeById(*it))); //Eles têm que ter o mesmo ID
        }
//        printf("Vou criar as arestas\n");
        for (std::list<Aresta*>::iterator it = arestasSelecionadas.begin(); it != arestasSelecionadas.end(); it++)     //Cria as arestas
        {
                const Vertice* velhoVerticeOrigem = (*it)->getVerticeOrigem();
                Vertice* novoVerticeOrigem = novoGrafo->findVerticeById(velhoVerticeOrigem->getId());

                const Vertice* velhoVerticeDestino = (*it)->getVerticeDestino();
                Vertice* novoVerticeDestino = novoGrafo->findVerticeById(velhoVerticeDestino->getId());

                Aresta* novaAresta = new Aresta(novoVerticeOrigem, novoVerticeDestino);
                novoGrafo->addAresta(novaAresta);
                if ((*it)->isBidirecional())
                        novaAresta->mudarTipo(); //Todas começam sem ser bidirecional
                novaAresta->editarValor((*it)->getValor());
        }
        return novoGrafo;
}

