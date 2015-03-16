//============================================================================
// Name        : leer_bicentenario.cpp
// Author      : judprog
// Version     :
// Copyright   : GenProg
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "fstream"
#include <string>
#include "mysql.h"
#include "algorithm"
#include "lib/lutilidades.h"
#include "lib/LCabecera.h"
#include "lib/LGrid.h"
#include "sstream"
#include "vector"
using namespace std;

int AfiliaBicentenario(MYSQL *mConexion, string nombre) {
	string rutaa = "./system/repository/txt/bicentenario/" + nombre;
	//string rutaa = nombre;
	ifstream archivo(rutaa.c_str());

	MYSQL_RES *result;
	MYSQL_ROW row;
	string cadenaTXT, credito, res, cad, coma, sQuery, tp = "";
	int i = 0, estado, pos1, pos2;
	getline(archivo, cadenaTXT);
	tp = cadenaTXT.substr(0, 13);
	if (tp == "1BICENTENARIO") {
		pos1 = 64;
		pos2 = 142;
		i = 0;
		coma = "";
		sQuery = "INSERT INTO t_afiliar_txt (credito_id,detalle) VALUES";
		while (!archivo.eof()) {
			getline(archivo, cadenaTXT);
			cad = cadenaTXT.substr(0, 1);
			if (cad == "2") {
				res = cadenaTXT.substr(pos2, 3);
				credito = cadenaTXT.substr(pos1, 16);
				if (i > 0) {
					coma = ",";
				}
				i++;
				sQuery += coma + "(" + credito + ",\"" + res + "\")";
			}
			//cout<<res<<"||"<<credito<<endl;
		}
		sQuery += " ON DUPLICATE KEY UPDATE detalle=VALUES(detalle);";
		//cout<<sQuery<<endl;
	} else {
		string sQuery = "DELETE FROM cpp_archivo WHERE nmbr=\"" + nombre+ "\";";
		estado = mysql_query(mConexion, sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(mConexion));
		}
		return 0;
	}
	estado = mysql_query(mConexion, sQuery.c_str());
	if (estado != 0) {
		printf(mysql_error(mConexion));
	}
	archivo.close();
	return 1;
}

int ProcesaBicentenario(MYSQL *mConexion, string nombre) {
	string rutaa = "./system/repository/txt/bicentenario/" + nombre;
	//string rutaa = nombre;
	ifstream archivo(rutaa.c_str());

	MYSQL_RES *result;
	MYSQL_ROW row;
	string cadenaTXT, auxTxt, ced, mto, mtodesc, cad, coma, sQuery,
			texto_inicio = "", aplicada = "", tp = "", credito;
	int band = 0, i = 0, estado, pos1, pos2, pos3, tam;

	getline(archivo, cadenaTXT);
	tp = cadenaTXT.substr(0, 1);
	//cout<<tp<<endl;
	if (tp != "1") {
		texto_inicio = cadenaTXT.substr(0, 13);
		if (texto_inicio == "Bicentenario,"
				|| texto_inicio == "Bicentenario ") {
			if (texto_inicio == "Bicentenario,") {
				aplicada = "CUENTAS APLICADAS";
				pos1 = 36;
				pos2 = 74;
				tam = 17;
			}
			if (texto_inicio == "Bicentenario ") {
				aplicada = "*** Cuentas Aplicadas ***";
				pos1 = 38;
				pos2 = 80;
				tam = 25;
			}
		} else {
			string sQuery = "DELETE FROM cpp_archivo WHERE nmbr=\"" + nombre+ "\";";
			estado = mysql_query(mConexion, sQuery.c_str());
			if (estado != 0) {
				printf(mysql_error(mConexion));
			}
			return 0;
		}

		i = 0;
		coma = "";
		sQuery = "INSERT INTO t_cargar_txt (cedula,monto,archivo) VALUES";
		while (!archivo.eof()) {
			getline(archivo, cadenaTXT);
			auxTxt = cadenaTXT.substr(0, 4);
			if (cadenaTXT.substr(0, tam) == aplicada) {
				band = 1;
			}
			if (auxTxt == "0175") {
				if (i > 0) {
					coma = ",";
				}
				i++;
				mto = cadenaTXT.substr(pos1, 7);
				ced = cadenaTXT.substr(pos2, 9);
				replace(mto.begin(), mto.end(), ',', '.');
				if (band != 1) {
					mto = "0.00";
				}
				sQuery += coma + "(" + ced + "," + mto + ",\"" + nombre + "\")";
			}
		}
		sQuery += ";";
	} else {
		pos1 = 157;
		pos2 = 43;
		pos3 = 68;
		i = 0;
		coma = "";
		sQuery = "INSERT INTO t_cargar_txt (cedula,monto,archivo,credito_id) VALUES";
		while (!archivo.eof()) {
			getline(archivo, cadenaTXT);
			auxTxt = cadenaTXT.substr(0, 1);
			//cout<<"*"<<auxTxt<<"//"<<cadenaTXT.length()<<endl;
			if(cadenaTXT.length() == 0){
				break;
			}
			if (auxTxt == "2" && cadenaTXT.length() >0) {
				cad = cadenaTXT.substr(pos1, 3);
				credito = cadenaTXT.substr(pos2, 16);
				//cout<<"**"<<credito<<"//"<<cad<<endl;
				if (i > 0) {
					coma = ",";
				}
				i++;
				mto = cadenaTXT.substr(pos3, 15);
				mtodesc = cadenaTXT.substr(83, 2);
				ced = cadenaTXT.substr(2, 10);
				mto += "." + mtodesc;
				if (cad != "074") {
					mto = "0.00";
				}
				sQuery += coma + "(" + ced + "," + mto + ",\"" + nombre + "\","	+ credito + ")";

			} else {
				string sQuery = "DELETE FROM cpp_archivo WHERE nmbr=\"" + nombre+ "\";";
				estado = mysql_query(mConexion, sQuery.c_str());
				if (estado != 0) {
					printf(mysql_error(mConexion));
				}
				return 2;
			}

			//cout<<res<<"||"<<credito<<endl;
		}
		sQuery += ";";

	}
	estado = mysql_query(mConexion, sQuery.c_str());
	if (estado != 0) {
		printf(mysql_error(mConexion));
	}
	archivo.close();
	return 1;
}

int ProcesaProvincial(MYSQL *mConexion, string nombre) {
	string rutaa = "./system/repository/txt/provincial/" + nombre;
	ifstream archivo(rutaa.c_str());
	MYSQL_RES *result;
	MYSQL_ROW row;
	string cadenaTXT, auxTxt, ced, mto, cad, coma, sQuery, texto_inicio = "",
			aplicada = "";
	int band = 0, i = 0, j = 0, estado, pos1, pos2, tam;

	getline(archivo, cadenaTXT);
	texto_inicio = cadenaTXT.substr(4, 10);
	if (texto_inicio != "J298378468" && texto_inicio != "J312074191") {
		string sQuery = "DELETE FROM cpp_archivo WHERE nmbr=\"" + nombre
				+ "\";";
		estado = mysql_query(mConexion, sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(mConexion));
		}
		return 0;
	}

	coma = "";
	sQuery = "INSERT INTO t_cargar_txt (cedula,monto,archivo) VALUES";
	while (!archivo.eof()) {
		getline(archivo, cadenaTXT);
		if (i == 0) {
			auxTxt = cadenaTXT.substr(30, 3);
			i++;
			if (auxTxt == "001") {
				if (j > 0)
					coma = ",";
				j++;
				ced = cadenaTXT.substr(16, 9);
				mto = cadenaTXT.substr(62, 4);
				mto += "." + cadenaTXT.substr(66, 2);
				if (cadenaTXT.substr(77, 1) == "1")
					mto = "0.00";
				sQuery += coma + "(" + ced + "," + mto + ",\"" + nombre + "\")";
			}
		} else {
			i = 0;
		}
	}
	sQuery += ";";
	estado = mysql_query(mConexion, sQuery.c_str());
	if (estado != 0) {
		printf(mysql_error(mConexion));
	}
	archivo.close();
	return 1;
}

int ProcesaBfc(MYSQL *mConexion, string nombre) {
	string rutaa = "./system/repository/txt/bfc/" + nombre;
	ifstream archivo(rutaa.c_str());
	MYSQL_RES *result;
	MYSQL_ROW row;
	string cadenaTXT, auxTxt, ced, mto, cad, coma, sQuery, texto_inicio = "",
			aplicada = "";
	int band = 0, i = 0, j = 0, estado, pos1, pos2, tam;

	getline(archivo, cadenaTXT);
	texto_inicio = cadenaTXT.substr(61, 24);
	if (texto_inicio != "CC0001510138528138022782") {
		string sQuery = "DELETE FROM cpp_archivo WHERE nmbr=\"" + nombre
				+ "\";";
		estado = mysql_query(mConexion, sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(mConexion));
		}
		return 0;
	}

	coma = "";
	sQuery = "INSERT INTO t_cargar_txt (cedula,monto,archivo) VALUES";
	while (!archivo.eof()) {
		getline(archivo, cadenaTXT);
		if (cadenaTXT.substr(0, 1) != "") {
			auxTxt = cadenaTXT.substr(77, 5);
			if (auxTxt == "ABONO") {
				if (j > 0)
					coma = ",";
				j++;
				ced = cadenaTXT.substr(30, 10);
				mto = cadenaTXT.substr(70, 3);
				mto += "." + cadenaTXT.substr(73, 2);
				if (cadenaTXT.substr(117, 4) != "0000")
					mto = "0.00";
				sQuery += coma + "(" + ced + "," + mto + ",\"" + nombre + "\")";
			}
		}

	}
	sQuery += ";";
	estado = mysql_query(mConexion, sQuery.c_str());
	if (estado != 0) {
		printf(mysql_error(mConexion));
	}
	archivo.close();
	cout << sQuery;
	return 1;
}

int main(int argc, char *argv[]) {
	MYSQL *mConexion = mysql_init(NULL), mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	LUtilidades util;
	/**
	 * contruir grid c++
	 */
	//LGrid Grid;
	//LCabecera cabecera;
	//DatosCuerpo cuerpo;
	//VecString fcuerpo(5);
	int estado, resp;
	string json, nombre = argv[1], enlace, comp = "0", banco = argv[2],
			tipo_archivo = argv[3], msj = "";
	mysql_init(&mysql);
	mConexion = mysql_real_connect(&mysql, "localhost", "root", "za63qj2p","electron", 0, 0, 0);
	if (mConexion == NULL) {
		printf(mysql_error(&mysql));
		return 1;
	}
	/**
	 * contruir grid c++
	 //LCabecera(titulo,atributos,tipo,funcion,parametro,ruta,metodo,oculto,total,buscar,mantiene)
	 //cabecera.Construir("cedula","width:50px;");
	 cabecera.setTitulo("Cedula");
	 cabecera.setAtributo("width:50px");
	 cabecera.Agregar();

	 cabecera.Construir("Datos Basicos", "width:250px;");
	 //cabecera.setTitulo("Datos Basicos");
	 //cabecera.setAtributo("width:250px");
	 cabecera.Agregar();

	 //cabecera.Construir("Monto","width:150px","","","","","","","1");
	 cabecera.setTitulo("Monto");
	 cabecera.setAtributo("width:150px");
	 cabecera.setTotal("1");
	 cabecera.Agregar();

	 //cabecera.Construir("Fecha","width:250px;");
	 cabecera.setTitulo("Fecha");
	 cabecera.setAtributo("width:200px");
	 cabecera.Agregar();

	 //cabecera.Construir("Cargar","width:20px","enlace","funcion","1,2","","1");
	 cabecera.setTitulo("#");
	 cabecera.setAtributo("width:20px");
	 cabecera.setTipo("checkbox");
	 cabecera.setFuncion("cargar_cuota");
	 cabecera.Agregar();
	 */

	/*string sQuery = "DELETE FROM t_cargar_txt WHERE archivo=\""+ argv[1] +"\";";
	 estado = mysql_query(mConexion, sQuery.c_str());
	 if (estado != 0) {
	 printf(mysql_error(mConexion));
	 }*/

	string sQuery = "SET NAMES \"utf8\";";
	estado = mysql_query(mConexion, sQuery.c_str());
	if (estado != 0) {
		printf(mysql_error(mConexion));
	}
	if (banco == "bicentenario") {
		if (tipo_archivo == "a") {
			resp = AfiliaBicentenario(mConexion, nombre);
		} else {
			resp = ProcesaBicentenario(mConexion, nombre);
		}
		if (resp == 0) {
			msj =
					"FORMATO DE ARCHIVO NO COINCIDE CON NINGUN FORMATO DEL BANCO BICENTENARIO.";
		}
		if (resp == 2) {
			msj =
				"FORMATO DE ARCHIVO NO COINCIDE CON NINGUN FORMATO DEL BANCO BICENTENARIO NUEVO.";
		}
	}
	if (banco == "provincial") {
		resp = ProcesaProvincial(mConexion, nombre);
		if (resp == 0) {
			msj =
					"FORMATO DE ARCHIVO NO COINCIDE CON NINGUN FORMATO DEL BANCO PROVINCIAL.";
		}
	}
	if (banco == "bfc") {
		resp = ProcesaBfc(mConexion, nombre);
		if (resp == 0) {
			msj =
					"FORMATO DE ARCHIVO NO COINCIDE CON NINGUN FORMATO DEL BANCO BFC.";
		}
	}

	if (msj != "") {
		cout << "{\"Error\":\"" + msj + "\"}";
		return 0;
	}
	//agrupar los montos por cedula
	if (tipo_archivo != "a") {
		sQuery =
				"SELECT cedula,SUM(monto),CONCAT(primer_nombre,\" \",segundo_nombre,\" \",primer_apellido,\" \",segundo_apellido)as nombre, "
						"cpp_archivo.crea,procesada "
						"FROM t_cargar_txt "
						"JOIN t_personas ON t_personas.documento_id=t_cargar_txt.cedula "
						"JOIN cpp_archivo ON cpp_archivo.nmbr = t_cargar_txt.archivo "
						"WHERE archivo=\"" + nombre + "\" GROUP BY cedula";
		//cout <<  endl << sQuery;
		estado = mysql_query(mConexion, sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(mConexion));
		}
		double dSuma = 0;
		stringstream sSuma;

		result = mysql_store_result(mConexion);
		while ((row = mysql_fetch_row(result))) {
			/*fcuerpo[0] = row[0];
			 fcuerpo[1] = row[2];
			 fcuerpo[2] = row[1];
			 fcuerpo[3] = row[3];
			 fcuerpo[4] = "";
			 cuerpo.push_back(fcuerpo);*/
			dSuma += atof(row[1]);
		}
		mysql_free_result(result);
		mysql_close(mConexion);
		//json = Grid.Generar_Json(cabecera, cuerpo, "json", "50", "1", "");
		sSuma << dSuma;
		//cout << json;
		cout
				<< "{\"Msj\":\"ARCHIVO DEL BANCO " + nombre
						+ " PROCESADO CON EXITO POR UN MONTO DE:  "
						+ sSuma.str() + " .\"}";
	} else {
		cout << "{\"Msj\":\"ARCHIVO " + nombre + " AFILIADO CON EXITO\"}";
	}

	return 0;
}

