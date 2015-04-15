#include "geometria/CurvaBSpline.h"
#include <iostream>
CurvaBSpline::CurvaBSpline() :
		ObjetoGeometrico() {
	this->pontosParametricosRedefinidos = false;
}

CurvaBSpline::CurvaBSpline(const CurvaBSpline& curva) :
		ObjetoGeometrico(curva) {
	for (int i = 0; i < curva.pontos.size(); i++)
		this->pontos.insert(i, curva.pontos.at(i));
	this->pontosParametricos = curva.pontosParametricos;
	this->pontosParametricosRedefinidos = curva.pontosParametricosRedefinidos;
}

CurvaBSpline::CurvaBSpline(const String& nome, const QList<Ponto>& pontos,
		const QColor& cor) :
		ObjetoGeometrico(nome, Tipo::CURVA_BSPLINE, cor) {
	for (int i = 0; i < pontos.size(); i++)
		this->pontos.insert(i, pontos.at(i));
	this->pontosParametricos = this->calcularPontosParametricos();
	this->pontosParametricosRedefinidos = false;
}

CurvaBSpline::~CurvaBSpline() {}

CurvaBSpline& CurvaBSpline::operator=(const CurvaBSpline& curva) {
	this->ObjetoGeometrico::operator =(curva);
	this->pontos.clear();
	for (int i = 0; i < curva.pontos.size(); i++)
		this->pontos.insert(i, curva.pontos.at(i));
	this->pontosParametricos = curva.pontosParametricos;
	this->pontosParametricosRedefinidos = curva.pontosParametricosRedefinidos;
	return *this;
}

ObjetoGeometrico* CurvaBSpline::clonar() const {
	return new CurvaBSpline(*this);
}

QList<Ponto> CurvaBSpline::getPontos() const {
	if (!this->pontosParametricosRedefinidos)
		return this->calcularPontosParametricos();
	std::cout << this->pontosParametricos.size() << std::endl;
	return this->pontosParametricos;
}

QList<Ponto*> CurvaBSpline::getPontosObjeto() {
	QList<Ponto*> lista;

	for (int i = 0; i < this->pontos.size(); i++)
		lista.insert(i, (Ponto*) &this->pontos.at(i));

	return lista;
}

const String CurvaBSpline::toString() const {
	String retorno = "[" + this->pontos.at(0).toString();
	for (int i = 1; i < this->pontos.size(); i++) {
		retorno += ", " + this->pontos.at(i).toString();
	}
	retorno += "]";
	return retorno;
}

void CurvaBSpline::setPontosParametricos(const QList<Ponto>& pontos) {
	this->pontosParametricos = pontos;
	this->pontosParametricosRedefinidos = true;
}

QList<Ponto> CurvaBSpline::calcularPontosParametricos(const double t) const {
	QList<Ponto> pontos;
	int tam = this->pontos.size();

	// Calcular os pontos do segmento Qm (m-3 ... m)
	for (int m = 3; m < tam; m++) {
		Ponto p[4] = { this->pontos.at(m-3), this->pontos.at(m-2),
					   this->pontos.at(m-1), this->pontos.at(m) };
		QList<Ponto> novosPontos =
				this->calcularPontosParametricosIntermediario(p, t, 10);
		for (int i = 0; i < novosPontos.size(); i++)
			pontos.insert(pontos.size(), novosPontos.at(i));
	}

//	*** NÃO ENTENDI O PQ DISSO ***

//	//pega os últimos 4 pontos para calcular a parte final da reta
//
//	Ponto p[4] = { this->pontos.at(tam - 4), this->pontos.at(tam - 3),
//			this->pontos.at(tam - 2), this->pontos.at(tam - 1) };
//	QList<Ponto> novosPontos = this->calcularPontosParametricosIntermediario(p,
//			t, 3);
//	for (int j = 0; j < novosPontos.size(); j++) {
//		pontos.insert(pontos.size(), novosPontos.at(j));
//	}

	return pontos;
}

QList<Ponto> CurvaBSpline::calcularPontosParametricosIntermediario(Ponto *p,
		const double t, int n) const {
	double matriz[4][4] = { { 0, 2/3, -1, 1 },
							{ 0, -1/3, 0, 1 },
							{ 0, 2/3, 1, 1 },
							{ 6, 11/3, 2, 1 } };
	double x[4] = { p[0].getX(), p[1].getX(), p[2].getX(), p[3].getX() };
	double y[4] = { p[0].getY(), p[1].getY(), p[2].getY(), p[3].getY() };
	double z[4] = { p[0].getZ(), p[1].getZ(), p[2].getZ(), p[3].getZ() };
	double ax = matriz[0][0] * x[0] + matriz[0][1] * x[1] + matriz[0][2] * x[2]
			+ matriz[0][3] * x[3];
	double ay = matriz[0][0] * y[0] + matriz[0][1] * y[1] + matriz[0][2] * y[2]
			+ matriz[0][3] * y[3];
	double az = matriz[0][0] * z[0] + matriz[0][1] * z[1] + matriz[0][2] * z[2]
			+ matriz[0][3] * z[3];
	double bx = matriz[1][0] * x[0] + matriz[1][1] * x[1] + matriz[1][2] * x[2]
			+ matriz[1][3] * x[3];
	double by = matriz[1][0] * y[0] + matriz[1][1] * y[1] + matriz[1][2] * y[2]
			+ matriz[1][3] * y[3];
	double bz = matriz[1][0] * z[0] + matriz[1][1] * z[1] + matriz[1][2] * z[2]
			+ matriz[1][3] * z[3];
	double cx = matriz[2][0] * x[0] + matriz[2][1] * x[1] + matriz[2][2] * x[2]
			+ matriz[2][3] * x[3];
	double cy = matriz[2][0] * y[0] + matriz[2][1] * y[1] + matriz[2][2] * y[2]
			+ matriz[2][3] * y[3];
	double cz = matriz[2][0] * z[0] + matriz[2][1] * z[1] + matriz[2][2] * z[2]
			+ matriz[2][3] * z[3];
	double dx = matriz[3][0] * x[0] + matriz[3][1] * x[1] + matriz[3][2] * x[2]
			+ matriz[3][3] * x[3];
	double dy = matriz[3][0] * y[0] + matriz[3][1] * y[1] + matriz[3][2] * y[2]
			+ matriz[3][3] * y[3];
	double dz = matriz[3][0] * z[0] + matriz[3][1] * z[1] + matriz[3][2] * z[2]
			+ matriz[3][3] * z[3];
	double matriz2[3][4] = { { pow(t, 3), pow(t, 2), t, 0 }, { 6 * pow(t, 3), 2
			* pow(t, 2), 0, 0 }, { 6 * pow(t, 3), 0, 0, 0 } };
	double deltaX = matriz2[0][0] * ax + matriz2[0][1] * bx + matriz2[0][2] * cx
			+ matriz2[0][3] * dx;
	double delta2X = matriz2[1][0] * ax + matriz2[1][1] * bx
			+ matriz2[1][2] * cx + matriz2[1][3] * dx;
	double delta3X = matriz2[2][0] * ax + matriz2[2][1] * bx
			+ matriz2[2][2] * cx + matriz2[2][3] * dx;
	double deltaY = matriz2[0][0] * ay + matriz2[0][1] * by + matriz2[0][2] * cy
			+ matriz2[0][3] * dy;
	double delta2Y = matriz2[1][0] * ay + matriz2[1][1] * by
			+ matriz2[1][2] * cy + matriz2[1][3] * dy;
	double delta3Y = matriz2[2][0] * ay + matriz2[2][1] * by
			+ matriz2[2][2] * cy + matriz2[2][3] * dy;
	double deltaZ = matriz2[0][0] * az + matriz2[0][1] * bz + matriz2[0][2] * cz
			+ matriz2[0][3] * dz;
	double delta2Z = matriz2[1][0] * az + matriz2[1][1] * bz
			+ matriz2[1][2] * cz + matriz2[1][3] * dz;
	double delta3Z = matriz2[2][0] * az + matriz2[2][1] * bz
			+ matriz2[2][2] * cz + matriz2[2][3] * dz;
	QList<Ponto> pontos;
	pontos.insert(0, p[0]);
	while (x[0] < p[n].getX()) {
		x[0] += deltaX;
		deltaX += delta2X;
		delta2X += delta3X;
		y[0] += deltaY;
		deltaY += delta2Y;
		delta2Y += delta3Y;
		z[0] += deltaZ;
		deltaZ += delta2Z;
		delta2Z += delta3Z;
		pontos.insert(pontos.size(), Ponto("", x[0], y[0], z[0]));
	}
	return this->pontos;
}
