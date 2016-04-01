/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vue;

import dao.JpaUtil;
import java.util.Date;
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
        /*List<Evenement> evenements =Services.selectUnassignedEvents();
        List<Lieu> lieux = Services.selectAllLieux();
        if(lieux.isEmpty()){
            System.out.println("lieux vide");
        }else if(evenements.isEmpty()){
            System.out.println("evenements vide");
        }else{
            Services.assignLocationToEvent(evenements.get(0), lieux.get(0));
        }*/
        Adherent user = new Adherent();
        Informations auth = new Informations();
        boolean login = false;
        boolean exit = false;

        System.out.println("TESTS -- TESTS -- TESTS");

        while (!exit) {

            String line = Saisie.lireChaine("Choisissez une action, help pour une liste des actions possibles.");

            switch (line) {
                case "register": {
                    //setters sur user
                    user.setNom(Saisie.lireChaine("Votre prénom ?"));
                    user.setPrenom(Saisie.lireChaine("Votre nom ?"));
                    user.setMail(Saisie.lireChaine("Votre mail ?"));
                    user.setAdresse(Saisie.lireChaine("Adresse ?"));
                    auth.setPassword(Saisie.lireChaine("Mot de passe?"));
                    auth.setResponsable(Saisie.lireChaine("Responsable?").equals("oui"));
                    //user.setCoordonnee();
                    auth.setAdherent(user);
                    login = (Services.register(auth) != 0);
                    break;
                }
                case "login": {
                    String mail = Saisie.lireChaine("Mail ?");
                    String mdp = Saisie.lireChaine("Mot de passe ?");
                    try {
                        auth = Services.identification(mail, mdp);
                        if (auth.getAdherent().getMail().equals(mail)) {
                            System.out.println("Bonjour " + auth.getAdherent().getPrenom());
                            user=auth.getAdherent();
                            login = true;
                        }
                    } catch (NullPointerException npe) {

                    } catch (Throwable ex) {
                        Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
                break;
                case "first": {
                    String mail = Saisie.lireChaine("Mail ?");
                    String mdp = Saisie.lireChaine("Mot de passe ?");
                    try {
                        auth = Services.premiereConnexion(mail, mdp);
                        if (auth.getAdherent().getMail().equals(mail)) {
                            System.out.println("Bonjour " + auth.getAdherent().getPrenom());
                        }
                    } catch (NullPointerException npe) {

                    } catch (Throwable ex) {
                        Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
                break;
                case "logout": {
                    user = new Adherent();
                    auth = new Informations();
                    login = false;
                    break;
                }
                case "activities": {
                    List<Activite> activities = Services.selectAllActivities();
                    for (Activite a : activities) {
                        System.out.println(a.toStringForUser());
                    }
                    if (activities.isEmpty()) {
                        System.out.println("Aucune activite???");
                    }
                    break;
                }
                case "lieux": {
                    List<Lieu> lieux = Services.selectAllLieux();
                    for (Lieu l : lieux) {
                        System.out.println(l.stringListe());
                    }
                    break;
                }
                case "post": {
                    if (login) {
                        line = Saisie.lireChaine("Choisissez une activité. \nTapez liste pour avoir une liste \n Ou retour pour revenir");
                        boolean activite = false;
                        boolean fin = false;
                        Activite act;
                        Demande dem = new Demande();
                        dem.setAdherent(user);
                        while (!activite) {
                            switch (line) {
                                case "retour": {
                                    fin = true;
                                    activite = true;
                                    break;
                                }
                                case "liste": {
                                    List<Activite> activities = Services.selectAllActivities();
                                    for (Activite a : activities) {
                                        System.out.println("[" + a.getId() + "]: " + a.getDenomination());
                                    }
                                    line = Saisie.lireChaine("Choisissez une activite ");
                                    break;
                                }
                                default: {
                                    List<Activite> list = Services.selectActivitiesByName(line);
                                    if (list.isEmpty()) {
                                        line = Saisie.lireChaine("Activite:" + line + " non trouve, choisissez une autre activite ");
                                    } else {
                                        act = list.get(0);
                                        System.out.println("[" + act.getId() + "]: " + act.getDenomination());
                                        activite = true;
                                        dem.setActivite(act);
                                    }
                                    break;
                                }
                            }
                        }
                        if (!fin) {
                            int jour = Saisie.lireInteger("Jour :");
                            int mois = Saisie.lireInteger("Mois :");
                            int annee = Saisie.lireInteger("Annee: ");
                            if(annee<2000){
                                annee+=2000;
                                System.out.println(annee);
                            }
                            Date date;
                            date = JpaUtil.creerDate(jour + "/" + mois + "/" + annee);
                            dem.setDate(date);
                            Services.postDemande(dem);
                        }
                    } else {
                        System.out.println("Il faut etre identifie pour pouvoir faire cette action");
                    }
                    break;
                }
                case "affecter": {
                    if (auth.isResponsable()) {
                        int nEvt = Saisie.lireInteger("Numero  Evenement?");
                        int nLieu = Saisie.lireInteger("Lieu?");
                        Lieu l;
                        Evenement evt;

                        try {
                            l = Services.selectLieuByNumber(nLieu);
                            evt = Services.selectEventByNumber((long) nEvt);
                            Services.assignLocationToEvent(evt, l);
                        } catch (Throwable ex) {
                            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
                        }
                        ;
                    } else {
                        System.out.println("Vous devez etre identifie en tant que responsable pour faire cette action");
                    }
                    break;
                }
                case "events": {
                    List<Evenement> evenements = Services.selectAllEvents();
                    for (Evenement e : evenements) {
                        System.out.println(e.stringListe());
                    }
                    break;
                }
                case "exit":
                    exit = true;
                    break;
                case "help":
                    System.out.println("exit :\n quitte l'application\nlogin:\n pour s'identifier \npost:\n pour poster une demande\nactivities:\n liste les activites");
                    if(auth.isResponsable()){
                        System.out.println("events:\n liste les evenements ! marque les evenements a affecter un lieu\naffecter:\n pour affecter un lieu\n lieux:\n liste les lieux disponibles");
                    }
                default:
                    System.out.println("Commande invalide, help pour afficher la liste de commandes");
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
