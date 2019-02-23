package br.puc.ibarreto.gui;

/**
 * Projeto Servo Motor
 * @author Paulo César Barreto da Silva
 * @date 13/07/2012
 */

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import br.puc.ibarreto.modelagem.ComunicacaoSerial;

public class frmServoMotor extends JFrame implements ActionListener, ChangeListener{
	private JSlider sldServo;
	private JButton btStatus;
	private Boolean status = false;
	private JLabel lbImagem;
	private static final long TEMPO = (1000); // atualiza a cada 1 segundo  
	private ComunicacaoSerial serial;
	
	public frmServoMotor(){
		super("Gestão do Servo Motor");
		setSize(350,370);
		setLayout(new FlowLayout());
		
		serial = new ComunicacaoSerial();
		serial.initialize();
		
		btStatus = new JButton("Desligado");
		btStatus.addActionListener(this);
				
		lbImagem = new JLabel(new ImageIcon("./src/br/puc/ibarreto/img/servoMotor.jpg"));
	
		add(lbImagem, "Center");
		
		add(btStatus, "North");
		
		sldServo = new JSlider(0, 180);
		sldServo.setMajorTickSpacing(45);
		sldServo.setPaintLabels(true);
		sldServo.addChangeListener(this);
		sldServo.setValue(0);
		add(sldServo, "South");
		Timer timer = null;    
		
        if (timer == null) {    
            timer = new Timer();    
            TimerTask tarefa = new TimerTask() {    
                public void run() {    
                    try { 
                    	//Girar de forma progressiva
                    	if (status == true){
                    		for(int pos = sldServo.getValue(); pos < 180; pos += 1){
                    			sldServo.setValue(pos);
                    			Thread.sleep(15); 
                    		}
                    		for(int pos = 180; pos>=1; pos-=1){
                    			sldServo.setValue(pos);
                    			Thread.sleep(15); 	
                    		}
                    	}
                    	
                    } catch (Exception e) {    
                        e.printStackTrace();    
                    }    
                }    
            };    
            timer.scheduleAtFixedRate(tarefa, TEMPO, TEMPO);    
       }
		setVisible(true);
	}

	//Tratamento de Ações
	public void actionPerformed(ActionEvent arg0) {
		status = !status;
		if (status)
			btStatus.setText("Ligado");
		else
			btStatus.setText("Desligado");
	}
	public void stateChanged(ChangeEvent arg0) {
		//System.out.println("Girar " + sldServo.getValue());	
		serial.setRele(sldServo.getValue());
	}
	
	public static void main(String args[]){
		frmServoMotor frm = new frmServoMotor();
		frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}