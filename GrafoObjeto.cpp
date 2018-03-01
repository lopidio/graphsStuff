/* *********************************************/
/********************************************  /
//
// @date -
//
// Project -
//
//  if (!bug)
//	@author Lop�dio (I love America)
//  else
//	@author Unkwonn
//
//
//  Good Luck!
** *********************************/
/* *******************************/


#include "GrafoObjeto.h"
#include "Principal.h"


/** @brief GrafoObjeto
  *
  * @todo: document this function
  */
 GrafoObjeto::GrafoObjeto()
{
}

/** @brief GrafoObjeto
  *
  * @todo: document this function
  */
 GrafoObjeto::GrafoObjeto(eTipoGrafo tipo_)
{
        tipoGrafo = tipo_;
        //Lembrar de pegar a cor selecionada
        cor = SColor(255,200,0,100);
        selecionado = false;
        mouseOver = false;
        valor = L"";
}

void  GrafoObjeto::loadImage()
{
        printf("OII fora\n");
}

/** @brief marcarParaRemover
  *
  * @todo: document this function
  */
void GrafoObjeto::marcarParaRemover()
{
        paraRemover = true;
}

/** @brief setCores
  *
  * @todo: document this function
  */
void GrafoObjeto::setCores(const SColor& cor_, const SColor& corTexto_)
{
        cor = cor_;
        corTexto = corTexto;
}

/** @brief selecionar
  *
  * @todo: document this function
  */
void GrafoObjeto::selecionar()
{
        if (!selecionado)
                MAIN->addGrafoALista(this);
        selecionado = true;
}

/** @brief desselecionar
  *
  * @todo: document this function
  */
void GrafoObjeto::desselecionar()
{
        if (selecionado)
                MAIN->deleteGrafoALista(this);
        selecionado = false;
}

/** @brief isMarcadoParaRemocao
  *
  * @todo: document this function
  */
bool GrafoObjeto::isMarcadoParaRemocao() const
{
        return paraRemover;
}

/** @brief isSelecionado
  *
  * @todo: document this function
  */
bool GrafoObjeto::isSelecionado() const
{
        return selecionado;
}

/** @brief getTipo
  *
  * @todo: document this function
  */
eTipoGrafo GrafoObjeto::getTipo() const
{
        return tipoGrafo;
}

/** @brief onClick
  *
  * @todo: document this function
  */
void GrafoObjeto::onClick()
{
         if (mouseOver) //Mouse t� em cima de mim
        {
                if (!selecionado)                 //Se eu tiver sido selecionado agr, eu me add � lista de sele��o
                {
                        if ( !(MENU == mO_criar && tipoGrafo == tG_aresta ) && MENU != mO_count) //N�o pode selecionar arestas no menu criar
                        {
                                selecionar();
                        }
                }
                else
                {
            //            if (MOUSE->getControl())
                        {
                                desselecionar();
                        }
                }
        }
        else
        {
                if (!MOUSE->isOver()) // Mouse n�o t� em ningu�m
                {
                        desselecionar();
                }
        }
}
/** @brief getValor
  *
  * @todo: document this function
  */
const wstring & GrafoObjeto::getValor() const
{
        return valor;
}

/** @brief verificaRetangulo
  *
  * @todo: document this function
  */
void GrafoObjeto::verificaRetangulo()
{
        if (MOUSE->getRetangulo())
        {
                if (isInsideRetangulo())
                {
                        selecionar();
                }
                else
                {
                        desselecionar();
                }
        }
}

