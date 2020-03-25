
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
           char  filnam[39];
};
static const struct sqlcxp sqlfpn =
{
    38,
    "J:\\V34\\AsterSrv\\projets\\scrut\\scrut.pc"
};


static unsigned long sqlctx = 1645066741;


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
            void  *sqhstv[25];
   unsigned int   sqhstl[25];
            int   sqhsts[25];
            void  *sqindv[25];
            int   sqinds[25];
   unsigned int   sqharm[25];
   unsigned int   *sqharc[25];
   unsigned short  sqadto[25];
   unsigned short  sqtdso[25];
} sqlstm = {10,25};

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

 static const char *sq0001 = 
"select numtrt ,nomprog ,nvl(libprog,' ') ,type ,execution ,nvl(media_edt,' '\
) ,nature ,nvl(to_char(exec_heure,'YYYYMMDDHH24MI'),'aucune') ,nvl(dir_prog,' \
') ,nvl(dir_edt,' ') ,nvl(dir_dem,' ') ,nvl(replace(destinataire,' ','-'),' ')\
 ,nvl(imprimante,' ') ,nvl(orientation,' ') ,nvl(copies,1) ,nvl(cod_format,'XX\
') ,nvl(recto_verso,'X') ,nvl(sens_rv,'X') ,nvl(bac,'X') ,code_fin ,dat_cre ,u\
ti_cre ,dat_maj ,uti_maj ,terminal  from b_traitement where code_fin='D' order\
 by numtrt            ";

 static const char *sq0002 = 
"select nomparam ,nvl(param,decode(b_traitement.type,'B','\"\"','C','\"\"',' \
'))  from b_paramtrt ,b_traitement where (b_paramtrt.numtrt=b_traitement.numtr\
t and b_paramtrt.numtrt=:b0) order by b_paramtrt.numtrt,b_paramtrt.indpar     \
       ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{10,4130,0,0,0,
5,0,0,3,232,0,4,496,0,0,1,0,0,1,0,2,9,0,0,
24,0,0,1,488,0,9,530,0,0,0,0,0,1,0,
39,0,0,1,0,0,13,541,0,0,25,0,0,1,0,2,3,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,
0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,
9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,
154,0,0,4,53,0,2,605,0,0,0,0,0,1,0,
169,0,0,5,0,0,29,612,0,0,0,0,0,1,0,
184,0,0,6,93,0,4,624,0,0,3,2,0,1,0,2,3,0,0,1,9,0,0,1,9,0,0,
211,0,0,7,59,0,4,643,0,0,1,0,0,1,0,2,9,0,0,
230,0,0,8,85,0,5,652,0,0,3,3,0,1,0,1,9,0,0,1,9,0,0,1,3,0,0,
257,0,0,9,0,0,29,663,0,0,0,0,0,1,0,
272,0,0,10,87,0,4,673,0,0,3,2,0,1,0,2,9,0,0,1,9,0,0,1,9,0,0,
299,0,0,11,71,0,122,689,0,0,2,2,0,1,0,1,9,0,0,1,9,0,0,
322,0,0,12,70,0,4,707,0,0,2,1,0,1,0,2,3,0,0,1,3,0,0,
345,0,0,2,235,0,9,787,0,0,1,1,0,1,0,1,3,0,0,
364,0,0,2,0,0,13,797,0,0,2,0,0,1,0,2,9,0,0,2,9,0,0,
387,0,0,2,0,0,15,861,0,0,0,0,0,1,0,
402,0,0,1,0,0,15,976,0,0,0,0,0,1,0,
};


/*
---------------------------------------------------------------------------
 Fichier         : scrut.pc 
 Date creation   : 29/12/99

 Logiciel          : ASTER                                           
 sous-systeme      : Scrutateur                                     
 Description     : Lancement des traitements postes (de type chaine de
                   traitements ou de type traitement simple)
 parametres entree :                                                
    1- Nom du fichier de configuration generale ASTER (emplacement.cfg)                                 
    2- Periode de scrutation (10 secondes par defaut)
    3- Nom de l'instance ORACLE                                      
    4- Nom de l'utilisateur ORACLE                                   
    5- Fichier des utilisateurs                                      
    6- Fichier des messages d'erreur                                 
                                                                     
 parametres sortie :                                                
    neant                                                            
---------------------------------------------------------------------------
 Auteur          	: FAU
 Version         	: @(#) scrut version 1.0-0 : FAU : 09/10/2000
 Date version    	: 09/10/2000
 Description	: modifications portage NT
---------------------------------------------------------------------------

	--------------------------------------------------------------------
	Fonction	|Date	    |Initiales	|Commentaires 		
	--------------------------------------------------------------------
@(#)	scrut 	|--/--/1999 | ---	| Creation 
@(#)	scrut 	|09/10/2000 | FAU	| modifications portage NT
@(#)	scrut 	|18/01/2001 | SNE	| adaptations corrections  	
@(#)	scrut 	|28/02/2002 | NDY	| suppression du fichier_des_demandes 
@(#)	scrut 	|08/04/2002 | NDY	| ajout creation-suppression de variables globales de traitement (date systeme, niveau de trace)
@(#)	scrut | 3.1b-1.5 | 11/07/2003 | SGN	| l acces au lanceur est recupere dans le fichier emplacement.cfg grace a la variable BATCH
@(#)	scrut | 3.1b-1.6 | 11/07/2003 | SGN	| correction des commentaires 3.1a
@(#)	scrut | 3.1b-1.7 | 12/07/2003 | SGN	| On ajoute exe au rep_batch pour indiquer le chemin du lanceur.
@(#)	scrut | 4260 | 13/05/2008 | FBT | Evolution DI44-2007-12 - Masquage de la commande lanceur.exe
---------------------------------------------------------------------------
*/ 

/*---------------------------------------------------------------------------
   algorithme :
     connexion a la base Oracle
     boucle de lecture de la table B_TRAITEMENT
         pour chaque ligne de la tables des traitements avec STATUT=D (demandé)
            calcul de l'heure du traitement
            initialisation de la ligne de commande avec les paramètres associes
            lancement de la commande AT , ou écriture de la ligne de commande
            dans le fichier des demandes.
            mise à jour du STATUT L=lancé

   Fichiers utilises :
     - SCRUT_<instance>     : fichier log du scrutateur
     - SCRUT_<instance>_AT  : fichier de trace de lancement de la commande at
     - lst_user.batch       : Fichier de configuration des users batch autorisés
                              (extraction du password de l'utilisateur de connexion
                              pour le scrutateur).
     - lst_erreur.batch       : Fichier des messages d'erreur.
                           
   Tables utilisées :
     - b_traitement         : Table des demandes de traitements batch.
     - b_paramtrt           : Table des parametres des traitements batch.
     - sr_param             : Table des parametres applicatifs(Extraction du
                              site courant).
     - fh_util              : Table des utilisateurs applicatifs(Extraction du
                              password de l'utilisateur de connexion pour le
                              traitement).
                              
    Procédure externes :
     - Security.UnEncrypt   : Décryptage du password de l'utilisateur applicatif.

-----------------------------------------------------------------------------*/

/* Les fichiers inclus */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../commun/commun.h"
#include "../commun/combase.h"

/* SNE, 27/12/2000 */
#ifdef WIN32
#define NBRE_ARG_REQUIS 	7
#else
#define NBRE_ARG_REQUIS 	6
#endif
#define ARRET_SCRUTATEUR	"SCRUT_STOP"
#define DATE_DEPASSEE		DATE_ANTERIEURE

#define SCRUT_ERR_00002       COMMUN_ERR_00002
#define SCRUT_ERR_000002      COMMUN_ERR_000002
#define SCRUT_ERR_000007      COMMUN_ERR_000007
#define SCRUT_ERR_000010      COMMUN_ERR_000010
#define SCRUT_ERR_000026      COMMUN_ERR_000026
#define SCRUT_ERR_000027      COMMUN_ERR_000027
#define SCRUT_ERR_000028      COMMUN_ERR_000028
#define SCRUT_ERR_000029      COMMUN_ERR_000029
#define SCRUT_ERR_000034      COMMUN_ERR_000034
#define SCRUT_ERR_000038      COMMUN_ERR_000038
#define SCRUT_ERR_000039      COMMUN_ERR_000039
#define SCRUT_ERR_000040      COMMUN_ERR_000040
#define SCRUT_ERR_000044      COMMUN_ERR_000044
#define SCRUT_ERR_000049      COMMUN_ERR_000049
#define SCRUT_ERR_000050      COMMUN_ERR_000050
#define SCRUT_ERR_000051      COMMUN_ERR_000051
#define SCRUT_ERR_712		712
#define SCRUT_ERR_713		713
#define SCRUT_ERR_743		743

#define SCRUT_VERSION_FICHIER	"1.0"

#define SCRUT_VAR_DATE_SYSTEME	"DATE_SYSTEME_VAR"
#define SCRUT_VAR_P_DAT_SYS		"P_DAT_SYS"
#define SCRUT_VAR_DATE_SYS_VAL	CBASE_VAR_DATE_SYS_VAL

#define SCRUT_VAR_NIVEAU_TRACE	"NIVEAU_TRACE_VAR"
#define SCRUT_VAR_P_NIV_TRACE		"P_NIV_TRACE"

#define PARAM_NOM_FIC_CFG	1
#define PARAM_PERIODE_SCR	2
#define PARAM_NOM_INS_SCR	3
#define PARAM_NOM_UTI_SCR	4

#define PARAM_NOM_FIC_UTI	5
#define PARAM_NOM_FIC_ERR	6
#define PARAM_MODE_TRACE 	7
#define PARAM_NIVEAU_DEBUG	8
#define PARAM_NOM_FIC_LOG	9

#define VAR_SCRUT_LOG	"SCRUT_LOG"
#define VAR_SCRUT_TMP	"SCRUT_LOG"
#define SCRUT_SUFFIXE_MESS_ERR	"(==> %s)"
#define BTRT_LG_NOMPROG		21
#define SCRUT_NOM_PROGRAMME	"SCRUTATEUR "

/* EXEC SQL BEGIN DECLARE SECTION; */ 

  /* VARCHAR sql_scrut_user[40]; */ 
struct { unsigned short len; unsigned char arr[40]; } sql_scrut_user;

  /* VARCHAR sql_scrut_pssw[40]; */ 
struct { unsigned short len; unsigned char arr[40]; } sql_scrut_pssw;

  int     sql_count;
  int     sql_nbparam;

/* table b_traitement */
  int     sql_numtrt;
  /* VARCHAR sql_nomprog[21]; */ 
struct { unsigned short len; unsigned char arr[21]; } sql_nomprog;

  /* VARCHAR sql_libprog[57]; */ 
struct { unsigned short len; unsigned char arr[57]; } sql_libprog;

  /* VARCHAR sql_type[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } sql_type;

  /* VARCHAR sql_execution[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } sql_execution;

  /* VARCHAR sql_media_edt[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } sql_media_edt;

  /* VARCHAR sql_nature[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } sql_nature;

  /* VARCHAR sql_exec_heure[40]; */ 
struct { unsigned short len; unsigned char arr[40]; } sql_exec_heure;

  /* VARCHAR sql_dir_prog[61]; */ 
struct { unsigned short len; unsigned char arr[61]; } sql_dir_prog;

  /* VARCHAR sql_dir_edt[61]; */ 
struct { unsigned short len; unsigned char arr[61]; } sql_dir_edt;

  /* VARCHAR sql_dir_dem[61]; */ 
struct { unsigned short len; unsigned char arr[61]; } sql_dir_dem;

  /* VARCHAR sql_destinataire[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sql_destinataire;

  /* VARCHAR sql_imprimante[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } sql_imprimante;

  /* VARCHAR sql_orientation[10]; */ 
struct { unsigned short len; unsigned char arr[10]; } sql_orientation;

  /* VARCHAR sql_copies[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } sql_copies;

  /* VARCHAR sql_cod_format[3]; */ 
struct { unsigned short len; unsigned char arr[3]; } sql_cod_format;

  /* VARCHAR sql_recto_verso[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } sql_recto_verso;

  /* VARCHAR sql_sens_rv[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } sql_sens_rv;

  /* VARCHAR sql_bac[21]; */ 
struct { unsigned short len; unsigned char arr[21]; } sql_bac;

  /* VARCHAR sql_code_fin[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } sql_code_fin;

  /* VARCHAR sql_lib_erreur[251]; */ 
struct { unsigned short len; unsigned char arr[251]; } sql_lib_erreur;

  /* VARCHAR sql_dat_cre[40]; */ 
struct { unsigned short len; unsigned char arr[40]; } sql_dat_cre;

  /* VARCHAR sql_uti_cre[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } sql_uti_cre;

  /* VARCHAR sql_dat_maj[40]; */ 
struct { unsigned short len; unsigned char arr[40]; } sql_dat_maj;

  /* VARCHAR sql_uti_maj[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } sql_uti_maj;

  /* VARCHAR sql_terminal[11]; */ 
struct { unsigned short len; unsigned char arr[11]; } sql_terminal;

  /* VARCHAR sql_glu[99]; */ 
struct { unsigned short len; unsigned char arr[99]; } sql_glu;

   
/* table b_paramtrt */
  /* VARCHAR sql_nomparam[21]; */ 
struct { unsigned short len; unsigned char arr[21]; } sql_nomparam;

  /* VARCHAR sql_param[33]; */ 
struct { unsigned short len; unsigned char arr[33]; } sql_param;


/* table sr_param   */
  /* VARCHAR sql_site_util[6]; */ 
struct { unsigned short len; unsigned char arr[6]; } sql_site_util;

   
/* table fh_util   */
  /* VARCHAR sql_pwd_crypt[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sql_pwd_crypt;

  /* VARCHAR sql_pwd_uncrypt[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sql_pwd_uncrypt;

  
  /* VARCHAR sql_instance[10]; */ 
struct { unsigned short len; unsigned char arr[10]; } sql_instance;

 
/* EXEC SQL END DECLARE SECTION; */ 

/* EXEC SQL INCLUDE sqlca;
 */ 
/*
 * $Header: \Referentiel/aster v430x/distrib_poste/distribution/AsterSrv/projets/scrut/scrut.c,v 1.1 2010/02/02 08:53:07 ilaronde-cp Exp $ sqlca.h 
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


static char scrut_version_fichier[]="@(#) "SCRUT_NOM_PROGRAMME " version "COMMUN_VERSION_ASTER"-"SCRUT_VERSION_FICHIER" - "__DATE__" "__TIME__;
char scrut_dernier_message_erreur[COMMUN_LG_LIBL_ERR]="";
t_indicateurs_prog scrut_param_exec;
char *v_file = "tmp.xxxxx2";


char  v_utilisateur[LG_NOM_OBJ]="\0",
     v_passwd[80]="\0",
     v_dev_null[LG_NOM_FIC]="\0",
     v_cfg_file[LG_NOM_FIC]="\0",
     v_separateur[LG_SEPARATEUR]="\0",
     v_scrut_log[LG_NOM_FIC]="\0",
     v_batch_log[LG_NOM_FIC]="\0",
     v_batch_tmp[LG_NOM_FIC]="\0",
     /* -- AT -- v_scrut_log_at[LG_NOM_FIC]="\0", */
     v_fic_sav[LG_NOM_FIC]="\0",
     v_batch_dir[LG_NOM_FIC]="\0";

char      scrut_separateur_chemin[LG_SEPARATEUR]="\0";
int scrut_os=0;
int scrut_debug = DEBUG_SANS_DEBUG;


char dat[LG_NOM_OBJ]="\0";

void fin_prg(int p_status, char *fichier_temp) ;
int SCRUT_lancer_traitement(char *p_nom_programme, char *p_commande, char *p_fichier_log);




/*
 ====================================================================================
   Nom 		: change_etat_traitement	
   Description 	: Fonction de changement d'etat d'un traitement       
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <p_status> : indicateur de fin de programme (OK/KO)              
     <p_msg_erreur> : dernier message d'erreur signalée par le programme
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   change_etat_traitement	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/

int change_etat_traitement(int p_statut, char *p_msg_erreur)
{
int v_retour;
     if ( ( v_retour = CBASE_change_etat_traitement(sql_numtrt, sql_code_fin.arr, sql_nature.arr, p_statut, p_msg_erreur)) == ERR_EXEC_SQL )
          fin_prg(KO, NULL);
return (v_retour);
}

/*
 ====================================================================================
   Nom 		: fin_prg	
   Description 	: affiche les infos de fin de programme
   Auteur	: Florent AUBARET
   Date creation: 09/10/2000
   parametres    :                                                     
      <p_status> : indicateur de fin de programme (OK/KO)                
     <p_fichier_temp> : Nom du fichier temporaire a supprimer
   Historique	:
	---------------------------------------------------------------------------
	Fonction	|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   fin_prg	|09/10/2000 | FAU		| Creation (@fonction)
@(#)   fin_prg	|09/10/2000 | SNE		| Adaptation, mise au point
 ====================================================================================
*/
void fin_prg(int p_status, char *p_fichier_temp) 
{

  char v_commande[100]="\0";
 

  /* Destruction du fichier temporaire */
  if (p_fichier_temp != NULL && strlen(p_fichier_temp) ) remove(p_fichier_temp);

  /* rename des fichier logs SCRUTATEUR et AT */
  COMMUN_Date_du_jour(FRMT_EXT_F_LOG, dat);
  sprintf(v_fic_sav, "%s_%s.log", v_scrut_log, dat);

/*
	Arret des traces scrutateur (fermeture fichier & renommage)
*/
  if ( COMMUN_close_log(v_scrut_log) != TRT_OK){
	p_status = KO;
  }

COMMUN_ecrit_log_var(COMMUN_BALISE_INFORMATIVE, "%s %d\n", v_scrut_log, COMMUN_existe_fichier(v_scrut_log) );
    /* rename des fichier logs SCRUTATEUR et AT */
	if ( rename(v_scrut_log, v_fic_sav) == 0 ){
         CBASE_affiche_message(SCRUT_ERR_000007, COMMUN_BALISE_INFORMATIVE, scrut_param_exec.nom_programme, NULL, NULL);
      }
      else{
	   switch(errno){
		case ENOENT:
    			CBASE_affiche_message(SCRUT_ERR_000049, COMMUN_BALISE_ERREUR, v_scrut_log, NULL, NULL);
		break;
		
		case EACCES:
    			CBASE_affiche_message(SCRUT_ERR_000050, COMMUN_BALISE_ERREUR, v_scrut_log, NULL, NULL);
		break;

		case EINVAL:
    			CBASE_affiche_message(SCRUT_ERR_000051, COMMUN_BALISE_ERREUR, v_fic_sav, NULL, NULL);
		break;

		default:
			sprintf(v_fic_sav, "%d\0", errno);		/* on se sert de v_fic_sav juste pour la conversion int->char */
    			CBASE_affiche_message(SCRUT_ERR_000029, COMMUN_BALISE_ERREUR, v_fic_sav, NULL, NULL);
		break;
	   }
	}

  if (p_status == OK)
       exit(0);
   else 
       exit(1);
} /* fin de fin_prg */



/*
 ====================================================================================
   Nom 		: main
   Description 	: Programme principal
   Auteur	: Florent AUBARET
   Date creation: 09/10/2000
   parametres    :
      <argc> : Nombre de parametres de la lignes de commande                
      <argv> : pointeur sur la liste des parametres 
   Historique	:
	---------------------------------------------------------------------------
	Fonction	|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   main		|09/10/2000 | FAU		| Creation (@fonction)
@(#)   main 	|18/01/2001 | SNE		| Adaptation, mise au point
 ====================================================================================
*/
main(argc,argv)
  int  argc; 
  char *argv[];
{
  /* variables locales */
  int v_fin=0,
      v_sleep=0,
      v_flag_lance=0,
	v_retour;

  char v_user_file[256]="\0",
       v_cfg_file[256]="\0",
       v_temp[800]="\0",
       v_fcmd[1024]="\0",
       v_fcmd_log[1024]="\0",
       v_fcmd_par[1024]="\0",
       v_fic_edt[256]="\0",
       v_cmdat[1024]="\0",
       v_cmd[1024]="\0",
	v_nom_fic_log[256] = "",

       v_annee[6]="\0",
       v_mois[4]="\0",
       v_jour[4]="\0",
       v_heure[4]="\0",
       v_minute[4]="\0",
       v_seconde[4]="\0",

       v_at_file[256]="\0",
       v_commande[100]="\0",
	   v_commande2[100]="\0",
       v_instance[LG_NOM_INSTANCE]="\0",
       v_error_file[LG_NOM_FIC]="\0",
       v_date_systeme[20]="\0",
 	 v_ret_char[10] ="\0";

  char v_nivdebug[2]="\0";

  FILE *v_fat;

  /*------------------------*/
  /* analyse des parametres */
  /*------------------------*/
  scrut_os = COMMUN_intGet_Os();
  COMMUN_Date_du_jour(FORMAT_DAT_LOG, v_date_systeme);

  if (argc < NBRE_ARG_REQUIS) 
  {
    printf(ENTETE_MESSAGE_LOG " : nombre de parametre %d incorrect\n", v_date_systeme, BALISE_ERREUR, SCRUT_NOM_PROGRAMME, argc);
    printf("#E#%s : %s <fichier config> <periode> <instance> <utilisateur> <fichier utilisateurs> <fichier erreurs> \n", SCRUT_NOM_PROGRAMME, SCRUT_NOM_PROGRAMME);
    exit(1);
  } 

  strcpy(v_cfg_file, argv[PARAM_NOM_FIC_CFG]);
  v_sleep=atoi(argv[PARAM_PERIODE_SCR]);
  strcpy(v_instance, argv[PARAM_NOM_INS_SCR]);
  strcpy(v_utilisateur, argv[PARAM_NOM_UTI_SCR]);
  scrut_param_exec.mode_trace = TRACE_DANS_FIC;
  scrut_param_exec.niveau_debug = DEBUG_SANS_DEBUG;

  if (argc > PARAM_NOM_FIC_UTI) strcpy(v_user_file, argv[PARAM_NOM_FIC_UTI]);
  if (argc > PARAM_NOM_FIC_ERR) strcpy(v_error_file, argv[PARAM_NOM_FIC_ERR]);
  if (argc > PARAM_MODE_TRACE) scrut_param_exec.mode_trace = atoi( argv[PARAM_MODE_TRACE]);
  if (argc > PARAM_NIVEAU_DEBUG) scrut_param_exec.niveau_debug = atoi( argv[PARAM_NIVEAU_DEBUG]);
  if (argc > PARAM_NOM_FIC_LOG) strcpy(v_scrut_log, argv[PARAM_NOM_FIC_LOG]);
 
 /* SNE, 03/01/2001 : Fixation du mode et du niveau de trace d'execution */
 strcpy(scrut_param_exec.fichier_config, v_cfg_file);
 strcpy(scrut_param_exec.fichier_erreur, v_error_file);
 strcpy(scrut_param_exec.nom_programme, *argv);
 COMMUN_init_param_execution (scrut_param_exec);
  
  /* concaténation de _L1 au nom de l'instance pour */
  /* avoir le nom conventionnel du listener nommé   */


  /* -- AT -- sprintf(v_scrut_log_at, "%s_AT", v_scrut_log); */
  /* SNE, 2/01/2001 : Si nom log non specifie alors on va le chercher dans le fichier de configuration */
  if (!strlen(v_scrut_log)) 
  	if ( COMMUN_lire_info(v_cfg_file, v_instance, VAR_SCRUT_TMP, v_scrut_log) != OK) 
			fin_prg(KO, NULL);

  if (scrut_param_exec.niveau_debug >= DEBUG_NIVEAU_DETAIL){
	 printf(ENTETE_MESSAGE_LOG " Apres lecture : Nom du fichier cfg :%s\n", v_date_systeme, BALISE_INFORMATIVE, SCRUT_NOM_PROGRAMME, v_scrut_log);
  }
  /*
	SNE, 27/02/2001 : Adaptation de la fonction
  */
  if (COMMUN_open_log(v_scrut_log, SCRUT_NOM_PROGRAMME) != TRT_OK){
	exit(1);
  }
  if ( COMMUN_lire_info(v_cfg_file, v_instance, VAR_BATCH, v_batch_dir) != OK) {
	fin_prg(KO, NULL);
  }
  if ( COMMUN_lire_info(v_cfg_file, v_instance, VAR_BATCH_LOG, v_batch_log) != OK ){
	 fin_prg(KO, NULL);
  }
  if ( COMMUN_lire_info(v_cfg_file, v_instance, VAR_BATCH_TMP, v_batch_tmp) != OK )
	 strcpy(v_batch_tmp, v_batch_log);

  /* Contrôle de l'environnement */
  COMMUN_check_env(v_batch_log, v_separateur, v_dev_null, scrut_separateur_chemin);

  

  /*----------------*/
  /* Connect ORACLE */
  /*----------------*/
  /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 

  if ( CBASE_connexion_base(scrut_param_exec.fichier_config, v_instance, v_user_file, v_utilisateur) != TRT_OK){
    CBASE_affiche_message(SCRUT_ERR_00002,  COMMUN_BALISE_ERREUR,  sqlca.sqlerrm.sqlerrmc,  NULL, NULL);
    exit(1);
  }

  CBASE_mot_de_passe_connexion(v_passwd);

  sprintf(v_temp, "%s %d %s %s", v_scrut_log, v_sleep, v_utilisateur, v_user_file);
  CBASE_affiche_message(SCRUT_ERR_000039, COMMUN_BALISE_INFORMATIVE, v_temp, NULL, NULL);

  /*-----------------*/
  /* Curseurs ORACLE */
  /*-----------------*/
  /* EXEC SQL DECLARE c_b_traitement CURSOR FOR
    SELECT numtrt,
           nomprog,
           nvl(libprog,' '),
           type,
           execution,
           nvl(media_edt,' '),
           nature,
           nvl(to_char(exec_heure,'YYYYMMDDHH24MI'), 'aucune'),
           nvl(dir_prog,' '),
           nvl(dir_edt,' '),
           nvl(dir_dem,' '),
           nvl(replace(destinataire, ' ', '-'), ' '),
           nvl(imprimante,' '),
           nvl(orientation,' '),
           nvl(copies,1),
           nvl(cod_format,'XX'),
           nvl(recto_verso,'X'),
           nvl(sens_rv,'X'),
           nvl(bac,'X'),
           code_fin,
           dat_cre,
           uti_cre,
           dat_maj,
           uti_maj,
           terminal
    FROM b_traitement
    WHERE code_fin='D'
    ORDER BY numtrt; */ 


  /* EXEC SQL DECLARE c_b_paramtrt CURSOR FOR
    SELECT nomparam,
           nvl(param,decode(b_traitement.type,'B','""','C','""',' '))
    FROM b_paramtrt,
         b_traitement
    WHERE b_paramtrt.numtrt = b_traitement.numtrt
      AND b_paramtrt.numtrt = :sql_numtrt
    ORDER BY b_paramtrt.numtrt,b_paramtrt.indpar; */ 


  /* -------------------------- */ 
  /* Extraction du site courant */
  /* -------------------------- */
  /* EXEC SQL WHENEVER NOT FOUND continue; */ 

  /* EXEC SQL SELECT val_param 
           INTO sql_site_util
           FROM sr_param
           WHERE sr_param.ide_param = 'SM0008'
             AND ( TRUNC(sr_param.dat_dval) <= TRUNC(sysdate) OR sr_param.dat_dval IS NULL )
             AND ( TRUNC(sr_param.dat_fval) >= TRUNC(sysdate) OR sr_param.dat_fval IS NULL ); */ 

{
  struct sqlexd sqlstm;

  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 1;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select val_param into :b0  from sr_param where ((sr_param.i\
de_param='SM0008' and (TRUNC(sr_param.dat_dval)<=TRUNC(sysdate) or sr_param.da\
t_dval is null )) and (TRUNC(sr_param.dat_fval)>=TRUNC(sysdate) or sr_param.da\
t_fval is null ))";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&sql_site_util;
  sqlstm.sqhstl[0] = (unsigned int  )8;
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



  if ( sqlca.sqlcode < 0 ) 
  {
    CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
    fin_prg(KO, NULL);
  }
      
  sql_site_util.arr[sql_site_util.len]='\0';


   /* NDY 08/04/2002 V3.0 : creation des variables globales de traitement (date systeme et niveau de trace) */
   if ( CBASE_cree_var_trt(SCRUT_VAR_DATE_SYSTEME,SCRUT_VAR_P_DAT_SYS,SCRUT_VAR_DATE_SYS_VAL) != OK)
	   fin_prg(KO, NULL);
   sprintf(v_nivdebug,"%d",scrut_param_exec.niveau_debug);
   if ( CBASE_cree_var_trt(SCRUT_VAR_NIVEAU_TRACE,SCRUT_VAR_P_NIV_TRACE,v_nivdebug) != OK)
	   fin_prg(KO, NULL);


  /*------------------------------*/
  /* boucle infinie de traitement */
  /*------------------------------*/
  v_fin=0;
  while ( v_fin==0 ) 
  {

    /*---------------------------------*/
    /* Traitement curseur B_TRAITEMENT */
    /*---------------------------------*/
    /* EXEC SQL OPEN c_b_traitement; */ 

{
    struct sqlexd sqlstm;

    sqlstm.sqlvsn = 10;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = sq0001;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )24;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


    if ( sqlca.sqlcode != 0 ) 
    {
      CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
      fin_prg(KO, NULL);
    }

    /* boucle parcours curseur B_TRAITEMENT */
    /* EXEC SQL WHENEVER NOT FOUND DO break; */ 

    while (1) 
    {
      /* EXEC SQL FETCH c_b_traitement 
               INTO :sql_numtrt,
                    :sql_nomprog,
                    :sql_libprog,
                    :sql_type,
                    :sql_execution,
                    :sql_media_edt,
                    :sql_nature,
                    :sql_exec_heure,
                    :sql_dir_prog,
                    :sql_dir_edt,
                    :sql_dir_dem,
                    :sql_destinataire,
                    :sql_imprimante,
                    :sql_orientation,
                    :sql_copies,
                    :sql_cod_format,
                    :sql_recto_verso,
                    :sql_sens_rv,
                    :sql_bac,
                    :sql_code_fin,
                    :sql_dat_cre,
                    :sql_uti_cre,
                    :sql_dat_maj,
                    :sql_uti_maj,
                    :sql_terminal; */ 

{
      struct sqlexd sqlstm;

      sqlstm.sqlvsn = 10;
      sqlstm.arrsiz = 25;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )39;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&sql_numtrt;
      sqlstm.sqhstl[0] = (unsigned int  )4;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)&sql_nomprog;
      sqlstm.sqhstl[1] = (unsigned int  )23;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)&sql_libprog;
      sqlstm.sqhstl[2] = (unsigned int  )59;
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void  *)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void  *)&sql_type;
      sqlstm.sqhstl[3] = (unsigned int  )4;
      sqlstm.sqhsts[3] = (         int  )0;
      sqlstm.sqindv[3] = (         void  *)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqhstv[4] = (         void  *)&sql_execution;
      sqlstm.sqhstl[4] = (unsigned int  )4;
      sqlstm.sqhsts[4] = (         int  )0;
      sqlstm.sqindv[4] = (         void  *)0;
      sqlstm.sqinds[4] = (         int  )0;
      sqlstm.sqharm[4] = (unsigned int  )0;
      sqlstm.sqadto[4] = (unsigned short )0;
      sqlstm.sqtdso[4] = (unsigned short )0;
      sqlstm.sqhstv[5] = (         void  *)&sql_media_edt;
      sqlstm.sqhstl[5] = (unsigned int  )4;
      sqlstm.sqhsts[5] = (         int  )0;
      sqlstm.sqindv[5] = (         void  *)0;
      sqlstm.sqinds[5] = (         int  )0;
      sqlstm.sqharm[5] = (unsigned int  )0;
      sqlstm.sqadto[5] = (unsigned short )0;
      sqlstm.sqtdso[5] = (unsigned short )0;
      sqlstm.sqhstv[6] = (         void  *)&sql_nature;
      sqlstm.sqhstl[6] = (unsigned int  )4;
      sqlstm.sqhsts[6] = (         int  )0;
      sqlstm.sqindv[6] = (         void  *)0;
      sqlstm.sqinds[6] = (         int  )0;
      sqlstm.sqharm[6] = (unsigned int  )0;
      sqlstm.sqadto[6] = (unsigned short )0;
      sqlstm.sqtdso[6] = (unsigned short )0;
      sqlstm.sqhstv[7] = (         void  *)&sql_exec_heure;
      sqlstm.sqhstl[7] = (unsigned int  )42;
      sqlstm.sqhsts[7] = (         int  )0;
      sqlstm.sqindv[7] = (         void  *)0;
      sqlstm.sqinds[7] = (         int  )0;
      sqlstm.sqharm[7] = (unsigned int  )0;
      sqlstm.sqadto[7] = (unsigned short )0;
      sqlstm.sqtdso[7] = (unsigned short )0;
      sqlstm.sqhstv[8] = (         void  *)&sql_dir_prog;
      sqlstm.sqhstl[8] = (unsigned int  )63;
      sqlstm.sqhsts[8] = (         int  )0;
      sqlstm.sqindv[8] = (         void  *)0;
      sqlstm.sqinds[8] = (         int  )0;
      sqlstm.sqharm[8] = (unsigned int  )0;
      sqlstm.sqadto[8] = (unsigned short )0;
      sqlstm.sqtdso[8] = (unsigned short )0;
      sqlstm.sqhstv[9] = (         void  *)&sql_dir_edt;
      sqlstm.sqhstl[9] = (unsigned int  )63;
      sqlstm.sqhsts[9] = (         int  )0;
      sqlstm.sqindv[9] = (         void  *)0;
      sqlstm.sqinds[9] = (         int  )0;
      sqlstm.sqharm[9] = (unsigned int  )0;
      sqlstm.sqadto[9] = (unsigned short )0;
      sqlstm.sqtdso[9] = (unsigned short )0;
      sqlstm.sqhstv[10] = (         void  *)&sql_dir_dem;
      sqlstm.sqhstl[10] = (unsigned int  )63;
      sqlstm.sqhsts[10] = (         int  )0;
      sqlstm.sqindv[10] = (         void  *)0;
      sqlstm.sqinds[10] = (         int  )0;
      sqlstm.sqharm[10] = (unsigned int  )0;
      sqlstm.sqadto[10] = (unsigned short )0;
      sqlstm.sqtdso[10] = (unsigned short )0;
      sqlstm.sqhstv[11] = (         void  *)&sql_destinataire;
      sqlstm.sqhstl[11] = (unsigned int  )33;
      sqlstm.sqhsts[11] = (         int  )0;
      sqlstm.sqindv[11] = (         void  *)0;
      sqlstm.sqinds[11] = (         int  )0;
      sqlstm.sqharm[11] = (unsigned int  )0;
      sqlstm.sqadto[11] = (unsigned short )0;
      sqlstm.sqtdso[11] = (unsigned short )0;
      sqlstm.sqhstv[12] = (         void  *)&sql_imprimante;
      sqlstm.sqhstl[12] = (unsigned int  )18;
      sqlstm.sqhsts[12] = (         int  )0;
      sqlstm.sqindv[12] = (         void  *)0;
      sqlstm.sqinds[12] = (         int  )0;
      sqlstm.sqharm[12] = (unsigned int  )0;
      sqlstm.sqadto[12] = (unsigned short )0;
      sqlstm.sqtdso[12] = (unsigned short )0;
      sqlstm.sqhstv[13] = (         void  *)&sql_orientation;
      sqlstm.sqhstl[13] = (unsigned int  )12;
      sqlstm.sqhsts[13] = (         int  )0;
      sqlstm.sqindv[13] = (         void  *)0;
      sqlstm.sqinds[13] = (         int  )0;
      sqlstm.sqharm[13] = (unsigned int  )0;
      sqlstm.sqadto[13] = (unsigned short )0;
      sqlstm.sqtdso[13] = (unsigned short )0;
      sqlstm.sqhstv[14] = (         void  *)&sql_copies;
      sqlstm.sqhstl[14] = (unsigned int  )4;
      sqlstm.sqhsts[14] = (         int  )0;
      sqlstm.sqindv[14] = (         void  *)0;
      sqlstm.sqinds[14] = (         int  )0;
      sqlstm.sqharm[14] = (unsigned int  )0;
      sqlstm.sqadto[14] = (unsigned short )0;
      sqlstm.sqtdso[14] = (unsigned short )0;
      sqlstm.sqhstv[15] = (         void  *)&sql_cod_format;
      sqlstm.sqhstl[15] = (unsigned int  )5;
      sqlstm.sqhsts[15] = (         int  )0;
      sqlstm.sqindv[15] = (         void  *)0;
      sqlstm.sqinds[15] = (         int  )0;
      sqlstm.sqharm[15] = (unsigned int  )0;
      sqlstm.sqadto[15] = (unsigned short )0;
      sqlstm.sqtdso[15] = (unsigned short )0;
      sqlstm.sqhstv[16] = (         void  *)&sql_recto_verso;
      sqlstm.sqhstl[16] = (unsigned int  )4;
      sqlstm.sqhsts[16] = (         int  )0;
      sqlstm.sqindv[16] = (         void  *)0;
      sqlstm.sqinds[16] = (         int  )0;
      sqlstm.sqharm[16] = (unsigned int  )0;
      sqlstm.sqadto[16] = (unsigned short )0;
      sqlstm.sqtdso[16] = (unsigned short )0;
      sqlstm.sqhstv[17] = (         void  *)&sql_sens_rv;
      sqlstm.sqhstl[17] = (unsigned int  )4;
      sqlstm.sqhsts[17] = (         int  )0;
      sqlstm.sqindv[17] = (         void  *)0;
      sqlstm.sqinds[17] = (         int  )0;
      sqlstm.sqharm[17] = (unsigned int  )0;
      sqlstm.sqadto[17] = (unsigned short )0;
      sqlstm.sqtdso[17] = (unsigned short )0;
      sqlstm.sqhstv[18] = (         void  *)&sql_bac;
      sqlstm.sqhstl[18] = (unsigned int  )23;
      sqlstm.sqhsts[18] = (         int  )0;
      sqlstm.sqindv[18] = (         void  *)0;
      sqlstm.sqinds[18] = (         int  )0;
      sqlstm.sqharm[18] = (unsigned int  )0;
      sqlstm.sqadto[18] = (unsigned short )0;
      sqlstm.sqtdso[18] = (unsigned short )0;
      sqlstm.sqhstv[19] = (         void  *)&sql_code_fin;
      sqlstm.sqhstl[19] = (unsigned int  )4;
      sqlstm.sqhsts[19] = (         int  )0;
      sqlstm.sqindv[19] = (         void  *)0;
      sqlstm.sqinds[19] = (         int  )0;
      sqlstm.sqharm[19] = (unsigned int  )0;
      sqlstm.sqadto[19] = (unsigned short )0;
      sqlstm.sqtdso[19] = (unsigned short )0;
      sqlstm.sqhstv[20] = (         void  *)&sql_dat_cre;
      sqlstm.sqhstl[20] = (unsigned int  )42;
      sqlstm.sqhsts[20] = (         int  )0;
      sqlstm.sqindv[20] = (         void  *)0;
      sqlstm.sqinds[20] = (         int  )0;
      sqlstm.sqharm[20] = (unsigned int  )0;
      sqlstm.sqadto[20] = (unsigned short )0;
      sqlstm.sqtdso[20] = (unsigned short )0;
      sqlstm.sqhstv[21] = (         void  *)&sql_uti_cre;
      sqlstm.sqhstl[21] = (unsigned int  )18;
      sqlstm.sqhsts[21] = (         int  )0;
      sqlstm.sqindv[21] = (         void  *)0;
      sqlstm.sqinds[21] = (         int  )0;
      sqlstm.sqharm[21] = (unsigned int  )0;
      sqlstm.sqadto[21] = (unsigned short )0;
      sqlstm.sqtdso[21] = (unsigned short )0;
      sqlstm.sqhstv[22] = (         void  *)&sql_dat_maj;
      sqlstm.sqhstl[22] = (unsigned int  )42;
      sqlstm.sqhsts[22] = (         int  )0;
      sqlstm.sqindv[22] = (         void  *)0;
      sqlstm.sqinds[22] = (         int  )0;
      sqlstm.sqharm[22] = (unsigned int  )0;
      sqlstm.sqadto[22] = (unsigned short )0;
      sqlstm.sqtdso[22] = (unsigned short )0;
      sqlstm.sqhstv[23] = (         void  *)&sql_uti_maj;
      sqlstm.sqhstl[23] = (unsigned int  )18;
      sqlstm.sqhsts[23] = (         int  )0;
      sqlstm.sqindv[23] = (         void  *)0;
      sqlstm.sqinds[23] = (         int  )0;
      sqlstm.sqharm[23] = (unsigned int  )0;
      sqlstm.sqadto[23] = (unsigned short )0;
      sqlstm.sqtdso[23] = (unsigned short )0;
      sqlstm.sqhstv[24] = (         void  *)&sql_terminal;
      sqlstm.sqhstl[24] = (unsigned int  )13;
      sqlstm.sqhsts[24] = (         int  )0;
      sqlstm.sqindv[24] = (         void  *)0;
      sqlstm.sqinds[24] = (         int  )0;
      sqlstm.sqharm[24] = (unsigned int  )0;
      sqlstm.sqadto[24] = (unsigned short )0;
      sqlstm.sqtdso[24] = (unsigned short )0;
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
      if (sqlca.sqlcode == 1403) break;
}



      sql_nomprog.arr[sql_nomprog.len]='\0';
      sql_libprog.arr[sql_libprog.len]='\0';
      sql_type.arr[sql_type.len]='\0';
      sql_execution.arr[sql_execution.len]='\0';
      sql_media_edt.arr[sql_media_edt.len]='\0';
      sql_nature.arr[sql_nature.len]='\0';
      sql_exec_heure.arr[sql_exec_heure.len]='\0';
      sql_dir_prog.arr[sql_dir_prog.len]='\0';
      sql_dir_edt.arr[sql_dir_edt.len]='\0';
      sql_dir_dem.arr[sql_dir_dem.len]='\0';
      sql_destinataire.arr[sql_destinataire.len]='\0';
      sql_imprimante.arr[sql_imprimante.len]='\0';
      sql_orientation.arr[sql_orientation.len]='\0';
      sql_copies.arr[sql_copies.len]='\0';
      sql_cod_format.arr[sql_cod_format.len]='\0';
      sql_recto_verso.arr[sql_recto_verso.len]='\0';
      sql_sens_rv.arr[sql_sens_rv.len]='\0';
      sql_bac.arr[sql_bac.len]='\0';
      sql_code_fin.arr[sql_code_fin.len]='\0';
      sql_uti_cre.arr[sql_uti_cre.len]='\0';
      sql_dat_cre.arr[sql_dat_cre.len]='\0';
      sql_uti_maj.arr[sql_uti_maj.len]='\0';
      sql_dat_maj.arr[sql_dat_maj.len]='\0';
      sql_terminal.arr[sql_terminal.len]='\0';

      if ( sqlca.sqlcode != 0 ) 
      {
        CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
        fin_prg(KO, NULL);
      }

      if (strcmp(sql_nomprog.arr,ARRET_SCRUTATEUR) == 0) 
      {
        /* arret du scrutateur */
        v_fin=1;
        CBASE_affiche_message(SCRUT_ERR_000038, COMMUN_BALISE_INFORMATIVE, NULL, NULL, NULL);
        /* EXEC SQL WHENEVER NOT FOUND continue; */ 

        /* EXEC SQL DELETE FROM b_traitement
                 WHERE nomprog = 'SCRUT_STOP'; */ 

{
        struct sqlexd sqlstm;

        sqlstm.sqlvsn = 10;
        sqlstm.arrsiz = 25;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "delete  from b_traitement  where nomprog='SCRUT_STOP'";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )154;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)256;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        if ( sqlca.sqlcode < 0 ) 
        {
          CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
          fin_prg(KO, NULL);
        }
        /* EXEC SQL COMMIT; */ 

{
        struct sqlexd sqlstm;

        sqlstm.sqlvsn = 10;
        sqlstm.arrsiz = 25;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )169;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)256;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        if ( sqlca.sqlcode != 0 ) 
        {
          CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
          fin_prg(KO, NULL);
        }
        break;
      }

      /* Extraction du mot de passe de l'utilisateur de connexion */
      /* Extraction du mot de passe crypte                        */
      /* EXEC SQL WHENEVER NOT FOUND continue; */ 

      /* EXEC SQL SELECT count(*)
               INTO :sql_count
               FROM fh_util
               WHERE fh_util.ide_site = :sql_site_util
                 AND fh_util.cod_util = :sql_uti_cre; */ 

{
      struct sqlexd sqlstm;

      sqlstm.sqlvsn = 10;
      sqlstm.arrsiz = 25;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "select count(*)  into :b0  from fh_util where (fh_util.\
ide_site=:b1 and fh_util.cod_util=:b2)";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )184;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&sql_count;
      sqlstm.sqhstl[0] = (unsigned int  )4;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)&sql_site_util;
      sqlstm.sqhstl[1] = (unsigned int  )8;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)&sql_uti_cre;
      sqlstm.sqhstl[2] = (unsigned int  )18;
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


      if ( sqlca.sqlcode != 0 )
      {
        CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
        fin_prg(KO, NULL);
      }

      if ( sql_count == 0 ) 
      {
        /* utilisateur non défini dans la table des utilisateurs */
        /* --> le traitement ne pourra jamais être lancé         */
        CBASE_affiche_message(SCRUT_ERR_000040, COMMUN_BALISE_ERREUR, sql_uti_cre.arr, NULL, NULL);
        strcpy(sql_code_fin.arr, "A");
        sql_code_fin.len = strlen(sql_code_fin.arr);
        /* EXEC SQL WHENEVER NOT FOUND continue; */ 

        /* EXEC SQL SELECT libl
                 INTO sql_lib_erreur
                 FROM sr_mess_err
                 WHERE ide_mess_err = 9; */ 

{
        struct sqlexd sqlstm;

        sqlstm.sqlvsn = 10;
        sqlstm.arrsiz = 25;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select libl into :b0  from sr_mess_err where ide_mess\
_err=9";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )211;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)256;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)&sql_lib_erreur;
        sqlstm.sqhstl[0] = (unsigned int  )253;
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

 
        sql_lib_erreur.arr[sql_lib_erreur.len]='\0';

        /* maj du traitement + sortie de la boucle :                     */ 
        /* ne pas lancer ce traitement, il n'a pas d'utilisateur correct */
        /* EXEC SQL WHENEVER NOT FOUND continue; */ 

        /* EXEC SQL UPDATE b_traitement
                 SET code_fin = :sql_code_fin,
                     lib_erreur = :sql_lib_erreur,
                     dat_maj  = sysdate
                 WHERE numtrt = :sql_numtrt; */ 

{
        struct sqlexd sqlstm;

        sqlstm.sqlvsn = 10;
        sqlstm.arrsiz = 25;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "update b_traitement  set code_fin=:b0,lib_erreur=:b1,\
dat_maj=sysdate where numtrt=:b2";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )230;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)256;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)&sql_code_fin;
        sqlstm.sqhstl[0] = (unsigned int  )4;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         void  *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned int  )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (         void  *)&sql_lib_erreur;
        sqlstm.sqhstl[1] = (unsigned int  )253;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         void  *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned int  )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (         void  *)&sql_numtrt;
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


        if ( sqlca.sqlcode < 0 ) 
        {
          CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
          fin_prg(KO, NULL);
        }

        /* EXEC SQL COMMIT; */ 

{
        struct sqlexd sqlstm;

        sqlstm.sqlvsn = 10;
        sqlstm.arrsiz = 25;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )257;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)256;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        if ( sqlca.sqlcode != 0 ) 
        {
          CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
          fin_prg(KO, NULL);
        }
        break;  
      }

      /* EXEC SQL WHENEVER NOT FOUND continue; */ 

      /* EXEC SQL SELECT pwd
               INTO sql_pwd_crypt
               FROM fh_util
               WHERE fh_util.ide_site = :sql_site_util
                 AND fh_util.cod_util = :sql_uti_cre; */ 

{
      struct sqlexd sqlstm;

      sqlstm.sqlvsn = 10;
      sqlstm.arrsiz = 25;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "select pwd into :b0  from fh_util where (fh_util.ide_si\
te=:b1 and fh_util.cod_util=:b2)";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )272;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&sql_pwd_crypt;
      sqlstm.sqhstl[0] = (unsigned int  )33;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)&sql_site_util;
      sqlstm.sqhstl[1] = (unsigned int  )8;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)&sql_uti_cre;
      sqlstm.sqhstl[2] = (unsigned int  )18;
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


      if ( sqlca.sqlcode != 0 ) 
      {
        CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
        CBASE_affiche_message(SCRUT_ERR_712,  COMMUN_BALISE_ERREUR,  NULL, NULL, NULL);
        COMMUN_dernier_message_erreur(scrut_dernier_message_erreur);
	  if (change_etat_traitement(KO, scrut_dernier_message_erreur) == ERR_EXEC_SQL) fin_prg(KO, NULL);
        break;
      }
      else 
      {
        /* Décryptage du mot de passe */
        /* EXEC SQL CALL Security.UnEncrypt(:sql_pwd_crypt, 'azertyuiopmlkjhgfdsqwxcvbn1593')
                 INTO :sql_pwd_uncrypt; */ 

{
        struct sqlexd sqlstm;

        sqlstm.sqlvsn = 10;
        sqlstm.arrsiz = 25;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "call Security.UnEncrypt(:b0,'azertyuiopmlkjhgfdsqwxcv\
bn1593') into :b1 ";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )299;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)256;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)&sql_pwd_crypt;
        sqlstm.sqhstl[0] = (unsigned int  )33;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         void  *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned int  )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (         void  *)&sql_pwd_uncrypt;
        sqlstm.sqhstl[1] = (unsigned int  )33;
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


        if ( sqlca.sqlcode != 0 ) 
        {
          CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
          CBASE_affiche_message(SCRUT_ERR_713,  COMMUN_BALISE_ERREUR,  NULL, NULL, NULL);
    	    COMMUN_dernier_message_erreur(scrut_dernier_message_erreur);
	    if (change_etat_traitement(KO, scrut_dernier_message_erreur) == ERR_EXEC_SQL) fin_prg(KO, NULL);
          break;

        }
      }

      sql_pwd_crypt.arr[sql_pwd_crypt.len]='\0';       
      sql_pwd_uncrypt.arr[sql_pwd_uncrypt.len]='\0';

      /* Recherche du nombre de parametres utilisateurs */
      /* EXEC SQL WHENEVER NOT FOUND continue; */ 

      /* EXEC SQL SELECT COUNT(*) 
               INTO :sql_nbparam
               FROM  b_paramtrt
               WHERE b_paramtrt.numtrt = :sql_numtrt; */ 

{
      struct sqlexd sqlstm;

      sqlstm.sqlvsn = 10;
      sqlstm.arrsiz = 25;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "select count(*)  into :b0  from b_paramtrt where b_para\
mtrt.numtrt=:b1";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )322;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&sql_nbparam;
      sqlstm.sqhstl[0] = (unsigned int  )4;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)&sql_numtrt;
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


      if ( sqlca.sqlcode < 0 ) 
      {
        CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
        fin_prg(KO, NULL);
      }

      /* initialisation chaine de commande fonction de la nature du traitement exploitant(E) ou utilisateur(U)         */
      /* --> nature E : preparation de l'enregistrement à inserer dans le fichier des demandes                         */
      /* --> nature U : preparation de la commnades à lancer (prise en compte des parametres implicites) :             */
      /*                Instance                                                                                       */
      /*                Utilisateur                                                                                    */      
      /*                Mot de passe                                                                                   */
      /*                Numero de traitement                                                                           */
      /*                Nom du programme                                                                               */
      /*                Type de traitement                                                                             */
      /*                Repertoire du programme                                                                        */
      /*                Libelle du traitement                                                                          */
      /*                Nombre de parametres                                                                           */

      if (strcmp(sql_nature.arr, COMMUN_CODE_NAT_PRG_EXPL) == 0) 
      {
        sprintf(v_fcmd,"%s;%s;%s;%s;%s;\0", sql_nomprog.arr, sql_dir_prog.arr, sql_type.arr, sql_uti_cre.arr, sql_dat_maj.arr);         
      }
      else 
      {
           sprintf(v_fcmd, "%s %s %s %d %s %s %s \"%s\" %d\0", v_instance, sql_uti_cre.arr, sql_pwd_uncrypt.arr, sql_numtrt, sql_nomprog.arr, sql_type.arr, sql_dir_prog.arr, sql_libprog.arr, sql_nbparam);
           sprintf(v_fcmd_log, "%s %s ****** %d %s %s %s \"%s\" %d\0", v_instance, sql_uti_cre.arr, sql_numtrt, sql_nomprog.arr, sql_type.arr, sql_dir_prog.arr, sql_libprog.arr, sql_nbparam);
      }
      
      /* Traitement des parametres REPORTS pour les editions (TYPE = E) ou les chaines (TYPE = C) */
      /* Valorisation des parametres :                                                            */
      /*   DESNAME, DESTYPE, DESFORMAT, ORIENTATION, COPIES, FORMAT, RECTO/VERSO, SENS RV, BAC    */
      sprintf(v_fcmd_par,"");
    
      if ( (strcmp(sql_type.arr, COMMUN_CODE_TYP_PRG_EDIT) == 0 ) || (strcmp(sql_type.arr, COMMUN_CODE_TYP_PRG_CHAINE) == 0 ) ) 
      {
        if (strcmp(sql_media_edt.arr, COMMUN_DST_TRT_FICHIER) == 0 ) 
        {
		
  	    COMMUN_Date_du_jour(FRMT_EXT_F_LOG, dat);
          sprintf(v_fic_edt, "%s%s%s_%s_%s_%s.edt", sql_dir_edt.arr, v_separateur, sql_nomprog.arr, sql_destinataire.arr, sql_uti_cre.arr, dat); 
          strcat(v_fcmd_par," DESTYPE=FILE\0");		/* SNE, 04/01/2001 */
	    if (strlen(v_fic_edt)){
              strcat(v_fcmd_par," DESNAME=\0");
              strcat(v_fcmd_par, v_fic_edt);
	    }
          strcat(v_fcmd_par," DESFORMAT=\0");
          strcat(v_fcmd_par, sql_imprimante.arr);
        }
        else 
        {
          strcat(v_fcmd_par," DESTYPE=printer\0");
	    if (strlen(sql_imprimante.arr)){
          	strcat(v_fcmd_par," DESNAME=\0");
          	strcat(v_fcmd_par, sql_imprimante.arr);
	    }
          strcat(v_fcmd_par," DESFORMAT=dflt\0");
        }
        strcat(v_fcmd_par," ORIENTATION=\0");
        strcat(v_fcmd_par, sql_orientation.arr);
        strcat(v_fcmd_par," COPIES=\0");
        strcat(v_fcmd_par, sql_copies.arr); 
        strcat(v_fcmd_par," ");
        strcat(v_fcmd_par, sql_cod_format.arr);
        strcat(v_fcmd_par," ");
        strcat(v_fcmd_par, sql_recto_verso.arr);
        strcat(v_fcmd_par," ");
        strcat(v_fcmd_par, sql_sens_rv.arr);
        strcat(v_fcmd_par," ");
        strcat(v_fcmd_par, sql_bac.arr);
      }     

      /*-----------------------------------*/
      /* boucle de parcours des parametres */
      /* constitution chaine parametre     */
      /*-----------------------------------*/
      /* EXEC SQL OPEN c_b_paramtrt; */ 

{
      struct sqlexd sqlstm;

      sqlstm.sqlvsn = 10;
      sqlstm.arrsiz = 25;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = sq0002;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )345;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&sql_numtrt;
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


      if ( sqlca.sqlcode != 0 ) 
      {
        CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
        fin_prg(KO, NULL);
      }

      while (1) 
      {
        /* EXEC SQL WHENEVER NOT FOUND DO break; */ 

        /* EXEC SQL FETCH c_b_paramtrt 
                 INTO :sql_nomparam,
                      :sql_param; */ 

{
        struct sqlexd sqlstm;

        sqlstm.sqlvsn = 10;
        sqlstm.arrsiz = 25;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )364;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)256;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)&sql_nomparam;
        sqlstm.sqhstl[0] = (unsigned int  )23;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         void  *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned int  )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (         void  *)&sql_param;
        sqlstm.sqhstl[1] = (unsigned int  )35;
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
        if (sqlca.sqlcode == 1403) break;
}


            
        sql_nomparam.arr[sql_nomparam.len]='\0';
        sql_param.arr[sql_param.len]='\0'; 
            
        if ( sqlca.sqlcode != 0 ) 
        {
          CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
          fin_prg(KO, NULL);
        }
        if (scrut_os == UNIX)
        {
          if (strcmp(sql_type.arr, COMMUN_CODE_TYP_PRG_EDIT) == 0) 
          {
            /* Formatage :                                                                           */
            /*    "PAR=xx yy zz" (pour prendre en compte les parametres de type libelle par exemple) */
            strcat(v_fcmd_par," \"\0");
            strcat(v_fcmd_par, sql_nomparam.arr);
            strcat(v_fcmd_par,"=\0");
            strcat(v_fcmd_par, sql_param.arr);
            strcat(v_fcmd_par,"\0");
            strcat(v_fcmd_par,"\"");
          }
          else 
          {   
            strcat(v_fcmd_par," \"\0");
            strcat(v_fcmd_par, sql_param.arr);
            strcat(v_fcmd_par,"\0");
            strcat(v_fcmd_par,"\"");
          }
        }
        else
        {
          if (strcmp(sql_type.arr, COMMUN_CODE_TYP_PRG_EDIT) == 0) 
          {
            /* Formatage :                                                                           */
            /*    "PAR=xx yy zz" (pour prendre en compte les parametres de type libelle par exemple) */
            strcat(v_fcmd_par," \0");
            strcat(v_fcmd_par, sql_nomparam.arr);
            strcat(v_fcmd_par,"=\"\0");
            if (strcmp(sql_param.arr," \0") != 0)

            {
               strcat(v_fcmd_par, sql_param.arr);
               strcat(v_fcmd_par,"\0");
            }
            strcat(v_fcmd_par,"\"");
          }
          else 
          {   
            strcat(v_fcmd_par," \"\0");
            strcat(v_fcmd_par, sql_param.arr);
            strcat(v_fcmd_par,"\0");
            strcat(v_fcmd_par,"\"");
          }
        }
       
      }  /* FIN DE LA BOUCLE DE PARCOURS DES PARAMETRES */ 

      strcat(v_fcmd, v_fcmd_par);   
      strcat(v_fcmd_log, v_fcmd_par);

      /* EXEC SQL CLOSE c_b_paramtrt; */ 

{
      struct sqlexd sqlstm;

      sqlstm.sqlvsn = 10;
      sqlstm.arrsiz = 25;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )387;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


      if ( sqlca.sqlcode != 0 ) 
      {
        CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
        fin_prg(KO, NULL);
      }

      /*----------------------------------------------------------------------*/
      /* lancement du AT ou dépose de la demande dans le fichier des demandes */
      /*   NATURE = E (exploitation)  --> fichier                             */
      /*   NATURE = U (utilisateur)   --> AT                                  */
      /*----------------------------------------------------------------------*/
      if ( strcmp(sql_nature.arr, COMMUN_CODE_NAT_PRG_UTIL) == 0) 
      {

          COMMUN_Date_du_jour(FRMT_EXT_F_LOG, dat);
          if ( strcmp(sql_exec_heure.arr, "aucune") == 0) 
          {
            sprintf(v_cmdat,"");
            v_flag_lance=1;
          }
          else /* Verification de l'heure */
          {
		if ( COMMUN_quand_date(sql_exec_heure.arr) == DATE_DEPASSEE )
            {
              sprintf(v_cmdat,"");
              v_flag_lance=1;
            }
            else
            {
              v_flag_lance=0;
            }
          }
          
          if (v_flag_lance == 1)
          {
          	CBASE_affiche_message(SCRUT_ERR_000007, COMMUN_BALISE_ERREUR, LANCEUR_ASTER, NULL, NULL);
	    	COMMUN_dernier_message_erreur(scrut_dernier_message_erreur);
		if ( change_etat_traitement(TRT_OK, scrut_dernier_message_erreur) == ERR_EXEC_SQL) fin_prg(KO, NULL);
 
            /* construction du fichier */
            /* sprintf(v_at_file, "%s%sstart_%s.bat", v_batch_log, v_separateur, dat); */
            sprintf(v_at_file, "%s%sstart_%s.bat", v_batch_tmp, v_separateur, dat);
            if ((v_fat = fopen(v_at_file,"w")) == NULL) 
            {
              CBASE_affiche_message(SCRUT_ERR_000027, COMMUN_BALISE_ERREUR, v_at_file, NULL, NULL);
		  fclose(v_fat);
              fin_prg(KO, v_at_file);
            }

            /* -- AT -- if ( fprintf(v_fat, "%s%sbatc%s"LANCEUR_ASTER" %s %s %s 2>>%s", v_batch_dir, v_separateur, v_separateur, v_error_file, v_cfg_file, v_fcmd, v_scrut_log_at) < 0 )  */
/*	SNE, 04/01/2001 : La redirection pose quelque probleme a Win Dose haine-tea (dixit pb de possession du fichier)
		On envoie aussi le numero de traitement pour permettre de mettre a jour le traitement à la fin
            if ( fprintf(v_fat, "%s%sbatc%s"LANCEUR_ASTER" %s %s %s 2>>%s", v_batch_dir, v_separateur, v_separateur, v_error_file, v_cfg_file, v_fcmd, v_scrut_log) < 0 )  
*/
		sprintf(v_nom_fic_log, "%s%s%s_%s_%s.log\0", v_batch_log, v_separateur, sql_nomprog.arr, sql_uti_cre.arr, dat);

            /*  MODIF SGN 3.1a-1.5 : on indique le chemin complet pour le lancement de lanceur.exe
              if ( fprintf(v_fat, LANCEUR_ASTER" %s %s %s %s %s %s\n", v_error_file, v_cfg_file, v_fcmd, v_nom_fic_log, v_utilisateur, v_user_file) < 0 )
            */
            /* MODIF SGN 3.1b-1.7 : ajout du chemin exe en dur dans la commande. */
            if ( fprintf(v_fat, "%s%sexe%s"LANCEUR_ASTER" %s %s %s %s %s %s\n", v_batch_dir, v_separateur, v_separateur, v_error_file, v_cfg_file, v_fcmd, v_nom_fic_log, v_utilisateur, v_user_file) < 0 )
            /* fin modif sgn */
            {
              CBASE_affiche_message(SCRUT_ERR_000044, COMMUN_BALISE_ERREUR, v_at_file, NULL, NULL);
		  fclose(v_fat);
	    	  COMMUN_dernier_message_erreur(scrut_dernier_message_erreur);
	    	  if (change_etat_traitement(KO, scrut_dernier_message_erreur) == ERR_EXEC_SQL) fin_prg(KO, NULL);
              fin_prg(KO, v_at_file);
            }

            fclose(v_fat);
/*		On verifie qu'un ancien log de reports de traine pas la par hasard */
		if ( COMMUN_existe_fichier(COMMUN_LOG_REPORTS) == CODE_FICHIER_EXISTANT) v_retour = (remove(COMMUN_LOG_REPORTS) == -1?errno:0);

		/* 
		SNE, Pour les fichiers UNIX, il faut d'abord les rendre executables independamment du masque de creation 
			par defaut (umask)
		*/
		COMMUN_chmod(v_at_file, COMMUN_UNIX_MODE_ADD "" COMMUN_UNIX_MODE_EXE);

			/* FBT le 13/05/2008 - EVOLUTION DI44-2007-12 */
			/* affichage */
			CBASE_affiche_message(743, COMMUN_BALISE_INFORMATIVE, sql_nomprog.arr, NULL, NULL);
			COMMUN_dernier_message_erreur(scrut_dernier_message_erreur);
			sprintf(v_commande2, "ECHO '%s'", scrut_dernier_message_erreur);
			system(v_commande2);
			/* Redirection de la commande pour ne pas l'afficher */
            sprintf(v_commande, "%s %s >> %s", v_cmdat, v_at_file,"cmd.log");

/*		if (SCRUT_lancer_traitement(LANCEUR_ASTER, v_commande, v_nom_fic_log) == OK){*/

		if (CBASE_lancer_traitement(LANCEUR_ASTER, v_commande, NULL, v_nom_fic_log, COMMUN_VRAI, scrut_dernier_message_erreur) == OK){
         		if ( strlen(scrut_dernier_message_erreur) == 0){
					CBASE_affiche_message(SCRUT_ERR_000007, COMMUN_BALISE_ERREUR, sql_nomprog.arr, NULL, NULL);
 	     			COMMUN_dernier_message_erreur(scrut_dernier_message_erreur);
		  			if (change_etat_traitement(OK, scrut_dernier_message_erreur) == ERR_EXEC_SQL) fin_prg(KO, NULL);
				}
				else
		  			if (change_etat_traitement(KO, scrut_dernier_message_erreur) == ERR_EXEC_SQL) fin_prg(KO, NULL);
		}
		else{
			CBASE_affiche_message(SCRUT_ERR_000010, COMMUN_BALISE_ERREUR, sql_nomprog.arr, NULL, NULL);
			sprintf(scrut_dernier_message_erreur, "%s " SCRUT_SUFFIXE_MESS_ERR "\0", scrut_dernier_message_erreur, v_nom_fic_log);
	  		if (change_etat_traitement(KO, scrut_dernier_message_erreur) == ERR_EXEC_SQL) fin_prg(KO, NULL);
 		}
			
		/* FBT le 13/05/2008 - EVOLUTION DI44-2007-12 */
		/* suppression des fichiers temporaires */
		remove(v_at_file);		
		remove("cmd.log");
		/* affichage */
		CBASE_affiche_message(178, COMMUN_BALISE_INFORMATIVE, sql_nomprog.arr, NULL, NULL);
		COMMUN_dernier_message_erreur(scrut_dernier_message_erreur);
		sprintf(v_commande2, "ECHO '%s'", scrut_dernier_message_erreur);
		system(v_commande2);

          }    /* flag_lance == 1 */
      }     /* nature == COMMUN_CODE_NAT_PRG_UTIL */
      else 
      {
		/*  SNE, 15/01/2001 : La demande passe a l'etat 'Poste' */
	  if ( change_etat_traitement(TRT_OK, scrut_dernier_message_erreur) == ERR_EXEC_SQL) fin_prg(KO, NULL);
		/*  NDE, 28/02/2002 : suppression du fichier_des_demandes */
      }
        COMMUN_Temporiser(2);

    } /* FIN DE LA BOUCLE DE PARCOURS DES TRAITEMENTS */

    /* close curseur B_TRAITEMENT */
    /* EXEC SQL CLOSE c_b_traitement; */ 

{
    struct sqlexd sqlstm;

    sqlstm.sqlvsn = 10;
    sqlstm.arrsiz = 25;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )402;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


    if ( sqlca.sqlcode != 0 ) 
    {
      CBASE_affiche_message(SCRUT_ERR_000002, COMMUN_BALISE_ERREUR, sqlca.sqlerrm.sqlerrmc, NULL, NULL);
      fin_prg(KO, NULL);
    }

    /* temporisation */
/*	SNE, 02/01/2001 : Adapatation NT */
    COMMUN_Temporiser(v_sleep);

  } /* FIN DE LA BOUCLE INFINIE */

   /* NDY 08/04/2002 V3.0 : suppresion des variables globales de traitement */
   if ( CBASE_supp_var_trt(SCRUT_VAR_DATE_SYSTEME) != OK)
	   fin_prg(KO, NULL);
   if ( CBASE_supp_var_trt(SCRUT_VAR_NIVEAU_TRACE) != OK)
	   fin_prg(KO, NULL);

  /*------------------*/
  /* Arret scrutateur */
  /*------------------*/
  CBASE_affiche_message(SCRUT_ERR_000038, COMMUN_BALISE_INFORMATIVE, NULL, NULL, NULL);
  fin_prg(OK, NULL);
} /* FIN DU PROGRAMME */

