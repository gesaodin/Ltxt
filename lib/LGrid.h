/*
 * LGrid.h
 *
 *  Created on: 26/04/2013
 *      Author: linuxone
 */

#ifndef LGRID_H_
#define LGRID_H_
#include "sstream"
typedef vector<VecString> DatosCuerpo;

class LGrid {
	struct elementos{
		LCabecera cabecera;
		DatosCuerpo cuerpo;
		string origen;
		string paginador;
		string editable;
		string parametros;
		string objetos;
	};
	elementos tabla;
	string json;

public:

	/**
	 * Contructor
	 */
	LGrid() {

	}

	void Clear() {

	}

	/**
	 * METODOS GET Y SET DE ATRIBUTOS DE LA CLASE
	 */
	void setCabecera(LCabecera cb){this->tabla.cabecera = cb;}
	LCabecera getCabecera(){return this->tabla.cabecera;}

	void setCuerpo(DatosCuerpo cu){this->tabla.cuerpo = cu;}
	DatosCuerpo getCuerpo(){return this->tabla.cuerpo;}

	void setOrigen(string ori){this->tabla.origen = ori;}
	string getOrigen(){return this->tabla.origen;}

	void setPag(string pg){this->tabla.paginador = pg;}
	string getPag(){return this->tabla.paginador;}

	void setEdit(string ed){this->tabla.editable = ed;}
	string getEdit(){return this->tabla.editable;}

	void setParametros(string pr){this->tabla.parametros = pr;}
	string getParametros(){return this->tabla.parametros;}

	string Generar_Json(LCabecera cb,DatosCuerpo cp, string origen, string pg="",string edit="",string parametros = ""){
		string cadena,aux,coma="",coma2="",pos1,pos2;
		cadena = "{\"Cabezera\":{";
		int i,j ;
		/**
		 * Construye cabezera del tgrid
		 * Lee objero TCabecera
		 */
		for(i=0;i < cb.arreglo.size();i++){
			stringstream convertido;
			convertido << i+1;
			aux = convertido.str();
			if(i>0){coma=",";}
			cadena += coma + "\""+ aux +"\":{";
			if(cb.arreglo[i].atributos != "") cadena += "\"atributos\":\"" + cb.arreglo[i].atributos + "\",";
			if(cb.arreglo[i].buscar != "") cadena += "\"buscar\":" + cb.arreglo[i].buscar + ",";
			if(cb.arreglo[i].funcion != "") cadena += "\"funcion\":\"" + cb.arreglo[i].funcion + "\",";
			if(cb.arreglo[i].mantiene != "") cadena += "\"mantiene\":" + cb.arreglo[i].mantiene + ",";
			if(cb.arreglo[i].metodo != "") cadena += "\"metodo\":" + cb.arreglo[i].metodo + ",";
			if(cb.arreglo[i].oculto != "") cadena += "\"oculto\":" + cb.arreglo[i].oculto + ",";
			if(cb.arreglo[i].parametro != "") cadena += "\"parametro\":\"" + cb.arreglo[i].parametro + "\",";
			if(cb.arreglo[i].ruta != "") cadena += "\"ruta\":\"" + cb.arreglo[i].ruta + "\",";
			if(cb.arreglo[i].tipo != "") cadena += "\"tipo\":\"" + cb.arreglo[i].tipo + "\",";
			if(cb.arreglo[i].titulo != "") cadena += "\"titulo\":\"" + cb.arreglo[i].titulo + "\",";
			if(cb.arreglo[i].total != "") cadena += "\"total\":" + cb.arreglo[i].total + ",";
			cadena += "\"fin\":\""+aux+"\"}";

		}
		cadena += "},\"Cuerpo\":{";
		/**
		 * Construye Cuerpo Del Tgrid
		 * Lee Objeto Datos Cuerpo
		 */
		coma="";
		for(i=0 ; i < cp.size() ; i++){
			stringstream convertido;
			convertido << i+1;
			pos1 = convertido.str();
			if(i > 0){coma = ",";}
			cadena += coma + "\""+ pos1 +"\":{";
			coma2="";
			for(j=0 ; j < cp[i].size() ; j++){
				stringstream convertido2;
				convertido2 << j+1;
				pos2 = convertido2.str();
				if(j > 0){coma2 = ",";}
				cadena += coma2+ "\""+ pos2 +"\":\""+ cp[i][j] +"\"";
			}
			cadena += "}";
		}
		cadena += "},\"Paginador\":"+ pg +",\"Origen\":\""+ origen +"\",\"Editable\":\""+ edit +"\",\"Parametros\":\""+ parametros +"\"}";

		return cadena;
	}

};


#endif /* LGRID_H_ */
