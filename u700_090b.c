
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned long magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[47];
};
static const struct sqlcxp sqlfpn =
{
    46,
    "J:\\V34\\AsterSrv\\projets\\u700_090b\\u700_090b.pc"
};


static unsigned long sqlctx = 268903093;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
            void  *sqhstv[1];
   unsigned int   sqhstl[1];
            int   sqhsts[1];
            void  *sqindv[1];
            int   sqinds[1];
   unsigned int   sqharm[1];
   unsigned int   *sqharc[1];
   unsigned short  sqadto[1];
   unsigned short  sqtdso[1];
} sqlstm = {10,1};

/* SQLLIB Prototypes */
extern void sqlcxt (void **, unsigned long *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlcx2t(void **, unsigned long *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlbuft(void **, char *);
extern void sqlgs2t(void **, char *);
extern void sqlorat(void **, unsigned long *, void *);

/* Forms Interface */
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern void sqliem(char *, int *);

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{10,4130,0,0,0,
};


/*
---------------------------------------------------------------------------
 Fichier         : U700_090B.pc
 Date creation   : 06-12-1999

 Logiciel          : ASTER                                           
 sous-systeme      : MES
 Description     : recoie les dépêches et les route (U700_031B) ou les charge (U700_032B)

 parametres entree :                                                
    1- Nom du fichier de configuration generale ASTER (emplacement.cfg)                                 
    2- Nom de l'instance ORACLE                                      
    3- Nom de l'utilisateur ORACLE                                   
    4- Fichier des utilisateurs                                      
    5- Fichier des messages d'erreur                                 
    6- Niveau de trace (pour debogage)
                                                                     
 parametres sortie :                                                
    neant                                                            
---------------------------------------------------------------------------
 Version         	: @(#) U700_090B version 2.1-1.2 
--------------------------------------------------------------------------

	--------------------------------------------------------------------
		Fonction	|Version	|Date    	|Initiales	|Commentaires 		
	--------------------------------------------------------------------
@(#)	U700_090B	|1.0-1.0	|06/12/1999 | FAU	| Creation 
@(#)	U700_090B 	|2.0-1.1	|02/02/2001 | SNE	| Reecriture/Adaptations pour modifications portage NT
@(#)	U700_090B 	|2.0-1.2	|24/09/2001 | SNE	| Correction ano 227 : Prise en compte modif U700_032B
@(#)	U700_090B 	|2.0-1.2	|18/10/2001 | SNE	| Repostionnement du pointeur de début de liste(tri de la liste des fichiers)
---------------------------------------------------------------------------
*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../commun/commun.h"
#include "../commun/combase.h"
#include "../commun/commes.h"

#define U700_090B_NOM_PROGRAMME	"U700_090B"
#define U700_090B_LIB_PROGRAMME	U700_090B_NOM_PROGRAMME ": Integration / routage des depeches"
#define U700_090B_VERSION_FICHIER	"1.2"

#define U700_090B_ERR_00001	CMES_ERR_00001		/* 542 : Utilisateur %1 non defini ...*/
#define U700_090B_ERR_00002	CMES_ERR_00002		/* 105 : Erreur Oracle %1 */
#define U700_090B_ERR_00003	CMES_ERR_00003		/* 159 : Parametre %1 non trouve */
#define U700_090B_ERR_00004	CMES_ERR_00004		/* 999 : Erreur pendant l'appel ... */
#define U700_090B_ERR_00005	CMES_ERR_00005		/* 196 : Le repertoire %1 n'existe pas */
#define U700_090B_ERR_00006	CMES_ERR_00006		/* 159 : Parametre %1 non trouve */
#define U700_090B_ERR_00007	CMES_ERR_00007		/* 178 : Fin sans erreur */
#define U700_090B_ERR_00010	CMES_ERR_00010		/* 179 : Fin avec erreur */

#define U700_090B_NB_PARAM_MIN		6
#define U700_090B_NB_PARAM_MAX		7
#define U700_090B_PARAM_FIC_CFG		1
#define U700_090B_PARAM_INSTANCE	2
#define U700_090B_PARAM_UTIL		3
#define U700_090B_PARAM_FIC_UTIL	4
#define U700_090B_PARAM_FIC_ERR		5
#define U700_090B_PARAM_NIV_TRC		6

#define U700_090B_LG_EXTENSION_FIC	121
#define U700_090B_LG_NOM_FICHIER	121
#define U700_090B_LG_ENVIRONNEMENT	2
#define U700_090B_LG_SITE_DEPART	6
#define U700_090B_LG_SITE_DEST	6
#define U700_090B_LG_NUM_DEPECHE	7
#define U700_090B_LG_LIGNE_COMMAND	1000


#define U700_090B_CHAR_ETOILE		CMES_CHAR_ETOILE
#define U700_090B_SEPARATEUR_MASK	CMES_SEPARATEUR_MASK
#define U700_090B_EXT_FIC_DONNEES	CMES_EXT_FIC_DONNEES

#define U700_090B_CHARGMT_DEPECHE 	"u700_032b"
#define U700_090B_ROUTAGE_DEPECHE 	"u700_031b"

/* EXEC SQL INCLUDE sqlca;
 */ 
/*
 * $Header: \Referentiel/aster v430x/distrib_poste/distribution/AsterSrv/projets/u700_090b/u700_090b.c,v 1.1 2010/02/02 08:53:18 ilaronde-cp Exp $ sqlca.h 
 */

/* Copyright (c) 1985,1986, 1998 by Oracle Corporation. */
 
/*
NAME
  SQLCA : SQL Communications Area.
FUNCTION
  Contains no code. Oracle fills in the SQLCA with status info
  during the execution of a SQL stmt.
NOTES
  **************************************************************
  ***                                                        ***
  *** This file is SOSD.  Porters must change the data types ***
  *** appropriately on their platform.  See notes/pcport.doc ***
  *** for more information.                                  ***
  ***                                                        ***
  **************************************************************

  If the symbol SQLCA_STORAGE_CLASS is defined, then the SQLCA
  will be defined to have this storage class. For example:
 
    #define SQLCA_STORAGE_CLASS extern
 
  will define the SQLCA as an extern.
 
  If the symbol SQLCA_INIT is defined, then the SQLCA will be
  statically initialized. Although this is not necessary in order
  to use the SQLCA, it is a good pgming practice not to have
  unitialized variables. However, some C compilers/OS's don't
  allow automatic variables to be init'd in this manner. Therefore,
  if you are INCLUDE'ing the SQLCA in a place where it would be
  an automatic AND your C compiler/OS doesn't allow this style
  of initialization, then SQLCA_INIT should be left undefined --
  all others can define SQLCA_INIT if they wish.

  If the symbol SQLCA_NONE is defined, then the SQLCA variable will
  not be defined at all.  The symbol SQLCA_NONE should not be defined
  in source modules that have embedded SQL.  However, source modules
  that have no embedded SQL, but need to manipulate a sqlca struct
  passed in as a parameter, can set the SQLCA_NONE symbol to avoid
  creation of an extraneous sqlca variable.
 
MODIFIED
    lvbcheng   07/31/98 -  long to int
    jbasu      12/12/94 -  Bug 217878: note this is an SOSD file
    losborne   08/11/92 -  No sqlca var if SQLCA_NONE macro set 
  Clare      12/06/84 - Ch SQLCA to not be an extern.
  Clare      10/21/85 - Add initialization.
  Bradbury   01/05/86 - Only initialize when SQLCA_INIT set
  Clare      06/12/86 - Add SQLCA_STORAGE_CLASS option.
*/
 
#ifndef SQLCA
#define SQLCA 1
 
struct   sqlca
         {
         /* ub1 */ char    sqlcaid[8];
         /* b4  */ int     sqlabc;
         /* b4  */ int     sqlcode;
         struct
           {
           /* ub2 */ unsigned short sqlerrml;
           /* ub1 */ char           sqlerrmc[70];
           } sqlerrm;
         /* ub1 */ char    sqlerrp[8];
         /* b4  */ int     sqlerrd[6];
         /* ub1 */ char    sqlwarn[8];
         /* ub1 */ char    sqlext[8];
         };

#ifndef SQLCA_NONE 
#ifdef   SQLCA_STORAGE_CLASS
SQLCA_STORAGE_CLASS struct sqlca sqlca
#else
         struct sqlca sqlca
#endif
 
#ifdef  SQLCA_INIT
         = {
         {'S', 'Q', 'L', 'C', 'A', ' ', ' ', ' '},
         sizeof(struct sqlca),
         0,
         { 0, {0}},
         {'N', 'O', 'T', ' ', 'S', 'E', 'T', ' '},
         {0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}
         }
#endif
         ;
#endif
 
#endif
 
/* end SQLCA */


COMMUN_t_contexte_exec u700_090b_ctx_exec;
static char U700_090B_version_fichier[]="@(#) " U700_090B_LIB_PROGRAMME	" version "COMMUN_VERSION_ASTER"-"U700_090B_VERSION_FICHIER" - "__DATE__ " "__TIME__;

char u700_090b_instance[10]
	, u700_090b_user[80]
  	, u700_090b_rep_batch[121]
	, u700_090b_site_local[6]
	, u700_090b_rep_arrivee[121]
	, u700_090b_fic_usr [256]
	;

/*
 ====================================================================================
		SNE, 12/10/2001 : Traitement des listes
*/

/*
	SNE, Definition de type pour liste chainee permettant de stocker les fichiers 
		et de les trier en même temps
*/
typedef struct U700_090B_liste{
  struct U700_090B_liste *precedent;
  char nom_fichier[U700_090B_LG_NOM_FICHIER];
  struct U700_090B_liste *suivant;
} t_liste_fichiers;

/*
	Déclaration de l'objet 'Liste chainee'
*/
t_liste_fichiers *U700_090B_liste_fichiers = NULL;

/*
		SNE, 12/10/2001 : Fin des définition pour traitement de listes
 ====================================================================================
*/


/*
 ====================================================================================
   Nom 		: u700_090B_init_membre
   Description 	: Fonction d'initialisation d'un nouvel élément de la liste
   Auteur		: Sofiane NEKERE
   Date creation	: 12/10/2001
   parametres    	: 
					  p_element : Element à initialiser
     
   Retour		: 
     			: OK - Le prise en compte du fichier s'est bien passé
				: KO - Le fichier n'a pu être inséré dans la liste (faute de mémoire);
   Historique	:
	---------------------------------------------------------------------------
	Fonction					|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   u700_090B_init_membre	|12/10/2001 | SNE		| Creation (@fonction)
 ====================================================================================
*/
void u700_090B_init_membre(t_liste_fichiers *p_element)
{
   p_element->precedent = NULL;
   p_element->suivant = NULL;
   memset(p_element->nom_fichier, 0, U700_090B_LG_NOM_FICHIER);
}


/*
 ====================================================================================
   Nom 		: u700_090b_inserer_avant
   Description 	: Fonction d'insertion d'un fichier dans la liste à une place quelconque
				: sachant l'element qui doit suivre
   Auteur		: Sofiane NEKERE
   Date creation	: 12/10/2001
   parametres    	: p_nom_fichier : Nom du fichier à ajouter à la liste
					  p_suivant	: Element devant suivre l'element en cours d'insertion
     
   Retour		: 
     			: OK - Le prise en compte du fichier s'est bien passé
				: KO - Le fichier n'a pu être inséré dans la liste (faute de mémoire);
   Historique	:
	---------------------------------------------------------------------------
	Fonction					|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   u700_090b_inserer_avant	|12/10/2001 | SNE		| Creation (@fonction)
 ====================================================================================
*/
int u700_090b_inserer_avant(char *p_nom_fichier, t_liste_fichiers **p_suivant)
{
  t_liste_fichiers *v_nouveau = NULL;
  t_liste_fichiers *v_precedent = NULL;

 v_precedent = (*p_suivant)->precedent;

  if ( (v_nouveau = malloc(sizeof(t_liste_fichiers))) != NULL) {
		u700_090B_init_membre(v_nouveau);
		strncpy(v_nouveau->nom_fichier, p_nom_fichier, U700_090B_LG_NOM_FICHIER-1);
		if (*p_suivant == NULL) 
			*p_suivant = v_nouveau;
		else{
			v_nouveau->suivant = *p_suivant;
			v_nouveau->precedent  = (*p_suivant)->precedent;
			(*p_suivant)->precedent = v_nouveau;
			if (v_precedent != NULL) v_precedent->suivant = v_nouveau;
		}
	return(OK);
  }
  return(KO);
}

/*
 ====================================================================================
   Nom 		: u700_090b_ajouter
   Description 	: Fonction d'ajout d'un fichier en fin de liste liste 
   Auteur		: Sofiane NEKERE
   Date creation	: 12/10/2001
   parametres    	: p_nom_fichier : Nom du fichier à ajouter à la liste
     
   Retour		: 
     			: OK - Le prise en compte du fichier s'est bien passé
				: KO - Le fichier n'a pu être inséré dans la liste (faute de mémoire);
   Historique	:
	---------------------------------------------------------------------------
	Fonction							|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   U700_090B_ajouter_fichier_liste	|12/10/2001 | SNE		| Creation (@fonction)
 ====================================================================================
*/
int u700_090b_ajouter(char *p_nom_fichier)
{
  t_liste_fichiers *v_index= NULL;
  t_liste_fichiers *v_nouveau = NULL;

  if ( (v_nouveau = malloc(sizeof(t_liste_fichiers))) != NULL) {
		u700_090B_init_membre(v_nouveau);
		strncpy(v_nouveau->nom_fichier, p_nom_fichier, U700_090B_LG_NOM_FICHIER-1);
		  if (U700_090B_liste_fichiers != NULL){
				for (v_index = U700_090B_liste_fichiers; v_index->suivant != NULL; v_index = v_index->suivant);
				v_index->suivant = v_nouveau;
				v_nouveau->precedent = v_index;
		  }
		  else
			U700_090B_liste_fichiers = v_nouveau;
   return(OK);
  }
  return(KO);
}

/*
 ====================================================================================
   Nom 		: U700_090B_ajouter_fichier_liste
   Description 	: Fonction principale d'ajout d'un fichier à la liste des fichiers 
				:  à traiter: Le fichier est inséré à la place qui doit être la sienne 
				: en respectant un ordre alphabétique
   Auteur		: Sofiane NEKERE
   Date creation	: 12/10/2001
   parametres    	: Aucun
     
   Retour		: 
     			: OK - Le prise en compte du fichier s'est bien passé
				: KO - Le fichier n'a pu être inséré dans la liste;
   Historique	:
	---------------------------------------------------------------------------
	Fonction							|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   U700_090B_ajouter_fichier_liste	|12/10/2001 | SNE	| Creation (@fonction)
@(#)   U700_090B_ajouter_fichier_liste	|18/10/2001 | SNE	| Repostionnement du pointeur de début de liste
 ====================================================================================
*/
int U700_090B_ajouter_fichier_liste(char *p_nom_fichier)
{
   t_liste_fichiers *v_place= NULL;
   t_liste_fichiers *v_index= NULL;
   int v_ret = OK;

   if (U700_090B_liste_fichiers == NULL){
		v_ret = u700_090b_ajouter(p_nom_fichier);
   }
   else{
	   for (v_place = U700_090B_liste_fichiers; v_place != NULL ; v_place = v_place->suivant)
	   {
		   if ( strcmp(v_place->nom_fichier, p_nom_fichier) >= 0) break;
	   }
	   if (v_place != NULL)
			v_ret = u700_090b_inserer_avant(p_nom_fichier, &v_place);
	   else
			v_ret = u700_090b_ajouter(p_nom_fichier);
	}

/* On se repositionne en début */
	while (U700_090B_liste_fichiers->precedent != NULL) 
	 U700_090B_liste_fichiers = U700_090B_liste_fichiers->precedent;
   return(v_ret);
}

/*
 ====================================================================================
   Nom 		: u700_090b_liberer
   Description 	: Libère la mémoire occupée par la liste des fichiers
   Auteur		: Sofiane NEKERE
   Date creation	: 12/10/2001
   parametres    	: Aucun
     
   Retour		:
     			: Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   u700_090b_liberer	|12/10/2001 | SNE		| Creation (@fonction)
 ====================================================================================
*/
void u700_090b_liberer(t_liste_fichiers *p_liste)
{
   if (p_liste->suivant != NULL)
      u700_090b_liberer(p_liste->suivant);
	free(p_liste);
	p_liste = NULL;
}


/*
 ====================================================================================
   Nom 		: U700_090B_traiter_fichier
   Description 	: Fonction d'aiguillage lors du traitement des fichiers depeches
			: Elle determine pour un fichier donne, le traitement (routage, chargement)
			: a lancer.
   Auteur		: Sofiane NEKERE
   Date creation	: 23/01/2001
   parametres    	:                                                     
     <p_result>  	: Variable receptacle (recoit le mot de passe en retour)
   Retour		:
     			: Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   U700_090B_traiter_fichier	|02/02/2001 | SNE		| Creation (@fonction)
@(#)   U700_090B_traiter_fichier	|25/09/2001 | SNE		| Ajout du paramètre 'flag réception manuelle' (Ano 227)
 ====================================================================================
*/

int U700_090B_traiter_fichier(char *p_nom_fichier)
{
   int v_retour;
   char v_environnement[U700_090B_LG_ENVIRONNEMENT];
   char v_site_depart[U700_090B_LG_SITE_DEPART];
   char v_site_dest[U700_090B_LG_SITE_DEST];
   char v_numero_depeche[U700_090B_LG_NUM_DEPECHE];
   char v_command[U700_090B_LG_LIGNE_COMMAND];

   memset(v_environnement, 0, U700_090B_LG_ENVIRONNEMENT);
   memset(v_site_depart, 0, U700_090B_LG_SITE_DEPART);
   memset(v_site_dest, 0, U700_090B_LG_SITE_DEST);
   memset(v_numero_depeche, 0, U700_090B_LG_NUM_DEPECHE);

    v_retour = CMES_decompose_nom_fichier(p_nom_fichier, v_environnement, v_site_depart, v_site_dest, v_numero_depeche);
    if (v_retour == OK){
	     memset(v_command, 0, U700_090B_LG_LIGNE_COMMAND);
	     if (strcmp(v_site_dest, u700_090b_site_local) == 0)
		  sprintf(v_command, U700_090B_CHARGMT_DEPECHE " %s %s %s %s %s %s %s 0 %d\0", u700_090b_ctx_exec.fichier_config, u700_090b_instance, u700_090b_user, p_nom_fichier, v_site_dest, u700_090b_fic_usr, u700_090b_ctx_exec.fichier_erreur, u700_090b_ctx_exec.niveau_debug);
	     else
		  sprintf(v_command, U700_090B_ROUTAGE_DEPECHE " %s %s %s %s %s %s %s\0", u700_090b_ctx_exec.fichier_config, u700_090b_instance, u700_090b_user, p_nom_fichier, v_site_dest, u700_090b_fic_usr, u700_090b_ctx_exec.fichier_erreur);
         switch( v_retour = COMMUN_lancer_commande(v_command, NULL, NULL) ){
			case TRT_OK:
			break;

			case COMMUN_CODE_FICHIER_INEXISTANT:
    				CBASE_affiche_message(COMMUN_ERR_00034,  COMMUN_BALISE_ERREUR
								,  (strcmp(v_site_dest, u700_090b_site_local) == 0)? (U700_090B_CHARGMT_DEPECHE):(U700_090B_ROUTAGE_DEPECHE)
								,  NULL, NULL);
			break;

			case CODE_FICHIER_VERROUILLE:
    				CBASE_affiche_message(COMMUN_ERR_00034,  COMMUN_BALISE_ERREUR
								,  (strcmp(v_site_dest, u700_090b_site_local) == 0)? (U700_090B_CHARGMT_DEPECHE):(U700_090B_ROUTAGE_DEPECHE)
								,  NULL, NULL);
			break;

			default:
				sprintf(v_command, "%d\0", v_retour);
    				CBASE_affiche_message(COMMUN_ERR_00026,  COMMUN_BALISE_ERREUR,  v_command,  NULL, NULL);
			break;
	    }
    }
    return (v_retour);
}


/*
 ====================================================================================
   Nom 		: U700_090B_Traiter_liste
   Description 	: Parcourt la liste des fichiers triée puis traite les dépêches correspondantes
   Auteur		: Sofiane NEKERE
   Date creation	: 12/10/2001
   parametres    	: Aucun
     
   Retour		:
     			: OK - Tous les fichiers ont été correctement traités
				: Autre (KO) : Problème lors du traitement d'un des fichiers 
   Historique	:
	---------------------------------------------------------------------------
	Fonction					|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   U700_090B_Traiter_liste	|12/10/2001 | SNE		| Creation (@fonction)
 ====================================================================================
*/

int U700_090B_Traiter_liste(void)
{
    t_liste_fichiers *v_element = NULL;
	int v_ret = OK;

	if (U700_090B_liste_fichiers != NULL){
		for (v_element = U700_090B_liste_fichiers; v_element != NULL; v_element = v_element->suivant)
		{
			v_ret = U700_090B_traiter_fichier(v_element->nom_fichier);
		}
		u700_090b_liberer(U700_090B_liste_fichiers);
	}
	return(v_ret);
}

/*
 ====================================================================================
   Nom 		: main
   Description 	: Programme principal
   Auteur		: Sofiane NEKERE
   Date creation	: 02/02/2001
   parametres    	:                                                     
     <p_result>  	: Variable receptacle (recoit le mot de passe en retour)
   Retour		:
     			: Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction	|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   main		| 02/02/2001 | SNE		| Creation (@fonction)
 ====================================================================================
*/


main(argc, argv)
  int argc;
  char *argv[];
{
  /* déclaration des variables */
  char  v_extension[U700_090B_LG_EXTENSION_FIC]
	;

  int lg_rec = 80;


  /* analyse des paramètres */

  if (argc < U700_090B_NB_PARAM_MIN || argc > U700_090B_NB_PARAM_MAX) {
    COMMUN_ecrit_log_var(BALISE_INFORMATIVE, "%s\n" , U700_090B_version_fichier+4);
    COMMUN_ecrit_log_var(COMMUN_BALISE_ERREUR, "u700_090b <fichcier cfg> <instance> <user> <user file> <error file> ==> niveau de gravité : 5\n");
    exit(1);
  }

  memset(&u700_090b_ctx_exec, 0, sizeof(COMMUN_t_contexte_exec));
  strcpy(u700_090b_ctx_exec.nom_programme, argv[0]);
  strcpy(u700_090b_instance, argv[U700_090B_PARAM_INSTANCE]);
  strcpy(u700_090b_user, argv[U700_090B_PARAM_UTIL]);
  strcpy(u700_090b_fic_usr, argv[U700_090B_PARAM_FIC_UTIL]);
  strcpy(u700_090b_ctx_exec.fichier_erreur, argv[U700_090B_PARAM_FIC_ERR]);
  strcpy(u700_090b_ctx_exec.fichier_config, argv[U700_090B_PARAM_FIC_CFG]);

  if (argc > U700_090B_PARAM_NIV_TRC)
	  u700_090b_ctx_exec.niveau_debug = atoi(argv[U700_090B_PARAM_NIV_TRC]);
  else
	  u700_090b_ctx_exec.niveau_debug = COMMUN_DEBUG_SANS_DEBUG;

  u700_090b_ctx_exec.mode_trace = COMMUN_TRACE_DANS_FIC;
  COMMUN_init_param_execution(u700_090b_ctx_exec);

  /* connection ORACLE */
  /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 

  if ( CBASE_connexion_base(u700_090b_ctx_exec.fichier_config, u700_090b_instance, u700_090b_fic_usr, u700_090b_user) != TRT_OK){
    CBASE_affiche_message(U700_090B_ERR_00002,  COMMUN_BALISE_ERREUR,  sqlca.sqlerrm.sqlerrmc,  NULL, NULL);
    exit(1);
  }

  /* récupération de la valeur du paramètre base du répertoire d'arrivee des depeches */
  if (CMES_verif_rep("IR0026", u700_090b_rep_arrivee) != TRT_OK) exit(1);

  /* récupération de la valeur du paramètre base du site local */ 
  memset(u700_090b_site_local, 0, 6);
  if (CMES_get_param("SM0008", u700_090b_site_local)  != TRT_OK) exit(1);

  /* récupération de la valeur du paramètre base du répertoire d'arrivee des batchs */
  if (CMES_verif_rep("IR0010", u700_090b_rep_batch) != TRT_OK) exit(1);

  /*
	SNE, Recherche de l'extension des fichiers a charger : par defaut *.dat
  */
  CMES_extension_fichiers_donnees(v_extension);

  /* appel du shell qui va demander le routage ou le chargement des dépêches */

  /*
		SNE, 12/10/2001 : Changement de la fonction appelée pour le traitement de la liste des 
		   fichiers
  */
  if (COMMUN_Traiter_Liste_Fichiers(u700_090b_rep_arrivee, v_extension, U700_090B_ajouter_fichier_liste) == TRT_OK){
    if ( U700_090B_Traiter_liste() == OK){
  		CBASE_affiche_message(U700_090B_ERR_00007,  COMMUN_BALISE_ERREUR,  u700_090b_ctx_exec.nom_programme,  NULL, NULL);
		exit(TRT_OK);
	}
  }
  CBASE_affiche_message(U700_090B_ERR_00010,  COMMUN_BALISE_ERREUR,  u700_090b_ctx_exec.nom_programme,  NULL, NULL);
  exit (KO);
} /* fin du main */  

