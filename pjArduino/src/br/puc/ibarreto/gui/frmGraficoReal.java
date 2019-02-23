package br.puc.ibarreto.gui;

/**
 * Projeto de Gerência
 * Disciplina: 21845- SISTEMAS INFORMAÇÃO GERÊNCIA TELECOMUNICAÇÕES
 * Classe que modela conceitualmente acompanhamento da Medição de Energia
 * @autor Paulo C. Barreto / Luiz R. Barreto
 * @date 27/05/2012
 */
/**
 * Pilar de Gerencia Monitoramento
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GradientPaint;
import java.awt.Point;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.dial.DialBackground;
import org.jfree.chart.plot.dial.DialCap;
import org.jfree.chart.plot.dial.DialPlot;
import org.jfree.chart.plot.dial.DialTextAnnotation;
import org.jfree.chart.plot.dial.DialValueIndicator;
import org.jfree.chart.plot.dial.StandardDialFrame;
import org.jfree.chart.plot.dial.StandardDialRange;
import org.jfree.chart.plot.dial.StandardDialScale;
import org.jfree.data.general.DefaultValueDataset;
import org.jfree.data.general.ValueDataset;
import org.jfree.ui.GradientPaintTransformType;
import org.jfree.ui.StandardGradientPaintTransformer;

public class frmGraficoReal extends JFrame
{
	private static float corrente;
	private static final long TEMPO = (1000); // atualiza a cada 1 segundo  

	private static JSlider slider;
	private static DefaultValueDataset dataset;
	
	static class PainelGrafico extends JPanel
	implements ChangeListener
	{
		public static JFreeChart createStandardDialChart(String s, String s1, ValueDataset valuedataset, double d, double d1, double d2, int i)
		{
			DialPlot dialplot = new DialPlot();
			dialplot.setDataset(valuedataset);
			dialplot.setDialFrame(new StandardDialFrame());
			dialplot.setBackground(new DialBackground());
			DialTextAnnotation dialtextannotation = new DialTextAnnotation(s1);
			dialtextannotation.setFont(new Font("Dialog", 1, 14));
			dialtextannotation.setRadius(0.69999999999999996D);
			dialplot.addLayer(dialtextannotation);
			DialValueIndicator dialvalueindicator = new DialValueIndicator(0);
			dialplot.addLayer(dialvalueindicator);
			StandardDialScale standarddialscale = new StandardDialScale(d, d1, -120D, -300D, 10D, 4);
			standarddialscale.setMajorTickIncrement(d2);
			standarddialscale.setMinorTickCount(i);
			standarddialscale.setTickRadius(0.88D);
			standarddialscale.setTickLabelOffset(0.14999999999999999D);
			standarddialscale.setTickLabelFont(new Font("Dialog", 0, 14));
			dialplot.addScale(0, standarddialscale);
			dialplot.addPointer(new org.jfree.chart.plot.dial.DialPointer.Pin());
			DialCap dialcap = new DialCap();
			dialplot.setCap(dialcap);
			return new JFreeChart(s, dialplot);
		}

		public void stateChanged(ChangeEvent changeevent)
		{
			//Recebe medida de corrente instântanea
			dataset.setValue(corrente);			
		}

		public PainelGrafico(float corrente)
		{
			super(new BorderLayout());
			dataset = new DefaultValueDataset(10D);
			JFreeChart jfreechart = createStandardDialChart("Gerência de Monitoramento", "Corrente de Energia", dataset, 0D, 60D, 10D, 4);
			DialPlot dialplot = (DialPlot)jfreechart.getPlot();
			StandardDialRange standarddialrange = new StandardDialRange(40D, 60D, Color.red);
			standarddialrange.setInnerRadius(0.52000000000000002D);
			standarddialrange.setOuterRadius(0.55000000000000004D);
			dialplot.addLayer(standarddialrange);
			StandardDialRange standarddialrange1 = new StandardDialRange(20D, 40D, Color.orange);
			standarddialrange1.setInnerRadius(0.52000000000000002D);
			standarddialrange1.setOuterRadius(0.55000000000000004D);
			dialplot.addLayer(standarddialrange1);
			StandardDialRange standarddialrange2 = new StandardDialRange(0D, 20D, Color.green);
			standarddialrange2.setInnerRadius(0.52000000000000002D);
			standarddialrange2.setOuterRadius(0.55000000000000004D);
			dialplot.addLayer(standarddialrange2);
			GradientPaint gradientpaint = new GradientPaint(new Point(), new Color(255, 255, 255), new Point(), new Color(170, 170, 220));
			DialBackground dialbackground = new DialBackground(gradientpaint);
			dialbackground.setGradientPaintTransformer(new StandardGradientPaintTransformer(GradientPaintTransformType.VERTICAL));
			dialplot.setBackground(dialbackground);
			dialplot.removePointer(0);
			org.jfree.chart.plot.dial.DialPointer.Pointer pointer = new org.jfree.chart.plot.dial.DialPointer.Pointer();
			pointer.setFillPaint(Color.yellow);
			dialplot.addPointer(pointer);
			ChartPanel chartpanel = new ChartPanel(jfreechart);
			chartpanel.setPreferredSize(new Dimension(400, 400));
			slider = new JSlider(0, 60);
			slider.setMajorTickSpacing(5);
			slider.setPaintLabels(true);
			slider.addChangeListener(this);
			add(chartpanel);
			add(slider, "South");
			slider.setVisible(false);
		}
	}
	
	public frmGraficoReal(String s)
	{
		super(s);
		setDefaultCloseOperation(3);
		setContentPane(createPainelGrafico(corrente));
		Timer timer = null;    
        if (timer == null) {    
            timer = new Timer();    
            TimerTask tarefa = new TimerTask() {    
                public void run() {    
                    try {    
            			slider.setValue((int)(corrente * 10));
                        //chamar metodo    
                    } catch (Exception e) {    
                        e.printStackTrace();    
                    }    
                }    
            };    
            timer.scheduleAtFixedRate(tarefa, TEMPO, TEMPO);    
       }    
	}

	public static JPanel createPainelGrafico(float corrente)
	{
		return new PainelGrafico(corrente);
	}

	public static float getCorrente() {
		return corrente;
	}

	public static void setCorrente(float corrente) {
		frmGraficoReal.corrente = corrente;
	}
}