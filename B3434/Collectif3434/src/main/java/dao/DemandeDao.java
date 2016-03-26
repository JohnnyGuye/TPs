package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import modele.Adherent;
import modele.Demande;

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
    
    public List<Demande> findByDateAndActiviteFree(Demande dem) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            //requete parametree : 
            Query query = em.createQuery("select d from Demande d where d.date=:Date and d.activite=:activite and d.numeroTeam=:team");
            query.setParameter("Date", dem.getDate());
            query.setParameter("activite", dem.getActivite());
            query.setParameter("team", -1);
            demandes = (List<Demande>) query.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
    
    public List<Demande> findByOwner(Adherent adh) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Demande> demandes = null;
        try {
            String req = "SELECT a FROM Demande a WHERE a.adherent='"+adh.getId()+"'";
            Query q = em.createQuery(req);
            demandes = (List<Demande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
}
