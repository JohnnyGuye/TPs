package modele;

import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import modele.Activite;
import modele.Adherent;
import modele.Evenement;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2016-03-26T11:57:27")
@StaticMetamodel(Demande.class)
public class Demande_ { 

    public static volatile SingularAttribute<Demande, Long> id;
    public static volatile SingularAttribute<Demande, Integer> numeroTeam;
    public static volatile SingularAttribute<Demande, Activite> activite;
    public static volatile SingularAttribute<Demande, Evenement> evenement;
    public static volatile SingularAttribute<Demande, Adherent> adherent;
    public static volatile SingularAttribute<Demande, Date> date;

}