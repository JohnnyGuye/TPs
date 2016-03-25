/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package services;


import dao.*;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.Properties;
import javax.persistence.Query;
import modele.*;
import vue.main;

/**
 *
 * @author lokumuraon
 */
public class Services {
    
    public void Services()
    {
        
    }
    
    public void sendMail()
    {
        
    }
    
    public static void sendEventNotificationMail(Evenement evt){
        Query query = JpaUtil.request("select d From Demande d Where d.evenement_id =\""+evt.getId()+"\"");
        List<Demande> dems = query.getResultList();
        for(Demande d:dems){
            //query = JpaUtil.request("select a from Adherent a where id=\""+d.getAdherent().getId()+"\"");
            System.out.println("Envoyer un couriel a "+d.getAdherent().getMail()+" contenant pour l'évènement");
            System.out.println(evt.toString());
        }
    }
    
    // ==== Services métier ====
    // === Adhérent ===
    //S'inscrire
    public static Long register(Adherent adherent){
        JpaUtil.creerEntityManager();
        
        
        AdherentDao adhDao = new AdherentDao();
        //verifie que l'adresse mail n'est pas encore utilise
        try {
            if(adhDao.findByMail(adherent.getMail()).isEmpty()){
                return null;
            }
        } catch (Throwable ex) {
            Logger.getLogger(Services.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
        try{  
            JpaUtil.ouvrirTransaction();         
            adhDao.create(adherent);
            JpaUtil.validerTransaction();
        }catch(Exception e){JpaUtil.validerTransaction();
            e.printStackTrace();
        }catch (Throwable ex){
            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
        }finally{
            JpaUtil.fermerEntityManager();  
        }
        
        return adherent.getId();  
    }
    
    /**
     * Récupère la liste de tout les adhérents
     * @return
     * @throws Throwable 
     */
    public static List<Adherent> selectAllAdherents() throws Throwable{          
        JpaUtil.creerEntityManager(); 
        
        AdherentDao adhDao = new AdherentDao();
        
        List <Adherent> adherents; 
        adherents = adhDao.findAll();
        
        JpaUtil.fermerEntityManager();
        return adherents;
    }
    /**
     * Recherche d'adherent par nom
     * 
     * @param name prénom
     * @param surname nom
     * @return List contenant les adherents trouves
     */
    public static List<Adherent> selectAdherentsByName(String name, String surname) throws Throwable{
        JpaUtil.creerEntityManager(); 
        
        AdherentDao adhDao = new AdherentDao();
        
        List <Adherent> adherents; 
        adherents = adhDao.findByName(name,surname);
        
        JpaUtil.fermerEntityManager();
        return adherents;
    }
    
    public static boolean identification(String mail, String mdp) throws Throwable{
        JpaUtil.creerEntityManager();
        AdherentDao adhDao = new AdherentDao();
        boolean b = adhDao.authentication(mail,mdp);
        JpaUtil.fermerEntityManager();
        return b;
    }
 
    // === Activté ===
    
    /**
     * Ajoute une activite au catalogue
     * @param activite l'activite à ajouter
     * @return true si l'activite a été ajoutee
     */
    public static boolean addActivite(Activite activite){
            JpaUtil.creerEntityManager();
            JpaUtil.ouvrirTransaction();
            boolean ok = true;

            try{
                ActiviteDao actDao = new ActiviteDao();
                actDao.create(activite);
            }catch(Exception e){
                e.printStackTrace();
                ok = false;
            }catch (Throwable ex){
                Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
                ok = false;
            }finally{
                JpaUtil.validerTransaction();
                JpaUtil.fermerEntityManager();  
            }
        
        return ok;  
       }
    
    /**
     * Selectionne toutes les activites
     * @return la liste de toutes les activites
     */
    public static List<Activite> selectAllActivities(){
        List <Activite> activities;       
        try{
            ActiviteDao evntDao = new ActiviteDao();
            activities = evntDao.findAll();
        } catch (Throwable e){
            activities = new LinkedList();
        }
        return activities;
    }
    
    /**
     * Selectionne les activites avec un nom précis
     * @param name le nom recherche
     * @return La liste des activite avec ce nom
     */
    public static List<Activite> selectActivitiesByName(String name){
        List <Activite> activites;     
        JpaUtil.creerEntityManager();
        Query query = JpaUtil.request("select a from Activite a where a.denomination=\"" + name + "\"");
        activites = query.getResultList();
        JpaUtil.fermerEntityManager();
        return activites;
    }
    
    // === Lieu ===
    
    /**
     * Ajoute un lieu au catalogue
     * @param lieu
     * @return true si le lieu a bien ete ajoute 
     */
    public static boolean addLieu(Lieu lieu){
            JpaUtil.creerEntityManager();
            JpaUtil.ouvrirTransaction();
            boolean ok = true;

            try{
                LieuDao actDao = new LieuDao();
                actDao.create(lieu);
            }catch(Exception e){
                e.printStackTrace();
                ok = false;
            }catch (Throwable ex){
                Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
                ok = false;
            }finally{
                JpaUtil.validerTransaction();
                JpaUtil.fermerEntityManager();  
            }
        
        return ok;  
       }
    
    /**
     * Selectionne tout les lieux
     * @return la liste de tout les lieux
     */
    public static List<Lieu> selectAllLieux(){
        List <Lieu> lieux;       
        JpaUtil.creerEntityManager();
        Query query = JpaUtil.request("select a from Lieu a");
        lieux = query.getResultList();
        JpaUtil.fermerEntityManager();
        return lieux;
    }
    /**
     * Cherche les lieux par leur nom
     * 
     * @param name
     * @return 
     */
    public static List<Lieu> selectLieuxByName(String name){
        List <Lieu> lieux;     
        JpaUtil.creerEntityManager();
        Query query = JpaUtil.request("select a from Lieu a where a.denomination=\"" + name + "\"");
        lieux = query.getResultList();
        JpaUtil.fermerEntityManager();
        return lieux;
    }
    
    // === Demande ===
    /**
     * 
     * @param dem
     * @return l'id de la demande le cas ou la demande est passee
     */
    public static Long postDemande(Demande dem){
        JpaUtil.creerEntityManager();
        DemandeDao demDao = new DemandeDao();
        
        try{    
            JpaUtil.ouvrirTransaction();
        
            demDao.create(dem);
            JpaUtil.validerTransaction();
            
        }catch(Exception e){
            e.printStackTrace();
        }catch (Throwable ex){
            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        //Création d'évènement
        
        Activite act = dem.getActivite();
        int nbP = act.getNbParticipants();
        
        EvenementDao evtDao = new EvenementDao();
        
        List<Demande> dems;
        try {
            
            JpaUtil.ouvrirTransaction();
            dems = demDao.findByDateAndActiviteFree(dem);
            
            if(dems.size() >= nbP){
                Evenement event;
                
                if(act.isParEquipe()){
                    event  = new EvenementTeam();
                    
                    evtDao.create(event);
                    
                    for(int i = 0; i < nbP; i++){
                        Demande d = dems.remove(0);
                        d.setEvenement(event);
                        d.setNumeroTeam(i%2);

                        demDao.update(d);
                        
                    }
                }else{
                    event  = new EvenementSolo();
                    
                    evtDao.create(event);
                    
                    for(int i = 0; i < nbP; i++){
                        Demande d = dems.remove(0);
                        d.setEvenement(event);
                        d.setNumeroTeam(i);
                        
                        demDao.update(d);  
                    }
                } 
                JpaUtil.validerTransaction();
            }
        } catch (Throwable ex) {
            Logger.getLogger(Services.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        JpaUtil.fermerEntityManager();
        
        return dem.getId();
    }
    
    protected static void ValidTransac(boolean ok){
        if(ok)
            JpaUtil.validerTransaction();
        else
            JpaUtil.annulerTransaction();
    }
   
    
    // === Evenement ===
    
    public static List<Evenement> selectAllEvents()  {
        List <Evenement> events;       
        try{
            EvenementDao evntDao = new EvenementDao();
            events = evntDao.findAll();
        } catch (Throwable e){
            events = new LinkedList();
        }
        return events;
    }
    
    public static List<Evenement> selectEventsByName(String name){
        List <Evenement> events;     
        JpaUtil.creerEntityManager();
        Query query = JpaUtil.request("select a from Evenement a where a.denomination=\"" + name + "\"");
        events = query.getResultList();
        JpaUtil.fermerEntityManager();
        return events;
    }
    
    public static boolean assignLocationToEvent(Evenement event, Lieu lieu){
        try{
            EvenementDao evntDao = new EvenementDao();
            Evenement evnt = evntDao.findById(event.getId());
            evnt.setLieu(lieu);
            evntDao.update(evnt);
        }catch(Throwable e){
            e.printStackTrace();
            return false;
        }
        
        //TODO envoyer confirmation aux adherents
        sendEventNotificationMail(event);
        return true;
    }
    
}
