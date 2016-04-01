package dao;

import java.util.Date;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import modele.Activite;
import modele.Adherent;
import modele.Demande;
import modele.Evenement;

public class DemandeDao {
    
    public void create(Demande demande) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(demande);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Demande update(Demande demande) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            demande = em.merge(demande);
        }
        catch(Exception e){
            throw e;
        }
        return demande;
    }
    
    public Demande findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Demande demande = null;
        try {
            demande = em.find(Demande.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return demande;
    }
    
    public List<Demande> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            Query q = em.createQuery("SELECT a FROM Demande a");
            demandes = (List<Demande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
    /**
     * 
     * utilise pour connaitre les demandes pour une activite a une date specifique
     * @param dem
     * @return
     * @throws Throwable 
     */
    public List<Demande> findByDateAndActiviteFree(Activite act,Date date) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            //requete parametree : 
            Query query = em.createQuery("select d from Demande d where d.date=:Date and d.activite=:activite and d.numeroTeam=:team");
            query.setParameter("Date", date);
            query.setParameter("activite", act);
            query.setParameter("team", -1);
            demandes = (List<Demande>) query.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
    /**
     * utilise pour connaitre les demandes faites par un utilisateur
     * @param adh
     * @return
     * @throws Throwable 
     */
    public List<Demande> findByOwner(Adherent adh) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            String req = "SELECT d FROM Demande d WHERE d.adherent=:adherent";
            Query q = em.createQuery(req);
            q.setParameter("adherent",adh);
            demandes = (List<Demande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
    /**
     * Requete utilise pour recuperer les demandes correspondantes a un evenement
     * 
     * @param evt
     * @return 
     */
    public List<Demande> findByEvent(Evenement evt){
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            String req = "SELECT a FROM Demande a WHERE a.evenement=:evenement";
            Query q = em.createQuery(req);
            q.setParameter("evenement", evt);
            demandes = (List<Demande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
}
