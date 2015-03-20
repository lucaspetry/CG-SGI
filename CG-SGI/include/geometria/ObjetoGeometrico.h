#ifndef OBJETOGEOMETRICO_H_
#define OBJETOGEOMETRICO_H_

#include <QtCore/qlist.h>
#include <cmath>
#include <string>

typedef std::string String;

class Ponto;

/**
 * Objeto Geométrico.
 */
class ObjetoGeometrico {

public:
	/**
	 * Tipos de objetos geométricos
	 */
	enum Tipo {
		POLIGONO,
		PONTO,
		RETA,
		WINDOW
	};

	/**
	 * Construtor.
	 */
	ObjetoGeometrico();

	/**
	 * Construtor.
	 * @param objeto objeto a ser copiado.
	 */
	ObjetoGeometrico(const ObjetoGeometrico& objeto);

	/**
	 * Construtor.
	 * @param nome nome do objeto.
	 * @param tipo tipo do objeto.
	 */
	ObjetoGeometrico(const String& nome, const Tipo tipo);

	/**
	 * Destrutor.
	 */
	virtual ~ObjetoGeometrico();

	/**
	 * Operador de atribuição.
	 * @param objeto objeto a ser copiado.
	 * @return objeto geométrico copiado.
	 */
	ObjetoGeometrico& operator=(const ObjetoGeometrico& objeto);

	/**
	 * Obter os pontos do objeto.
	 * @return lista de pontos.
	 */
	virtual QList<Ponto*> getPontos();

	/**
	 * Converter o objeto em string.
	 * @return string representando o objeto.
	 */
	virtual const String toString() const;

	/**
	 * Obter o nome.
	 * @return nome do objeto.
	 */
	const String& getNome() const;

	/**
	 * Obter o tipo.
	 * @return tipo do objeto.
	 */
	Tipo getTipo() const;

	/**
	 * Obter o tipo.
	 * @return tipo do objeto.
	 */
	const String getTipoString() const;

	/**
	 * Obter o centro geométrico do objeto.
	 * @return o ponto correspondento ao centro.
	 */
	const Ponto getCentroGeometrico();

	/**
	 * Operador de stream de saída.
	 * @param out stream de saída.
	 * @param o objeto geométrico.
	 * @return o stream de saída.
	 */
	friend std::ostream& operator<<(std::ostream& out, const ObjetoGeometrico& o){
		return out << o.toString();
	}

	/**
	 * Transladar o objeto.
	 * @param x fator de translação do eixo x.
	 * @param y fator de translação do eixo y.
	 * @param z fator de translação do eixo z.
	 */
	void transladar(const double x, const double y, const double z);

	/**
	 * Escalonar o objeto.
	 * @param x fator de escalonamento do eixo x.
	 * @param y fator de escalonamento do eixo y.
	 * @param z fator de escalonamento do eixo z.
	 */
	void escalonar(const double x, const double y, const double z);

	/**
	 * Rotacionar em relação a um ponto específico.
	 * @param ponto ponto de rotação.
	 * @param angulo ângulo de rotação em graus.
	 */
	void rotacionarPorPonto(const Ponto& ponto, const double angulo);

	/**
	 * Rotacionar em relação ao centro geométrico.
	 * @param angulo ângulo de rotação em graus.
	 */
	void rotacionarPeloCentro(const double angulo);

protected:
	/**
	 * Aplicar uma transformação ao objeto.
	 * @param matriz matriz de transformação.
	 */
	void aplicarTransformacao(const double matriz[4][4]);

	String nome;
	Tipo tipo;

};

#endif /* OBJETOGEOMETRICO_H_ */
