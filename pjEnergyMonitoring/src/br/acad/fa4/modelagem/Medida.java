package br.acad.fa4.modelagem;

/**
 * Classe de Modelagem Conceitual da Medida
 * @date 29/11/2015
 */

import java.util.GregorianCalendar;

public class Medida {
	private float valor;
	private GregorianCalendar data;
	
	public Medida(){
		
	}

	public float getValor() {
		return valor;
	}

	public void setValor(float valor) {
		this.valor = valor;
	}

	public GregorianCalendar getData() {
		return data;
	}

	public void setData(GregorianCalendar data) {
		this.data = data;
	}
}