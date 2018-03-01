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


#include "Floyd.h"

Floyd::Floyd()
{
        matrizRetorno = new int*[numVertices];
        for (int i = 0; i < numVertices; i++)
                matrizRetorno[i] = new int[numVertices];


    //ctor
}

Floyd::~Floyd()
{
        for (int i = 0; i < numVertices; i++)
                delete[] matrizRetorno[i];
        delete[] matrizRetorno;
        matrizRetorno = NULL;
    //dtor
}


void printMatrizQuadrada(int ** m, int n)
{
        printf("print matriz *******************\n");
        for (int i = 0; i < n; i++)
        {
                for (int j = 0; j < n; j++)
                {
                        int x = m[i][j];
                        if (x == SEM_ARESTA)
                                x = -99;
                        printf("%5d  ", x);
                }
                printf("\n");
        }
        printf("********************************\n");
}


/** @brief execute
  *
  * @todo: document this function
  */
Grafo* Floyd::execute()
{
        printf("Floyd::execute\n");
        for (int i = 0; i < numVertices; i++)
                for (int j = 0; j < numVertices; j++)
                        matrizRetorno[i][j] = matriz[i][j]; //copia a matriz
        printMatrizQuadrada(matrizRetorno, numVertices);

        for(int k=0; k<numVertices; k++)
                for(int i=0; i<numVertices; i++)
                        for(int j=0; j<numVertices; j++)
                                if( i!=k && matrizRetorno[i][k] != SEM_ARESTA  && matrizRetorno[k][j] != SEM_ARESTA)
                                        if( matrizRetorno[i][j] > matrizRetorno[i][k]+matrizRetorno[k][j] )
                                                matrizRetorno[i][j] = matrizRetorno[i][k]+matrizRetorno[k][j];


        printMatrizQuadrada(matrizRetorno, numVertices);
        return createGraph();
}

/** @brief createGraph
  *
  * @todo: document this function
  */
Grafo* Floyd::createGraph()
{
        Grafo* novoGrafo = new Grafo();
        int id = origem->getId();
        Vertice* novaOrigem = new Vertice(id, origem);
        novoGrafo->addVertice(novaOrigem);
        for (int j = 0; j < numVertices; j++)
        {
                if (j != id) //Sim, eu conheço o CONTINUE, mas tava dando pau. Oo
                {
                        Vertice* novoVertice = new Vertice(j, grafo->findVerticeById(j));
                        novoGrafo->addVertice(novoVertice);

                }
        }

        for (int j = 0; j < numVertices; j++)
        {
                if (j != id) //Sim, eu conheço o CONTINUE, mas tava dando pau. Oo
                {
                        Aresta* novaAresta = new Aresta(novaOrigem, novoGrafo->findVerticeById(j));
                        novaAresta->editarValor(MAIN->StringToWString(MAIN->IntToString(matrizRetorno[id][j])));
                        novoGrafo->addAresta(novaAresta);
                }
        }
        return novoGrafo;
}

/** @brief needOrigem
  *
  * @todo: document this function
  */
bool Floyd::needOrigem() const
{
        return true;
}

/** @brief getNome
  *
  * @todo: document this function
  */
const std::string Floyd::getNome() const
{
        return "Floyd";
}




/** @brief especificCondition
  *
  * @todo: document this function
  */
bool Floyd::especificCondition() const
{
        vector<Aresta*> arestas = grafo->getArestas();
        for (unsigned int i = 0; i < arestas.size(); i++)
        {
                if (arestas[i]->getFloatValor() < 0)
                {
                        AMBIENTE->addMessageBox(L"Algoritmo de Floyd", L"O algoritmo nao aceita ciclos negativos");
                        return false;
                }
        }
        //retorno = retorno && grafo->isConexoOrientadoFrom(origem->getId());
        return true;
}

