/*
 * LCabecera.h
 *
 *  Created on: 25/04/2013
 *      Author: linuxone
 */

#ifndef LCABECERA_H_
#define LCABECERA_H_

/*
 * Herramientas de asignacion y construccion de cabezeras para objetos tgrid
 *
 * Creada Por: Judelvis Rivas
 * Fecha : 25/04/2013
 *
 */

class LCabecera {
	struct elementos {
		string titulo;
		string atributos;
		string tipo;
		string funcion;
		string parametro;
		string ruta;
		string metodo;
		string oculto;
		string total;
		string buscar;
		string mantiene;
	};

	elementos celda;

public:
	vector<elementos> arreglo;
	/**
	 * Contructor
	 */
	LCabecera() {
		this->celda.atributos = "";
		this->celda.buscar = "";
		this->celda.funcion = "";
		this->celda.mantiene = "";
		this->celda.metodo = "";
		this->celda.oculto = "";
		this->celda.parametro = "";
		this->celda.ruta = "";
		this->celda.tipo = "";
		this->celda.titulo = "";
		this->celda.total = "";
	}
	//LCabecera(titulo,atributos,tipo,funcion,parametro,ruta,metodo,oculto,total,buscar,mantiene)
	void Construir(string titulo = "", string atributos = "", string tipo = "",
			string funcion = "", string parametro = "", string ruta = "",
			string metodo = "", string oculto = "", string total = "",
			string buscar = "", string mantiene = "") {
		this->celda.atributos = atributos;
		this->celda.buscar = buscar;
		this->celda.funcion = funcion;
		this->celda.mantiene = mantiene;
		this->celda.metodo = metodo;
		this->celda.oculto = oculto;
		this->celda.parametro = parametro;
		this->celda.ruta = ruta;
		this->celda.tipo = tipo;
		this->celda.titulo = titulo;
		this->celda.total = total;
	}

	void Clear() {
		this->celda.atributos = "";
		this->celda.buscar = "";
		this->celda.funcion = "";
		this->celda.mantiene = "";
		this->celda.metodo = "";
		this->celda.oculto = "";
		this->celda.parametro = "";
		this->celda.ruta = "";
		this->celda.tipo = "";
		this->celda.titulo = "";
		this->celda.total = "";
	}

	/**
	 * METODOS GET Y SET DE ATRIBUTOS DE LA CLASE
	 */
	void setAtributo(string at) {
		this->celda.atributos = at;
	}
	string getAtributo() {
		return this->celda.atributos;
	}

	void setBuscar(string b) {
		this->celda.buscar = b;
	}
	string getBuscar() {
		return this->celda.buscar;
	}

	void setFuncion(string fn) {
		this->celda.funcion = fn;
	}
	string getFuncion() {
		return this->celda.funcion;
	}

	void setMantiene(string mn) {
		this->celda.mantiene = mn;
	}
	string getMantiene() {
		return this->celda.mantiene;
	}

	void setMetodo(string mt) {
		this->celda.metodo = mt;
	}
	string getMetodo() {
		return this->celda.metodo;
	}

	void setOculto(string oc) {
		this->celda.oculto = oc;
	}
	string getOculto() {
		return this->celda.oculto;
	}

	void setParametro(string pr) {
		this->celda.parametro = pr;
	}
	string getParametro() {
		return this->celda.parametro;
	}

	void setRuta(string rt) {
		this->celda.ruta = rt;
	}
	string getRuta() {
		return this->celda.ruta;
	}

	void setTipo(string tp) {
		this->celda.tipo = tp;
	}
	string getTipo() {
		return this->celda.tipo;
	}

	void setTitulo(string tt) {
		this->celda.titulo = tt;
	}
	string getTitulo() {
		return this->celda.titulo;
	}

	void setTotal(string to) {
		this->celda.total = to;
	}
	string getTotal() {
		return this->celda.total;
	}

	void Agregar() {
		this->arreglo.push_back(this->celda);
		this->Clear();
	}

	void Generar() {
		int i = 0;
		for (i = 0; i < this->arreglo.size(); i++) {
			cout << "*************************" << endl;
			if (this->arreglo[i].atributos != "")
				cout << "Atributo:" << this->arreglo[i].atributos << endl;
			if (this->arreglo[i].buscar != "")
				cout << "Buscar:" << this->arreglo[i].buscar;
			if (this->arreglo[i].funcion != "")
				cout << "Funcion:" << this->arreglo[i].funcion << endl;
			if (this->arreglo[i].mantiene != "")
				cout << "Mantiene:" << this->arreglo[i].mantiene;
			if (this->arreglo[i].metodo != "")
				cout << "Metodo:" << this->arreglo[i].metodo;
			if (this->arreglo[i].oculto != "")
				cout << "Oculto:" << this->arreglo[i].oculto;
			if (this->arreglo[i].parametro != "")
				cout << "Parametro:" << this->arreglo[i].parametro << endl;
			if (this->arreglo[i].ruta != "")
				cout << "Ruta:" << this->arreglo[i].ruta << endl;
			if (this->arreglo[i].tipo != "")
				cout << "Tipo:" << this->arreglo[i].tipo << endl;
			if (this->arreglo[i].titulo != "")
				cout << "Titulo:" << this->arreglo[i].titulo << endl;
			cout << "*************************" << endl;
		}
	}

};

#endif /* LCABECERA_H_ */
