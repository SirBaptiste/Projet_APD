import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.ParseException;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.BadLocationException;

public class APDFrame extends JFrame {
	private final String COLSEP = ";";
	private final String LINESEP = "\n";
	private boolean saveImgs;
	
	public APDFrame() throws HeadlessException {
		super("Propagation de la chaleur");
		saveImgs = false;
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JPanel panelTexte = new JPanel(new SpringLayout());

		JLabel labelCol = new JLabel("Nombre de colonnes : ", JLabel.TRAILING);
		panelTexte.add(labelCol);
		JTextField nbCol = new JTextField("1", 4);
		nbCol.getDocument().addDocumentListener(new DocumentListener() {
			@Override
			public void removeUpdate(DocumentEvent e) {
			}

			@Override
			public void insertUpdate(DocumentEvent e) {
				if (!nbCol.getText().matches("[0-9]+"))
					JOptionPane.showMessageDialog(null, "\"" + nbCol.getText() + "\" n'est pas un entier",
							"ERREUR dans nombre de colonnes", JOptionPane.ERROR_MESSAGE);
			}

			@Override
			public void changedUpdate(DocumentEvent e) {
			}
		});
		labelCol.setLabelFor(nbCol);
		panelTexte.add(nbCol);

		JLabel labelLigne = new JLabel("Nombre de lignes : ", JLabel.TRAILING);
		panelTexte.add(labelLigne);
		JTextField nbLignes = new JTextField("1", 4);
		nbLignes.getDocument().addDocumentListener(new DocumentListener() {
			@Override
			public void removeUpdate(DocumentEvent e) {}
			@Override
			public void insertUpdate(DocumentEvent e) {
				if (!nbLignes.getText().matches("[0-9]+"))
					JOptionPane.showMessageDialog(null, "\"" + nbLignes.getText() + "\" n'est pas un entier",
							"ERREUR dans nombre de lignes", JOptionPane.ERROR_MESSAGE);
			}
			@Override
			public void changedUpdate(DocumentEvent e) {}
		});
		labelLigne.setLabelFor(nbLignes);
		panelTexte.add(nbLignes);

		JLabel labelDuree = new JLabel("Duree (en s) : ", JLabel.TRAILING);
		panelTexte.add(labelDuree);
		JTextField duree = new JTextField("1", 3);
		duree.getDocument().addDocumentListener(new DocumentListener() {
			@Override
			public void removeUpdate(DocumentEvent e) {}
			@Override
			public void insertUpdate(DocumentEvent e) {
				if (!duree.getText().matches("[0-9]+"))
					JOptionPane.showMessageDialog(null, "\"" + duree.getText() + "\" n'est pas un entier",
							"ERREUR dans duree", JOptionPane.ERROR_MESSAGE);
			}
			@Override
			public void changedUpdate(DocumentEvent e) {}
		});
		labelDuree.setLabelFor(duree);
		panelTexte.add(duree);

		JLabel labelTemp = new JLabel("Seuil de temperature : ", JLabel.TRAILING);
		panelTexte.add(labelTemp);
		JTextField seuil_temp = new JTextField("1.0", 4);
		seuil_temp.getDocument().addDocumentListener(new DocumentListener() {
			@Override
			public void removeUpdate(DocumentEvent e) {}
			@Override
			public void insertUpdate(DocumentEvent e) {
				if (!seuil_temp.getText().matches("[0-9]*.[0-9]*"))
					JOptionPane.showMessageDialog(null, "\"" + seuil_temp.getText() + "\" n'est pas un flottant",
							"ERREUR dans seuil de temperature", JOptionPane.ERROR_MESSAGE);
			}
			@Override
			public void changedUpdate(DocumentEvent e) {}
		});
		labelTemp.setLabelFor(seuil_temp);
		panelTexte.add(seuil_temp);
		
		JCheckBox save = new JCheckBox("Enregistrer les images ?");
		save.addItemListener(new ItemListener() {			
			@Override
			public void itemStateChanged(ItemEvent e) {saveImgs = (e.getStateChange() == ItemEvent.SELECTED);}
		});
		panelTexte.add(save);
		panelTexte.add(new JLabel(""));

		JButton bouton = new JButton("Valider");
		bouton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				genMatrice(nbCol.getText(), nbLignes.getText(), duree.getText(), seuil_temp.getText());
			}
		});
		panelTexte.add(bouton);

		JButton bouton2 = new JButton("Reset");
		bouton2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(null,
						"etes-vous sur de vouloir reinitialiser les champs ?", "RESET", JOptionPane.YES_NO_OPTION)) {
					nbCol.setText("1");
					nbLignes.setText("1");
					duree.setText("1");
					seuil_temp.setText("1.0");
				}
			}
		});
		panelTexte.add(bouton2);

		SpringUtilities.makeCompactGrid(panelTexte, 6, 2, 6, 6, 6, 6);

		panelTexte.setOpaque(true);
		this.setContentPane(panelTexte);

		this.pack();
		this.setVisible(true);
	}

	public APDFrame(GraphicsConfiguration arg0) {super(arg0);}
	public APDFrame(String arg0) throws HeadlessException {super(arg0);}
	public APDFrame(String arg0, GraphicsConfiguration arg1) {super(arg0, arg1);}

	private void genMatrice(String col, String lignes, String duree, String seuil_temp) {
		try {
			int nbCol = Integer.parseInt(col);
			int nbLignes = Integer.parseInt(lignes);
			int dureeSec = Integer.parseInt(duree);
			float seuilTemp = Float.parseFloat(seuil_temp);
			JPanel panel = new JPanel(new SpringLayout());
			JTextField textFields[] = new JTextField[nbCol * nbLignes];

			for (int i = 0; i < nbCol * nbLignes; i++) {
				textFields[i] = new JTextField(seuil_temp, 5);
				textFields[i].getDocument().addDocumentListener(new DocumentListener() {
					@Override
					public void removeUpdate(DocumentEvent e) {}
					@Override
					public void insertUpdate(DocumentEvent e) {
						try {
							String txt;
							if (!(txt = e.getDocument().getText(0, e.getDocument().getLength()))
									.matches("[0-9]*.[0-9]*"))
								JOptionPane.showMessageDialog(null,
										"\"" + txt + "\" n'est pas un flottant", "ERREUR",
										JOptionPane.ERROR_MESSAGE);
						} catch (HeadlessException | BadLocationException osef) {}
					}
					@Override
					public void changedUpdate(DocumentEvent e) {}
				});
				panel.add(textFields[i]);
			}

			SpringUtilities.makeGrid(panel, nbLignes, nbCol, 5, 5, 5, 5);
			
			JPanel panel2 = new JPanel(new BorderLayout());
			
			panel2.add(panel,BorderLayout.NORTH);
			JButton bouton = new JButton("Valider");
			bouton.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String values[] = new String[nbCol*nbLignes];
					for(int i=0; i<nbCol*nbLignes; i++)
						values[i] = textFields[i].getText();
					
					saveFileAndExeC(values, nbCol, nbLignes, dureeSec, seuilTemp);
				}
			});
			panel2.add(bouton,BorderLayout.SOUTH);
			JScrollPane scroll = new JScrollPane(panel2);
			scroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
			scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
			this.setContentPane(scroll);
			this.repaint();
			this.revalidate();
			this.pack();
		} catch (NumberFormatException e) {
			JOptionPane.showMessageDialog(null, e.getMessage(), "Erreur dans les valeurs", JOptionPane.ERROR_MESSAGE);
			new APDFrame();
		}
	}
	
	private void saveFileAndExeC(String[] values, int nbCol, int nbLignes, int dureeSec, float seuilTemp) {
		try(BufferedWriter bf = new BufferedWriter(new FileWriter("tmp.txt"))) {
			if(nbLignes != 1)
				bf.write(Integer.toString(nbLignes)+COLSEP+Integer.toString(nbCol)+LINESEP);
			else
				bf.write(Integer.toString(nbCol)+LINESEP);
			
			bf.write(Integer.toString(dureeSec)+LINESEP);
			bf.write(Float.toString(seuilTemp)+LINESEP);
			
			for (int i=0; i<nbLignes*nbCol;i++) {
				bf.write(values[i]+COLSEP);

				if((i+1)%nbCol==0)
					bf.write(LINESEP);
			}
		} catch (IOException e) {e.printStackTrace();}
		
		String cmd = "./test";
		if(saveImgs)	cmd += " save";

		try {
			Process p = Runtime.getRuntime().exec(cmd);
			p.waitFor();
		} catch (IOException | InterruptedException e) {e.printStackTrace();}
		
		System.exit(1);
	}
}