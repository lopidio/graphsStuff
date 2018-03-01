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


#include "Detalhes.h"

Detalhes::Detalhes(IGUIWindow* janela_, IGUIStaticText* campoTexto_)
{
        janela = janela_;
        janela->setText(L"Informacoes");
        janela->setVisible(false);
 	campoTexto = campoTexto_;
        nadaSelecionado();
//        janela->setPosition
}

Detalhes::~Detalhes()
{
        //dtor
}

/** @brief nadaSelecionado
  *
  * @todo: document this function
  */
void Detalhes::nadaSelecionado()
{
 	campoTexto->setText(L"---");
}

/** @brief verticesAndArestas
  *
  * @todo: document this function
  */
void Detalhes::verticesAndArestas()
{
        std::list<GrafoObjeto*> lista = MAIN->getSelecionados();
        int arestas = 0;
        int vertices = 0;
        for (std::list<GrafoObjeto*>::iterator it = lista.begin(); it != lista.end() ; it++)
        {
                (*it)->getTipo() == tG_aresta ? arestas++: vertices++;
        }
        wstring arestasString = MAIN->StringToWString(MAIN->IntToString(arestas));
        wstring verticesString = MAIN->StringToWString(MAIN->IntToString(vertices));
        wstring final = L"Detalhes:\n";
        final.append(L"Nao e um grafo valido");final.append(L"\n");
        final.append(L"Numero de arestas: "); final.append(arestasString); final.append(L"\n");
        final.append(L"Numero de vertices: "); final.append(verticesString); final.append(L"\n");
        campoTexto->setText(final.c_str());
}

wstring boolToWString(bool b)
{
        wstring retorno = L"Nao";
        if (b)
                retorno = L"Sim";
        return retorno;
}

/** @brief totalGrafo
  *
  * @todo: document this function
  */
void Detalhes::totalGrafo()
{
        const Grafo* grafo = MAIN->getGrafo();
        printf("Detalhes::isCiclico\n");
        wstring conexo = boolToWString(grafo->isConexo());
        wstring ciclico = boolToWString(grafo->isCiclico());
        wstring fortementeConexo = boolToWString(grafo->isFortementeConexo());
        wstring completo = boolToWString(grafo->isCompleto());
        wstring digrafo = boolToWString(grafo->isDigrafo());

        wstring final = L"Detalhes:\n";
        final.append(L"Conexo: "); final.append(conexo); final.append(L"\n");
        final.append(L"Fortemente Conexo: "); final.append(fortementeConexo); final.append(L"\n");
        final.append(L"Completo: "); final.append(completo); final.append(L"\n");
        final.append(L"Ciclico: "); final.append(ciclico); final.append(L"\n");
        final.append(L"Digrafo: "); final.append(digrafo); final.append(L"\n");
        campoTexto->setText(final.c_str());
}




/** @brief umaAresta
  *
  * @todo: document this function
  */
void Detalhes::umaAresta()//label, id dos vertices, tipo (adjacente ou misto)
{
        Aresta* aresta = static_cast<Aresta*>(MAIN->getSelecionados().front());
        wstring valor = aresta->getValor();
        wstring origem = aresta->getVerticeOrigem()->getValor();
        wstring destino = aresta->getVerticeDestino()->getValor();
        wstring tipo = (aresta->isBidirecional() == tA_bidirecional)? L"Bidirecional" : L"Unidirecional";
        wstring final = L"Detalhes:\n";
        final.append(L"Peso: "); final.append(valor); final.append(L"\n");
        final.append(L"Tipo: "); final.append(tipo); final.append(L"\n");
        final.append(L"Vertice origem: "); final.append(origem); final.append(L"\n");
        final.append(L"Vertice destino: "); final.append(destino); final.append(L"\n");
        campoTexto->setText(final.c_str());
}

/** @brief umVertice
  *
  * @todo: document this function
  */
void Detalhes::umVertice()//label, posição, arestas adjacentes, arestas incidentes
{
        printf("Detalhes::umVertice()\n");
        Vertice* vertice = static_cast<Vertice*>(MAIN->getSelecionados().front());
        int id = vertice->getId();
        wstring valor = vertice->getValor();
        int numArestasAdjacentes = MAIN->numArestasDoVertice(vertice->getId());
        int numArestasIncidente = 0;
        int** matriz = MAIN->getGrafo()->getMatriz();
        for (int i = 0; i < MAIN->numVertices(); i++)
                numArestasIncidente += matriz[i][id] != SEM_ARESTA;

        wstring arestasAdjacentes =  MAIN->StringToWString(MAIN->IntToString(numArestasAdjacentes));
        wstring arestasIncidentes =  MAIN->StringToWString(MAIN->IntToString(numArestasIncidente));
        wstring stringId = MAIN->StringToWString(MAIN->IntToString(id));
        wstring posX =  MAIN->StringToWString(MAIN->IntToString(vertice->getPosicao().X));
        wstring posY =  MAIN->StringToWString(MAIN->IntToString(vertice->getPosicao().Y));

        wstring final = L"Detalhes:\n";
        final.append(L"Label: "); final.append(valor); final.append(L"\n");
        final.append(L"ID: "); final.append(stringId); final.append(L"\n");
        final.append(L"Arestas adjacentes: "); final.append(arestasAdjacentes); final.append(L"\n");
        final.append(L"Arestas incidentes: "); final.append(arestasIncidentes); final.append(L"\n");
        final.append(L"Posicao: "); final.append(posX); final.append(L", "); final.append(posY); final.append(L"\n");
        campoTexto->setText(final.c_str());
}

/** @brief arestasOnly
  *
  * @todo: document this function
  */
void Detalhes::arestasOnly()//numArestas, soma dos pesos, média dos pesos
{
        std::list<GrafoObjeto*> lista = MAIN->getSelecionados();
        int somaPesos = 0;
        bool orientado = false;
        bool bidirecional = false;
        for (std::list<GrafoObjeto*>::iterator it = lista.begin(); it != lista.end() ; it++)
        {
                somaPesos += MAIN->StringToInt(MAIN->WStringToString((*it)->getValor()));
                static_cast<Aresta*>((*it))->isBidirecional() == tA_bidirecional?  bidirecional = true :orientado = true;
        }
        wstring soma = MAIN->StringToWString(MAIN->IntToString(somaPesos));
        wstring media = MAIN->StringToWString(MAIN->FloatToString((float)somaPesos/lista.size()));
        wstring numArestas = MAIN->StringToWString(MAIN->IntToString(lista.size()));
        wstring tipo;
        if (orientado)
        {
                if (bidirecional)
                        tipo = L"Mistas";
                else
                        tipo = L"Unidirecionais";
        }
        else
        {
                if (bidirecional)
                        tipo = L"Bidirecionais";
        }
        wstring final = L"Detalhes:\n";
        final.append(L"Numero de arestas: "); final.append(numArestas); final.append(L"\n");
        final.append(L"Peso: "); final.append(soma); final.append(L"\n");
        final.append(L"Media de custo: "); final.append(media); final.append(L"\n");
        final.append(L"Arestas tipo: "); final.append(tipo); final.append(L"\n");
        campoTexto->setText(final.c_str());
}

/** @brief verticesOnly
  *
  * @todo: document this function
  */
void Detalhes::verticesOnly()//numVertices
{
        std::list<GrafoObjeto*> lista = MAIN->getSelecionados();
        wstring numVertices = MAIN->StringToWString(MAIN->IntToString(lista.size()));

        wstring final = L"Detalhes:\n";
        final.append(L"Numero de vertices: "); final.append(numVertices); final.append(L"\n");
        campoTexto->setText(final.c_str());
}

/** @brief isVisivel
  *
  * @todo: document this function
  */
bool Detalhes::isVisivel() const
{
        return janela->isVisible();
}

/** @brief setVisibilidade
  *
  * @todo: document this function
  */
void Detalhes::setVisibilidade(bool novo)
{
        janela->setVisible(novo);
        if (novo)
                update();
}

/** @brief update
  *
  * @todo: document this function
  */
void Detalhes::update()
{
        if (!isVisivel())
                return;
        bool existeVertice = false;
        bool existeAresta = false;
        const std::list<GrafoObjeto*> lista = MAIN->getSelecionados();
        for (std::list<GrafoObjeto*>::const_iterator it = lista.begin(); it != lista.end(); it++)
        {
                if ((*it)->getTipo() == tG_aresta)
                        existeAresta = true;
                else
                        existeVertice = true;
                if (existeAresta && existeVertice)
                        break;
        }


        if (MAIN->isTodoGrafoSelecionado())
                totalGrafo();
        else if (lista.size() == 1)
        {
                if (existeAresta)
                        umaAresta();
                else
                        umVertice();
        }
        else if (lista.size() > 1)
        {
                if (existeAresta && !existeVertice)
                        arestasOnly();
                else if (existeVertice && !existeAresta)
                        verticesOnly();
                else
                        verticesAndArestas();
        }
        else
                nadaSelecionado();
}

