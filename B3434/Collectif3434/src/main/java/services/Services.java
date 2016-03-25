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
    public static boolean addAdherent(Adherent adherent){
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();
        boolean ok = true;
        
        try{
            AdherentDao adhDao = new AdherentDao();
            adhDao.create(adherent);
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
    
    public static List<Activite> selectAllAdherents(){
        List <Activite> adherents;       
        JpaUtil.creerEntityManager();
        Query query = JpaUtil.request("select a from Activite a");
        adherents = query.getResultList();
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
    public static List<Adherent> selectAdherentsByName(String name, String surname){
        List <Adherent> adherent;     
        JpaUtil.creerEntityManager();
        Query query = JpaUtil.request("select a from Adherent a where a.prenom=\"" + name + "\" AND a.nom=\"" + surname + "\"" );
        adherent = query.getResultList();
        JpaUtil.fermerEntityManager();
        return adherent;
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
        List <Activite> activites;       
        JpaUtil.creerEntityManager();
        Query query = JpaUtil.request("select a from Activite a");
        activites = query.getResultList();
        JpaUtil.fermerEntityManager();
        return activites;
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
    public static boolean postDemande(Demande demande){
        JpaUtil.creerEntityManager();
        JpaUtil.ouvrirTransaction();
        boolean ok = true;
        
        try{
            DemandeDao demDao = new DemandeDao();
            demDao.create(demande);
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
        
        createEvent(demande);
        
        return ok;
    }
    
    // === Evenement ===
    
    public static boolean addEvenement(Evenement activite){
            JpaUtil.creerEntityManager();
            JpaUtil.ouvrirTransaction();
            boolean ok = true;

            try{
                EvenementDao actDao = new EvenementDao();
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
    
    protected static boolean createEvent(Demande dem){
        JpaUtil.creerEntityManager();
        Activite act = dem.getActivite();
        int nbP = act.getNbParticipants();
        
        //Query query = JpaUtil.request("select d from Demande d where d.date=\"" 
        //        + dem.getDate() + "\" and d.activite_id=:\"" + act.getId()+"\"");
        Query query = JpaUtil.request("select d from Demande d where d.date=\"" 
                + dem.getDate() + "\" and d.activite_id=:\"" + 38+"\""); 
        List<Demande> dems = query.getResultList();
        JpaUtil.fermerEntityManager();  
        if(dems.size() >= nbP){
            
            DemandeDao demDao = new DemandeDao();
            Evenement event;
            
            if(act.isParEquipe()){
                event  = new EvenementTeam();
                addEvenement(event);
                for(int i = 0; i < nbP; i++){
                    Demande d = dems.remove(0);
                    d.setEvenement(event);
                    d.setNumeroTeam(i%2);
                    
                    try{
                        demDao.update(d);
                    } catch (Throwable ex) {
                        Logger.getLogger(Services.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }else{
                event  = new EvenementSolo();
                addEvenement(event);
                for(int i = 0; i < nbP; i++){
                    Demande d = dems.remove(0);
                    d.setEvenement(event);
                    d.setNumeroTeam(i);
                    
                    try{
                        demDao.update(d);
                    } catch (Throwable ex) {
                        Logger.getLogger(Services.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            } 
            return true;
        }
        return false;
    }
}
