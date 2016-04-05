#détruit tout les sémaphores et mémoires partagées non détruit par le programme (fermeture brutale)
#De par son fonctionnement, s'il y a reboot de la session entre, il faut pas faire les deletions à la main
#nettoie aussi les canaux
ME=`whoami`
IPCS_S=`ipcs -s | grep -e "0x[0-9a-f]+ [0-9]+" | grep $ME | cut -f2 -d" "`
IPCS_M=`ipcs -m | grep -e "0x[0-9a-f]+ [0-9]+" | grep $ME | cut -f2 -d" "`
IPCS_Q=`ipcs -q | grep -e "0x[0-9a-f]+ [0-9]+" | grep $ME | cut -f2 -d" "`
for id in $IPCS_M; do ipcrm -m $id; done
for id in $IPCS_S; do ipcrm -s $id; done
for id in $IPCS_Q; do ipcrm -q $id; done
rm -f Canal*
