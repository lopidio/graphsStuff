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
#include "Kruskal.h"
#include "Prim.h"
#include "BFS.h"
#include "Floyd.h"
#include "BuscaProfundidade.h"
#include "Algoritmos.h"



//Algoritmos::Algoritmos()
//{
//        //ctor
//}

Algoritmos::~Algoritmos()
{
        //dtor
}


/** @brief needRalo
  *
  * @todo: document this function
  */
bool Algoritmos::needDestino() const
{
        return false;
}

/** @brief needFonte
  *
  * @todo: document this function
  */
bool Algoritmos::needOrigem() const
{
        return false;
}

/** @brief getAlgoritmoFromID
  *
  * @todo: document this function
  */
Algoritmos* Algoritmos::getAlgoritmoFromID(short id)
{
        if (id == aID_buscaProfundidade)
                return new BuscaProfundidade();
        if (id == aID_dijkstra)
                return new Dijkstra();
        if (id == aID_kruskal)
                return new Kruskal();
        if (id == aID_prim)
                return new Prim();
        if (id == aID_buscaLargura)
                return new BFS();
        if (id == aID_floyd)
                return new Floyd();
        return NULL; //Retorno padrão!!!
}

/** @brief executeFromGrafo
  *
  * @todo: document this function
  */
Grafo* Algoritmos::executeFromGrafo(Grafo*grafo_)
{
        grafo = grafo_;
        getOrigem();
        getDestino();
        if ((needOrigem() && !origem) || (needDestino() && !destino))
                return NULL; //Condições básicas não cumpridas
        if (especificCondition() && grafo)
        {
                animacao = &grafo->getAnimacao();
                animacao->zerar();
                grafo->limparListaDeSelecao(); //
                animacao->comecarAGravar();

                //Depois de pegar a origem e o destino, desselecionar todos
                matriz = grafo->getMatriz();
                numVertices = grafo->getNumVertices();
                Grafo* retorno = execute();
                if (retorno)
                {
                        {//Nomeando o novo grafo
                                wstring novoNome = grafo->getNome();
                                novoNome.append(L"_");
                                novoNome.append(MAIN->StringToWString(getNome()));
                                if (needOrigem())
                                {
                                        novoNome.append(origem->getValor());
                                }
                                if (needDestino())
                                {
                                        novoNome.append(L"-");
                                        novoNome.append(destino->getValor());
                                }
                                retorno->setNome(novoNome); //Pega o nome do filho
                        }
                        printf("Algoritmos:: numVertices: %d\n", retorno->getNumVertices());

                        { //Detalhes da animação
                                animacao->zerarSelecoesEmUmStep();
                                animacao->pararGravacao();
                                grafo->limparListaDeSelecao(); //A limpeza é gravada
                                animacao->start();
                        }
                }
                return retorno;
        }
        return NULL;
}

/** @brief especifCondition
  *
  * @todo: document this function
  */
bool Algoritmos::especificCondition() const
{
        return true;
}


/** @brief getNome
  *
  * @todo: document this function
  */
const std::string Algoritmos::getNome() const
{
        return std::string("Algoritmo sem nome");
}

/** @brief getDestino
  *
  * @todo: document this function
  */
void Algoritmos::getDestino()
{
        destino = NULL;
        if (!needDestino())
                return;
        std::list<GrafoObjeto*> selecionados = grafo->getSelecionados();
        bool retorno = false;
        std::list<GrafoObjeto*>::iterator it = selecionados.end();
        if (needOrigem())
        {
                if (selecionados.size() > 1)
                {
                        it = selecionados.begin();
                        it++;
                }
                else
                        retorno = true;
        }
        else
        {
                it = selecionados.begin();
        }
        if (it != selecionados.end() && (*it)->getTipo() == tG_vertice)
                destino = static_cast<Vertice*>(*it);
        else
                retorno = true;
        if (retorno)
                AMBIENTE->addMessageBox(L"Instancia incompleta", L"O grafo precisa de um vertice de destino");
}

/** @brief getOrigem
  *
  * @todo: document this function
  */
void Algoritmos::getOrigem()
{
        origem = NULL;
        if (!needOrigem())
                return;
        std::list<GrafoObjeto*> selecionados = grafo->getSelecionados();
        if (selecionados.size() > 0 &&
            selecionados.front()->getTipo() == tG_vertice)
        {
                origem = static_cast<Vertice*>(selecionados.front());
        }
        else
        {
                AMBIENTE->addMessageBox(L"Instancia incompleta", L"O grafo precisa de um vertice de origem");
        }
}

