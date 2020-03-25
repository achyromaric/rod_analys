
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
    "J:\\V34\\AsterSrv\\projets\\u700_031b\\u700_031b.pc"
};


static unsigned long sqlctx = 269083493;


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
            void  *sqhstv[3];
   unsigned int   sqhstl[3];
            int   sqhsts[3];
            void  *sqindv[3];
            int   sqinds[3];
   unsigned int   sqharm[3];
   unsigned int   *sqharc[3];
   unsigned short  sqadto[3];
   unsigned short  sqtdso[3];
} sqlstm = {10,3};

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
5,0,0,1,94,0,4,209,0,0,3,2,0,1,0,2,9,0,0,1,9,0,0,1,9,0,0,
};


/*
---------------------------------------------------------------------------
 Fichier			: U700_031B.pc
 Date creation		: 06-12-1999
 Auteur          	: FAU

 Logiciel			: ASTER
 sous-systeme		: MES
 Description		: Route la dépêche passé en paramètre vers le bon répertoire de départ 

 parametres entree	:                                                
    1- Nom du fichier de configuration generale ASTER (emplacement.cfg)                                 
    2- Nom de l'instance ORACLE                                      
    3- Nom de l'utilisateur ORACLE                                   
    4- Nom du fichier depeche a charge
    5- Site destinatiaire de la depeche
    6- Fichier des utilisateurs  (optionnel: si non fourni, doit etre indique dans le fichier config)
    7- Fichier des messages d'erreur (optionnel: si non fourni, doit etre indique dans le fichier config)
                                                                     
 parametres sortie :                                                
    neant                                                            
---------------------------------------------------------------------------
 Version         	: @(#) U700_031B version 2.1-1.2
---------------------------------------------------------------------------

	--------------------------------------------------------------------
	Fonction		| version	|Date	    	|Initiales	|Commentaires 		
	--------------------------------------------------------------------
@(#)	U700_031B	|1.0-1.0|06/12/1999 | FAU	| Creation 
@(#)	U700_031B 	|2.0-1.1|02/02/2001 | SNE	| Reecriture/Adaptations pour modifications portage NT
@(#)	U700_031B 	|2.1-1.2|16/10/2001 | SNE	| Correction anomalies V2.05
---------------------------------------------------------------------------
*/ 



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../commun/commun.h"
#include "../commun/combase.h"
#include "../commun/commes.h"

#define U700_031B_NOM_PROGRAMME	"u700_031b"
#define U700_031B_LIB_PROGRAMME	U700_031B_NOM_PROGRAMME " - Routage des depeches"
#define U700_031B_VERSION_FICHIER	"1.2"

#define U700_031B_PARAM_FIC_CFG	1
#define U700_031B_PARAM_INSTANCE	2
#define U700_031B_PARAM_UTIL		3
#define U700_031B_PARAM_FIC_DAT	4
#define U700_031B_PARAM_SITE_DEST	5
#define U700_031B_PARAM_FIC_UTIL	6
#define U700_031B_PARAM_FIC_ERR	7

#define U700_031B_NBRE_PARAM_MIN	6
#define U700_031B_NBRE_PARAM_MAX	8

#define U700_031b_SANS_ERREUR		0
#define U700_031b_ENREG_NON_TROUVE	-100


#define U700_031B_MSG_ERR_SYNTAXE	" %s <fichier cfg> <instance> <utilisateur> <fichier de donnees> <destination> [<fichier utilisateurs>] [<fichier erreur>] ==> niveau de gravite 5\n"
#define U700_031B_MSG_ERR_VAR_ENV	CMES_MSG_ERR_VAR_ENV

/* EXEC SQL BEGIN DECLARE SECTION; */ 


  /* VARCHAR u700_031b_sql_site_dest[6]; */ 
struct { unsigned short len; unsigned char arr[6]; } u700_031b_sql_site_dest;

  /* VARCHAR u700_031b_sql_site_routage[6]; */ 
struct { unsigned short len; unsigned char arr[6]; } u700_031b_sql_site_routage;

  /* VARCHAR u700_031b_sql_site_courant[6]; */ 
struct { unsigned short len; unsigned char arr[6]; } u700_031b_sql_site_courant;


/* EXEC SQL END DECLARE SECTION; */ 

/* EXEC SQL INCLUDE sqlca;
 */ 
/*
 * $Header: \Referentiel/aster v430x/distrib_poste/distribution/AsterSrv/projets/u700_031b/u700_031b.c,v 1.1 2010/02/02 08:53:11 ilaronde-cp Exp $ sqlca.h 
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



char u700_031b_separateur[2]
	, u700_031b_separateur_var_path[2]
      , u700_031b_rep_arrivee[121]
      , u700_031b_rep_depart[121]
      , u700_031b_fichier[80]
      , u700_031b_fichier_utilisateur[80]
	, u700_031b_user[31]
	, u700_031b_instance[10]
      ;

int u700_031b_retour;

COMMUN_t_contexte_exec u700_031b_ctx_exec;
static char U700_031B_version_fichier[]="@(#) " U700_031B_LIB_PROGRAMME	" version "COMMUN_VERSION_ASTER"-"U700_031B_VERSION_FICHIER" - "__DATE__ " "__TIME__;

/*
 ====================================================================================
   Nom 		: U700_031b_non_trouve
   Description 	: Fonction d'utilite technique; declenche des qu'un requete ne ramene 
			: aucune ligne
   Auteur		: Sofiane NEKERE
   Date creation	: 02/02/2001
   parametres    	: Aucun
   Retour		: Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   U700_031b_non_trouve	|02/02/2001	| SNE		| Creation (@fonction)
 ====================================================================================
*/
void U700_031b_non_trouve(void)
{
    u700_031b_retour = U700_031b_ENREG_NON_TROUVE;
}

/*
 ====================================================================================
   Nom 		: main
   Description 	: Programme principal
   Auteur		: Sofiane NEKERE
   Date creation	: 23/01/2001
   parametres    	:                                                     
     <argc>  	: nombre de parametres de la ligne de commande
     <argv>  	: tableau des parametres de la lignes de commande
   Retour		:
     			:  - OK : traitement reussi
			:  - Autre : Probleme
   Historique	:
	---------------------------------------------------------------------------
	Fonction	|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   main		|02/02/2001	| SNE		| Creation (@fonction)
@(#)   main		|16/10/2001	| SNE		| Modification de la création des répertoires
 ====================================================================================
*/
main(argc, argv)
  int argc;
  char *argv[];
{

  /* déclaration des variables */
  char  v_tmp1[512]
	 , v_tmp2[512]
	;


  /* analyse des paramètres */
  memset(&u700_031b_ctx_exec, 0, sizeof(COMMUN_t_contexte_exec));
  strcpy(u700_031b_ctx_exec.nom_programme, argv[0]);

  if ( argc < U700_031B_NBRE_PARAM_MIN || argc > U700_031B_NBRE_PARAM_MAX ) {
    COMMUN_ecrit_log_var(BALISE_INFORMATIVE, "\n%s\n" , U700_031B_version_fichier+4);
    COMMUN_ecrit_log_var(BALISE_ERREUR, U700_031B_MSG_ERR_SYNTAXE,  *argv);
    exit(1);
    }


  strcpy(u700_031b_instance, argv[U700_031B_PARAM_INSTANCE]);
  strcpy(u700_031b_user, argv[U700_031B_PARAM_UTIL]);
  strcpy(u700_031b_ctx_exec.fichier_config, argv[U700_031B_PARAM_FIC_CFG]);
  strcpy(u700_031b_fichier, argv[U700_031B_PARAM_FIC_DAT]);
  strcpy(u700_031b_sql_site_dest.arr, argv[U700_031B_PARAM_SITE_DEST]);
  u700_031b_sql_site_dest.len = strlen(u700_031b_sql_site_dest.arr);

  if (argc > U700_031B_PARAM_FIC_UTIL)
  	strcpy(u700_031b_fichier_utilisateur, argv[U700_031B_PARAM_FIC_UTIL]);
  else{
      if (COMMUN_lire_info(u700_031b_ctx_exec.fichier_config, u700_031b_instance, COMMUN_VAR_FIC_UTIL, u700_031b_fichier_utilisateur) != OK){
		COMMUN_ecrit_log_var(BALISE_ERREUR, U700_031B_MSG_ERR_VAR_ENV, COMMUN_VAR_FIC_UTIL, u700_031b_ctx_exec.fichier_config);
		exit(KO);
	}
  }

  if (argc > U700_031B_PARAM_FIC_ERR)
	 strcpy(u700_031b_ctx_exec.fichier_erreur, argv[U700_031B_PARAM_FIC_ERR]);
  else{
      if (COMMUN_lire_info(u700_031b_ctx_exec.fichier_config, u700_031b_instance, COMMUN_VAR_FIC_ERR, u700_031b_ctx_exec.fichier_erreur) != OK){
		COMMUN_ecrit_log_var(BALISE_ERREUR, U700_031B_MSG_ERR_VAR_ENV, COMMUN_VAR_FIC_ERR, u700_031b_ctx_exec.fichier_config);
		exit(KO);
	}
  }

		

  u700_031b_ctx_exec.niveau_debug = COMMUN_DEBUG_SANS_DEBUG;
  u700_031b_ctx_exec.mode_trace = COMMUN_TRACE_DANS_FIC;
  COMMUN_init_param_execution(u700_031b_ctx_exec);

  /* connection ORACLE */
  /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 

  if ( CBASE_connexion_base(u700_031b_ctx_exec.fichier_config, u700_031b_instance, u700_031b_fichier_utilisateur, u700_031b_user) != TRT_OK){
    CBASE_affiche_message(CMES_ERR_00002,  COMMUN_BALISE_ERREUR,  sqlca.sqlerrm.sqlerrmc,  NULL, NULL);
    exit(1);
  }

  /* récupération de la valeur du paramètre base du répertoire d'arrivee des depeches */
  if ( CMES_get_param("IR0026", u700_031b_rep_arrivee) == KO) exit(1);
   
  /* récupération de la valeur du paramètre base du répertoire de départ des depeches */
  if ( CMES_get_param("IR0025", u700_031b_rep_depart) == KO) exit(1);

  /* récupération de la valeur du paramètre base du répertoire de départ des depeches */
  if ( CMES_get_param("SM0008", u700_031b_sql_site_courant.arr) == KO) exit(1);
  u700_031b_sql_site_courant.arr[u700_031b_sql_site_courant.len] = '\0';

  COMMUN_check_env(NULL, u700_031b_separateur, NULL, u700_031b_separateur_var_path);
  /* récupération de la valeur du site de routage */
  u700_031b_retour = U700_031b_SANS_ERREUR;

  /* EXEC SQL WHENEVER NOT FOUND DO U700_031b_non_trouve(); */ 

  /* EXEC SQL SELECT ide_site_rout
           INTO :u700_031b_sql_site_routage
           FROM rm_routage
           WHERE ide_site_emet = :u700_031b_sql_site_courant
           AND ide_site_dest = :u700_031b_sql_site_dest; */ 

{
  struct sqlexd sqlstm;

  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 3;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select ide_site_rout into :b0  from rm_routage where (ide_s\
ite_emet=:b1 and ide_site_dest=:b2)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&u700_031b_sql_site_routage;
  sqlstm.sqhstl[0] = (unsigned int  )8;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&u700_031b_sql_site_courant;
  sqlstm.sqhstl[1] = (unsigned int  )8;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&u700_031b_sql_site_dest;
  sqlstm.sqhstl[2] = (unsigned int  )8;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
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
  if (sqlca.sqlcode == 1403) U700_031b_non_trouve();
}



  u700_031b_sql_site_routage.arr[u700_031b_sql_site_routage.len] = '\0';

  /*
	 le répertoire sql_rep_depart/sql_site_routage existe-t-il ? 
		SNE, S'il n'est pas defini alors c'est un routage direct
*/
  if (u700_031b_retour == U700_031b_ENREG_NON_TROUVE){
	strcpy(u700_031b_sql_site_routage.arr, u700_031b_sql_site_dest.arr);
	u700_031b_sql_site_routage.len = strlen(u700_031b_sql_site_routage.arr);
	u700_031b_retour = OK;
  }
   sprintf(v_tmp1, "%s%s%s\0", u700_031b_rep_depart, u700_031b_separateur, u700_031b_sql_site_routage.arr);
   u700_031b_retour = CMES_verif_cre_rep(v_tmp1, CMES_OPTION_CRE_REP);
   if (u700_031b_retour != OK){
	   switch(COMMUN_existe_repertoire(v_tmp1)){
		case COMMUN_CODE_REP_EXISTANT:
		break;

		case COMMUN_CODE_REP_INEXISTANT:
				if (COMMUN_creer_repertoire(v_tmp1) != 0){
					sprintf(v_tmp1, "%d\0", errno);
    					CBASE_affiche_message(CMES_ERR_00026,  COMMUN_BALISE_ERREUR,  v_tmp1,  NULL, NULL);
					u700_031b_retour = KO;
				}
				COMMUN_chmod(v_tmp1, COMMUN_UNIX_MODE_TOUS COMMUN_UNIX_MODE_ADD COMMUN_UNIX_MODE_READ COMMUN_UNIX_MODE_WRITE COMMUN_UNIX_MODE_EXE );
		break;

		default:
				u700_031b_retour = KO;
		break;
	   }
	}

   if (u700_031b_retour == OK){  
	sprintf(v_tmp1, "%s%s%s\0", u700_031b_rep_arrivee, u700_031b_separateur, u700_031b_fichier);
	sprintf(v_tmp2, "%s%s%s%s%s\0", u700_031b_rep_depart, u700_031b_separateur, u700_031b_sql_site_routage.arr, u700_031b_separateur, u700_031b_fichier);
	if (COMMUN_move_fichier(v_tmp1, v_tmp2, COMMUN_CP_ECRASE_FICHIER) != OK){

		CBASE_affiche_message(CMES_ERR_00009,  COMMUN_BALISE_ERREUR,  u700_031b_fichier,  u700_031b_sql_site_routage.arr, NULL);
		u700_031b_retour = KO;
	}
	else
		u700_031b_retour = OK;
   }

   if ( u700_031b_retour == OK)
   	CBASE_affiche_message(CMES_ERR_00007,  COMMUN_BALISE_ERREUR,  u700_031b_ctx_exec.nom_programme,  NULL, NULL);
   else
   	CBASE_affiche_message(CMES_ERR_00010,  COMMUN_BALISE_ERREUR,  u700_031b_ctx_exec.nom_programme,  NULL, NULL);
    exit(u700_031b_retour);
} /* fin du main */  

