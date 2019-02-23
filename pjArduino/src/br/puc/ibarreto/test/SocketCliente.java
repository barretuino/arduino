package br.puc.ibarreto.test;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class SocketCliente {

	public static void main(String[] args) throws IOException{
		Socket client = new Socket("192.168.1.201", 80);      /*criando uma conecxao para o servidor localizado
		 * em 192.169.1.201 porta 80
		 */


		//Cria um canal para receber dados.
		DataInputStream in=new DataInputStream(client.getInputStream());
		//Cria um canal para enviar dados.
		DataOutputStream out=new DataOutputStream(client.getOutputStream());

		out.writeBytes("OI");       //enviando uma string

		String s = in.readUTF(); //Aguarda o recebimento de uma string.

		out.writeBytes("Obrigado!");      //enviando uma string

		System.out.println(s);      //imprimendo a string recebida

		//Fecha os canais de entrada e saída.
		in.close();
		out.close();
		//Fecha o socket.
		client.close();


	}

}
