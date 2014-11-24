/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package my.counterexample;

/**
 *
 * @author damaib
 */

 public class Model extends java.util.Observable {
   
     //Constantes pour les valeurs max et min
     public int  MIN = -50;
     public int  MAX = 50;
     
    Model(CE_UI_Console c, CE_UI_Fenetre f, CE_UI_Slider s)
    {
        //Ajout d'observer qui doivent être mis a jour lorsque le modèle change
        addObserver(c);
        addObserver(f);
        addObserver(s);
    }
     
    private Integer valeur = 1;
    
    protected void incremente()
    {
        if(valeur < MAX)
        {
            valeur++;            
            setChanged();
            notifyObservers();
        }

    }
    
    protected void decremente()
    {
        if(valeur > MIN)
        {
            valeur--;
            setChanged();
            notifyObservers();
        }
    }
    
    protected void setValeur(int v)
    {
        valeur = v;
        setChanged();
        notifyObservers();
    }
    
    protected String getValeur()
    {
        return valeur.toString();
    }
    
    protected int getIntValeur()
    {
        return valeur;
    }
}
