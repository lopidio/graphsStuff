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

#include <stack>
#include "Grafo.h"

Grafo::Grafo()
{
        nome = L"Nova ";
        modificado = false;
        matriz = NULL;
}

///** @brief Grafo
//  *
//  * @todo: document this function
//  */
// Grafo::Grafo(std::list<GrafoObjeto*> novoGrafo)
//{
//        nome = L"Nova ";
//        modificado = false;
//        matriz = NULL;
//        animando = false;
//        animationTime = 1000;
//
//        for (std::list<GrafoObjeto*>::iterator it = novoGrafo.begin(); it != novoGrafo.end(); it++)
//        {
//                switch( (*it)->getTipo())
//                {
//                        case tG_vertice:
//                                        vertices.push_back(new Vertice(static_cast<Vertice*>(*it)));
//                                break;
//                        case tG_aresta:
//                                        Vertice* origem = const_cast<Vertice*>(static_cast<Aresta*>((*it))->getVerticeOrigem());
//                                        Vertice* destino = const_cast<Vertice*>(static_cast<Aresta*>((*it))->getVerticeDestino());
//                                        arestas.push_back(new Aresta(origem, destino));
//                                break;
//                }
//        }
//}

Grafo::~Grafo()
{
        printf("DESTRUIU GRAFO\n");
        deletarMatriz();
        while(vertices.size() > 0)
        {
                deleteVertice(vertices.front());
        }
        printf("/DESTRUIU GRAFO\n");
        //dtor
}
/** @brief setNome
  *
  * @todo: document this function
  */
void Grafo::setNome(const wstring& novoNome)
{
        nome = novoNome;
}

/** @brief getNome
  *
  * @todo: document this function
  */
const wstring & Grafo::getNome() const
{
        return nome;
}

/** @brief draw
  *
  * @todo: document this function
  */
void Grafo::draw() const
{
//        printf("\Grafo::draw\n");
        for (int i = arestas.size() - 1; i >= 0; --i)
                arestas[i]->draw();
//        printf("\t\tGrafo::draw1\n");

        for (int i = vertices.size() - 1; i >= 0; --i)
                if (!vertices[i]->isSelecionado())        //Maneira de puxar os selecionados sempre para o topo
                        vertices[i]->draw();
//        printf("\t\t/Grafo::draw2\n");

        for (int i = vertices.size() - 1; i >= 0; --i)
                if (vertices[i]->isSelecionado())
                        vertices[i]->draw();
//        printf("\t\t/Grafo::draw3\n");

//        printf("\t/Grafo::draw\n");
}

/** @brief update
  *
  * @todo: document this function
  */
void Grafo::update()
{
        //Atualizando todos os GrafoObjetos
        for (int i = 0 ;i < (int)vertices.size(); ++i)
                vertices[i]->update(); //Atualiza todos os vértices
        for (int i = arestas.size() - 1; i >= 0; --i)
                arestas[i]->update(); //Atualiza todos as arestas

        //animacao.update(); /Quem dá o play na animação é o animationPlayer!
}

/** @brief mover
  *
  * @todo: document this function
  */
void Grafo::mover()
{
        position2df ponto = MOUSE->getMovimento();
        for (int i = vertices.size() - 1; i >= 0; --i)
        {
                vertices[i]->mover(ponto.X, ponto.Y);
        }
        sofreuAlteracao();
}

/** @brief getVertices
  *
  * @todo: document this function
  */
const vector<Vertice*> &Grafo::getVertices() const
{
        return vertices;
}

/** @brief getArestas
  *
  * @todo: document this function
  */
const vector<Aresta*>& Grafo::getArestas() const
{
        return arestas;
}

//True caso o primeiro seja menor
bool compareAresta (const Aresta* a, const Aresta* b)
{
        return MAIN->StringToInt( MAIN->WStringToString(a->getValor() ))  < MAIN->StringToInt( MAIN->WStringToString(b->getValor() ));
}


/** @brief ordenarArestasPorPeso
  *
  * @todo: document this function
  */
void Grafo::ordenarArestasPorPeso()
{
        std::list<Aresta*> listaArestaProvisoria;
        for (int i = 0; i < (int)arestas.size(); i++)
                listaArestaProvisoria.push_back(arestas[i]);
        listaArestaProvisoria.sort(compareAresta);
        arestas.clear();
        for (std::list<Aresta*>::iterator it = listaArestaProvisoria.begin(); it != listaArestaProvisoria.end(); it++)
                arestas.push_back(*it);
}



/** @brief desselecionarGrafoObjeto
  *
  * @todo: document this function
  */
void Grafo::desselecionarGrafoObjeto(GrafoObjeto* obj)
{
    //    if (animacao.isGravando() && MENU == mO_mover)
                animacao.addStep(obj, eA_deselect);
        selecionados.remove(obj);
}

/** @brief addAresta
  *
  * @todo: document this function
  */
void Grafo::addAresta()
{
        //No menu criar, só é possível selecionar vértices
       Vertice * origem = static_cast<Vertice*>(selecionados.front());
        std::list<GrafoObjeto*>::iterator depoisDoUltimo = selecionados.end();
        depoisDoUltimo--;
        Vertice *destino = static_cast<Vertice*>(*depoisDoUltimo);
        if (destino != origem)
        {
                Aresta* nova = new Aresta(origem, destino);
                if (!existeArestaIgual(nova))
                        arestas.push_back(nova);
                else
                        delete nova;
                origem->desselecionar();
                destino->selecionar();
        }
        sofreuAlteracao();
        atualizarMatriz();
}

/** @brief addAresta
  *
  * @todo: document this function
  */
void Grafo::addAresta(Aresta* nova)
{
        if (nova)
        {
                arestas.push_back(nova);
                sofreuAlteracao();
                atualizarMatriz();
        }
}



/** @brief addVertice
  *
  * @todo: document this function
  */
void Grafo::addVertice(Vertice* novo)
{
//        printf("Grafo::add vertice: %d\n", novo);
//        system("pause>null");
        vertices.push_back(novo);
        sofreuAlteracao();
        atualizarMatriz();
//        printf("/Grafo::add vertice\n");
}

/** @brief limparListaDeSelecao
  *
  * @todo: document this function
  */
void Grafo::limparListaDeSelecao()
{
        while (selecionados.size() > 0)
        {
                selecionados.front()->desselecionar();
        }
}

/** @brief selecionarGrafoObjeto
  *
  * @todo: document this function
  */
void Grafo::selecionarGrafoObjeto(GrafoObjeto* objeto)
{
      //  if (animacao.isGravando()  && MENU == mO_mover)
                animacao.addStep(objeto, eA_select);
        sofreuAlteracao();
        selecionados.push_back(objeto);
}


/** @brief existeArestaIgual
  *
  * @todo: document this function
  */
Aresta* Grafo::existeArestaIgual(Aresta* nova) const
{
        for (int i = arestas.size() - 1; i >= 0; i--)
        {
                if (*nova == *arestas[i])
                        return arestas[i];
        }
        return NULL;
}

/** @brief findArestaByVerticesID
  *
  * @todo: document this function
  */
Aresta* Grafo::findArestaByVerticesID(int i , int j)
{
        Aresta* teste = new Aresta(findVerticeById(i),findVerticeById(j));
        Aresta* existe = existeArestaIgual(teste);
        if (existe)
        {
                if (existe->isBidirecional() || teste->getVerticeOrigem()->getId() == existe->getVerticeOrigem()->getId()) //Aresta é igual de verdade
                {
                        delete teste;
                        return existe;
                }
        }
        delete teste;
        return NULL;
}

/** @brief deleteVertice
  *
  * @todo: document this function
  */
void Grafo::deleteVertice(Vertice* vertice)
{
        desselecionarGrafoObjeto(vertice);
        animacao.deleteAllReferences(vertice);
        for (int i = 0; i < (int)vertices.size(); i++)
        {
                if (vertice->getId() == vertices[i]->getId())
                {
                        for (std::vector<Aresta*>::iterator it = arestas.begin(); it != arestas.end() && arestas.size() > 0; it++) //Apaga todas as arestas relacionadas ao vértice
                        {
                          //      printf("Comecei o laco das arestas\n");
                                if ((*it)->eDoVertice(vertices[i])) //Cópia da função deleteArestas
                                {
                           //             printf("Apaguei uma aresta\n");
                                        desselecionarGrafoObjeto(*it);
                                        delete *it;
                                        arestas.erase(it);
                                        it--;
                                }
                        }
                        delete vertices[i];
                        vertices[i] = NULL;
                        vertices.erase(vertices.begin() + i);
                        for (; i < (int)vertices.size(); i++)
                                vertices[i]->setId(i);
                        break; //Inútil.. Mas vai que...?
                }
        }
        sofreuAlteracao();
        atualizarMatriz();
}

/** @brief deleteAresta
  *
  * @todo: document this function
  */
void Grafo::deleteAresta(Aresta* aresta)
{
        desselecionarGrafoObjeto(aresta);
        animacao.deleteAllReferences(aresta);
        for (int i = arestas.size() - 1; i >= 0; i--)
        {
                if (*aresta == *arestas[i])
                {
                        delete arestas[i];
                        arestas[i] = NULL;
                        arestas.erase(arestas.begin() + i);
                        //break;
                }
        }
        sofreuAlteracao();
        atualizarMatriz();
}

/** @brief findVerticeById
  *
  * @todo: document this function
  */
Vertice* Grafo::findVerticeById(int id) const
{
        for (int i = 0; i < (int)vertices.size(); ++i)
                if (vertices[i]->getId() == id)
                        return vertices[i];
        return NULL;
}

/** @brief numArestasDoVertice
  *
  * @todo: document this function
  */
int Grafo::numArestasDoVertice(int id)
{
        atualizarMatriz();
        if (id>= 0 && id < getNumVertices())
        {
                int retorno = 0;
                for (int i = 0; i < (int)vertices.size(); ++i)
                        if (matriz[id][i] != SEM_ARESTA)
                                ++retorno;
                return retorno;
        }
        return -1;
}




/** @brief isConexo
  *
  * @todo: document this function
  */
bool Grafo::isConexo() const
{
        int n = vertices.size();
        eVerticeState* states = new eVerticeState[n];
        for (int i = 0; i < n; i++)
                states[i] = VerticeNaoLido;

        std::stack<int> pilha;
        pilha.push(0);
        while (pilha.size() > 0)
        {
                int i = pilha.top();
                pilha.pop();
                states[i] = VerticeLido;
                for (int j = 0; j < n; j++)
                        if (matriz[j][i] != SEM_ARESTA || matriz[i][j] != SEM_ARESTA) //Confere se atinge ou se é atingido
                                if (states[j] != VerticeLido)
                                        pilha.push(j);
        }
        bool retorno = true;
        for (int i = 0; i < n; i++)
                if (states[i] != VerticeLido)
                        retorno = false;
        delete[] states;
        return retorno;
}



/** @brief isFortementeConexo
  *
  * @todo: document this function
  */
bool Grafo::isFortementeConexo() const
{
        for (int i = 0; i < (int)vertices.size(); i++)
                if (!isConexoOrientadoFrom(i))
                        return false;
        return true;
}

/** @brief isConexoOrientadoFrom
  *
  * @todo: document this function
  */
bool Grafo::isConexoOrientadoFrom(int inicial) const
{
        int n = vertices.size();
        eVerticeState* states = new eVerticeState[n];
        for (int i = 0; i < n; i++)
                states[i] = VerticeNaoLido;

        std::stack<int> pilha;
        pilha.push(inicial);
        while (pilha.size() > 0)
        {
                int i = pilha.top();
                pilha.pop();
                states[i] = VerticeLido;
                for (int j = 0; j < n; j++)
                        if (matriz[i][j] != SEM_ARESTA) //Confere se atinge ou se é atingido
                                if (states[j] != VerticeLido)
                                        pilha.push(j);
        }
        bool retorno = true;
        for (int i = 0; i < n; i++)
                if (states[i] != VerticeLido)
                        retorno = false;
        delete[] states;
        return retorno;
}


/** @brief isCompleto
  *
  * @todo: document this function
  */
bool Grafo::isCompleto() const
{
        return arestas.size() == vertices.size()*(vertices.size() - 1)/2;
}


/** @brief existeCaminhoEntre
  *
  * @todo: document this function
  */
int Grafo::existeCaminhoEntre(int pai, int a, int b) const
{
  //      printf("Existe caminho\n");
        int n = vertices.size();
        if (a == b)
                return 0;
        for (int j = 0; j < n; j++)
                if ((matriz[a][j] != SEM_ARESTA || matriz[j][a] != SEM_ARESTA) && j != pai) //Confere se atinge ou se é atingido
                {
                        int existe = existeCaminhoEntre(a, j,b);
                        if (existe > -1)
                        {
//                                printf("%d  ", a);
                                return existe + 1;
                        }
                }
        return -1;
}




/** @brief isCiclico
  *
  * @todo: document this function
  */
bool Grafo::isCiclico() const
{
   //     printf("Grafo::isCiclico  \n");
        int n = vertices.size();
        for (int i = 1; i < n; i++)
                for (int j = 1; j < n; j++)
                        if (matriz[i][j] != SEM_ARESTA || matriz[j][i] != SEM_ARESTA)
                        {
//                                bool retorno = );
//                                printf("\n");
                                if ((existeCaminhoEntre(i, j,i) > 1))
                                        return true;
                        }
        return false;
}

/** @brief isDigrafo
  *
  * @todo: document this function
  */
bool Grafo::isDigrafo() const
{
        for (int i =0; i < arestas.size(); i++)
                if (arestas[i]->isBidirecional())
                        return false;
        return true;
}

/** @brief isBidirecional
  *
  * @todo: document this function
  */
bool Grafo::isBidirecional() const
{
        for (int i =0; i < arestas.size(); i++)
                if (!arestas[i]->isBidirecional())
                        return false;
        return true;
}


bool Grafo::isTodoSelecionado() const
{
        return selecionados.size() == vertices.size() + arestas.size();
}

void Grafo::atualizarMatriz()
{
        int tamanho = vertices.size();
        realocarMatriz(tamanho);
        tamanhoMatriz = tamanho;
        for (int i = 0 ; i < (int)arestas.size(); i++)
	{
                Aresta* a = arestas[i];
                int valor = atoi(MAIN->WStringToString(a->getValor()).c_str());
                matriz[a->getVerticeOrigem()->getId()][a->getVerticeDestino()->getId()] = valor;
                if (a->isBidirecional())
                        matriz[a->getVerticeDestino()->getId()][a->getVerticeOrigem()->getId()] = valor;    //Simetria
	}
//                printf("***************** Atualizou MATRIZ :%d********\n", matriz);
//	for (int i = 0; i < tamanho; ++i)
//	{
//	        for (int j = 0; j < tamanho; ++j)
//                        printf("%10d ", matriz[i][j] == SEM_ARESTA ? -99: matriz[i][j]);
//                printf("\n");
//	}
//                printf("***************** fim MATRIZ **************\n");
}

void Grafo::deletarMatriz()
{
        if (!matriz)
                return;
	for (int i = 0; i < tamanhoMatriz; i++)
                delete[] matriz[i];
	delete[] matriz;
	matriz = NULL;
}

void Grafo::realocarMatriz(int tamanho)
{
        if (matriz)
                deletarMatriz();
	matriz = new int*[tamanho];
	for (int i = 0; i < tamanho; i++)
		matriz[i] = new int[tamanho];
	for (int i = 0; i < tamanho; ++i) //Carreguei toda a matriz
		for (int j = 0; j < tamanho; ++j)
			matriz[i][j] = SEM_ARESTA;		 //Valor padrão para quando não há arestas
}


/** @brief sofreuAlteracao
  *
  * @todo: document this function
  */
void Grafo::sofreuAlteracao()
{
        if (!modificado)
        {
                wstring asterisco = L"*";
                nome = asterisco.append(nome);
             //   MAIN->nomeAbaModificado();
        }
        modificado = true;
}


/** @brief getModificado
  *
  * @todo: document this function
  */
bool Grafo::getModificado() const
{
        return modificado;
}

/** @brief isVazio
  *
  * @todo: document this function
  */
bool Grafo::isVazio() const
{
        return vertices.size() == 0;
}



void Grafo::novoArquivo()
{
        if (isVazio())
                return;
        sofreuAlteracao();
	deletarMatriz();
	while(vertices.size() > 0)
		deleteVertice(*vertices.begin()); //Esse método se encarrega de deletar todas as arestas relacionadas e em tirá-lo da lista de seleçao
        vertices.clear();
        arestas.clear();
        selecionados.clear();
}


/** @brief abrirArquivo
  *
  * @todo: document this function
  */
void Grafo::abrirArquivo(std::string &nomeArquivo)
{
        novoArquivo();
        if ((int)nomeArquivo.find(".grafo") == -1)
        {
                printf("nome errado\n");
                return arquivoCorrompido();
        }
        FILE* fp = fopen(nomeArquivo.c_str(), "rt");
	int n;
	fscanf(fp, "%d\n", &n);
	//printf("Quantidade: %d\n", n);
	for (int i = 0; i < n; i++)
	{
		Vertice* novo = new Vertice(i , fp);
		vertices.push_back(novo);
	}
	for (int idOrigem = 0; idOrigem < n; idOrigem++)
	{
	        int inutil;
		int qtdArestas;
		fscanf(fp, "%d %d ", &inutil, &qtdArestas);
		Vertice*origem = findVerticeById(idOrigem);
		if (!origem)// mandar mensagem de arquivo corrompido
                {
//                        printf("vertice nao encontrado. idOrigem: %d\n", idOrigem);
                        return arquivoCorrompido();
                }
                for (int i = 0; i < qtdArestas; ++i)
		{
		        int idDestino, custo;
                        fscanf(fp, "%d %d ", &idDestino, &custo);
                        Vertice*destino = findVerticeById(idDestino);
                        if (!destino)// mandar mensagem de arquivo corrompido
                        {
//                                printf("vertice destino nao encontrado. idDestino: %d\n", idDestino);
                                return arquivoCorrompido();
                        }
                        Aresta* nova = new Aresta(origem, destino);
                        stringw custoStr = MAIN->StringToWString(MAIN->IntToString(custo).c_str()).c_str();
                        nova->editarValor(custoStr.c_str());
                        Aresta* igual = existeArestaIgual(nova);
                        if (igual)
                        {
                                igual->mudarTipo();
                                delete nova;
                        }
                        else
                                arestas.push_back(nova);
		}
	}
     //   printf("Abriu com sucesso\n");
        nome = MAIN->StringToWString(nomeArquivo);
        modificado = false;
        atualizarMatriz();
	fclose(fp);
}

/** @brief salvarArquivo
  *
  * @todo: document this function
  */
void Grafo::salvarArquivo(std::string & nomeArquivo)
{
        nomeArquivo.append(".grafo");
        FILE* fp = fopen(nomeArquivo.c_str(), "wt");
	atualizarMatriz();
	int n = vertices.size();
	fprintf(fp, "%d\n", n);
	for (int i = 0; i < n; i++)
		vertices[i]->salvar(fp, -1);
	for (int i = 0; i < n; i++) //Id do vértice origem
	{
                printf( "Vertice origem %d %d", i, numArestasDoVertice(i));
                fprintf(fp, "%d %d ", i, numArestasDoVertice(i));
                for (int j = 0; j < n; j++) //id do vértice destino
		{
			Aresta* aresta = findArestaByVerticesID(i,j); //id do vertice destino
			if (aresta)
			{
				aresta->salvar(fp, i); //Salva o destino e o custo
			}
		}
                printf("\n");
                fprintf(fp, "\n");
	}
	modificado = false;
	fclose(fp);
}

/** @brief getMatriz
  *
  * @todo: document this function
  */
int** Grafo::getMatriz()
{
        atualizarMatriz();
        return matriz;
}



/** @brief arquivoCorrompido
  *
  * @todo: document this function
  */
void Grafo::arquivoCorrompido()
{
        novoArquivo();
        AMBIENTE->addMessageBox(L"Arquivo corrompido", L"O arquivo nao se encontra em um formato valido");
}

/** @brief getNumVertices
  *
  * @todo: document this function
  */
int Grafo::getNumVertices() const
{
        return vertices.size();
}

/** @brief getSelecionados
  *
  * @todo: document this function
  */
std::list<GrafoObjeto*> & Grafo::getSelecionados()
{
        return selecionados;
}

/** @brief selecionarTodasArestas
  *
  * @todo: document this function
  */
void Grafo::selecionarTodasArestas()
{
        limparListaDeSelecao();
        for (int i = arestas.size() - 1; i >= 0; --i)
                arestas[i]->selecionar(); //Atualiza todos as arestas
}

/** @brief selecionarTodosVertices
  *
  * @todo: document this function
  */
void Grafo::selecionarTodosVertices()
{
        limparListaDeSelecao();
        for (int i = vertices.size() - 1; i >= 0; --i)
                vertices[i]->selecionar(); //Selecionar todos os vértices
}

/** @brief selecionarTudo
  *
  * @todo: document this function
  */
void Grafo::selecionarTudo()
{
        selecionarTodasArestas();
        for (int i = vertices.size() - 1; i >= 0; --i)
                vertices[i]->selecionar(); //Selecionar todos os vértices
}


/** @brief getAnimacao
  *
  * @todo: document this function
  */
Animacao & Grafo::getAnimacao()
{
        return animacao;
}

