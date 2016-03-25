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
public class EvenementSolo extends Evenement{

    public EvenementSolo() {
        super();
    }

    public EvenementSolo(Lieu lieu) {
        super(lieu);
    }
}
