package modele;

import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import modele.Lieu;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2016-03-18T18:04:04")
@StaticMetamodel(Evenement.class)
public class Evenement_ { 

    public static volatile SingularAttribute<Evenement, Long> id;
    public static volatile SingularAttribute<Evenement, Lieu> lieu;
    public static volatile SingularAttribute<Evenement, Integer> SOLO;
    public static volatile SingularAttribute<Evenement, Integer> typeEquipe;
    public static volatile SingularAttribute<Evenement, Integer> TEAM;

}