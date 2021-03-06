#ifndef CONTROLADORUI_H_
#define CONTROLADORUI_H_

#include <QtWidgets/qmessagebox.h>

#include "excecao/ExcecaoArquivoInvalido.h"
#include "excecao/ExcecaoLeituraArquivo.h"
#include "geometria/Ponto.h"
#include "geometria/Mundo.h"

class ControladorPrincipal;
class FormPrincipal;
class FormInsercaoObjeto;
class ObjectTransformationWindow;

/**
 * Controlador da Interface Gráfica.
 */
class ControladorUI {

public:
	/**
	 * Construtor.
	 */
	ControladorUI(ControladorPrincipal* const controladorPrincipal);

	/**
	 * Destrutor.
	 */
	virtual ~ControladorUI();

	/**
	 * Exibir janela principal do sistema.
	 */
	void exibirFormPrincipal();

	/**
	 * Exibir janela de inserção de objetos.
	 */
	void exibirFormInsercaoObjeto();

	/**
	 * Exibir janela de transformação de objetos.
	 * @param nomeObjeto nome do objeto a ser transformado.
	 */
	void exibirFormTransformacaoObjeto(const String& nomeObjeto);

	/**
	 * Exibir mensagem de erro.
	 * @param mensagem mensagem de erro.
	 */
	void exibirMensagemErro(const String& mensagem, QWidget* pai = 0) const;

	/**
	 * Exibir mensagem de informação.
	 * @param mensagem mensagem de informação.
	 */
	void exibirMensagemInformacao(const String& mensagem, QWidget* pai = 0) const;

	/**
	 * Exibir mensagem de confirmação.
	 * @param mensagem mensagem de confirmação.
	 * @return true caso o usuário responda sim.
	 */
	bool requisitarConfirmacaoUsuario(const String& mensagem, QWidget* pai = 0) const;

	/**
	 * Navegar no mundo (mover a window).
	 * @param direcao direção de navegação.
	 * @param fator fator de navegação.
	 */
	void navegarNoMundo(const Mundo::Direcao direcao, const double fator);

	/**
	 * Definir o tipo de projeção da window.
	 * @param tipoProjecao tipo de projeção.
	 */
	void setProjetorVisualizacao(const Projetor::TipoProjecao& tipoProjecao);

	/**
	 * Redimensionar a window do mundo (aplicação de zoom).
	 * @param fator fator de escalonamento.
	 */
	void redimensionarWindow(const double fator);

	/**
	 * Rotacionar a visualização.
	 * @param angulo ângulo de rotação em graus.
	 * @param eixo eixo de rotação.
	 */
	void rotacionarWindow(const double angulo, const Mundo::Eixo& eixo);

	/**
	 * Escalonar objeto.
	 * @nome nome do objeto.
	 * @param sX fator de escalonamento da coordenada x.
	 * @param sY fator de escalonamento da coordenada y.
	 * @param sZ fator de escalonamento da coordenada z.
	 */
	void escalonarObjeto(const String& nome, const double sX, const double sY,
			const double sZ);

	/**
	 * Transladar objeto.
	 * @nome nome do objeto.
	 * @param sX fator de translação da coordenada x.
	 * @param sY fator de translação da coordenada y.
	 * @param sZ fator de translação da coordenada z.
	 */
	void transladarObjeto(const String& nome, const double sX, const double sY,
			const double sZ);

	/**
	 * Rotacionar objeto em relação a um ponto específico.
	 * @nome nome do objeto.
	 * @param ponto ponto de rotação.
	 * @param angulo ângulo de rotação em graus.
	 * @param eixo eixo de rotação.
	 */
	void rotacionarObjetoPorPonto(const String& nome, const Ponto& ponto,
			const double angulo, const Mundo::Eixo& eixo);

	/**
	 * Rotacionar objeto em relação ao centro geométrico.
	 * @nome nome do objeto.
	 * @param angulo ângulo de rotação em graus.
	 * @param eixo eixo de rotação.
	 */
	void rotacionarObjetoPeloCentro(const String& nome, const double angulo, const Mundo::Eixo& eixo);

	/**
	 * Inserir objeto geométrico.
	 * @param nome nome do objeto.
	 * @param pontos pontos do objeto.
	 * @param tipo tipo do objeto.
	 * @param cor cor do objeto.
	 */
	void inserirObjeto(const String& nome, const QList<Ponto> pontos,
			ObjetoGeometrico::Tipo tipo, const QColor& cor);

	/**
	 * Remover objeto geométrico.
	 * @param nome nome do objeto.
	 */
	void removerObjeto(const String& nome);

	/**
	 * Remover objetos do mundo.
	 */
	void removerObjetosMundo();

	/**
	 * Verificar se o mundo contém um objeto.
	 * @param nome nome do objeto.
	 * @return true se o objeto existe.
	 */
	bool contemObjeto(const String& nome);

	/**
	 * Importar cena de um arquivo OBJ (Wavefront).
	 * @param arquivo nome completo do arquivo.
	 * @throws ExcecaoArquivoInvalido caso o arquivo seja inválido.
	 * @throws ExcecaoLeituraArquivo caso não seja possível ler a cena do arquivo.
	 */
	void importarCena(const String& arquivo) throw(ExcecaoArquivoInvalido, ExcecaoLeituraArquivo);

	/**
	 * Exportar cena para um arquivo OBJ (Wavefront).
	 * @param arquivo nome completo do arquivo.
	 */
	void exportarCena(const String& arquivo);

	/**
	 * Reposicionar window, reestabelecendo as coordenadas iniciais.
	 */
	void reiniciarWindow();

	void atualizarCena(const QList<ObjetoGeometrico*>& objetos);

protected:
	ControladorPrincipal* controladorPrincipal;
	Mundo mundo;
	FormPrincipal* formPrincipal;
	FormInsercaoObjeto* objectInsertionWindow;
	ObjectTransformationWindow* objectTransformationWindow;

};

#endif /* CONTROLADORUI_H_ */
