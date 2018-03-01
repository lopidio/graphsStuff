#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <Irrlicht.h>
#include <sstream>
#include "GrafoObjeto.h"
#include <vector>
#include <list>
#include "Vertice.h"
#include "Aresta.h"
#include "Grafo.h"
#include "Algoritmos.h"
#include "Animacao.h"

#define SEM_ARESTA INT_MAX

class Vertice;
class Aresta;

class Grafo
{
        public:
                Grafo();
//                Grafo(std::list<GrafoObjeto*>);
                virtual ~Grafo();
                std::list<GrafoObjeto*>& getSelecionados();

                void selecionarGrafoObjeto(GrafoObjeto*);
                void desselecionarGrafoObjeto(GrafoObjeto*);
                void addVertice(Vertice*);
                void addAresta(); //Aqui mesmo eu checo os objetos selecionados!
                void addAresta(Aresta*);
                void limparListaDeSelecao();
                void selecionarTudo();
                void selecionarTodosVertices();
                void selecionarTodasArestas();
                void deleteAresta(Aresta*);
                void deleteVertice(Vertice*);
                void sofreuAlteracao();
                Vertice* findVerticeById(int) const;
                Aresta* findArestaByVerticesID(int, int);
                int getNumVertices() const;
                int ** getMatriz();
                bool isConexo( ) const;
                bool isFortementeConexo() const;
                bool isCiclico() const;
                bool isCompleto() const;
                bool isBidirecional() const;
                bool isTodoSelecionado() const;
                bool isConexoOrientadoFrom(int) const;
                bool isDigrafo() const;
                int existeCaminhoEntre(int, int, int) const;
                const vector<Vertice*>& getVertices() const;
                const vector<Aresta*>& getArestas() const;
                void ordenarArestasPorPeso();


		void mover ();
                const wstring& getNome() const;
                void setNome(const wstring& novoNome);
                void abrirArquivo(std::string &);
                void salvarArquivo(std::string &);
                void novoArquivo();
                void update();
                void atualizarMatriz();
                void draw() const;
                Animacao& getAnimacao();
                bool isVazio() const;

                bool getModificado() const;
                int numArestasDoVertice(int);
        protected:
        private:
                enum eVerticeState {VerticeNaoLido, VerticeNaEspera, VerticeLido};
                Animacao animacao;

                void arquivoCorrompido();
                vector<Vertice*> vertices;
                vector<Aresta*> arestas;
                std::list<GrafoObjeto*> selecionados;
                int ** matriz; //Matriz de adjacências
                int tamanhoMatriz;
                bool modificado; //Responde se o arquivo foi modificado desde a última salvagem. :D
                Aresta* existeArestaIgual(Aresta*) const;
                void deletarMatriz();
                void realocarMatriz(int);
                wstring nome;
};

#endif // GRAFO_H
