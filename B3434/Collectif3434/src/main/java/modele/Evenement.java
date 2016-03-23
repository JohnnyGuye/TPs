/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modele;

import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

/**
 *
 * @author lokumuraon
 */
@Entity
public class Evenement implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    protected Long id;
    protected Lieu lieu;
    protected int typeEquipe;
    
    public final int 
            SOLO = 0,
            TEAM = 1;
    
    protected Evenement(Lieu lieu, int typeEquipe)
    {
        this.lieu = lieu;
        this.typeEquipe = typeEquipe;
    }
    
    public Evenement(Lieu lieu){
        this(lieu, 0);
    }
    
    public Evenement(){
    }
    
    public Evenement(int typeEquipe){
        this.typeEquipe=typeEquipe;
    }
    
    public int getTypeEquipe(){
        return typeEquipe;
    }
    public Lieu getLieu(){
        return lieu;
    }
    
    public void setLieu(Lieu lieu){
        this.lieu = lieu;
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
        if (!(object instanceof Evenement)) {
            return false;
        }
        Evenement other = (Evenement) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "metier.modele.Evenement[ id=" + id + " ]";
    }
    
}
