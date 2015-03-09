/* Ce fichier sert pour  :
 * 1-associer des noms aux semaphores Unix ,
 * 2-donner le nom du fichier contenant la variable 
 * nbre_lecteur utilisee dans les fonctions
 * premier et dernier.
 */

/* Les  semaphores utilises */
#define VERROU "/sem88"
#define VERROULEC "/sem99"
#define VERROUANTIFAMINE "/sem11"

/* Le fichier contenant nbre_lecteur */
#define FICLEC "lecteurs.dat"
