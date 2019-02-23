package br.acad.fa4.jdbc;
/**
 * ConnectionFactory - Fábrica de Conexões com o Banco
 * @date 29/11/2015
 */

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionFactory {
	public static Connection getConnection() throws SQLException {
		try {
			Class.forName("com.mysql.jdbc.Driver");
			return DriverManager.getConnection("jdbc:mysql://localhost/pjGerencia","root","admin");
		} catch (ClassNotFoundException e) {
			throw new SQLException(e.getMessage());
		}				
	}
}