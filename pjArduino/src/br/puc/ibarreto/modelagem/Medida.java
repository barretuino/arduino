package br.puc.ibarreto.modelagem;
/**
 * Projeto de Gerência
 * Disciplina: 21845- SISTEMAS INFORMAÇÃO GERÊNCIA TELECOMUNICAÇÕES
 * Modelagem Conceitual de Medida
 * @autor Paulo C. Barreto / Luiz R. Barreto
 * @date 26/05/2012
 */

import java.util.GregorianCalendar;


public class Medida {
	private float corrente;
	private GregorianCalendar data;
	
	public Medida(){
		
	}

	public float getCorrente() {
		return corrente;
	}

	public void setCorrente(float corrente) {
		this.corrente = corrente;
	}

	public GregorianCalendar getData() {
		return data;
	}

	public void setData(GregorianCalendar data) {
		this.data = data;
	}
}
