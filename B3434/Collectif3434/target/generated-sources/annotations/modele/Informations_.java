package modele;

import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import modele.Adherent;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2016-04-01T13:11:57")
@StaticMetamodel(Informations.class)
public class Informations_ { 

    public static volatile SingularAttribute<Informations, Long> id;
    public static volatile SingularAttribute<Informations, Boolean> responsable;
    public static volatile SingularAttribute<Informations, Adherent> adherent;
    public static volatile SingularAttribute<Informations, String> password;

}