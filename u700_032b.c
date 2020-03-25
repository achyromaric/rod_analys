
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
    "J:\\V34\\AsterSrv\\projets\\u700_032b\\u700_032b.pc"
};


static unsigned long sqlctx = 269067093;


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
            void  *sqhstv[7];
   unsigned int   sqhstl[7];
            int   sqhsts[7];
            void  *sqindv[7];
            int   sqinds[7];
   unsigned int   sqharm[7];
   unsigned int   *sqharc[7];
   unsigned short  sqadto[7];
   unsigned short  sqtdso[7];
} sqlstm = {10,7};

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
5,0,0,1,34,0,122,347,0,0,1,1,0,1,0,1,9,0,0,
24,0,0,2,33,0,122,348,0,0,1,1,0,1,0,1,3,0,0,
43,0,0,3,44,0,122,351,0,0,3,3,0,1,0,1,9,0,0,1,9,0,0,1,3,0,0,
70,0,0,4,146,0,4,372,0,0,5,4,0,1,0,2,68,0,0,1,9,0,0,1,9,0,0,1,9,0,0,1,9,0,0,
105,0,0,5,154,0,4,393,0,0,6,5,0,1,0,2,68,0,0,1,9,0,0,1,9,0,0,1,9,0,0,1,68,0,0,
1,9,0,0,
144,0,0,6,43,0,122,488,0,0,7,7,0,1,0,1,9,0,0,1,9,0,0,1,9,0,0,1,68,0,0,1,3,0,0,
1,9,0,0,1,3,0,0,
};


/*
---------------------------------------------------------------------------
 Fichier			: U700_032B.pc
 Date creation		: 06-12-1999

 Logiciel			: ASTER
 sous-systeme		: MES
 Description		: Charge la dépêche passé en paramètre

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
 Auteur          	: SNE
 Version         	: @(#) U700_031B version 2.1-1.1 : SNE : 24/09/2001
 Date version    	: 02/02/2001
 Description	: Reecriture/Adaptations pour modifications portage NT
---------------------------------------------------------------------------

	--------------------------------------------------------------------
	Fonction	|Date	    	|Initiales	|Commentaires 		
	--------------------------------------------------------------------
@(#)	U700_031B	|06/12/1999 | FAU	| Creation 
@(#)	U700_031B 	|02/02/2001 | SNE	| Reecriture/Adaptations pour modifications portage NT
@(#)	U700_031B 	|24/09/2001 | SNE	| Forcage du chargement pour chargement manuel
---------------------------------------------------------------------------
*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../commun/commun.h"
#include "../commun/combase.h"
#include "../commun/commes.h"

#define U700_032B_NOM_PROGRAMME	"U700_032b"
#define U700_032B_LIB_PROGRAMME	U700_032B_NOM_PROGRAMME " -  Chargement des depeches"
#define U700_032B_VERSION_FICHIER	"1.2"
#define U700_032B_MSG_ERR_SYNTAXE	" %s <fichier cfg> <instance> <utilisateur> <fichier de donnees> <site destination> [<fichier utilisateurs>] [<fichier erreur>] ==> niveau de gravite 5\n"
#define u700_032b_MSG_ERR_VAR_ENV	CMES_MSG_ERR_VAR_ENV
#define U700_032B_MSG_ERR_OUV_FIC	COMMUN_MSG_ERR_OUV_FIC
#define U700_032b_MSG_INF_FIC_TRC	U700_032B_NOM_PROGRAMME " Niveau de trace (%d) Des procedures stockees dans %s \n"
#define U700_032B_LG_NOM_FIC	80
#define U700_032B_LG_NOM_REP	121
#define U700_032B_EXT_FIC_BAD	".bad"
#define U700_032B_EXT_FIC_DIS	".dis"

#define U700_032B_PARAM_FIC_CFG	1
#define U700_032B_PARAM_INSTANCE	2
#define U700_032B_PARAM_UTIL		3
#define U700_032B_PARAM_FIC_DAT		4
#define U700_032B_PARAM_SITE_DEST	5
#define U700_032B_PARAM_FIC_UTIL	6
#define U700_032B_PARAM_FIC_ERR	7
#define U700_032B_PARAM_CHG_MANUEL	8
#define U700_032B_PARAM_NIV_TRACE	9

#define U700_032B_NBRE_PARAM_MIN	6
#define U700_032B_NBRE_PARAM_MAX	10


#define U700_032B_ERR_000002    CMES_ERR_00002
#define U700_032B_ERR_000003    CMES_ERR_00003
#define U700_032B_ERR_000004    CMES_ERR_00004
#define U700_032B_ERR_000005    CMES_ERR_00005
#define U700_032B_ERR_000007    CMES_ERR_00007
#define U700_032B_ERR_000010    CMES_ERR_00010
#define U700_032B_ERR_000011    CMES_ERR_00011
#define U700_032B_ERR_000012    CMES_ERR_00012
#define U700_032B_ERR_000013    CMES_ERR_00013
#define U700_032B_ERR_000014    CMES_ERR_00014
#define U700_032B_ERR_000015    CMES_ERR_00015
#define U700_032B_ERR_000016    CMES_ERR_00016
#define U700_032B_ERR_000019	CMES_ERR_00019
#define U700_032B_ERR_000022    CMES_ERR_00022
#define U700_032B_ERR_000023    CMES_ERR_00023
#define U700_032B_ERR_000024    CMES_ERR_00024

#define U700_032B_MES_CTL_FILE	"mes.ctl"
#define U700_032B_LOG_SQL_LOADER	"%s%sldr_%s.log"
#define U700_032B_FRMT_CMD_SQL_LDR	"sqlldr userid=%s/%s@%s control='%s%s"U700_032B_MES_CTL_FILE"' log='%s' data='%s%s%s' bad='%s%s%s' discard='%s%s%s' "COMMUN_CMD_SIGN_REDIR_ERREUR " " COMMUN_CMD_SIGN_REDIR " " COMMUN_DEV_NULL "\0"


/* EXEC SQL BEGIN DECLARE SECTION; */ 


  /* VARCHAR sql_rep_arrivee[121]; */ 
struct { unsigned short len; unsigned char arr[121]; } sql_rep_arrivee;

  /* VARCHAR sql_rep_batch[121]; */ 
struct { unsigned short len; unsigned char arr[121]; } sql_rep_batch;

  /* VARCHAR sql_rep_archive[121]; */ 
struct { unsigned short len; unsigned char arr[121]; } sql_rep_archive;

  /* VARCHAR sql_rep_travail[121]; */ 
struct { unsigned short len; unsigned char arr[121]; } sql_rep_travail;


  /* VARCHAR u700_032b_sql_cod_env[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } u700_032b_sql_cod_env;

  /* VARCHAR u700_032b_sql_site_emet[6]; */ 
struct { unsigned short len; unsigned char arr[6]; } u700_032b_sql_site_emet;

  /* VARCHAR u700_032b_sql_site_dest[6]; */ 
struct { unsigned short len; unsigned char arr[6]; } u700_032b_sql_site_dest;

  unsigned long u700_032b_sql_no_depeche;

  unsigned long u700_032b_sql_max_ide_depeche;
  unsigned long u700_032b_sql_count_depeche;

  /* VARCHAR u700_032b_sql_commentaire[121]; */ 
struct { unsigned short len; unsigned char arr[121]; } u700_032b_sql_commentaire;


  /* VARCHAR u700_032b_sql_libl[121]; */ 
struct { unsigned short len; unsigned char arr[121]; } u700_032b_sql_libl;

  /* VARCHAR u700_032b_sql_flg_recu[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } u700_032b_sql_flg_recu;

  /* VARCHAR u700_032b_fichier_trace_exec[200]; */ 
struct { unsigned short len; unsigned char arr[200]; } u700_032b_fichier_trace_exec;

  int u700_032b_retour;
  int u700_032b_flg_sql_loader
      , u700_032b_fichier_niveau_trace;
 
/* EXEC SQL END DECLARE SECTION; */ 

/* EXEC SQL INCLUDE sqlca;
 */ 
/*
 * $Header: \Referentiel/aster v430x/distrib_poste/distribution/AsterSrv/projets/u700_032b/u700_032b.c,v 1.1 2010/02/02 08:53:13 ilaronde-cp Exp $ sqlca.h 
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



COMMUN_t_contexte_exec u700_032b_ctx_exec;
static char U700_032B_version_fichier[]="@(#) " U700_032B_LIB_PROGRAMME " version "COMMUN_VERSION_ASTER"-"U700_032B_VERSION_FICHIER" - "__DATE__ " "__TIME__;

char u700_032b_separateur[2]
	, u700_032b_separateur_var_path[2]
    , u700_032b_rep_arrivee[U700_032B_LG_NOM_REP]
    , u700_032b_rep_archive[U700_032B_LG_NOM_REP]
    , u700_032b_rep_batch[U700_032B_LG_NOM_REP]
    , u700_032b_rep_log[U700_032B_LG_NOM_REP]
    , u700_032b_rep_err[U700_032B_LG_NOM_REP]
    , u700_032b_rep_travail[U700_032B_LG_NOM_REP]
    , u700_032b_fichier[U700_032B_LG_NOM_FIC]
    , u700_032b_fichier_bad[U700_032B_LG_NOM_FIC]
    , u700_032b_fichier_dis[U700_032B_LG_NOM_FIC]
    , u700_032b_fichier_utilisateur[U700_032B_LG_NOM_FIC]
	, u700_032b_user[31]
	, u700_032b_instance[10]
	, u700_032b_user_passwd[40]
	, u700_032b_rep_tmp[COMMUN_LG_PATHNAME]
      ;


int U700_032B_lire_variable(char *p_nom_var, char *p_dest)
{
   int v_ret = OK;

      switch (v_ret = COMMUN_lire_info(u700_032b_ctx_exec.fichier_config, u700_032b_instance, p_nom_var, p_dest)){
		case OK:
			break;
		case COMMUN_GI_ERR_OUV_FIC:
  			COMMUN_ecrit_log_var(BALISE_ERREUR, U700_032B_MSG_ERR_OUV_FIC, u700_032b_ctx_exec.fichier_config);
			break;

		case COMMUN_GI_ERR_INFO_NTFD:
  			COMMUN_ecrit_log_var(BALISE_ERREUR, u700_032b_MSG_ERR_VAR_ENV, p_nom_var, u700_032b_ctx_exec.fichier_config, u700_032b_instance);
			break;
	  }
   return(v_ret);
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
 ====================================================================================
*/
main(argc, argv)
  int argc;
  char *argv[];
{

  /* déclaration des variables */
  char v_instance_L1[10]
       , v_commande[512]
	 , v_log_sql_loader[130]
	 , v_date_systeme[] = "YYYYMMDD_HHMISS"
       , v_no_depeche[7]
  	 , v_tmp1[256]
  	 , v_tmp2[256]
	 , v_fic_travail[COMMUN_LG_PATHNAME]
	;
  int v_retour
	, v_chargement_manuel = 0
  ;


/*
	 SNE, Initialisations ...
*/
  u700_032b_flg_sql_loader = 0;
  memset(&u700_032b_ctx_exec, 0, sizeof(COMMUN_t_contexte_exec));
  strcpy(u700_032b_ctx_exec.nom_programme, argv[0]);
  memset(u700_032b_fichier_trace_exec.arr, 0, 200);
  memset(u700_032b_rep_log, 0, U700_032B_LG_NOM_REP);
  memset(v_fic_travail, 0, COMMUN_LG_PATHNAME);
  memset(u700_032b_rep_tmp, 0, COMMUN_LG_PATHNAME);
  memset(u700_032b_rep_err, 0, U700_032B_LG_NOM_REP);
  memset(u700_032b_fichier_bad, 0, U700_032B_LG_NOM_FIC);
  memset(u700_032b_fichier_dis, 0, U700_032B_LG_NOM_FIC);

/*
	SNE, Fixation des parametres environnementaux lies au systeme d'exploitation
*/
  COMMUN_check_env(NULL, u700_032b_separateur, NULL, u700_032b_separateur_var_path);

  /* analyse des paramètres */
  if ( argc < U700_032B_NBRE_PARAM_MIN || argc > U700_032B_NBRE_PARAM_MAX ) {
    COMMUN_ecrit_log_var(BALISE_INFORMATIVE, "%s\n" , U700_032B_version_fichier+4);
    COMMUN_ecrit_log_var(BALISE_ERREUR, U700_032B_MSG_ERR_SYNTAXE,  *argv);
    exit(1);
    }

  strcpy(u700_032b_instance, argv[U700_032B_PARAM_INSTANCE]);
  strcpy(u700_032b_user, argv[U700_032B_PARAM_UTIL]);
  strcpy(u700_032b_ctx_exec.fichier_config, argv[U700_032B_PARAM_FIC_CFG]);
  strcpy(u700_032b_fichier, argv[U700_032B_PARAM_FIC_DAT]);

/*	Constitution du nom du fichier bad */
  strcpy(u700_032b_fichier_bad, u700_032b_fichier);
  if (strchr(u700_032b_fichier_bad, '.') != NULL){
      sprintf(strchr(u700_032b_fichier_bad, '.'), "%s\0", U700_032B_EXT_FIC_BAD);
  }
  else
     strcat(u700_032b_fichier_bad, U700_032B_EXT_FIC_BAD);


/*
	Constitution du nom du fichier dis
*/
  strcpy(u700_032b_fichier_dis, u700_032b_fichier);
  if (strchr(u700_032b_fichier_dis, '.') != NULL){
      sprintf(strchr(u700_032b_fichier_dis, '.'), "%s\0", U700_032B_EXT_FIC_DIS);
  }
  else
     strcat(u700_032b_fichier_dis, U700_032B_EXT_FIC_DIS);

 /*
	Recherche du nom du fichier utilisateur: si la valeur n'est pas spécifiée parmi les paramètres
		alors on recherche dans le fichier de configuration générale
 */
  if (argc > U700_032B_PARAM_FIC_UTIL)
  	strcpy(u700_032b_fichier_utilisateur, argv[U700_032B_PARAM_FIC_UTIL]);
  else{
	  if (U700_032B_lire_variable(COMMUN_VAR_FIC_UTIL, u700_032b_fichier_utilisateur) != OK)
		exit(KO);
  }

/*
	Recherche du fichier erreur : même méthode de recherche que pour le fichier des mots de passe
*/

  if (argc > U700_032B_PARAM_FIC_ERR)
	 strcpy(u700_032b_ctx_exec.fichier_erreur, argv[U700_032B_PARAM_FIC_ERR]);
  else{
	  if (U700_032B_lire_variable(COMMUN_VAR_FIC_ERR, u700_032b_ctx_exec.fichier_erreur) != OK)
		exit(KO);
  }

  if (argc > U700_032B_PARAM_CHG_MANUEL)
	 v_chargement_manuel = atoi(argv[U700_032B_PARAM_CHG_MANUEL]);
  
/*
	SNE, On va rechercher le parametre instance si defini
  if (COMMUN_lire_info(u700_032b_ctx_exec.fichier_config, u700_032b_instance, COMMUN_VAR_INSTANCE, v_instance_L1) != OK)
*/
  if (U700_032B_lire_variable(COMMUN_VAR_INSTANCE, v_instance_L1) != OK)
	sprintf(v_instance_L1, "%s_L1\0", u700_032b_instance);



  u700_032b_ctx_exec.niveau_debug = COMMUN_DEBUG_SANS_DEBUG;
/*
  SNE, 23/04/2001 : Mise en place des traces d'execution
*/
/*
  COMMUN_lire_info(u700_032b_ctx_exec.fichier_config, u700_032b_instance, COMMUN_VAR_BATCH_LOG, u700_032b_rep_log);
  if (COMMUN_lire_info(u700_032b_ctx_exec.fichier_config, u700_032b_instance, COMMUN_VAR_BATCH_LOG, u700_032b_rep_log) != OK)
   if (!strlen(u700_032b_rep_log))
	strcpy(u700_032b_rep_log, u700_032b_rep_batch);
*/

  if (U700_032B_lire_variable(COMMUN_VAR_BATCH_LOG, u700_032b_rep_log) != OK)
	exit(1);

  if (U700_032B_lire_variable(COMMUN_VAR_BATCH_ERR, u700_032b_rep_err) != OK)
    strcpy(u700_032b_rep_err, u700_032b_rep_log);

  if (argc > U700_032B_PARAM_NIV_TRACE){
	  if (strlen(u700_032b_rep_log) > 0){
	   u700_032b_fichier_niveau_trace = u700_032b_ctx_exec.niveau_debug = atoi(argv[U700_032B_PARAM_NIV_TRACE]);
	   sprintf(u700_032b_fichier_trace_exec.arr, "%s%s%s.log", u700_032b_rep_log, u700_032b_separateur, u700_032b_ctx_exec.nom_programme);
	   u700_032b_fichier_trace_exec.len = strlen(u700_032b_fichier_trace_exec.arr);  
       COMMUN_ecrit_log_var(BALISE_INFORMATIVE, U700_032b_MSG_INF_FIC_TRC, u700_032b_fichier_niveau_trace , u700_032b_fichier_trace_exec.arr);
	  }
  }

  u700_032b_ctx_exec.mode_trace = COMMUN_TRACE_DANS_FIC;
  COMMUN_init_param_execution(u700_032b_ctx_exec);

  /* connection ORACLE */
  /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 

  if ( CBASE_connexion_base(u700_032b_ctx_exec.fichier_config, u700_032b_instance, u700_032b_fichier_utilisateur, u700_032b_user) != TRT_OK){
    CBASE_affiche_message(CMES_ERR_00002,  COMMUN_BALISE_ERREUR,  sqlca.sqlerrm.sqlerrmc,  NULL, NULL);
    exit(1);
  }

  CBASE_mot_de_passe_connexion(u700_032b_user_passwd);
  
  COMMUN_open_debug(NULL);

/*
   SNE, 24/09/2001 : Correction Ano 227 (Redirection de la commande SQL*Loader)
					 ==========================================================
*/
   COMMUN_Date_du_jour(COMMUN_FRMT_EXT_F_LOG, v_date_systeme);
   if (COMMUN_lire_info(u700_032b_ctx_exec.fichier_config, u700_032b_instance, COMMUN_VAR_BATCH_TMP, u700_032b_rep_tmp) != OK){
      sprintf(v_fic_travail, "%s%s"U700_032B_NOM_PROGRAMME"_%s."COMMUN_EXTENSION_FIC_SHELL"\0", u700_032b_rep_tmp, u700_032b_separateur, v_date_systeme);
   }
/*
   SNE, 24/09/2001 : ==========================================================
*/

  v_retour = CMES_decompose_nom_fichier(u700_032b_fichier, u700_032b_sql_cod_env.arr, u700_032b_sql_site_emet.arr, u700_032b_sql_site_dest.arr, v_no_depeche);
  u700_032b_sql_cod_env.len = strlen(u700_032b_sql_cod_env.arr);
  u700_032b_sql_site_emet.len = strlen(u700_032b_sql_site_emet.arr);
  u700_032b_sql_site_dest.len = strlen(u700_032b_sql_site_dest.arr);
  u700_032b_sql_no_depeche = strtoul(v_no_depeche, NULL, 10);

  /*
  	SNE, 23/04/2001 : Initialisation des parametres de trace
  */
  if (u700_032b_fichier_trace_exec.len > 0){
	  /* EXEC SQL CALL GLOBAL.INI_FICHIER_TRACE(:u700_032b_fichier_trace_exec); */ 

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
   sqlstm.sqhstv[0] = (         void  *)&u700_032b_fichier_trace_exec;
   sqlstm.sqhstl[0] = (unsigned int  )202;
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


	  /* EXEC SQL CALL GLOBAL.INI_NIVEAU_TRACE(:u700_032b_fichier_niveau_trace); */ 

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
   sqlstm.sqhstv[0] = (         void  *)&u700_032b_fichier_niveau_trace;
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
  
  /* EXEC SQL CALL EXT_CODEXT('EMIS_RECU', 'R', :u700_032b_sql_libl, :u700_032b_sql_flg_recu, :u700_032b_retour); */ 

{
  struct sqlexd sqlstm;

  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 3;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "call EXT_CODEXT('EMIS_RECU','R',:b0,:b1,:b2)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )43;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&u700_032b_sql_libl;
  sqlstm.sqhstl[0] = (unsigned int  )123;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&u700_032b_sql_flg_recu;
  sqlstm.sqhstl[1] = (unsigned int  )18;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&u700_032b_retour;
  sqlstm.sqhstl[2] = (unsigned int  )4;
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
}


  if (sqlca.sqlcode != 0) {
	CBASE_affiche_message(U700_032B_ERR_000002,  COMMUN_BALISE_ERREUR,  sqlca.sqlerrm.sqlerrmc, NULL, NULL);
    	exit(1);
    }
  if (u700_032b_retour != 1) {
	CBASE_affiche_message(U700_032B_ERR_000011,  COMMUN_BALISE_ERREUR,  "EMIS_RECU",  "R", NULL);
    exit(1);
    }
  u700_032b_sql_libl.arr[u700_032b_sql_libl.len] = '\0';
  u700_032b_sql_flg_recu.arr[u700_032b_sql_flg_recu.len] = '\0';
 
  /* la dépêche est-elle reçue en séquence */
/*
======================================================================================
		SNE, 25/09/2001 : On n'effectue plus le test de la reception en sequence dans le cas d'un
		    chargement manuel - le flag 'chargement manuel' permet de forcer le chargement 
			d'une dépêche
======================================================================================
*/
 if (!v_chargement_manuel){
  /* EXEC SQL SELECT NVL(MAX(ide_depeche), 0)
           INTO :u700_032b_sql_max_ide_depeche
           FROM fm_depeche
           WHERE ide_env = :u700_032b_sql_cod_env
             AND ide_site_emet = :u700_032b_sql_site_emet
             AND ide_site_dest = :u700_032b_sql_site_dest
             AND flg_emis_recu = :u700_032b_sql_flg_recu; */ 

{
  struct sqlexd sqlstm;

  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 5;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select NVL(max(ide_depeche),0) into :b0  from fm_depeche wh\
ere (((ide_env=:b1 and ide_site_emet=:b2) and ide_site_dest=:b3) and flg_emis_\
recu=:b4)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )70;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&u700_032b_sql_max_ide_depeche;
  sqlstm.sqhstl[0] = (unsigned int  )4;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&u700_032b_sql_cod_env;
  sqlstm.sqhstl[1] = (unsigned int  )4;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&u700_032b_sql_site_emet;
  sqlstm.sqhstl[2] = (unsigned int  )8;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)&u700_032b_sql_site_dest;
  sqlstm.sqhstl[3] = (unsigned int  )8;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)&u700_032b_sql_flg_recu;
  sqlstm.sqhstl[4] = (unsigned int  )18;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
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
	CBASE_affiche_message(U700_032B_ERR_000002,  COMMUN_BALISE_ERREUR,  sqlca.sqlerrm.sqlerrmc,  NULL, NULL);
    exit(1);
    }

    if (u700_032b_sql_no_depeche  > (u700_032b_sql_max_ide_depeche + 1)) {
    /* hors sequence */
	CBASE_affiche_message(U700_032B_ERR_000012,  COMMUN_BALISE_ERREUR,  u700_032b_fichier,  NULL, NULL);
    	exit(1);
    }
  }

  /* la dépêche est-elle reçue en double */
  /* EXEC SQL SELECT count(*)
           INTO :u700_032b_sql_count_depeche
           FROM fm_depeche
           WHERE ide_env = :u700_032b_sql_cod_env
             AND ide_site_emet = :u700_032b_sql_site_emet
             AND ide_site_dest = :u700_032b_sql_site_dest
             AND ide_depeche = :u700_032b_sql_no_depeche
             AND flg_emis_recu = :u700_032b_sql_flg_recu; */ 

{
  struct sqlexd sqlstm;

  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 6;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select count(*)  into :b0  from fm_depeche where ((((ide_en\
v=:b1 and ide_site_emet=:b2) and ide_site_dest=:b3) and ide_depeche=:b4) and f\
lg_emis_recu=:b5)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )105;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&u700_032b_sql_count_depeche;
  sqlstm.sqhstl[0] = (unsigned int  )4;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&u700_032b_sql_cod_env;
  sqlstm.sqhstl[1] = (unsigned int  )4;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&u700_032b_sql_site_emet;
  sqlstm.sqhstl[2] = (unsigned int  )8;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)&u700_032b_sql_site_dest;
  sqlstm.sqhstl[3] = (unsigned int  )8;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)&u700_032b_sql_no_depeche;
  sqlstm.sqhstl[4] = (unsigned int  )4;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)&u700_032b_sql_flg_recu;
  sqlstm.sqhstl[5] = (unsigned int  )18;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
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
	CBASE_affiche_message(U700_032B_ERR_000002,  COMMUN_BALISE_ERREUR,  sqlca.sqlerrm.sqlerrmc,  NULL, NULL);
    exit(1);
    }

  if (u700_032b_sql_count_depeche != 0) {
    /* depeche en double */
	CBASE_affiche_message(U700_032B_ERR_000013,  COMMUN_BALISE_ERREUR,  u700_032b_fichier,  NULL, NULL);
    exit(1);
    }
  
  /* contrôles OK => chargement de la dépêche */

  /* récupération de la valeur du paramètre base du répertoire d'arrivee des depeches */
  if (CMES_verif_rep("IR0026", u700_032b_rep_arrivee) != TRT_OK) exit(1);
   

  /* récupération de la valeur du paramètre base du répertoire d'archive des depeches */
  if (CMES_verif_rep("IR0027", u700_032b_rep_archive) != TRT_OK) exit(1);

  /* récupération de la valeur du paramètre base du répertoire d'arrivee des batchs */
  if (CMES_verif_rep("IR0010", u700_032b_rep_batch) != TRT_OK) exit(1);

  /* récupération de la valeur du paramètre base du répertoire de travail */
  if (CMES_verif_rep("IR0032", u700_032b_rep_travail) != TRT_OK) exit(1);



  /* 
				chargement du fichier 
   */

  COMMUN_Date_du_jour(COMMUN_FRMT_EXT_F_LOG, v_date_systeme);
  sprintf(v_log_sql_loader, U700_032B_LOG_SQL_LOADER, u700_032b_rep_log, u700_032b_separateur, v_date_systeme);
/* LGD - 02/10/2003 */
  sprintf(v_commande, U700_032B_FRMT_CMD_SQL_LDR, u700_032b_user, u700_032b_user_passwd, v_instance_L1, u700_032b_rep_batch, u700_032b_separateur, v_log_sql_loader, u700_032b_rep_arrivee, u700_032b_separateur, u700_032b_fichier, u700_032b_rep_err, u700_032b_separateur, u700_032b_fichier_bad, u700_032b_rep_err, u700_032b_separateur, u700_032b_fichier_dis); 
  /*
  CBASE_affiche_message(COMMUN_INF_EXEC_PRG,  COMMUN_BALISE_INFORMATIVE,  v_commande,  NULL, NULL);
		SNE, 24/09/2001 : Execution via un fichier de la commande
  */
  switch( v_retour = COMMUN_lancer_commande(v_commande, v_fic_travail, NULL)){
	case COMMUN_CODE_FICHIER_INEXISTANT:
	break;

	case CODE_FICHIER_VERROUILLE:
	break;

	case 0:
		CBASE_affiche_message(U700_032B_ERR_000022,  COMMUN_BALISE_INFORMATIVE,  "SQL*Loader",  NULL, NULL);
	break;

	case 256:
		CBASE_affiche_message(U700_032B_ERR_000014,  COMMUN_BALISE_ERREUR,  NULL,  NULL, NULL);
		CBASE_affiche_message(U700_032B_ERR_000023,  COMMUN_BALISE_ERREUR,  NULL,  NULL, NULL);
	    	u700_032b_flg_sql_loader = -1;

	    	/* recherche du libellé du message de notification */
		COMMUN_lire_message_erreur(v_log_sql_loader, COMMUN_TAG_MSG_ORACLE, u700_032b_sql_commentaire.arr);
      	u700_032b_sql_commentaire.len = strlen(u700_032b_sql_commentaire.arr);
	break;

	case 512:
		CBASE_affiche_message(U700_032B_ERR_000014,  COMMUN_BALISE_ERREUR,  NULL,  NULL, NULL);
		CBASE_affiche_message(U700_032B_ERR_000023,  COMMUN_BALISE_ERREUR,  NULL,  NULL, NULL);
	    	u700_032b_flg_sql_loader = -1;

    		/* recherche du libellé du message de notification */
		COMMUN_lire_message_erreur(v_log_sql_loader, COMMUN_TAG_MSG_ORACLE, u700_032b_sql_commentaire.arr);
      	u700_032b_sql_commentaire.len = strlen(u700_032b_sql_commentaire.arr);
	break;

	default:
		CBASE_affiche_message(U700_032B_ERR_000014,  COMMUN_BALISE_ERREUR,  NULL,  NULL, NULL);
		CBASE_affiche_message(U700_032B_ERR_000024,  COMMUN_BALISE_ERREUR,  NULL,  NULL, NULL);
      	u700_032b_flg_sql_loader = -1;

    		/* recherche du libellé du message de notification */
		COMMUN_lire_message_erreur(v_log_sql_loader, COMMUN_TAG_MSG_ORACLE, u700_032b_sql_commentaire.arr);
      	u700_032b_sql_commentaire.len = strlen(u700_032b_sql_commentaire.arr);
	break;
  }


  
  /*   1. appel à u700_070b, formattage des messages */
  /*      d'une dépêche reçue                        */
  /*   2. archivage de la dépêche (paramètre IR0027  */
  /* EXEC SQL CALL u700_070b(:u700_032b_sql_cod_env, :u700_032b_sql_site_emet, :u700_032b_sql_site_dest, :u700_032b_sql_no_depeche, :u700_032b_flg_sql_loader, :u700_032b_sql_commentaire, :u700_032b_retour); */ 

{
  struct sqlexd sqlstm;

  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 7;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "call u700_070b(:b0,:b1,:b2,:b3,:b4,:b5,:b6)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )144;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&u700_032b_sql_cod_env;
  sqlstm.sqhstl[0] = (unsigned int  )4;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&u700_032b_sql_site_emet;
  sqlstm.sqhstl[1] = (unsigned int  )8;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&u700_032b_sql_site_dest;
  sqlstm.sqhstl[2] = (unsigned int  )8;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)&u700_032b_sql_no_depeche;
  sqlstm.sqhstl[3] = (unsigned int  )4;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)&u700_032b_flg_sql_loader;
  sqlstm.sqhstl[4] = (unsigned int  )4;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)&u700_032b_sql_commentaire;
  sqlstm.sqhstl[5] = (unsigned int  )123;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)&u700_032b_retour;
  sqlstm.sqhstl[6] = (unsigned int  )4;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
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
	CBASE_affiche_message(U700_032B_ERR_000004,  COMMUN_BALISE_ERREUR,  "u700_070b",  sqlca.sqlerrm.sqlerrmc, NULL);
    exit(1);
    }

  /* affichage des messages générés par la procédure u700_070b */
  sprintf(v_tmp1, "%s%su700_070b.err", u700_032b_rep_travail, u700_032b_separateur);
  COMMUN_afficher_fichier(v_tmp1);  
 
  switch (u700_032b_retour) {
	case 0:
		CBASE_affiche_message(U700_032B_ERR_000010,  COMMUN_BALISE_ERREUR,  NULL,  NULL, NULL);
    		/* on archive la dépêche */
		sprintf(v_tmp1, "%s%s%s\0", u700_032b_rep_arrivee, u700_032b_separateur, u700_032b_fichier);
		sprintf(v_tmp2, "%s%s%s\0", u700_032b_rep_archive, u700_032b_separateur, u700_032b_fichier);
		if (COMMUN_move_fichier(v_tmp1, v_tmp2, COMMUN_CP_ECRASE_FICHIER) != OK){
			CBASE_affiche_message(CMES_ERR_00009,  COMMUN_BALISE_ERREUR,  u700_032b_fichier,  u700_032b_rep_archive, NULL);
			exit(1);
		}
	break;

  	case -1:
		CBASE_affiche_message(U700_032B_ERR_000015,  COMMUN_BALISE_ERREUR,  "u700_070b",  NULL, NULL);
		exit(1);
	break;

	case -2:
		CBASE_affiche_message(U700_032B_ERR_000016,  COMMUN_BALISE_ERREUR,  u700_032b_fichier,  NULL, NULL);
   		/* on détruit la dépêche */
		/*sprintf(v_tmp1, "%s%s%s\0", u700_032b_rep_arrivee, u700_032b_separateur, u700_032b_fichier);
		if (remove(v_tmp1) != 0){
			CBASE_affiche_message(U700_032B_ERR_000019,  COMMUN_BALISE_ERREUR,  v_tmp1, NULL, NULL);
			exit(1);
		}*/
		/* FBT - 26/03/2008 - Evol DI44-2007-10 - on ne suprime plus la dépèche mais on l'archive */
		/* on déplace la depeche dans le répertoire des archives */
		sprintf(v_tmp1, "%s%s%s\0", u700_032b_rep_arrivee, u700_032b_separateur, u700_032b_fichier);
		sprintf(v_tmp2, "%s%s%s\0", u700_032b_rep_err, u700_032b_separateur, u700_032b_fichier);
		if (COMMUN_move_fichier(v_tmp1, v_tmp2, COMMUN_CP_ECRASE_FICHIER) != OK){
			CBASE_affiche_message(CMES_ERR_00009,  COMMUN_BALISE_ERREUR,  u700_032b_fichier,  u700_032b_rep_err, NULL);
			exit(1);
		}
	break;

	default:
	break;
   } 

   /*
		Suppression des fichiers de travail
   */
   if ( COMMUN_existe_fichier(v_fic_travail) == CODE_FICHIER_EXISTANT )
      remove(v_fic_travail);

   CBASE_affiche_message(U700_032B_ERR_000007,  COMMUN_BALISE_INFORMATIVE,  *argv, NULL, NULL);

} /* fin du main */  


