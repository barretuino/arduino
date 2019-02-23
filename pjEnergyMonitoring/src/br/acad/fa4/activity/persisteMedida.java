package br.acad.fa4.activity;

import java.io.IOException;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import br.acad.fa4.dao.MedidaDAO;
import br.acad.fa4.modelagem.Medida;

/**
 * Servlet implementation class persisteMedida
 * @date 29/11/2015
 */

@WebServlet("/persisteMedida")
public class persisteMedida extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private Medida medida;
	private MedidaDAO dao;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public persisteMedida() {
        super();
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.getWriter().append("Servidor de aplicação: ").append(request.getContextPath());
		doPost(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        medida = new Medida();
        
        if (!request.getParameter("medida").equals(""))
			medida.setValor(Float.parseFloat(request.getParameter("medida")));
              
        try {
			dao = new MedidaDAO();
			dao.adiciona(medida);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
}