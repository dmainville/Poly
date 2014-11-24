/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package my.counterexample;

import java.util.Observable;

/**
 *
 * @author damaib
 */
public class CE_UI_Console implements java.util.Observer{

    CE_Controleur controleur;

    public CE_UI_Console(CE_Controleur c) {
        controleur = c;
    }
    
    @Override
    public void update(Observable o, Object arg) {
        controleur.afficherValeur(false); //appelle le controleur pour mettre a jour l'interface
    }
    
}
