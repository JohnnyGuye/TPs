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
import util.Saisie;
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
    
    
    // ==== Services métier ====
    // === Adhérent ===
    //S'inscrire
    /**
     * 
     * Service utilise pour s'inscrire
     * @param informations
     * @return 
     */
    public static Long register(Informations informations){
        JpaUtil.creerEntityManager();
        
        
        AdherentDao adhDao = new AdherentDao();
        InformationsDao infoDao = new InformationsDao();
        //verifie que l'adresse mail n'est pas encore utilise
        try {
            if(!(adhDao.findByMail(informations.getAdherent().getMail()).isEmpty())){
                return null;
            }
        } catch (Throwable ex) {
            Logger.getLogger(Services.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
        try{  
            JpaUtil.ouvrirTransaction();         
            adhDao.create(informations.getAdherent());
            infoDao.create(informations);
            JpaUtil.validerTransaction();
        }catch(Exception e){JpaUtil.validerTransaction();
            e.printStackTrace();
        }catch (Throwable ex){
            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
        }finally{
            JpaUtil.fermerEntityManager();  
        }
        
        return informations.getAdherent().getId();  
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
    /**
     * Service utilise pour verifier qui est inscrit
     * 
     * @param mail
     * @return
     * @throws Throwable 
     */
    public static List<Adherent> selectAdherentByMail(String mail) throws Throwable{
        JpaUtil.creerEntityManager();;
        AdherentDao adhDao = new AdherentDao();
        List<Adherent> adherent;
        adherent = adhDao.findByMail(mail);
        return adherent;
    }
    /**
     * Identification de l'utilisateur
     * 
     * @param mail
     * @param mdp
     * @return
     * @throws Throwable 
     */
    public static Informations identification(String mail,String mdp) throws Throwable{
        JpaUtil.creerEntityManager();
        AdherentDao adhDao = new AdherentDao();
        InformationsDao infoDao = new InformationsDao();
        List<Adherent> adh;
        Informations info=new Informations();
        adh=adhDao.findByMail(mail);
        if(adh.isEmpty()){
            System.out.println("Utilisateur non inscrit");
        }else{
            info=infoDao.authentification(adh.get(0),mdp);
            return info;
        }
        JpaUtil.fermerEntityManager();
        return info;
    }
    /**
     * Utile pour les adherents qui s'ont deja presents dans la base de donnees , n'ayant pas encore un objet
     * Informations associe
     * @param mail
     * @return 
     */
    public static Informations premiereConnexion(String mail, String mdp) throws Throwable{
        JpaUtil.creerEntityManager();
        AdherentDao adhDao = new AdherentDao();
        InformationsDao infoDao = new InformationsDao();
        List<Adherent> adh;
        Informations info=new Informations();
        adh=adhDao.findByMail(mail);
        if(adh.isEmpty()){
            
        }else{
            JpaUtil.ouvrirTransaction();
            info=infoDao.registerUser(adh.get(0),mdp);
            JpaUtil.validerTransaction();
            JpaUtil.fermerEntityManager();
            return info;
        }
        return info;
    }
 
    // === Activté ===
    
    /**
     * Ajoute une activite au catalogue, service non utilise dans le main,
     * mais peut etre utile pour la suite, si on veutfaire evoluer le catalogue
     * des activites
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
        JpaUtil.creerEntityManager();
        try{
            ActiviteDao evntDao = new ActiviteDao();
            activities = evntDao.findAll();
        } catch (Throwable e){
            activities = new LinkedList();
        }
        JpaUtil.fermerEntityManager();
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
    /**
     * renvoie le lieu avec le numero correspondant
     * @param number
     * @return
     * @throws Throwable 
     */
    public static Lieu selectLieuByNumber(long number) throws Throwable{
        Lieu lieu;     
        LieuDao lieuDao = new LieuDao();
        JpaUtil.creerEntityManager();
        lieu = lieuDao.findById(number);
        JpaUtil.fermerEntityManager();
        return lieu;
    }
    
    // === Demande ===
    /**
     * Service utilise pour poster une demande
     * @param dem
     * @return l'id de la demande le cas ou la demande est passee
     */
    public static Long postDemande(Demande dem){
        JpaUtil.creerEntityManager();
        DemandeDao demDao = new DemandeDao();
        
        try{    
            JpaUtil.ouvrirTransaction();
        
            demDao.create(dem);
            Saisie.lireChaine("Pause pour la demonstration, appuyez sur la touche entree");
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
            dems = demDao.findByDateAndActiviteFree(dem.getActivite(),dem.getDate());
            
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
    /**
     * 
     * Service utilise pour connaitre les demandes faites par un adherent
     * @param adh
     * @return 
     */
    public static List<Demande> mesDemandes(Adherent adh){
        List <Demande> demandes;       
        try{
            JpaUtil.creerEntityManager();
            DemandeDao demDao = new DemandeDao();
            demandes = demDao.findByOwner(adh);
            JpaUtil.fermerEntityManager();
        } catch (Throwable e){
            demandes = new LinkedList();
        }
        return demandes;
    }
    // === Evenement ===
    /**
     * Selectionne tous les evenements
     * @return 
     */
    public static List<Evenement> selectAllEvents()  {
        List <Evenement> events;       
        try{
            JpaUtil.creerEntityManager();
            EvenementDao evntDao = new EvenementDao();
            events = evntDao.findAll();
            JpaUtil.fermerEntityManager();
        } catch (Throwable e){
            events = new LinkedList();
        }
        return events;
    }
    /**
     * Service utilise pour afficher les evenements et ses details,
     * cette methode est utilise parce que les evenements ne contiennent ni la
     * date ni l'activite de l'evenement.
     * 
     * @return 
     */
    public static boolean Evenements(){
        boolean affecter = false;
        List <Evenement> events;       
        try{
            JpaUtil.creerEntityManager();
            EvenementDao evntDao = new EvenementDao();
            DemandeDao demDao = new DemandeDao();
            events = evntDao.findAll();
            if(events.isEmpty()){
                System.out.println("Aucun evenement trouve");
            }
            for(Evenement e:events){
                System.out.print(e.stringListe());
                List<Demande> demandes;
                demandes=demDao.findByEvent(e);
                System.out.print(demandes.get(0).getActivite().getDenomination());
                for(Demande d:demandes){
                    Adherent adh = d.getAdherent();
                    System.out.println(adh.getNom()+" "+adh.getPrenom());
                }
                if(e.getLieu()==null){
                    affecter=true;
                }
            }
            JpaUtil.fermerEntityManager();
        } catch (Throwable e){
            events = new LinkedList();
        }
        return affecter;
    }
    
    /**
     * Selectionne les evenements dont le lieu n'a pas encore été affecté
     * @return 
     */
    public static List<Evenement> selectUnassignedEvents(){
        List <Evenement> events;       
        try{
            JpaUtil.creerEntityManager();
            EvenementDao evntDao = new EvenementDao();
            events = evntDao.findUnassigned();
            JpaUtil.fermerEntityManager();
        } catch (Throwable e){
            events = new LinkedList();
        }
        return events;
    }
    
    /**
     * Service utilise par le responsable pour recuperer un evenement precis
     * @param number
     * @return
     * @throws Throwable 
     */
    public static Evenement selectEventByNumber(long number) throws Throwable{
        Evenement events;     
        EvenementDao evtDao = new EvenementDao();
        JpaUtil.creerEntityManager();
        events = evtDao.findById(number);
        JpaUtil.fermerEntityManager();
        return events;
    }
    /**
     * Affecte un lieu a un événement et met a joour l'objet persistant
     * @param event
     * @param lieu
     * @return 
     */
    public static boolean assignLocationToEvent(Evenement event, Lieu lieu){
        JpaUtil.creerEntityManager();
        try{
            EvenementDao evntDao = new EvenementDao();
            event.setLieu(lieu);
            JpaUtil.ouvrirTransaction();
            evntDao.update(event);
            JpaUtil.validerTransaction();
        }catch(Throwable e){
            e.printStackTrace();
            return false;
        }
        
        //TODO envoyer confirmation aux adherents
        Query query = JpaUtil.request("select d From Demande d Where d.evenement=:evenement");
        query.setParameter("evenement", event);
        List<Demande> dems = query.getResultList();
        if(dems.isEmpty()){
            System.out.println("demandes introuvables");
        }
        for(Demande d:dems){
            //query = JpaUtil.request("select a from Adherent a where id=\""+d.getAdherent().getId()+"\"");
            System.out.println("Envoyer un couriel a "+d.getAdherent().getMail()+" contenant les informations pour le");
            System.out.println(d.getActivite().getDenomination()+"du "+d.getDate());
        }
        return true;
    }
    
}
