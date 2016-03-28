/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vue;

import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import services.Services;
import modele.*;
import util.Saisie;

/**
 *
 * @author lokumuraon
 */
public class main {


    public static void main(String[] args) {
        Adherent user = new Adherent();

        boolean exit = false;

        System.out.println("TESTS -- TESTS -- TESTS");

        while (!exit) {

            String line = Saisie.lireChaine("Choisissez une action, help pour une liste des actions possibles.");

            switch (line) {
                case "register":
                    //setters sur user
                    user.setNom(Saisie.lireChaine("Votre prénom ?"));
                    user.setPrenom(Saisie.lireChaine("Votre nom ?"));
                    user.setMail(Saisie.lireChaine("Votre mail ?"));
                    user.setAdresse(Saisie.lireChaine("Adresse ?"));
                    //user.setCoordonnee();
                    Services.register(user);
                    break;
                case "login":
                    String mail = Saisie.lireChaine("Mail ?");
                    String mdp = Saisie.lireChaine("Mot de passe ?");

                     {
                        try {
                            Services.identification(mail);
                        } catch (Throwable ex) {
                            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                    break;
                case "logout":
                    user = new Adherent();
                    break;
                case "activities":
                    List<Activite> activities = Services.selectAllActivities();
                    for (Activite a : activities) {
                        System.out.println(a.toString());
                    }
                    break;
                case "lieux":

                    break;
                case "post":
                    String activite = Saisie.lireChaine("Choisissez une activité. \nTapez liste pour avoir une liste ");
                    if(activite.equals("liste")){
                        System.out.println("liste des activites obtenue avec services.selectallactivities");
                    }
                    //Services.postDemande(demande);
                    break;
                case "exit":
                    exit = true;
                    break;
                case "help":
                    
                default:
                    System.out.println("Commande invalide");
                    break;
            }

            /*if (user.isResponsable()) {
                switch (line) {
                    case "Events":
                        break;
                    case "AddLieu":
                        break;
                    default:
                        break;
                }
            }*/

        }
    }
}
