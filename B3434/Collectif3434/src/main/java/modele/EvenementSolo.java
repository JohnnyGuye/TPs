/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modele;

/**
 *
 * @author lokumuraon
 */
public class EvenementSolo extends Evenement{

    public EvenementSolo(Lieu lieu) {
        super(lieu, 0);
    }
    
    public EvenementSolo(){
        super(0);
    }
}
