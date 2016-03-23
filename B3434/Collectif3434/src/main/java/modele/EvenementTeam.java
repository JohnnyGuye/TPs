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
public class EvenementTeam extends Evenement{

    public EvenementTeam(Lieu lieu) {
        super(lieu, 1);
    }
    public EvenementTeam(){
        super(1);
    }
    
}
