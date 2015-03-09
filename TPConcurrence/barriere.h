/* Ce fichier sert pour  :
 * 1-associer des noms aux semaphores Unix ,
 * 2-donner le nom du fichier contenant la variable 
 * partagee entre les acteurs attendevant la barriere .
 */


/* Les  semaphores utilises */
#define VERROU     "/verrou2012"
#define BARRIERE  "/barr2012"

/* Le fichier contenant nbre_acteur */
#define FICACTEURS "acteurs.dat"
