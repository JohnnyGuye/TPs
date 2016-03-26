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
        //String mail = "b.johnson@fb.com";
        //Adherent adh = new Adherent("Johnson", "Ben", "20 Avenue Albert Einstein, Villeurbanne", mail);
        //adh.setMdp("MomMotDePasse");
        //System.out.println(adh.compare("MomMotDePasse"));
        //Services.register(adh);
        
        try {
            List<Adherent> adherents = Services.selectAdherentsByName( "Ben","Johnson");
            
            List<Activite> activites = Services.selectActivitiesByName("Baby foot");
            
 
            
            
            Demande dem = new Demande(adherents.get(0), activites.get(0), JpaUtil.creerDate("27/03/2016"));
            Services.postDemande(dem);
            
            
     
        } catch (Throwable ex) {
            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
}
