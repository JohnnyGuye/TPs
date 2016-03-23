/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vue;


import dao.JpaUtil;
import java.text.ParseException;
import java.util.Date;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import services.Services;
import modele.*;
/**
 *
 * @author lokumuraon
 */
public class main {
    
    public static void main (String [] args)
    {
        System.out.println("TESTS -- TESTS -- TESTS");
        
        // Test ajout adhérent
        
        //Adherent adh = new Adherent("Guye", "Johnny", "26 rue Flachet, 69100 Villeurbanne", "quentin.guye@insa-lyon.fr");
        //Services.addAdherent(adh);
        
        List<Adherent> adherents = Services.selectAdherentsByName("Johnny", "Guye");
        
        List<Activite> activites = Services.selectActivitiesByName("Babyfoot");
        
        for(Activite a : activites){
            System.out.println(a.toStringForUser());
        }
        
        Demande dem = new Demande(adherents.get(0), activites.get(0), JpaUtil.creerDate("27/03/2016"));
        Services.postDemande(dem);   
    }
}
