///* *********************************************/
///********************************************  /
////
//// @date -
////
//// Project -
////
////  if (!bug)
////	@author Lopídio (I love America)
////  else
////	@author Unkwonn
////
////
////  Good Luck!
//** *********************************/
///* *******************************/
//
//
//#include "BuscaLargura.h"
//
//BuscaLargura::BuscaLargura()
//{
//    printf("Busca em largura construtor\n");
//}
//
//BuscaLargura::~BuscaLargura()
//{
//    //dtor
//}
//
//
//void printFila(queue<Vertice*> p)
//{
//    printf("Fila: --> ");
//    while (p.size() > 0)
//    {
//        printf("%d  ", p.front()->getId());
//        p.pop();
//    }
//    printf("\n");
//}
//
///** @brief stepExecute
//  *
//  * @todo: document this function
//  */
//bool BuscaLargura::stepExecute(int id)
//{
//    visitados.push_back(id);
//    Vertice* verticeAtual = fila.front();
//    animacao->addStep( verticeAtual ,eA_select); // Gera a animação
//    if (id == destino->getId())
//        return true;
//    printFila(fila);
//    bool temFilhoNaoVisitado = false;
//    for (int i = 0; i < numVertices; i++)
//    {
//        if (matriz[id][i] != SEM_ARESTA && !verificaExistenciaNaLista(i))
//        {
//            fila.push(grafo->findVerticeById(i));
//            temFilhoNaoVisitado = true;
//        }
//    }
//    if (temFilhoNaoVisitado)
//        fila.pop();
//    animacao->addStep( verticeAtual,eA_deselect); // Gera a animação
//    return false;
//}
//
///** @brief verificaExistenciaNaLista
//  *
//  * @todo: document this function
//  */
//bool BuscaLargura::verificaExistenciaNaLista(int i)
//{
//    for (std::list<int>::iterator it = visitados.begin(); it != visitados.end(); it++)
//    {
//        if ( *it == i)
//            return true;
//    }
//    return false;
//}
//
///** @brief execute
//  *
//  * @todo: document this function
//  */
Grafo* BuscaLargura::execute()
{
        return NULL;
}
//
///** @brief getNome
//  *
//  * @todo: document this function
//  */
//const std::string BuscaLargura::getNome() const
//{
//    return "Busca em Largura";
//}
//
///** @brief needDestino
//  *
//  * @todo: document this function
//  */
//bool BuscaLargura::needDestino() const
//{
//    return true;
//}
//
///** @brief needOrigem
//  *
//  * @todo: document this function
//  */
//bool BuscaLargura::needOrigem() const
//{
//    return true;
//}
//
