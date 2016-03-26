/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modele;

import javax.persistence.Entity;

/**
 *
 * @author lokumuraon
 */
@Entity
public class EvenementTeam extends Evenement{

    public EvenementTeam() {
        super();
    }

    public EvenementTeam(Lieu lieu) {
        super(lieu);
    }
    
}
