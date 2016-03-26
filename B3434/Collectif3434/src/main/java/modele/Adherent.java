package modele;

import com.google.maps.model.LatLng;
import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import util.GeoTest;
//enllver mdp et responsable
 
@Entity
public class Adherent implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String nom;
    private String prenom;
    private String mail;
    private String adresse;
    private Double longitude;
    private Double latitude;
    private String motDePasse;
    private String responsable; //Responsable ou Adherent

 
    public Adherent() {
    }

    public Adherent(String nom, String prenom, String adresse, String mail) {
        this.nom = nom;
        this.prenom = prenom;
        this.mail = mail;
        this.adresse = adresse;
        this.setCoordonnees(GeoTest.getLatLng(adresse));
        this.responsable = "Adherent";
    }

    public Long getId() {
        return id;
    }

    public String getNom() {
        return nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public String getMail() {
        return mail;
    }

    public String getAdresse() {
        return adresse;
    }

    public Double getLongitude() {
        return longitude;
    }

    public Double getLatitude() {
        return latitude;
    }
    
    public boolean compare(String mdp){
        return (encrypt(mdp).equals(motDePasse));
    }
    
    public void setMdp(String mdp){
        this.motDePasse = encrypt(mdp);
    }
    
    protected static String encrypt(String mdp){
        String str = "";
        int clé = 20;
        for(int i = 0; i < mdp.length() ; i++){
             str += (char)((mdp.charAt(i) + i + clé) % 256);
        }
        return str;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    public void setAdresse(String adresse) {
        this.adresse = adresse;
    }

    public void setCoordonnees(LatLng latLng) {
        this.longitude = latLng.lng;
        this.latitude = latLng.lat;
    }

       public String getMotDePasse() {
        return motDePasse;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

    public boolean isResponsable() {
        return responsable.equals("Responsable");
    }

    public void setResponsable(String responsable) {
        this.responsable = "Responsable";
    }
    public void setAdherent(String responsable){
        this.responsable = "Adherent";
    }
    
    @Override
    public String toString() {
        return "Adherent{" + "id=" + id + ", nom=" + nom + ", prenom=" + prenom + ", mail=" + mail + ", adresse=" + adresse + ", longitude=" + longitude + ", latitude=" + latitude + '}';
    }
}