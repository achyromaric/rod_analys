#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#ifdef WIN32
	#include <direct.h>
	#include <windows.h>
	#include <io.h>
#else
	#include <dirent.h>
	#include <unistd.h>
#endif


#define OK 0
#define KO !OK
#define UNIX 1
#define WINDOWS 0

#ifdef WIN32
	#define COMMUN_CMD_SET_ENV_VAR		"set "
	#define COMMUN_CMD_RUN_CMD			"@"
	#define COMMUN_CMD_VAL_ENV_VAR_PRE	"%%"
	#define COMMUN_CMD_VAL_ENV_VAR_SUF	"%%"
	#define COMMUN_EXTENSION_FIC_SHELL	"BAT"
	#define COMMUN_VAR_CFG_PLTFM		"NT"
	#define COMMUN_CMD_CAT_FICHIER		"type %s\0"
	#define COMMUN_CMD_MOVE_FICHIERS	"move"
	#define COMMUN_DEV_NULL				"nul"
	#define LANCEUR_ASTER 				"lanceur.exe"
	#define chdir						_chdir
	#define COMMUN_creer_repertoire(p)	_mkdir(p)
	#define F_OK	00
	#define X_OK	01
	#define W_OK	02
	#define R_OK	04
	#define COMMUN_CMD_VAR_NULL			"\"''\" \0"			/* ajout NDY 06/02/2002 Correction ano 124 pour V2.2 */
#else
	#define COMMUN_CMD_SET_ENV_VAR		"export "
	#define COMMUN_CMD_RUN_CMD			""
	#define COMMUN_CMD_VAL_ENV_VAR_PRE	"$"
	#define COMMUN_CMD_VAL_ENV_VAR_SUF	""
	#define COMMUN_EXTENSION_FIC_SHELL	"sh"
	#define COMMUN_VAR_CFG_PLTFM		"UX"
	#define COMMUN_DEV_NULL				"/dev/null"
	#define LANCEUR_ASTER 				"lanceur"
	#define COMMUN_creer_repertoire(p)	mkdir(p, S_IRWXU && S_IRWXG)
	#define COMMUN_CMD_MOVE_FICHIERS	"mv"
	#define COMMUN_CMD_CAT_FICHIER		"cat %s\0"
	#define COMMUN_CMD_VAR_NULL			"\\\"''\\\" \0"			/* ajout NDY 06/02/2002 Correction ano 124 pour V2.2 */
#endif
#define COMMUN_EXTENSION_FIC_EDIT		"edt"
#define COMMUN_LANCEUR_ASTER			LANCEUR_ASTER
#define	COMMUN_existe_repertoire		COMMUN_existe_fichier
#define COMMUN_FAUX						0
#define COMMUN_VRAI						!COMMUN_FAUX
#define TRT_OK							0
#define COMMUN_TRT_OK					0
#define COMMUN_TRT_KO					!COMMUN_TRT_OK
#define ERR_OUV_FIC						-1
#define ERR_TRT_FIC						ERR_OUV_FIC
#define ERR_MSG_NTFD					-2
#define ERR_EXEC_SQL					-3
#define COMMUN_ERREUR_GRAVE				KO
#define COMMUN_ERREUR_APPLICATIVE		-100
#define COMMUN_AVERTISSEMENT			100

#define COMMUN_ERR_EXEC_SQL				ERR_EXEC_SQL
#define COMMUN_EFERM_LOG				-4
#define COMMUN_EEXIST_FIC				-5
#define COMMUN_EACCES_FIC				-6
#define COMMUN_EALLOC_MEM				-7
#define COMMUN_EENVIR_VAR				-8
#define COMMUN_ENATUR_TRT				-9
#define COMMUN_CTL_NB_ARG				-10

#define COMMUN_GI_ERR_INFO_NTFD			-11
#define COMMUN_GI_ERR_OUV_FIC			-12

#define COMMUN_GP_ERR_PASW_NTFD			-13
#define COMMUN_GP_ERR_OUV_FIC			COMMUN_GI_ERR_OUV_FIC

#define COMMUN_CP_NO_SOURCE_FILE		-14
#define COMMUN_CP_EXIST_DEST_FILE		-15

/*
	==================================================================
	SNE, Messages d'erreurs utilisables par tous les modules; les numeros references
		 correspondent aux identifiants des messages dans SR_MESS_ERR
	==================================================================
*/
#define COMMUN_ERR_00001	542					/* Utilisateur %1 non trouvee dans le fichier des utilisateurs */
#define COMMUN_ERR_00002	105					/* Erreur Oracle : %1 */
#define COMMUN_ERR_00019	735					/* Impossible de déplacer le fichier %1 dans %2 #5*/
#define COMMUN_ERR_00026	736					/* Erreur système d'exploitation (%1) (%2) #5*/
#define COMMUN_ERR_00027	737					/* Ouverture du fichier %1 impossible #5*/
#define COMMUN_ERR_00030	190					/* Variable %1 non trouvée dans le fichier de configuration */
#define COMMUN_ERR_00034	738					/* Fichier %1 : Exécution refusée #5*/

#define COMMUN_ERR_000001	COMMUN_ERR_00001
#define COMMUN_ERR_000002	COMMUN_ERR_00002
#define COMMUN_ERR_000003	159					/* Paramètre %1 non trouve */
#define COMMUN_ERR_000004	739					/* Erreur pendant la procédure %1 #5*/
#define COMMUN_ERR_000005	196					/* Repertoire %1 n'existe pas */
#define COMMUN_ERR_000006	COMMUN_ERR_000003	/* Parametre %1 non trouve */
#define COMMUN_ERR_000007	178					/* Fin %1 sans erreur */
#define COMMUN_ERR_000010	179					/* Fin %1 avec erreur */
#define COMMUN_ERR_000011	188					/* Pb de codification */
#define COMMUN_ERR_000015	COMMUN_ERR_000004	/* Erreur pendant la procedure %1 */
#define COMMUN_ERR_000017	COMMUN_ERR_000005	/* Repertoire %1 n'existe pas */
#define COMMUN_ERR_000018	740					/* Impossible de copier le fichier %1 dans %2 #5*/
#define COMMUN_ERR_000019	COMMUN_ERR_00019	/* Impossible de deplacer le fichier %1 dans %2  */
#define COMMUN_ERR_000026	COMMUN_ERR_00026
#define COMMUN_ERR_000027	COMMUN_ERR_00027
#define COMMUN_ERR_000028	COMMUN_ERR_00027	/* Ouverture fichier %1 impossible */
#define COMMUN_ERR_000029	179					/* Fin %1 avec erreurs */
#define COMMUN_ERR_000034	741					/* Le fichier %1 n'existe pas #5*/
#define COMMUN_ERR_000038	742					/* Demande d'arrêt scrutateur OK #5*/
#define COMMUN_ERR_000039	743					/* Démarrage du scrutateur %1 #5*/
#define COMMUN_ERR_000040	9					/* Utilisateur %1 inconnu d'ASTER, veuillez le créer */
#define COMMUN_ERR_000044	744					/* Impossible d'écrire dans le fichier %1 #5*/
#define COMMUN_ERR_000045	747					/* Problème d'allocation de mémoire #5*/
#define COMMUN_ERR_000046	748					/* Nombre de paramètres (%1) incorrect #5*/
#define COMMUN_ERR_000047	COMMUN_ERR_000034	/* Problème d'allocation de mémoire #5*/
#define COMMUN_ERR_000048	749					/* Erreur pendant le postionnement des variables d'environnement #5*/
#define COMMUN_ERR_000049	COMMUN_ERR_000034	/* Le fichier %1 n'existe pas */
#define COMMUN_ERR_000050	745					/* Le fichier %1 est inaccessible #5*/
#define COMMUN_ERR_000051	746					/* %1 : Nom de fichier incorrect #5*/


#define COMMUN_ERR_712		712
#define COMMUN_ERR_713		713
#define COMMUN_ERR_188		188

#define COMMUN_ERR_VAL_VAR	190			/* Erreur d'initialisation variable %1#5*/
#define COMMUN_ERR_TRT_BAT	108			/* Erreur pendant le traitement batch %1 #5*/
#define COMMUN_ERR_NBR_PRM	COMMUN_ERR_000046
#define COMMUN_INF_EXEC_PRG	COMMUN_ERR_000039
#define COMMUN_INF_FTRACE	752			/* Information 'trace dans ...' */


#define COMMUN_CP_ECRASE_FICHIER	1
#define COMMUN_CP_PAS_CP_FICHIER	0

#define FICHIER_EXISTE				F_OK		/* 00 */
#define FICHIER_EN_ECRITURE			W_OK		/* 02 */
#define FICHIER_EN_LECTURE			R_OK		/* 04 */
#define FICHIER_EN_LECTURE_ECRITURE	R_OK||W_OK	/* 06 */

#define CODE_FICHIER_INEXISTANT		ENOENT
#define CODE_FICHIER_VERROUILLE		EACCES
#define CODE_FICHIER_EXISTANT		TRT_OK


#define COMMUN_CODE_FICHIER_EXISTANT	CODE_FICHIER_EXISTANT
#define COMMUN_CODE_FICHIER_INEXISTANT	CODE_FICHIER_INEXISTANT

#define COMMUN_CODE_REP_INEXISTANT	CODE_FICHIER_INEXISTANT
#define COMMUN_CODE_REP_INCCESSIBLE COMMUN_EACCES_FIC
#define COMMUN_CODE_REP_EXISTANT	CODE_FICHIER_EXISTANT
#define COMMUN_CODE_ERR_ACCES_REP	!COMMUN_CODE_REP_EXISTANT


#define COMMUN_CODE_FIN_ANORMALE	"A"
#define COMMUN_CODE_PROG_LANCE		"L"
#define COMMUN_CODE_PROG_POSTE		"P"
#define COMMUN_CODE_TRT_DEMANDE		"D"
#define COMMUN_CODE_TRT_TERMINE		"T"
#define COMMUN_CODE_TYP_PRG_EDIT	"E"
#define COMMUN_CODE_TYP_PRG_BATCH	"B"
#define COMMUN_CODE_NAT_PRG_UTIL	"U"
#define COMMUN_CODE_NAT_PRG_EXPL	"E"
#define COMMUN_CODE_TYP_PRG_CHAINE	"C"
#define COMMUN_DST_TRT_FICHIER		"F"
#define COMMUN_DST_TRT_IMPRIM 		"I"

#define DEBUG_SANS_DEBUG	0
#define DEBUG_NIVEAU_SIMPLE	1
#define DEBUG_NIVEAU_DETAIL	2
#define DEBUG_NIVEAU_FIN	3

#define TRACE_DANS_FIC	0
#define TRACE_A_LECRAN	1
#define TRACE_NULL_PAR	2

#define COMMUN_DEBUG_SANS_DEBUG		DEBUG_SANS_DEBUG
#define COMMUN_DEBUG_NIVEAU_SIMPLE	DEBUG_NIVEAU_SIMPLE
#define COMMUN_DEBUG_NIVEAU_DETAIL	DEBUG_NIVEAU_DETAIL
#define COMMUN_DEBUG_NIVEAU_FIN		DEBUG_NIVEAU_FIN

#define COMMUN_TRACE_DANS_FIC	TRACE_DANS_FIC
#define COMMUN_TRACE_A_LECRAN	TRACE_A_LECRAN
#define COMMUN_TRACE_NULL_PAR	TRACE_NULL_PAR


#define DATE_ANTERIEURE		1
#define DATE_A_VENIR		2

#define FORMAT_DAT_LOG	"%Y%m%d %H%M%S"
#define FRMT_EXT_F_LOG	"%Y%m%d_%H%M%S"
#define FORMAT_DAT_DEF	"%Y/%m/%d %H:%M%:S"
#define LG_MAX_DAT_CHAR	80
#define COMMUN_FRMT_EXT_F_LOG		FRMT_EXT_F_LOG

#define BALISE_INFORMATIVE	'I'
#define BALISE_ERREUR		'E'
#define BALISE_AVERTISSEMENT	'A'
#define FORMAT_BALISE	"#%c#"

#define COMMUN_BALISE_INFORMATIVE	BALISE_INFORMATIVE
#define COMMUN_BALISE_ERREUR		BALISE_ERREUR
#define COMMUN_BALISE_AVERTISSEMENT	BALISE_AVERTISSEMENT
#define COMMUN_FORMAT_BALISE		FORMAT_BALISE


#define COMMUN_MSG_ERR_VAR_ENV	"Variable %s non definie dans %s \n"
#define COMMUN_MSG_ERR_OUV_FIC	"Pb d'ouverture du fichier %s \n"
#define MESSAGE_ERR_NTFD_BASE	"Erreur Numero %d non defini\n"
#define MESSAGE_ERR_NTFD		"Erreur Numero %s non trouvee dans %s "
#define MESSAGE_EOUV_FIC		"%s : " FORMAT_BALISE "%s : Pb d'ouverture du fichier %s ==> niveau de gravité : 5"
#define MESSAGE_EFRM_FIC		"%s : " FORMAT_BALISE "%s : Pb de fermeture du fichier %s ==> niveau de gravité : 5"
#define MESSAGE_DEBT_TRC		"%s : " FORMAT_BALISE "%s : fichier %s ouvert"
#define MESSAGE_ARRT_TRC		"%s : " FORMAT_BALISE "%s : arret de la journalisation dans %s"
#define ENTETE_MESSAGE_LOG		"%s : " FORMAT_BALISE "%s : "


#define COMMUN_LG_LIBL_ERR			1000
#define COMMUN_LG_PATHNAME			256
#define	COMMUN_LG_ENTETE_MSG_LOG	50
#define COMMUN_LG_SR_MESS_ERR_LIBL	121
#define COMMUN_LG_PASSWORD			31
#define LG_NOM_OBJ					80
#define LG_NOM_FIC					COMMUN_LG_PATHNAME
#define LG_NOM_INSTANCE				10
#define COMMUN_LG_NOM_INSTANCE		LG_NOM_INSTANCE
#define LG_SEPARATEUR				5

#define VAR_BATCH					"BATCH"
#define VAR_BATCH_TMP				"BATCH_TMP"
#define VAR_BATCH_LOG				"BATCH_LOG"
#define VAR_INSTANCE 				"INSTANCE"
#define COMMUN_VAR_FIC_ERR			"FICHIER_ERREUR"
#define COMMUN_VAR_FIC_UTIL			"FICHIER_UTILISATEURS"
#define COMMUN_VAR_INSTANCE 		VAR_INSTANCE
#define COMMUN_VAR_BATCH_LOG		VAR_BATCH_LOG
#define COMMUN_VAR_BATCH_TMP		VAR_BATCH_TMP
#define COMMUN_VAR_BATCH_ERR		"BATCH_REP_ERR"
#define COMMUN_VAR_BATCH			VAR_BATCH
#define COMMUN_VAR_MES_LOG			"MES_LOG"		/* SNE, 12/06/2001 */

#define COMMUN_LOG_REPORTS			"reports.log"
#define COMMUN_LOG_SQLNET			"sqlnet.log"

#define COMMUN_BALISE_CHAINE_INFO 	"I"
#define COMMUN_BALISE_CHAINE_ERR	"E"
#define COMMUN_BALISE_CHAINE_AVERT	"A"
#define COMMUN_TAG_MSG_REPORTS	"REP-"
#define COMMUN_TAG_MSG_ORACLE	"ORA-"

#define COMMUN_TAG_ERR_ASTER  	"#" COMMUN_BALISE_CHAINE_ERR "#"
#define COMMUN_TAG_INFO_ASTER  	"#" COMMUN_BALISE_CHAINE_INFO "#"
#define COMMUN_TAG_AVERT_ASTER  	"#" COMMUN_BALISE_CHAINE_AVERT "#"

#define COMMUN_RECHERCHER_PARTOUT	'*'
#define COMMUN_RECHERCHER_EN_DEBUT	'^'
#define COMMUN_RECHERCHER_EN_FIN	'$'
#define COMMUN_UNIX_MODE_SUPPRES	"-"
#define COMMUN_UNIX_MODE_TOUS		"a"
#define COMMUN_UNIX_MODE_ADD		"+"
#define COMMUN_UNIX_MODE_EXE		"x"
#define COMMUN_UNIX_MODE_WRITE		"w"
#define COMMUN_UNIX_MODE_READ		"r"


#define COMMUN_SEPARATEUR_1_POINT	'.'
#define COMMUN_CHAINE_SEP_1_POINT	"."
#define COMMUN_SEPARATEUR_2_POINTS	":"
#define COMMUN_SEPARATEUR_PT_VIRGU	";"
#define COMMUN_COMMENTAIRE_DIESE 	'#'

#define COMMUN_t_contexte_exec		t_indicateurs_prog

#define COMMUN_VERSION_ASTER		"3.0"

#define COMMUN_CMD_COPY_FICHIERS		"copy"
#define COMMUN_CMD_SIGN_REDIR_ADD		">>"
#define COMMUN_CMD_SIGN_REDIR			">"
#define COMMUN_CMD_SIGN_REDIR_ERREUR	"2>&1"


typedef struct {
	int niveau_debug;
	int mode_trace;
	char fichier_erreur[COMMUN_LG_PATHNAME]; 
	char fichier_config[COMMUN_LG_PATHNAME];
	char nom_programme[COMMUN_LG_PATHNAME];
} t_indicateurs_prog;

__declspec (dllexport) void __cdecl 	COMMUN_Date_du_jour(char *format, char *resultat);
extern void		COMMUN_init_param_execution(t_indicateurs_prog p_indicateurs);
extern int		COMMUN_open_log(char *nom_fich_log, char *p_nom_prog);
extern int		COMMUN_close_log(char *nom_fich_log);
extern int		COMMUN_affiche_log(char p_error[], char p_param1[], char p_param2[], char p_param3[]) ;
extern char*	COMMUN_upper(char *p_chaine);
extern void		COMMUN_chmod(char *p_nom_fichier, char *p_mode);
extern void		COMMUN_check_env(char *p_batch_log, char *p_separateur, char *p_dev_null, char *p_separateur_var_path) ;
__declspec (dllexport) int __cdecl		COMMUN_get_passwd(char *p_user_file, char *p_nom_instance, char *p_nom_util, char *p_mot_de_passe);
extern int		COMMUN_get_info(char *p_cfg_file, char *p_instance, char *p_info, char *p_var_dest, char *p_separateur, char p_cfg_commentaire);
__declspec (dllexport) int __cdecl		COMMUN_lire_info(char *p_cfg_file, char *p_instance, char *p_info, char *p_var_dest);
extern int		COMMUN_intGet_Os(void);
extern int		COMMUN_quand_date(char *v_date);
extern void		COMMUN_Temporiser(int temps_attente);
extern int		COMMUN_existe_fichier(char *nom_fichier);
extern int		COMMUN_copy_fichier(char *p_fichier_source, char *p_fichier_dest, int p_mode_copy);
extern int		COMMUN_move_fichier(char *p_fichier_source, char *p_fichier_dest, int p_mode_copy);
extern int		COMMUN_Traiter_Liste_Fichiers(char *p_nom_rep, char *p_ext_fich, int (*p_fct_trt)( char *nom_fic) );
extern void		COMMUN_dernier_message_erreur(char *p_result);
__declspec (dllexport) int __cdecl		COMMUN_lire_message_erreur(char *p_fichier_log, char *p_tag_message, char* p_resultat);
extern FILE*	COMMUN_fp_fichier_log(void);
extern void		COMMUN_ecrit_log_fix(char p_type_trace, char *p_format_message, va_list p_arg);
extern void		COMMUN_ecrit_log_var(char p_type_trace, char *p_format_message,  ...);
extern void		COMMUN_debug_trace(int p_niveau_trace, char *p_format_message, ...);
__declspec (dllexport) int __cdecl		COMMUN_lancer_commande(char *p_commande, char *p_nom_fichier, char *p_fichier_sortie);
extern int		COMMUN_afficher_fichier(char *p_nom_fichier);
extern int		COMMUN_open_debug(char *p_nom_fichier);
extern FILE		*COMMUN_fp_fichier_debug(void);
extern void		COMMUN_close_debug(void);
extern int		COMMUN_recopie_fichier(char *p_fichier_source, char *p_fichier_dest);
extern void		COMMUN_ecrit_fichier(FILE *p_fp, char p_type_trace, char *p_format_message, ...);
__declspec (dllexport) int __cdecl		COMMUN_Get_Version_Aster(char *p_version);
__declspec (dllexport) int __cdecl		COMMUN_Extension_Shell(char *p_extension);
