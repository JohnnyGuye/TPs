package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import modele.Adherent;
import modele.Informations;

public class InformationsDao {
    
    public void create(Informations informations) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(informations);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Informations update(Informations informations) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            informations = em.merge(informations);
        }
        catch(Exception e){
            throw e;
        }
        return informations;
    }
    
    public Informations findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Informations informations = null;
        try {
            informations = em.find(Informations.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return informations;
    }
    
    public List<Informations> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Informations> informations = null;
        try {
            Query q = em.createQuery("SELECT a FROM Informations a");
            informations = (List<Informations>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return informations;
    }
    
    public Informations authentification(Adherent adh,String mdp){
        Informations info;
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Informations> informations = null;
        try {
            Query q = em.createQuery("SELECT i FROM Informations i WHERE i.adherent=:Adherent");
            q.setParameter("Adherent", adh);
            informations = (List<Informations>) q.getResultList();
            if(informations.isEmpty()){
                System.out.println("Utilisateur non inscrit. \n Utilisez la commande first si c'est votre premiere connexion");
            }else{
                info =informations.get(0);
                if(info.isPassword(mdp)){
                    return info;
                }else{
                    return null;
                }
            }
        }
        catch(Exception e) {
            throw e;
        }
        
        return null;
    }
    /**
     * 
     * methode utilise pour la premiere conexion d'un utilisateur
     * @param adh
     * @param mdp
     * @return 
     */
    public Informations registerUser(Adherent adh,String mdp){
        Informations info;
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Informations> informations = null;
        try {
            Query q = em.createQuery("SELECT a FROM Informations a WHERE a.adherent=:Adherent");
            q.setParameter("Adherent", adh);
            informations = (List<Informations>) q.getResultList();
            if(informations.isEmpty()){
                info = new Informations();
                info.setAdherent(adh);
                info.setPassword(mdp);
                info.setResponsable(false);
                em.persist(informations);
                System.out.println("Utilisateur inscrit");
            }else{
                System.out.println("Mot de passe deja cree");
            }
        }
        catch(Exception e) {
            throw e;
        }
        
        return null;
    }
}
