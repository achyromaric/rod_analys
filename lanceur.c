
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
           char  filnam[43];
};
static const struct sqlcxp sqlfpn =
{
    42,
    "J:\\V34\\AsterSrv\\projets\\lanceur\\lanceur.pc"
};


static unsigned long sqlctx = 552873253;


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
 Fichier         : lanceur.pc
 Date creation   : 24/10/2000

 Logiciel          : ASTER                                           
 sous-systeme      : Scrutateur                                     
 Description     : lancement d'un traitement batch                  
                      (pl/sql, report ou chaine)                       
 parametres entree :                                                
   1- <error file>   : fichier des messages d'erreur                    
   2- <cfg file>     : fichier de configuration                         
   3- <instance>     : nom d'instance oracle                            
   4- <user>         : user de connexion oracle                         
   5- <password>     : mot de passe de connexion                        
   6- <numtrt>       : numero de traitement                             
   7- <NOMPROG>      : nom du programme à lancer                        
   9- <LIBPROG>	   : Libelle du traitement a lancer
  10- <TYPPROG>      : type de traitement(B=batch, E=édition, C=chaine) 
  11- <DIRPROG>      : répertoire de localisation du programme          
                      répertoire bin pour une chaine(C)                
                      répertoire rdf pour une édition(E)               
                      répertoire sql pour un batch(B)                  
  12- [ ..]          : Parametres d'edition pour un impression
  12bis		   : Parametre utilisateur pour le traitement a lancer
  dernier		   : Nom du fichier de trace
 parametres sortie :                                                
    Valeurs retournees:                                                            
---------------------------------------------------------------------------
 Version         	: @(#) lanceur version 1.0-1 : SGN : 26/10/2001
 Auteur          	: FADate version    	: 24/10/2000
 Description	: version initiale
 Date version    	: 26/10/2001
 Description	: version initiale (mise au point)
---------------------------------------------------------------------------

	--------------------------------------------------------------------
	Fonction	|Date	    |Initiales	|Commentaires 		
	--------------------------------------------------------------------
@(#)	lanceur 	|24/10/2000 | FAU	| Creation 
@(#)	lanceur	|18/01/2001 | SNE	| adaptations corrections  	
@(#)	lanceur	|26/01/2001 | SGN	| Gestion des parametres comportant un
@(#)	                        | SGN	| espace ( correction anomalie 51, 83 ) 
@(#)	lanceur	|08/02/2002 | NDY	| Correction ano 124 pour V2.2 (passage parametre null)
---------------------------------------------------------------------------
*/

/* Les fichiers inclus */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../commun/commun.h"
#include "../commun/combase.h"


#define LANCE_NOM_PROGRAMME			"LANCEUR "
#define LANCE_VERSION_FICHIER		"1.1"

#define  VAR_REPORT6    			"REPORT6"
#define  VAR_TK6_PRINT_LP       	"TK6_PRINT_LP"
#define  VAR_TK6_PRINT_A3       	"TK6_PRINT_A3"
#define  VAR_TK6_PRINT_NO_RV    	"TK6_PRINT_NO_RV"
#define  VAR_TK6_PRINT_RV_NORM  	"TK6_PRINT_RV_NORM"
#define  VAR_TK6_PRINT_RV_INVE  	"TK6_PRINT_RV_INVE"
#define  VAR_TK6_PRINT_BAC      	"TK6_PRINT_BAC"
#define  VAR_TK6_PRINT_PRINTER  	"TK6_PRINT_PRINTER"
#define  VAR_CFG_NULL				"X"

#define  LANCE_CMD_SET_ENV_VAR		COMMUN_CMD_SET_ENV_VAR
#define  LANCE_EXTENSION_FIC_SHELL	COMMUN_EXTENSION_FIC_SHELL

#define  VAR_CFG_SPECIFIC_PLTFM		COMMUN_VAR_CFG_PLTFM

#define  LANCE_EXTENSION_FIC_DATA	"dat"
#define  LANCE_EXTENSION_FIC_SQL	"sql"
#define  LANCE_EXTENSION_FIC_RDF	"rdf"
#define  LANCE_EXTENSION_FIC_REP	"rep"

#define LANCEUR_REPORTS_BIN			"bin"
#define LANCEUR_REPORTS_LIB			"lib"
#define LANCEUR_REPORTS_EXE			"rwrun60"
#define LANCEUR_SQLPLUS_EXE			"sqlplus"


#define LANCEUR_TAG_MSG_ERREUR		"#E#"
#define LANCEUR_NB_PARAM_SUP_BATCH	11+3
#define LANCEUR_NB_PARAM_SUP_EDIT	20+3

#define LANCE_PARAM_FIC_LOG			argc-3
#define LANCE_PARAM_COD_USR			LANCE_PARAM_FIC_LOG + 1
#define LANCE_PARAM_FIC_USR			LANCE_PARAM_FIC_LOG + 2
#define LANCE_PREMIER_PARM_U_RPT    21
#define LANCE_PREMIER_PARM_U_SQL	12
#define LANCE_PARAM_NB_PARAM		11
#define LANCE_PARAM_NOM_USR			4
#define VRAI						COMMUN_VRAI
#define FAUX						COMMUN_FAUX


#define LANCEUR_ERR_000007      COMMUN_ERR_000007
#define LANCEUR_ERR_000010      COMMUN_ERR_000010
#define LANCEUR_ERR_000026      COMMUN_ERR_000026
#define LANCEUR_ERR_000027      COMMUN_ERR_000027
#define LANCEUR_ERR_000028      COMMUN_ERR_000028
#define LANCEUR_ERR_000044      COMMUN_ERR_000044
#define LANCEUR_ERR_000045      COMMUN_ERR_000045
#define LANCEUR_ERR_000046      COMMUN_ERR_000046
#define LANCEUR_ERR_000047      COMMUN_ERR_000047
#define LANCEUR_ERR_000048      COMMUN_ERR_000048

#define LANCEUR_INF_LANCE		COMMUN_INF_EXEC_PRG

static char lance_version_fichier[]="@(#) "LANCE_NOM_PROGRAMME " version "COMMUN_VERSION_ASTER"-"LANCE_VERSION_FICHIER" - "__DATE__" "__TIME__;

char lance_tmp_file[COMMUN_LG_PATHNAME] = "";

char v_instance[10]="\0",
     v_programme[80]="\0",
     v_error_file[256]="\0",
     v_cfg_file[256]="\0",
     v_batch_log[256]="\0",
     v_batch_tmp[256]="\0",
     v_report6[256]="\0",
     v_base_oracle[256]="\0",
     v_separateur[5]="\0",
     v_dev_null[256]="\0",
     v_tk6_print_lp[256]="\0",
     v_tk6_print_a3[256]="\0",
     v_tk6_print_no_rv[256]="\0",
     v_tk6_print_rv_norm[256]="\0",
     v_tk6_print_rv_inve[256]="\0",
     v_tk6_print_bac[256]="\0",
     v_tk6_print_printer[256]="\0",
     v_format_edt[256]="\0",
     v_rv_edt[256]="\0",
     v_sens_rv_edt[256]="\0",
     v_bac_edt[256]="\0",
     v_fic_exe[512]="\0"
     , v_lance_log[LG_NOM_FIC]="\0"
     , lance_user_file[256]
     , lance_utilisateur[30]
	 , lance_programme_a_lancer[256];
     ;

int v_os=0,
    v_report_sql=0,
    lanceur_test_file=0
   , lanceur_connexion_base=TRT_OK;

FILE *v_flog;

t_indicateurs_prog lance_ctx_execution;
char lanceur_dernier_message_erreur[COMMUN_LG_LIBL_ERR]="";
char lance_separateur_var_path[5] = ":"
    , lance_separateur_chemin[5] = "/";



int LANCEUR_affiche_message(unsigned long p_numero_mesg, char p_type_message, char p_param1[], char p_param2[], char p_param3[] )
{
  if (lanceur_connexion_base == OK)
	return(CBASE_affiche_message(p_numero_mesg, p_type_message, p_param1, p_param2, p_param3 ));
  else
	return(OK);
}

/*
 ====================================================================================
   Nom 		: fin_prg	
   Description 	: affiche les infos de fin de programme
   Auteur	: Florent AUBARET
   Date creation: 24/10/2000
   parametres    :                                                     
      <p_status> : indicateur de fin de programme (OK/KO)                
   Historique	:
	---------------------------------------------------------------------------
	Fonction	|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   fin_prg	|24/10/2000 | FAU		| Creation (@fonction)
@(#)   fin_prg	|18/01/2001 | SNE		| Adaptation, mise au point
 ====================================================================================
*/
void fin_prg(int p_status) 
{

  char v_commande[100]="\0";
 

  /* Destruction du fichier temporaire   */
    remove(lance_tmp_file);
    remove(v_fic_exe);

 if ( p_status == OK ) 
  {
  	LANCEUR_affiche_message(LANCEUR_ERR_000007, COMMUN_BALISE_INFORMATIVE,  lance_programme_a_lancer, NULL, NULL);
  }
  else 
  {
    	LANCEUR_affiche_message( LANCEUR_ERR_000010, COMMUN_BALISE_INFORMATIVE, lance_programme_a_lancer, NULL, NULL);
  }


/*
	Arret des traces scrutateur (fermeture fichier & renommage)
*/
  if ( COMMUN_close_log(v_lance_log) != TRT_OK){
	p_status = (p_status == OK)? COMMUN_EFERM_LOG:p_status;
  }
   exit(p_status);

} /* fin de fin_prg */


/*
 ====================================================================================
   Nom 		: LANCEUR_test_file	
   Description 	: affiche les infos de fin de programme
   Auteur	: Florent AUBARET
   Date creation: 24/10/2000
   parametres    :                                                     
      <p_status> : indicateur de fin de programme (OK/KO)                
   Historique	:
	---------------------------------------------------------------------------
	Fonction	|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   fin_prg	|24/10/2000 | FAU		| Creation (@fonction)
@(#)   fin_prg	|18/01/2001 | SNE		| Adaptation, mise au point
 ====================================================================================
*/

void LANCEUR_test_file(char *p_repertoire, char *p_file, char *p_extension) 
{

char v_nom_fichier[300];

sprintf(v_nom_fichier, "%s%s%s.%s\0", p_repertoire, lance_separateur_chemin, p_file, p_extension);
switch(COMMUN_existe_fichier(v_nom_fichier)){
	case CODE_FICHIER_EXISTANT:
    		lanceur_test_file=OK;
		break;
	case CODE_FICHIER_INEXISTANT:
      	LANCEUR_affiche_message(LANCEUR_ERR_000027, COMMUN_BALISE_ERREUR , p_file, NULL, NULL);
      	fin_prg(COMMUN_EEXIST_FIC);
		break;
	case CODE_FICHIER_VERROUILLE:
        	LANCEUR_affiche_message(LANCEUR_ERR_000028, COMMUN_BALISE_ERREUR , p_file, NULL, NULL);
      	fin_prg(COMMUN_EACCES_FIC);
		break;
	default:
    		lanceur_test_file=KO;
		break;
}
} /* fin de LANCEUR_test_file */


/*
 ====================================================================================
   Nom 		: LANCEUR_setenv_sql	
   Description 	: Configuration dynamique de l'environnement d'execution pour le lancement
			  de SQL*Plus
   Auteur	: Florent AUBARET
   Date creation: 24/10/2000
   parametres    :                                                     
      			Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   LANCEUR_setenv_sql	|24/10/2000 | FAU		| Creation (@fonction)
 ====================================================================================
*/
void LANCEUR_setenv_sql(void) 
{

  char *v_oracle_sid=NULL,
       *v_oracle_home=NULL,
       *v_ora_nls33=NULL,
       *v_path=NULL;

  char *v_temp=NULL;

  int v_ret=0;

  if ( (v_oracle_sid = malloc((size_t) (strlen(v_instance) + 12))) == NULL) 
  {
    LANCEUR_affiche_message(LANCEUR_ERR_000045, COMMUN_BALISE_ERREUR , NULL, NULL, NULL);
    fin_prg(COMMUN_EALLOC_MEM);
  }
  sprintf(v_oracle_sid, "ORACLE_SID=%s", v_instance);
  if ( putenv(v_oracle_sid) != 0 ) 
  {
    LANCEUR_affiche_message(LANCEUR_ERR_000048, COMMUN_BALISE_ERREUR , NULL, NULL, NULL);
    fin_prg(COMMUN_EENVIR_VAR);
  }

  free(v_oracle_sid);
  free(v_temp);
 
} /* fin de LANCEUR_setenv_sql */

/*
 ====================================================================================
   Nom 		: main
   Description 	: Programme principal
   Auteur	: Florent AUBARET
   Date creation: 24/10/2000
      <argc> : Nombre de parametres de la lignes de commande                
      <argv> : pointeur sur la liste des parametres 
   Historique	:
	---------------------------------------------------------------------------
	Fonction	|Date	    	|Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   main		|24/10/2000 | FAU		| Creation (@fonction)
@(#)   main 	|18/01/2001 | SNE		| Adaptation, mise au point
@(#)   main 	|26/10/2001 | SGN		| Correction anomalie 51, 83
 ====================================================================================
*/

main(argc,argv)
  int  argc; 
  char *argv[];
{

  char **arguments = NULL;
  char *v_temp=NULL,
       *v_temp2=NULL,
       *v_reste=NULL,
	 *v_param_val=NULL;  /* MODIF SGN ANO 51 */
  char v_fic_log[512]="\0",
       v_commande[512]="\0",
       v_complement[512]="\0",
	 v_instance_L1[12]="\0",
	 v_reports_path[200] ="",
	 v_param_name[512]="\0";  /* MODIF SGN ANO 51 */

  int i=0, v_retour,
      v_ind ; /* MODIF SGN ANO 51 */

  FILE *v_fexe;

  char dat[80]="\0",
	code_retour[5]="\0"
	, v_fic_temp[COMMUN_LG_PATHNAME] = ""
	;


  COMMUN_Date_du_jour(FORMAT_DAT_LOG, dat);

  memset(&lance_ctx_execution, 0, sizeof(COMMUN_t_contexte_exec));
  strcpy(lance_ctx_execution.nom_programme, argv[0]);

  if ( (arguments = malloc((size_t) (argc)*sizeof(*arguments))) != NULL) 
  {

    for (i=1; i<argc; i++) 
    {
      arguments[i] = argv[i];
      if (lance_ctx_execution.niveau_debug > DEBUG_NIVEAU_DETAIL)
  		printf (ENTETE_MESSAGE_LOG "%i eme argument  %s\n", dat, BALISE_INFORMATIVE, *argv, i, argv[i]);
    }

    strcpy(v_instance, arguments[3]);
    strcpy(v_programme, argv[0]);
    strcpy(v_error_file, arguments[1]);
    strcpy(v_cfg_file, arguments[2]);
    if ( strcmp(arguments[8], COMMUN_CODE_TYP_PRG_EDIT) == 0) 
    {
      v_report_sql=0;
      strcpy(v_format_edt, arguments[17]);
      strcpy(v_rv_edt, arguments[18]);
      strcpy(v_sens_rv_edt, arguments[19]);
      strcpy(v_bac_edt, arguments[20]);
    }
    else
    {
      v_report_sql=1;
    }

/*  
	SNE, Pour que le fichier de trace soit connu du programme appelant il doit etre constitue au moment de l'appel
	et founi en argument
*/
	strcpy(lance_programme_a_lancer, arguments[7]);
	strcpy(v_fic_log, argv[LANCE_PARAM_FIC_LOG]);
      strcpy(lance_user_file, arguments[LANCE_PARAM_FIC_USR]);
      strcpy(lance_utilisateur, arguments[LANCE_PARAM_COD_USR]);

/* SNE, Initialisation des parametres d'execution */
  lance_ctx_execution.mode_trace = TRACE_DANS_FIC;
  lance_ctx_execution.niveau_debug = DEBUG_SANS_DEBUG;
  strcpy(lance_ctx_execution.fichier_config, arguments[2]);
  strcpy(lance_ctx_execution.fichier_erreur, v_error_file);


  /* SNE, 03/01/2001 : Fixation du mode et du niveau de trace d'execution */
  COMMUN_init_param_execution (lance_ctx_execution);


    /* Récupération des infos dans le fichier de configuration */
    /*
	 SNE, 04/01/2001 : Le nom de l''instance n'est plus en dur dans les programmes!!! 
		L'appelation 'xxx_L1' est conservee comme valeur par defaut si le nom du listener n'est pas fourni
		par le fichier de configuration
	*/
    if ( COMMUN_lire_info(v_cfg_file, v_instance, VAR_INSTANCE, v_instance_L1) != TRT_OK)
        sprintf(v_instance_L1, "%s_L1\0", v_instance);

      COMMUN_lire_info(v_cfg_file, v_instance, VAR_BATCH_LOG, v_batch_log);
      COMMUN_lire_info(v_cfg_file, v_instance, VAR_BATCH_TMP, v_batch_tmp);

    lanceur_connexion_base = CBASE_connexion_base(lance_ctx_execution.fichier_config, v_instance, lance_user_file, lance_utilisateur);

  	if (COMMUN_open_log(v_fic_log, *argv) != TRT_OK){
		exit(1);
  	}


    /* Contrôle de l'environnement */
    COMMUN_check_env(v_batch_log, lance_separateur_chemin, v_dev_null, lance_separateur_var_path);

    COMMUN_Date_du_jour(FRMT_EXT_F_LOG, dat);

    sprintf(v_fic_exe, "%s%s%s_%s_%s." LANCE_EXTENSION_FIC_SHELL "\0", v_batch_tmp, lance_separateur_chemin, arguments[7], arguments[4], dat);


    if ( strcmp(arguments[8], COMMUN_CODE_TYP_PRG_BATCH) == 0) 
    {
      if ( (argc-1) < (atoi(arguments[LANCE_PARAM_NB_PARAM]) + LANCEUR_NB_PARAM_SUP_BATCH ) )
      {
		 sprintf(arguments[LANCE_PARAM_NB_PARAM], "%d (%d)\0", argc, LANCEUR_NB_PARAM_SUP_BATCH);
        LANCEUR_affiche_message(LANCEUR_ERR_000046, COMMUN_BALISE_ERREUR , arguments[LANCE_PARAM_NB_PARAM], NULL, NULL);
        fin_prg(COMMUN_CTL_NB_ARG);
      }
  
      LANCEUR_test_file(arguments[9], arguments[7], LANCE_EXTENSION_FIC_SQL);
      if (lanceur_test_file == KO) 
      {
        LANCEUR_affiche_message(LANCEUR_ERR_000047, COMMUN_BALISE_ERREUR , arguments[7], arguments[9], NULL);
        fin_prg(COMMUN_EEXIST_FIC);
      }

/*	SNE, 04/01/2001 : la regle de nommage de l'instance n'est plus impose mais decrite dans le fichier de configuration
	SNE, 09/01/2001 : Redirection vers le fichier log
*/
      sprintf(v_commande, LANCEUR_SQLPLUS_EXE " -s %s/%s@%s @%s%s%s.sql \0",arguments[4],arguments[5], v_instance_L1,arguments[9],lance_separateur_chemin, arguments[7]);

      for (i=LANCE_PREMIER_PARM_U_SQL; (i-LANCE_PREMIER_PARM_U_SQL)<atoi(arguments[LANCE_PARAM_NB_PARAM]); i++) 
      {
         if ( *arguments[i] == '\'' || *arguments[i] == '\"' )
			sprintf(v_complement,"%s \0",arguments[i]);
		 else{
		    /* MODIF SGN ANO 83 sprintf(v_complement,"\"%s\" \0",arguments[i]); */
		    sprintf(v_complement,"'\"%s\"' \0",arguments[i]);
		}

         /* ajout NDY 06/02/2002 Correction ano 124 pour V2.2 */
         if ( strcmp(v_complement, "\"\" \0") == 0)
             sprintf(v_complement,"%s",COMMUN_CMD_VAR_NULL);

         strcat(v_commande,v_complement);
      }

      LANCEUR_setenv_sql();

	if ( (v_flog=COMMUN_fp_fichier_log()) == NULL) v_flog=stdout;	/* SNE, 19/01/2001 */

      fprintf(v_flog, "====================================================\n");
      fprintf(v_flog, "%s\n", arguments[10]);
      fprintf(v_flog, "====================================================\n");
      fprintf(v_flog, "  %s\n", arguments[3]);
      fprintf(v_flog, "  %s\n", arguments[4]);
      fprintf(v_flog, "  %s%s%s\n", arguments[9], lance_separateur_chemin, arguments[7]);
      fprintf(v_flog, "  %s\n", v_instance_L1);
      fprintf(v_flog, "  %s\n", arguments[6]);
      fprintf(v_flog, "  %s\n", dat);
      fprintf(v_flog, "====================================================\n");

	sprintf(v_commande, "%s >> %s\0", v_commande, v_fic_log);     

	/*
		 SNE : Etant donne que le resultat de la commande executee est redirige vers le fichier log on
			doit fermer celui-ci au prealable 
	*/
  	COMMUN_close_log(v_fic_log);
	if (lance_ctx_execution.niveau_debug >= DEBUG_NIVEAU_DETAIL)   /* NDY, 19/03/2002 */
	  CBASE_affiche_message(LANCEUR_INF_LANCE,  COMMUN_BALISE_INFORMATIVE,  v_commande,  NULL, NULL);
      v_retour = system(v_commande);
      COMMUN_open_log(v_fic_log, *argv);
      if ( v_retour != 0) 
      {
	  sprintf(code_retour, "%d\0", v_retour);
        LANCEUR_affiche_message(LANCEUR_ERR_000026, COMMUN_BALISE_ERREUR , code_retour, NULL, NULL);
     	  COMMUN_dernier_message_erreur(lanceur_dernier_message_erreur);
        fin_prg(v_retour);
      }
    }
    else if ( strcmp(arguments[8], COMMUN_CODE_TYP_PRG_EDIT) == 0) 
    {
      /* Test sur le nombre d'arguments */
      if ( (argc - 1) < (atoi(arguments[LANCE_PARAM_NB_PARAM]) + LANCEUR_NB_PARAM_SUP_EDIT) ) 
      {
       LANCEUR_affiche_message(LANCEUR_ERR_000046, COMMUN_BALISE_ERREUR , arguments[LANCE_PARAM_NB_PARAM], NULL, NULL);
		 sprintf(arguments[LANCE_PARAM_NB_PARAM], "%d (%d)\0", argc, LANCEUR_NB_PARAM_SUP_EDIT);
       LANCEUR_affiche_message(LANCEUR_ERR_000046, COMMUN_BALISE_ERREUR , arguments[LANCE_PARAM_NB_PARAM], NULL, NULL);
        fin_prg(COMMUN_CTL_NB_ARG);
      }

      LANCEUR_test_file(arguments[9], arguments[7], LANCE_EXTENSION_FIC_RDF);
      if (lanceur_test_file == KO) 
      {
        LANCEUR_test_file(arguments[9], arguments[7], "rep");
        if (lanceur_test_file == KO) 
        {
          LANCEUR_affiche_message(LANCEUR_ERR_000047, COMMUN_BALISE_ERREUR , arguments[7], arguments[9], NULL);
          fin_prg(COMMUN_EEXIST_FIC);
        }
      }
	/* Generation d'un fichier de commandes et d'un fichier d'ordre pour REPORTS */
      sprintf(v_fic_exe, "%s%s%s_%s_%s." LANCE_EXTENSION_FIC_DATA "\0", v_batch_tmp, lance_separateur_chemin, arguments[7], arguments[4], dat);
      sprintf(lance_tmp_file, "%s%s%s_%s_%s." LANCE_EXTENSION_FIC_SHELL "\0", v_batch_tmp, lance_separateur_chemin, arguments[7], arguments[4], dat);
      if ((v_fexe = fopen(v_fic_exe,"w")) == NULL) 
      {
        LANCEUR_affiche_message(LANCEUR_ERR_000027, COMMUN_BALISE_ERREUR , v_fic_exe, NULL, NULL);
        fin_prg(COMMUN_EACCES_FIC);
      }
	/* SNE, 04/01/2001 : arguments[3] remplace par v_instance_l1 pour ne pas l'avoir en dur!!!*/
      if ( fprintf(v_fexe, "report=%s%s%s userid=%s/%s@%s batch=YES ", arguments[9], lance_separateur_chemin, arguments[7], arguments[4], arguments[5], v_instance_L1) < 0 ) 
      {
        LANCEUR_affiche_message(LANCEUR_ERR_000044, COMMUN_BALISE_ERREUR , v_fic_exe, NULL, NULL);
        fin_prg(COMMUN_EACCES_FIC);
      }

      if ( fprintf(v_fexe, "%s %s %s MODE=BITMAP %s %s ", arguments[12], arguments[13], arguments[14], arguments[15], arguments[16]) < 0 ) 
      {
        LANCEUR_affiche_message(LANCEUR_ERR_000044, COMMUN_BALISE_ERREUR , v_fic_exe, NULL, NULL);
        fin_prg(COMMUN_EACCES_FIC);
      }


      for (i=LANCE_PREMIER_PARM_U_RPT; (i-LANCE_PREMIER_PARM_U_RPT)<atoi(arguments[LANCE_PARAM_NB_PARAM]); i++) 
      {
	  /* MODIF SGN ANO 51 */
	  /* Recuperation de l indice ou se trouve le = */
	  v_ind = strcspn(arguments[i], "=");
	
	  /* Recuperation du nom du parametre */
	  strncpy (v_param_name, arguments[i], v_ind);
	  v_param_name[v_ind]='\0';
	  /* Recuperation de la valeur du parametre */
	  v_param_val = arguments[i]+v_ind+1; /* +1 car on ne recupere pas le = */


         /* ajout NDY 25/02/2002 Correction ano 124 pour V2.2 */
         if ( strcmp(v_param_val, " \0") == 0)
            sprintf(v_param_val, "\0");

	  /* Constitution correcte de la chaine */
	  sprintf(v_complement, "%s=\"%s\"\0",v_param_name,v_param_val);   

	  if ( fprintf(v_fexe, "%s ", v_complement) < 0 ) /* Fin Modif SGN if ( fprintf(v_fexe, "%s ", arguments[i]) < 0 )*/
        {
          LANCEUR_affiche_message(LANCEUR_ERR_000044, COMMUN_BALISE_ERREUR , v_fic_exe, NULL, NULL);
          fin_prg(COMMUN_EACCES_FIC);
        }
      }

      if ( fprintf(v_fexe, "\n\0") < 0 ) 
      {
        LANCEUR_affiche_message(LANCEUR_ERR_000044, COMMUN_BALISE_ERREUR , v_fic_exe, NULL, NULL);
        fin_prg(COMMUN_EACCES_FIC);
      }

      fclose(v_fexe);

	if ( (v_flog=COMMUN_fp_fichier_log()) == NULL) v_flog=stdout;

      fprintf(v_flog, "====================================================\n");
      fprintf(v_flog, "%s\n", arguments[10]);
      fprintf(v_flog, "====================================================\n");
      fprintf(v_flog, "  %s\n", arguments[3]);
      fprintf(v_flog, "  %s\n", arguments[4]);
      fprintf(v_flog, "  %s%s%s\n", arguments[9], lance_separateur_chemin, arguments[7]);
      fprintf(v_flog, "  %s\n", v_instance_L1);
      fprintf(v_flog, "  %s\n", arguments[6]);
      fprintf(v_flog, "  %s\n", arguments[12]);
      fprintf(v_flog, "  %s\n", arguments[13]);
      fprintf(v_flog, "  %s\n", arguments[17]);
      fprintf(v_flog, "  %s\n", arguments[18]);
      fprintf(v_flog, "  %s\n", arguments[19]);
      fprintf(v_flog, "  %s\n", arguments[20]);
      fprintf(v_flog, "  %s\n", dat);
      fprintf(v_flog, "====================================================\n");

     
      COMMUN_lire_info(v_cfg_file,  VAR_CFG_SPECIFIC_PLTFM, VAR_REPORT6, v_reports_path);
      sprintf(v_commande, LANCEUR_REPORTS_EXE " cmdfile=%s >> %s", v_fic_exe, v_fic_log);
      if ((v_fexe = fopen(lance_tmp_file,"w")) != NULL) {
      	fprintf(v_fexe, COMMUN_CMD_RUN_CMD "" LANCE_CMD_SET_ENV_VAR" ORACLE_HOME=%s\n", v_reports_path);
      	fprintf(v_fexe, COMMUN_CMD_RUN_CMD LANCE_CMD_SET_ENV_VAR "PATH="COMMUN_CMD_VAL_ENV_VAR_PRE"PATH"COMMUN_CMD_VAL_ENV_VAR_SUF "%s%s%s"LANCEUR_REPORTS_BIN"\n", lance_separateur_var_path, v_reports_path, lance_separateur_chemin);
      	fprintf(v_fexe, COMMUN_CMD_RUN_CMD LANCEUR_REPORTS_EXE " cmdfile=%s "COMMUN_CMD_SIGN_REDIR_ADD" %s 2>&1", v_fic_exe, v_fic_log);
	    fclose(v_fexe);
		sprintf(v_commande, "%s\0", lance_tmp_file);
		COMMUN_chmod(lance_tmp_file, COMMUN_UNIX_MODE_ADD "" COMMUN_UNIX_MODE_EXE);
		}
	/*
		 SNE : Etant donne que le resultat de la commande executee est redirige vers le fichier log on
			doit fermer celui-ci au prealable 
	*/
  	COMMUN_close_log(v_fic_log);
	if (lance_ctx_execution.niveau_debug >= DEBUG_NIVEAU_DETAIL)   /* NDY, 19/03/2002 */
	  CBASE_affiche_message(LANCEUR_INF_LANCE,  COMMUN_BALISE_INFORMATIVE,  v_commande,  NULL, NULL);
      v_retour = system(v_commande);
      COMMUN_open_log(v_fic_log, *argv);
      if ( v_retour != 0) 
      {
  	    sprintf(code_retour, "%d\0", v_retour);
        LANCEUR_affiche_message(LANCEUR_ERR_000026, COMMUN_BALISE_ERREUR , code_retour, NULL, NULL);
        fin_prg(v_retour);
      }
    }

    free(arguments);
    fin_prg(OK);
  }
  else 
  {
    LANCEUR_affiche_message(LANCEUR_ERR_000045, COMMUN_BALISE_ERREUR , NULL, NULL, NULL);
    fin_prg(COMMUN_ENATUR_TRT);
  }

} /* FIN DU PROGRAMME */

