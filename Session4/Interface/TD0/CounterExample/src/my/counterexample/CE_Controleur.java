/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package my.counterexample;

/**
 *
 * @author damaib
 */
public class CE_Controleur {
    
    //Création des différents pannels et du model
    private CE_UI_Fenetre boxAffichage = new CE_UI_Fenetre(this);
    private CE_UI_Boutons boxBoutons = new CE_UI_Boutons(this);
    private CE_UI_Slider boxSlider = new CE_UI_Slider(this);
    private CE_UI_Console console = new CE_UI_Console(this);
    private Model model = new Model(console,boxAffichage,boxSlider);
    
    //Variables pour les différents mode d'affichage
    private Boolean modeFenetre = true;
    private Boolean enableSlider = true;
    private String derniereAction = "";
    
    CE_Controleur()
    {
        boxAffichage.setVisible(true);
        boxBoutons.setVisible(true);
        boxSlider.setVisible(true);
        
        afficherValeur(true); //Afficher la valeur au début
    }
    
    public void incrementeValeur()
    {
        derniereAction = "Valeur incrémentée";
        model.incremente();
    }
    
    public void decrementeValeur()
    {
        derniereAction = "Valeur décrémentée.";
        model.decremente();
    }
    
    public void ajusteValeur()
    {
        //Ajuste la valeur selon la position du slider
        //Il faut également vérifier si il s'agit d'une augmentation ou d'une diminution
        if(!enableSlider)
            return;
            
        if(model.getIntValeur() > boxSlider.getSlider().getValue())
        {
            derniereAction = "Valeur décrémentée.";  
        }
        else
        {
            derniereAction = "Valeur incrémentée";
        }
        
        model.setValeur(boxSlider.getSlider().getValue());
        boxSlider.getSlider().setToolTipText(model.getValeur());
    }
    
    public void changerDeVue(Boolean fenetre)
    {
        //Change le mode d'affichage et disable les boutons correspondants
        
        modeFenetre = fenetre;
        afficherValeurActuelle();
        
        boxBoutons.getBoutonFenetre().setEnabled(!fenetre);
        boxBoutons.getBoutonConsole().setEnabled(fenetre);
    }
    
    public void afficherValeurActuelle()
    {
        //Lors d'un chagement de fenetre, affiche la valeur courrante dans la fenetre active
        
        if(modeFenetre)
        {
            boxAffichage.setValeur(model.getValeur());
        }
        else
        {
            System.out.println("Valeur actuelle : "+model.getValeur());
        }
    }
    
    public void afficherValeur(Boolean fenetre)
    {
        //Affiche la valeur du modele en fonction du mode d'affichage courrant
        if(modeFenetre && fenetre)
        {
            boxAffichage.setValeur(model.getValeur());
        }
        else if(!modeFenetre && !fenetre)
        {
            System.out.println(derniereAction+" Nouvelle valeur = "+model.getValeur()+".");
        }
    }

    public void ajusteSlider()
    {
        //Modifie la valeur du slider en fonction de celle du modele
        enableSlider = false;
        boxSlider.getSlider().setValue(model.getIntValeur());
        enableSlider = true;
    }
    
    public static void main(String args[]) {
        new CE_Controleur();
    }
    
}
