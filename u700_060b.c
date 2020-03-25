
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
    "J:\\V34\\AsterSrv\\projets\\u700_060b\\u700_060b.pc"
};


static unsigned long sqlctx = 269001493;


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
            void  *sqhstv[2];
   unsigned int   sqhstl[2];
            int   sqhsts[2];
            void  *sqindv[2];
            int   sqinds[2];
   unsigned int   sqharm[2];
   unsigned int   *sqharc[2];
   unsigned short  sqadto[2];
   unsigned short  sqtdso[2];
} sqlstm = {10,2};

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
5,0,0,1,34,0,122,309,0,0,1,1,0,1,0,1,9,0,0,
24,0,0,2,33,0,122,310,0,0,1,1,0,1,0,1,3,0,0,
43,0,0,3,19,0,122,327,0,0,1,1,0,1,0,1,3,0,0,
62,0,0,4,23,0,122,343,0,0,2,2,0,1,0,1,9,0,0,1,3,0,0,
};


/*
---------------------------------------------------------------------------
 Fichier			: U700_060B.pc
 Date creation		: 06-12-1999
 Auteur          	: FAU

 Logiciel			: ASTER
 sous-systeme		: MES
 Description		: Constitution des dépêche
                     1. demande la fermeture des messages de notification   
                        pièce (u700_061b)                                   
                     2. appelle la fonction de constitution des dépêches    
                        (u700_060b)                                         
                     3. déplace les fichiers constitués vers les repeertoires
                        appropries (u700_060b)                    

 parametres entree	:                                                
    1- Nom du fichier de configuration generale ASTER (emplacement.cfg)                                 
    2- Nom de l'instance ORACLE                                      
    3- Nom de l'utilisateur ORACLE                                   
    4- Fichier des utilisateurs  (optionnel: si non fourni, doit etre indique dans le fichier config)
    5- Fichier des messages d'erreur (optionnel: si non fourni, doit etre indique dans le fichier config)
    6- Site destinatiaire de la depeche (optionnel)
    7- Niveau de trace en cas de lancement en mode debug
                                                                     
 parametres sortie :                                                
    neant                                                            
---------------------------------------------------------------------------
 Version         	: @(#) U700_060B version 2.0-1.2 
---------------------------------------------------------------------------

	--------------------------------------------------------------------
	Fonction		|version	|Date	    	|Initiales	|Commentaires 		
	--------------------------------------------------------------------
@(#)	U700_060B	| 1.0-1.0	|06/12/1999 | FAU	| Creation 
@(#)	U700_060B 	| 2.0-1.1	|02/02/2001 | SNE	| Reecriture/Adaptations pour modifications portage NT
@(#)	U700_060B 	| 2.0-1.2	|17/10/2001 | SNE	| Correction d'anomalies liées à la version 2.05
---------------------------------------------------------------------------
*/ 


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../commun/commun.h"
#include "../commun/combase.h"
#include "../commun/commes.h"

#define U700_060B_NOM_PROGRAMME	"u700_060b"
#define U700_060B_LIB_PROGRAMME	U700_060B_NOM_PROGRAMME " - Constitution des depeches"
#define U700_060B_VERSION_FICHIER	"1.2"

#define U700_060B_MSG_ERR_SYNTAXE	" %s <fichier cfg> <instance> <utilisateur> [<fichier utilisateurs>] [<fichier erreur>] [<site>] [<niveau de trace>] ==> niveau de gravite 5\n"
#define U700_060B_MSG_ERR_VAR_ENV	CMES_MSG_ERR_VAR_ENV


#define U700_060B_ERR_000001	COMMUN_ERR_000001
#define U700_060B_ERR_000002	COMMUN_ERR_000002
#define U700_060B_ERR_000003	COMMUN_ERR_000003
#define U700_060B_ERR_000004	COMMUN_ERR_000004
#define U700_060B_ERR_000005	COMMUN_ERR_000005
#define U700_060B_ERR_000007	COMMUN_ERR_000007
#define U700_060B_ERR_000010	COMMUN_ERR_000010
#define U700_060B_ERR_000015	COMMUN_ERR_000015

#define U700_060B_NBRE_PARAM_MIN	4
#define U700_060B_NBRE_PARAM_MAX	8

#define U700_060B_PARAM_FIC_CFG	1

#define U700_060B_PARAM_INSTANCE	2
#define U700_060B_PARAM_UTIL		3
#define U700_060B_PARAM_FIC_UTIL	4
#define U700_060B_PARAM_FIC_ERR		5
#define U700_060B_PARAM_SITE		6
#define U700_060B_PARAM_NIVEAU_DBG	7

#define U700_060B_TOUS_SITES	"%%"
#define U700_060B_LG_ENVIRONNEMENT	2
#define U700_060B_LG_CHP_SITE		6
#define U700_060B_LG_SITE_DEPART	U700_060B_LG_CHP_SITE
#define U700_060B_LG_SITE_DEST	U700_060B_LG_CHP_SITE
#define U700_060B_LG_SITE_ROUTAGE	U700_060B_LG_CHP_SITE
#define U700_060B_LG_NUM_DEPECHE	3

#define U700_060B_LG_NOM_REPERTOIRE	121
#define U700_060B_LG_NOM_FICHIER	50

/* EXEC SQL BEGIN DECLARE SECTION; */ 


  /* VARCHAR sql_site[6]; */ 
struct { unsigned short len; unsigned char arr[6]; } sql_site;

  /* VARCHAR u700_060b_sql_site[6]; */ 
struct { unsigned short len; unsigned char arr[6]; } u700_060b_sql_site;


  int u700_060b_sql_retour;

  /* VARCHAR u700_060b_fichier_trace_exec[256]; */ 
struct { unsigned short len; unsigned char arr[256]; } u700_060b_fichier_trace_exec;

  int u700_060b_niveau_trace;

/* EXEC SQL END DECLARE SECTION; */ 

/* EXEC SQL INCLUDE sqlca;
 */ 
/*
 * $Header: \Referentiel/aster v430x/distrib_poste/distribution/AsterSrv/projets/u700_060b/u700_060b.c,v 1.1 2010/02/02 08:53:15 ilaronde-cp Exp $ sqlca.h 
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


COMMUN_t_contexte_exec u700_060b_ctx_exec;
static char U700_060B_version_fichier[]="@(#) " U700_060B_LIB_PROGRAMME " version "COMMUN_VERSION_ASTER"-"U700_060B_VERSION_FICHIER" - "__DATE__ " "__TIME__;

char	u700_060b_instance[10]
	, u700_060b_user[80]
  	, u700_060b_rep_batch[U700_060B_LG_NOM_REPERTOIRE]
  	, u700_060b_rep_log_mes[U700_060B_LG_NOM_REPERTOIRE]
  	, u700_060b_rep_travail[U700_060B_LG_NOM_REPERTOIRE]
	, u700_060b_separateur[2]
	, u700_060b_separateur_var_path[2]
	, u700_060b_fichier_utilisateur[80]
	;
char u700_060b_environnement[U700_060B_LG_ENVIRONNEMENT];
char u700_060b_site_depart[U700_060B_LG_SITE_DEPART];
char u700_060b_site_dest[U700_060B_LG_SITE_DEST];
char u700_060b_numero_depeche[U700_060B_LG_NUM_DEPECHE];
char u700_060b_site_routage[U700_060B_LG_SITE_ROUTAGE]
	, u700_060b_rep_depart[U700_060B_LG_NOM_REPERTOIRE]
	, u700_060b_rep_archive[U700_060B_LG_NOM_REPERTOIRE];
char u700_060b_fichier_donnees[U700_060B_LG_NOM_REPERTOIRE+U700_060B_LG_NOM_FICHIER];
char u700_060b_destination[U700_060B_LG_NOM_REPERTOIRE+U700_060B_LG_NOM_FICHIER];
char u700_060b_extension[6] = "x.xyz";
int u700_060b_retour;


/*
 ====================================================================================
   Nom 		: U700_060B_move_fichier
   Description 	: Cette fonction est appelee par la fonctions COMMUN_Traiter_Liste_Fichiers
			: qui contitue la liste des fichiers a traiter, puis pour chacun de ces fichiers
			: appelle cette fonction chargee de le traiter.
   Auteur		: Sofiane NEKERE
   Date creation	: 02/02/2001
   parametres    	: 
      <p_nom_fichier>	: Nom du fichier a traiter; le nom du fichier n'inclut pas sa localisation (nom de repertoire)
   Retour		: 
				- OK - Traitement reussi
				- KO - Anomalie
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   U700_060B_move_fichier	|09/02/2001	| SNE		| Creation (@fonction)
 ====================================================================================
*/

int U700_060B_move_fichier(char *p_nom_fichier)
{

   memset(u700_060b_site_routage, 0, U700_060B_LG_SITE_ROUTAGE);
   memset(u700_060b_environnement, 0, U700_060B_LG_ENVIRONNEMENT);
   memset(u700_060b_site_depart, 0, U700_060B_LG_SITE_DEPART);
   memset(u700_060b_site_dest, 0, U700_060B_LG_SITE_DEST);
   memset(u700_060b_numero_depeche, 0, U700_060B_LG_NUM_DEPECHE);

   memset(u700_060b_site_routage, 0, U700_060B_LG_NOM_REPERTOIRE);
   memset(u700_060b_rep_depart, 0, U700_060B_LG_NOM_REPERTOIRE);
   memset(u700_060b_rep_archive, 0, U700_060B_LG_NOM_REPERTOIRE);

   memset(u700_060b_fichier_donnees, 0, U700_060B_LG_NOM_REPERTOIRE+U700_060B_LG_NOM_FICHIER);
   memset(u700_060b_destination, 0, U700_060B_LG_NOM_REPERTOIRE+U700_060B_LG_NOM_FICHIER);

   sprintf(u700_060b_fichier_donnees, "%s%s%s\0", u700_060b_rep_travail, u700_060b_separateur, p_nom_fichier);
   CBASE_Change_mode(u700_060b_fichier_donnees, COMMUN_UNIX_MODE_TOUS COMMUN_UNIX_MODE_ADD COMMUN_UNIX_MODE_READ COMMUN_UNIX_MODE_WRITE COMMUN_UNIX_MODE_EXE );

   /* SNE, Le repertoire de depart doit etre defini et exister */
   if ( CMES_verif_rep(CMES_PARAM_REP_DEPART, u700_060b_rep_depart) == KO ) {
	return(KO);
   }

   /* SNE, Le repertoire d'archivage des depeches doit etre defini et exister */
   if ( ( u700_060b_retour = CMES_verif_rep(CMES_PARAM_REP_ARCH_REC, u700_060b_rep_archive)) == OK ) {
   	/* On decompose le fichier afin d'en extraire les composants du nom */
	  if ( (u700_060b_retour=CMES_decompose_nom_fichier(p_nom_fichier, u700_060b_environnement, u700_060b_site_depart, u700_060b_site_dest, u700_060b_numero_depeche)) == OK) {

	   	    /* SNE, Determination du site de routage pour la depeche */
		   if ( CMES_site_routage(u700_060b_site_dest, u700_060b_site_routage) != OK){
			/* SNE, Routage direct : le site de routage c'est le site destinataire */
			strcpy(u700_060b_site_routage, u700_060b_site_dest);
		   }

		    /* SNE, On verifie l'existence du repertoire de routage de la depeche; au besoin on le cree */
	 	   sprintf(u700_060b_destination, "%s%s%s\0", u700_060b_rep_depart, u700_060b_separateur, u700_060b_site_routage);
		   if ( (u700_060b_retour=CMES_verif_cre_rep(u700_060b_destination, CMES_OPTION_CRE_REP)) == OK){

			  /* SNE, On copie le fichier dans le repertoire de routage */
			   sprintf(u700_060b_destination, "%s%s%s\0", u700_060b_destination, u700_060b_separateur, p_nom_fichier);
			   if ( (u700_060b_retour=COMMUN_recopie_fichier(u700_060b_fichier_donnees, u700_060b_destination)) == OK){
			  	/* SNE, Enfin on archive le fichier */
				   sprintf(u700_060b_destination, "%s%s%s\0", u700_060b_rep_archive, u700_060b_separateur, p_nom_fichier);
				   if ( (u700_060b_retour = COMMUN_move_fichier(u700_060b_fichier_donnees, u700_060b_destination, COMMUN_CP_ECRASE_FICHIER)) != OK)
		    				CBASE_affiche_message(COMMUN_ERR_000019,  COMMUN_BALISE_ERREUR,  u700_060b_fichier_donnees,  u700_060b_destination, NULL);
			   }
			   else{
		    		CBASE_affiche_message(COMMUN_ERR_000018,  COMMUN_BALISE_ERREUR,  u700_060b_fichier_donnees,  u700_060b_destination, NULL);
			   }
		   }
	   }
     }
 return(u700_060b_retour);
}


/*
 ====================================================================================
   Nom 		: main
   Description 	: Programme principal
   Auteur		: Sofiane NEKERE
   Date creation	: 02/02/2001
   Retour		:
     			: 0 : Traitement correctement effectué
				: 1 : Traitement terminé avec des erreurs
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
  char v_errorfile[256];


  int v_retour;

  /* analyse des paramètres */

  memset(&u700_060b_ctx_exec, 0, sizeof(COMMUN_t_contexte_exec));
  strcpy(u700_060b_ctx_exec.nom_programme, argv[0]);
  u700_060b_ctx_exec.niveau_debug = COMMUN_DEBUG_SANS_DEBUG;
  u700_060b_ctx_exec.mode_trace = COMMUN_TRACE_DANS_FIC;

  if ( argc < U700_060B_NBRE_PARAM_MIN || argc > U700_060B_NBRE_PARAM_MAX ) {
    COMMUN_ecrit_log_var(BALISE_INFORMATIVE, "\n%s\n" , U700_060B_version_fichier+4);
    COMMUN_ecrit_log_var(BALISE_ERREUR, U700_060B_MSG_ERR_SYNTAXE,  *argv);
    exit(1);
    }


  strcpy(u700_060b_instance, argv[U700_060B_PARAM_INSTANCE]);
  strcpy(u700_060b_user, argv[U700_060B_PARAM_UTIL]);
  strcpy(u700_060b_ctx_exec.fichier_config, argv[U700_060B_PARAM_FIC_CFG]);

  if (argc > U700_060B_PARAM_FIC_UTIL)
  	strcpy(u700_060b_fichier_utilisateur, argv[U700_060B_PARAM_FIC_UTIL]);
  else{
      if (COMMUN_lire_info(u700_060b_ctx_exec.fichier_config, u700_060b_instance, COMMUN_VAR_FIC_UTIL, u700_060b_fichier_utilisateur) != OK){
    		COMMUN_ecrit_log_var(BALISE_ERREUR, U700_060B_MSG_ERR_VAR_ENV, COMMUN_VAR_FIC_UTIL, u700_060b_ctx_exec.fichier_config);
		exit(KO);
	}
  }

  if (argc > U700_060B_PARAM_FIC_ERR)
	 strcpy(u700_060b_ctx_exec.fichier_erreur, argv[U700_060B_PARAM_FIC_ERR]);
  else{
      if (COMMUN_lire_info(u700_060b_ctx_exec.fichier_config, u700_060b_instance, COMMUN_VAR_FIC_ERR, u700_060b_ctx_exec.fichier_erreur) != OK){
   		COMMUN_ecrit_log_var(BALISE_ERREUR, U700_060B_MSG_ERR_VAR_ENV, COMMUN_VAR_FIC_ERR, u700_060b_ctx_exec.fichier_config);
		exit(KO);
	}
  }
  if (argc > U700_060B_PARAM_SITE)
	 strcpy(u700_060b_sql_site.arr, argv[U700_060B_PARAM_SITE]);
  else{
	 strcpy(u700_060b_sql_site.arr, U700_060B_TOUS_SITES);
  }
  u700_060b_sql_site.len = strlen(u700_060b_sql_site.arr);

  if (argc > U700_060B_PARAM_NIVEAU_DBG )
        u700_060b_ctx_exec.niveau_debug = atoi(argv[U700_060B_PARAM_NIVEAU_DBG]);


/*
	SNE, Fixation des parametres environnementaux lies au systeme d'exploitation
*/
  COMMUN_check_env(NULL, u700_060b_separateur, NULL, u700_060b_separateur_var_path);

  /*
  	SNE, 12/06/2001 : Initialisation des parametres de trace des procedures basées
  */
  memset(u700_060b_fichier_trace_exec.arr, 0, 256);
  memset(u700_060b_rep_log_mes, 0, U700_060B_LG_NOM_REPERTOIRE);
  u700_060b_fichier_trace_exec.len = 0;
  u700_060b_niveau_trace = u700_060b_ctx_exec.niveau_debug;
  if (COMMUN_lire_info(u700_060b_ctx_exec.fichier_config, u700_060b_instance, COMMUN_VAR_MES_LOG, u700_060b_rep_log_mes) == OK){
	sprintf(u700_060b_fichier_trace_exec.arr, "%s%s" U700_060B_NOM_PROGRAMME ".log\0", u700_060b_rep_log_mes, u700_060b_separateur);
	u700_060b_fichier_trace_exec.len = strlen(u700_060b_fichier_trace_exec.arr);
  }
  COMMUN_init_param_execution(u700_060b_ctx_exec);


  /* récupération du mot de passe */
  /* connection ORACLE */
  /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 

  if ( CBASE_connexion_base(u700_060b_ctx_exec.fichier_config, u700_060b_instance, u700_060b_fichier_utilisateur, u700_060b_user) != TRT_OK){
    CBASE_affiche_message(CMES_ERR_00002,  COMMUN_BALISE_ERREUR,  sqlca.sqlerrm.sqlerrmc,  NULL, NULL);
    exit(1);
  }

  /*
  	SNE, 12/06/2001 : Initialisation des parametres de trace des procedures basées
  */
  if (u700_060b_fichier_trace_exec.len > 0){
	  /* EXEC SQL CALL GLOBAL.INI_FICHIER_TRACE(:u700_060b_fichier_trace_exec); */ 

{
   struct sqlexd sqlstm;

   sqlstm.sqlvsn = 10;
   sqlstm.arrsiz = 1;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "call GLOBAL.INI_FICHIER_TRACE(:b0)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)256;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&u700_060b_fichier_trace_exec;
   sqlstm.sqhstl[0] = (unsigned int  )258;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	  /* EXEC SQL CALL GLOBAL.INI_NIVEAU_TRACE(:u700_060b_niveau_trace); */ 

{
   struct sqlexd sqlstm;

   sqlstm.sqlvsn = 10;
   sqlstm.arrsiz = 1;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "call GLOBAL.INI_NIVEAU_TRACE(:b0)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )24;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)256;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&u700_060b_niveau_trace;
   sqlstm.sqhstl[0] = (unsigned int  )4;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


  }
	  CBASE_affiche_message(COMMUN_INF_FTRACE,  COMMUN_BALISE_INFORMATIVE,  u700_060b_fichier_trace_exec.arr,  NULL, NULL);
  

  /* récupération de la valeur du paramètre base du répertoire d'arrivee des depeches */


  /* récupération de la valeur du paramètre base du répertoire d'arrivee des batchs */
  if ( CMES_get_param(CMES_PARAM_REP_BATCH, u700_060b_rep_batch) == KO) exit(1);

  /* récupération de la valeur du paramètre base du répertoire de travail */
  if ( CMES_get_param(CMES_PARAM_REP_TRAVAIL, u700_060b_rep_travail) == KO) exit(1);



  /* fermeture des messages de notification pièce */
  /* EXEC SQL CALL u700_061b(:u700_060b_sql_retour); */ 

{
  struct sqlexd sqlstm;

  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 1;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "call u700_061b(:b0)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )43;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&u700_060b_sql_retour;
  sqlstm.sqhstl[0] = (unsigned int  )4;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


  if (sqlca.sqlcode != 0) {
	CBASE_affiche_message(U700_060B_ERR_000004,  COMMUN_BALISE_ERREUR,  "u700_061b",  sqlca.sqlerrm.sqlerrmc, NULL);
	exit(1);
   }

  /* affichage des messages générés par la procédure u700_061b */
  sprintf(v_errorfile, "%s%su700_061b.err", u700_060b_rep_travail, u700_060b_separateur);
  COMMUN_afficher_fichier(v_errorfile);  

  if (u700_060b_sql_retour != 0) {
	CBASE_affiche_message(U700_060B_ERR_000015,  COMMUN_BALISE_ERREUR,  "u700_061b",  NULL, NULL);
    exit(1);
    }

  /* constitution des dépêches */
  /* EXEC SQL CALL u700_060b(:u700_060b_sql_site, :u700_060b_sql_retour); */ 

{
  struct sqlexd sqlstm;

  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 2;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "call u700_060b(:b0,:b1)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )62;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&u700_060b_sql_site;
  sqlstm.sqhstl[0] = (unsigned int  )8;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&u700_060b_sql_retour;
  sqlstm.sqhstl[1] = (unsigned int  )4;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


  if (sqlca.sqlcode != 0) {
	CBASE_affiche_message(U700_060B_ERR_000004,  COMMUN_BALISE_ERREUR,  "u700_060b",  sqlca.sqlerrm.sqlerrmc, NULL);
	exit(1);
  }

  /* affichage des messages générés par la procédure u700_060b     */
  sprintf(v_errorfile, "%s%su700_060b.err", u700_060b_rep_travail, u700_060b_separateur);
  COMMUN_afficher_fichier(v_errorfile);  
  if (u700_060b_sql_retour != 0) {
	CBASE_affiche_message(U700_060B_ERR_000015,  COMMUN_BALISE_ERREUR,  "u700_060b",  NULL, NULL);
    	exit(1);
  }
 
  /*
	SNE, Recherche de l'extension des fichiers a charger : par defaut *.dat
  */
  CMES_extension_fichiers_donnees(u700_060b_extension);

  /* appel du shell qui va demander le routage ou le chargement des dépêches */
  v_retour = COMMUN_Traiter_Liste_Fichiers(u700_060b_rep_travail, u700_060b_extension, U700_060B_move_fichier ) ;

  if (v_retour == OK)
	  CBASE_affiche_message(U700_060B_ERR_000007,  BALISE_INFORMATIVE,  u700_060b_ctx_exec.nom_programme,  NULL, NULL);
  else
	  CBASE_affiche_message(U700_060B_ERR_000010,  COMMUN_BALISE_ERREUR,  u700_060b_ctx_exec.nom_programme,  NULL, NULL);
  exit(v_retour);
 
} /* fin du main */  

