/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modele;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Temporal;
import static javax.persistence.TemporalType.DATE;

/**
 *
 * @author lokumuraon
 */
@Entity
public class Demande implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private Adherent adherent;
    private Activite activite;
    private Evenement evenement;
    @Temporal(DATE)
    private Date date;
    private int numeroTeam;
    
    //Constructeur
     public Demande(Adherent adh, Activite act, Date date){
        this.date = date;
        this.adherent = adh;
        this.activite = act;
        this.evenement = null;
        this.numeroTeam = -1;
    }
    
    public Demande(){
        this(null, null, null);
    } 
    
    //Getters and setters
    public Adherent getAdherent() {
        return adherent;
    }

    public void setAdherent(Adherent adherent) {
        this.adherent = adherent;
    }

    public Activite getActivite() {
        return activite;
    }

    public void setActivite(Activite activite) {
        this.activite = activite;
    }

    public Evenement getEvenement() {
        return evenement;
    }

    public void setEvenement(Evenement evenement) {
        this.evenement = evenement;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public int getNumeroTeam() {
        return numeroTeam;
    }

    public void setNumeroTeam(int numeroTeam) {
        this.numeroTeam = numeroTeam;
    }

    
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Demande)) {
            return false;
        }
        Demande other = (Demande) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "modele.Demande[ id=" + id + " ]";
    }
    public String stringListe(){
        return "["+id+"]"+activite.getDenomination()+" le "+date;
    }
    
}
