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


#include "Kruskal.h"
#include <vector>

Kruskal::Kruskal()
{
        //ctor
}

Kruskal::~Kruskal()
{
        //dtor
}

/** @brief getNome
  *
  * @todo: document this function
  */
const std::string Kruskal::getNome() const
{
        return "Kruskal";
}


/** @brief execute
  *
  * @todo: document this function
  */
Grafo* Kruskal::execute()
{
        criarSemiComponentes();
        selecionarArestas();
        return criarNovoGrafo();
}

/** @brief especificCondition
  *
  * @todo: document this function
  */
bool Kruskal::especificCondition() const
{
        bool retorno = grafo->isConexo();
        if (!retorno)
                AMBIENTE->addMessageBox(L"Instancia incompleta", L"O grafo nao e conexo");
        return retorno;
}

/** @brief verificaVertice
  *
  * @todo: document this function
  */
bool Kruskal::SemiComponente::verificaVertice(int id)
{
        for (int j = verticesInclusos.size() - 1; j >= 0; --j)
                if (verticesInclusos[j] == id)
                        return true;
        return false;
}



/** @brief verificaVertice
  *
  * Retorna o índice do componente que o vértice pertence
  */
int Kruskal::verificaVertice(int id)
{
        for (int i = componentes.size() - 1; i >= 0; --i)
                if (componentes[i].verificaVertice(id))
                        return i;
        return -1;
}



/** @brief addComponente
  *
  * @todo: document this function
  */
void Kruskal::SemiComponente::addComponente(SemiComponente& a)
{
//        printf("Kruskal::SemiComponente::addComponente \n");
//                printf("IO\n");
        while (a.verticesInclusos.size() > 0)
        {
//                printf("Restam para copiar: %d\n", a.verticesInclusos.size());
                int aIncluir = a.verticesInclusos.back();
//                printf("aIncluir: %d\n", aIncluir);
                this->verticesInclusos.push_back(aIncluir);
                //verticesInclusos.insert(verticesInclusos.begin(), aIncluir);
//                printf("Kruskal::SemiComponente::addComponente  a.vertices.size(): %d\n", a.verticesInclusos.size());
                a.verticesInclusos.pop_back();
        }
//        printf("/ Kruskal::SemiComponente::addComponente \n");
}

/** @brief mergeComponente
  *
  * Insere b em A, e deleta b
  */
void Kruskal::mergeComponente(SemiComponente& a, SemiComponente& b)
{
//        printf("Kruskal::mergeComponente 1/3\n");
        a.addComponente(b);
//        printf("Kruskal::mergeComponente 2/3\n");
        for (int i = 0; i < (int)componentes.size(); i++)
        {
                if (componentes[i].verticesInclusos.size() == 0)//Deleta aquele que não tiver nenhum vértice
                {
                        componentes.erase(componentes.begin() + i);
                        return;
                }
        }
//        printf("Kruskal::mergeComponente 3/3\n");

}

/** @brief criarSemiComponentes
  *
  * @todo: document this function
  */
void Kruskal::criarSemiComponentes()
{
//        vector<Vertice*> vertices = grafo->getVertices();
        for (int i = numVertices - 1; i >= 0; --i)
        {
                SemiComponente novo;//(numVertices);
                grafo->findVerticeById(i)->selecionar();
                novo.verticesInclusos.push_back(i); //Os vértices sempre estão dispostos de 0 à n
                componentes.push_back(novo);
        }
}

/** @brief selecionarArestas
  *
  * @todo: document this function
  */
void Kruskal::selecionarArestas()
{
        grafo->ordenarArestasPorPeso();
        vector<Aresta*> arestasCandidatas = grafo->getArestas();

        for (int i = 0; componentes.size() > 1; i++) //Enquanto eu não tenho um só componente
        {
                printf("Iteracao  arestas.size(): %d      numComponentes:%d         i: %d\n", arestasSelecionadas.size(), componentes.size(), i);
                int origemId = arestasCandidatas[i]->getVerticeOrigem()->getId();
                int destinoId = arestasCandidatas[i]->getVerticeDestino()->getId();
                int indiceComponenteVerticeOrigem = verificaVertice(origemId);
                int indiceComponenteVerticeDestino = verificaVertice(destinoId);
                arestasCandidatas[i]->selecionar();
                printf("verifica aresta:      %d-%d\n", origemId, destinoId);
                if (indiceComponenteVerticeDestino != indiceComponenteVerticeOrigem)
                {
                        arestasSelecionadas.push_back(arestasCandidatas[i]);
                        //arestasCandidatas.erase(arestasCandidatas.begin() + i);
                        printf("------------------Add aresta:      %d-%d\n", origemId, destinoId);
                        mergeComponente(componentes[indiceComponenteVerticeDestino],
                                                        componentes[indiceComponenteVerticeOrigem]); //Mescla os dois
                }
                else
                        arestasCandidatas[i]->desselecionar();
                //i = 0;
        }
}


/** @brief criarNovoGrafo
  *
  * @todo: document this function
  */
Grafo* Kruskal::criarNovoGrafo()
{
        Grafo* novoGrafo = new Grafo();
        //Adicionando os vértices
        printf("Vou criar as vertices\n");
        vector<int>& vertices = componentes.back().verticesInclusos;
        for (int i = numVertices - 1; i >= 0; --i)
        {
                novoGrafo->addVertice(new Vertice(vertices[i], grafo->findVerticeById(vertices[i]))); //Eles têm que ter o mesmo ID
        }
        printf("Vou criar as arestas\n");
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


