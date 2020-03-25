/*
---------------------------------------------------------------------------
 Fichier        : commun.c
 Date creation  : 18/01/2001
 Auteur         : SNE

 Logiciel       : ASTER                                           
 sous-systeme   : Composants communs de premier niveau                                     
 Description    : Composants communs de premier niveau. Ce fichier ne doit contenir 
				: que des fonctions pures C/C++ => Ce fichier doit pouvoir etre compile
				: sur une machine ne disposant pas d'Oracle
                   
---------------------------------------------------------------------------
 Version        : @(#) commun version 3.1-.1-1
 Date version   : 09/10/2000
 Description	: Version initiale
---------------------------------------------------------------------------

---------------------------------------------------------------------------
 Version        : @(#) commun version 4.0-.1-2
 Date version   : 17/02/2005
 Description	: Evolutions pour ORACLE 9i (__declspec (dllexport) X __cdecl)
---------------------------------------------------------------------------

	--------------------------------------------------------------------
	Fonction	|Date	    |Initiales	|Commentaires 		
	--------------------------------------------------------------------
@(#)	commun 	|18/01/2001 | SNE	| Creation 
@(#)	commun 	|26/09/2001 | SNE	| Evolutions pour ASTER V2.1
@(#)	commun 	|17/02/2005 | PLL	| Evolutions pour ORACLE 9i (__declspec (dllexport) X __cdecl)
---------------------------------------------------------------------------
*/ 

/* Les fichiers inclus */
#define FIC_COMMUN	1

#include "commun.h"

#define COMMUN_NOM_PROGRAMME		"COMMUN"
#define COMMUN_LIB_PROGRAMME		COMMUN_NOM_PROGRAMME " - Composants communs de premier niveau"
#define COMMUN_VERSION_FICHIER		"1.2"

static char commun_version_fichier[]="@(#) " COMMUN_LIB_PROGRAMME " version "COMMUN_VERSION_ASTER"-"COMMUN_VERSION_FICHIER" - "__DATE__ " "__TIME__;

FILE *commun_flog = NULL;
FILE *commun_ftrace = NULL;
char commun_cfg_separateur[5] = ":",
	commun_cfg_commentaire = '#';
char  commun_error_file[COMMUN_LG_PATHNAME]="\0"
	, commun_cfg_file[COMMUN_LG_PATHNAME]="\0"
    , commun_nom_prog[LG_NOM_OBJ]="\0"
    ;
struct tm commun_dat_tm;
char commun_date_j[LG_MAX_DAT_CHAR]="";
char commun_dernier_msg_erreur [COMMUN_LG_LIBL_ERR]="";
int commun_os;
int commun_niveau_debug = 0;
int commun_mode_trace = TRACE_NULL_PAR;

/*
 ====================================================================================
   Nom 			: COMMUN_init_param_execution
   Description 	: Modification de l'etat d'un traitement avec mise a jour eventuelle
				: du libelle de l'erreur
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres   :                                                     
     <p_indicateurs>	: Contexte d'execution (sous la forme d'un type predefini)
   retour		:                                                     
					Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction						|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_init_param_execution	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_init_param_execution(t_indicateurs_prog p_indicateurs)
{
	commun_niveau_debug = p_indicateurs.niveau_debug;
	commun_mode_trace = p_indicateurs.mode_trace;
    if (p_indicateurs.fichier_erreur != NULL) strcpy(commun_error_file, p_indicateurs.fichier_erreur);
    if (p_indicateurs.fichier_config != NULL) strcpy(commun_cfg_file, p_indicateurs.fichier_config);
    if (p_indicateurs.nom_programme != NULL) strcpy(commun_nom_prog, p_indicateurs.nom_programme);
}

/*
 ====================================================================================
   Nom 			: COMMUN_intGet_Os
   Description 	: Cette fonction determine la plateforme de compilation => d'exécution
				: du present paquetage
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres   :                                                     
					Aucun
   retour	:                                                     
					WINDOWS (si plateforme Windows 32), UNIX (sinon)
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_intGet_Os	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_intGet_Os(void)
{
#ifdef WIN32
  commun_os = WINDOWS;
#else
  commun_os = UNIX;
#endif
  return(commun_os);
}

/*
 ====================================================================================
   Nom 			: COMMUN_check_env
   Description 	: Initialisation des parametres lies a l'environnement d'execution
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres   :                                                     
    <p_batch_log>	: Repertoire de stockage des traces d'execution 
    <p_separateur>	: Separateur nom complet de fichiers et de repertoires (/ UNIX ou \ WINDOWS)
    <p_dev_null>	: Fichier /dev/null
	<p_separateur_var_path>	: Separateur pour variables d'environnement (PATH, LIBPATH...)

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_check_env	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_check_env(char *p_batch_log, char *p_separateur, char *p_dev_null, char *p_separateur_var_path) 
{
#ifdef WIN32
    sprintf(p_separateur, "\\\0");
    if (p_dev_null != NULL) sprintf(p_dev_null, "%s%sdev_null\0", p_batch_log, p_separateur);
    sprintf(p_separateur_var_path , ";\0");
#else
    sprintf(p_separateur, "/\0");
    if (p_dev_null != NULL) sprintf(p_dev_null, "/dev/null\0");
    sprintf(p_separateur_var_path , ":\0");
#endif

} /* fin de COMMUN_check_env */

/*
 ====================================================================================
   Nom 			: COMMUN_Temporiser
   Description 	: Mise en attente du traitement (par la fonction sleep sous UNIX, 
				: ou par sa simulation sous WINDOWS)
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <temps_attente>	: Temps d'attente en secondes

  retour	:                                                     
					Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)   COMMUN_Temporiser	|18/01/2001 | SNE		| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_Temporiser(int temps_attente)
{
#ifdef WIN32
	time_t debut
		, maintenant;

	time(&debut);
	maintenant=debut;
	while ((int) difftime(maintenant, debut) < temps_attente) time(&maintenant);
#else
	sleep(temps_attente);
#endif
}

/*
 ====================================================================================
   Nom 			: COMMUN_quand_date
   Description 	: Determine si la date passee en parametre est deja depasse ou non 
				: 
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <p_date>		: Date a verifier

  retour	:                                                     
					DATE_ANTERIEURE : Date deja depassee
					DATE_A_VENIR	: Date non encore echue
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_quand_date	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_quand_date(char *p_date)
{
  char v_annee[6]="\0",
       v_mois[4]="\0",
       v_jour[4]="\0",
       v_heure[4]="\0",
       v_minute[4]="\0",
       v_seconde[4]="\0",
       v_date_systeme[20]="\0";

	memset(v_date_systeme, 0, 20);
	memset(v_seconde, 0, 4);
	memset(v_minute , 0, 4);
	memset(v_heure, 0, 4);
	memset(v_jour , 0, 4);
	memset(v_mois , 0, 4);
	memset(v_annee , 0, 4);

	COMMUN_Date_du_jour(FORMAT_DAT_DEF, NULL);

      strftime(v_annee, 30, "%Y",&commun_dat_tm);
      strftime(v_mois, 30, "%m",&commun_dat_tm);
      strftime(v_jour, 30, "%d",&commun_dat_tm);
      strftime(v_heure, 30, "%H",&commun_dat_tm);
      strftime(v_minute, 30, "%M",&commun_dat_tm);
      strftime(v_seconde, 30, "%S",&commun_dat_tm);
      if ( atoi(v_minute) >= 60 ) 
      {
              sprintf(v_heure, "%d", atoi(v_heure) + 1);
              sprintf(v_minute, "%d", atoi(v_minute) - 60);
      }
      if ( atoi(v_heure) == 24 ) 
      {
              sprintf(v_heure, "0");
      }

      sprintf(v_date_systeme,"%d%d%d%d%d",atoi(v_annee),atoi(v_mois),atoi(v_jour),atoi(v_heure),atoi(v_minute));
      if (strcmp(v_date_systeme,p_date) > 0)
	   return (DATE_ANTERIEURE);
      else
         return (DATE_A_VENIR);
}

/*
 ====================================================================================
   Nom 				: COMMUN_upper
   Description 		: Convertir une chaine de caractères en majuscules
   Auteur			: Sofiane NEKERE
   Date creation	: 18/01/2001
   parametres		:                                                     
    <p_chaine>		: chaine à transformer

   retour	:                                                     
				Pointeur p_chaine transforme
   Historique	:
	---------------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_upper	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
char *COMMUN_upper(char *p_chaine) 
{
unsigned int i=0;

  for (i=0; i<strlen(p_chaine); i++) 
  {
    p_chaine[i] = toupper(p_chaine[i]);
  }

  return p_chaine;
} /* fin de COMMUN_upper */

/*
 ====================================================================================
   Nom 				: COMMUN_rtrim
   Description 		: Supprime les espaces en fin de chaine
   Auteur			: Sofiane NEKERE
   Date creation	: 27/09/2001
   parametres		:                                                     
    <p_chaine>		: chaine à transformer (modifée en sortie)

   retour	:                                                     
				rien 
   Historique	:
	---------------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_rtrim	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_rtrim(char *p_chaine) 
{
  unsigned int i=0;
  for (i=strlen(p_chaine) -1; i>=0 && (p_chaine[i] == ' '||p_chaine[i] == '\r'||p_chaine[i] == '\n'); p_chaine[i--] = 0) ;
} /* fin de COMMUN_rtrim */

/*
	Traitement de fichier 
*/

/*
 ====================================================================================
   Nom 			: COMMUN_existe_fichier
   Description 	: Determine si un fichier existe ou pas  
				: 
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <p_nom_fichier>	: Nom du fichier

  retour	:                                                     
					CODE_FICHIER_EXISTANT : Le fichier existe
					Autre : Code retour systeme (voir errno.h pour l'interpretation)
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_existe_fichier	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_existe_fichier(char *p_nom_fichier)
{
	int v_ret = CODE_FICHIER_EXISTANT;
	v_ret = access(p_nom_fichier, FICHIER_EXISTE);

	if (v_ret == 0)
		v_ret = CODE_FICHIER_EXISTANT;
	else
		if (errno != 0 )
			v_ret = errno;
		else
			v_ret = CODE_FICHIER_INEXISTANT;
	return(v_ret);
}

/*
 ====================================================================================
   Nom 			: COMMUN_existe_rep 
   Description 	: Determine si un repertoire existe ou pas  (et s'il est accessible)
				: (Fonction mise de cote: preferer COMMUN_existe_repertoire)
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <p_nom_repertoire>	: Nom du repertoire

  retour	:                                                     
					COMMUN_CODE_REP_EXISTANT : Le repertoire existe
					COMMUN_CODE_REP_INCCESSIBLE : Le repertoire existe mais 
										n'est pas accessible a l'utilisateur courant
					COMMUN_CODE_ERR_ACCES_REP : Autre erreur (cf errno pour l'interpretation)
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_existe_rep	|25/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_existe_rep(char *p_nom_repertoire)
{
	return(COMMUN_existe_fichier(p_nom_repertoire));
}

/*
 ====================================================================================
   Nom 			: COMMUN_Traiter_Liste_Fichiers
   Description 	: Constitue Une liste de fichiers d'un repertoire donne et, pour chacun
				: de ces fichiers lance un traitement passe en parametre. La liste des 
				: fichiers traites peut etre filtree suivant une extension
   Auteur	: Sofiane NEKERE
   Date creation: 26/01/2001
   parametres    :                                                     
     <p_nom_rep>	: Nom du repertoire
     <p_ext_fich>	: Filtre sur es extensions
     <p_fct_trt>	: Nom du repertoire

  retour	: Renvoie le code retour des traitements appeles. Le traitement de la liste 
			 des fichiers est interrompu a la premier erreur.
   Historique	:
	---------------------------------------------------------------------------
	Fonction						|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_Traiter_Liste_Fichiers	|26/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_Traiter_Liste_Fichiers(char *p_nom_rep, char *p_ext_fich, int (*p_fct_trt)( char *nom_fic) )
{
	int v_ret = TRT_OK;
#ifdef WIN32
  WIN32_FIND_DATA v_fd;
  HANDLE v_hd_p;
  char v_mask_de_recherche[120];


  if ( COMMUN_existe_repertoire(p_nom_rep) == COMMUN_CODE_REP_EXISTANT){
	  sprintf(v_mask_de_recherche, "%s\\*%s\0", p_nom_rep, (p_ext_fich == NULL? "":p_ext_fich)  );
	  v_hd_p = FindFirstFile(v_mask_de_recherche, &v_fd);
	  if (v_hd_p != INVALID_HANDLE_VALUE){
		  if (p_fct_trt != NULL) {
			  v_ret = p_fct_trt(v_fd.cFileName);
		  }

		  while (FindNextFile(v_hd_p, &v_fd)) {
			  if ( v_ret != TRT_OK) break;
			  if (p_fct_trt != NULL) 
				  p_fct_trt(v_fd.cFileName);
		  }
		  FindClose(v_hd_p);
	  }
  }
#else
   DIR *v_pDirectoryPointer;
   struct dirent *v_dp;
   char *v_pos;

   if ( (v_pDirectoryPointer = opendir(p_nom_rep)) != NULL){
		for (v_dp = readdir(v_pDirectoryPointer); v_dp != NULL; v_dp = readdir(v_pDirectoryPointer))
		{
			if (p_ext_fich == NULL|| strcmp(p_ext_fich, "*") == 0){
				v_ret = p_fct_trt(v_dp->d_name);
			}
			else{
				v_pos = strchr( v_dp->d_name, (int) COMMUN_SEPARATEUR_1_POINT);
				if (  v_pos != NULL){
					if ( strcmp(p_ext_fich, v_pos ) == 0) {
							v_ret = p_fct_trt(v_dp->d_name);
					}
				}
			}
			if ( v_ret != TRT_OK) {
				break;
			}
		}
		closedir(v_pDirectoryPointer);
   }
   else 
	   v_ret = KO;
#endif
 return(v_ret);
}

/*
 ====================================================================================
   Nom 				: COMMUN_chmod
   Description 		: Change les droits d'acces a un fichier UNIX
   Auteur			: Sofiane NEKERE
   Date creation	: 18/01/2001
   parametres		:                                                     
    <p_nom_fichier>	: Nom du fichier
    <p_mode>		: Modificateur des attributs (format chmod UNIX)

   retour	:                                                     
				Rien
   Historique	:
	---------------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_chmod	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_chmod(char *p_nom_fichier, char *p_mode)
{
#ifndef WIN32
	char v_cmd[500];

	sprintf(v_cmd, "chmod %s %s\0", p_mode, p_nom_fichier);
	system(v_cmd);
#endif
}

/*
 ====================================================================================
   Nom 			: commun_deplace_fichier
   Description 	: Deplacement physique d'un fichier
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <p_fichier_source>	: Nom du fichier a deplacer ou a renommer
     <p_fichier_dest>	: Nouveau nom ou nouvel emplacement du fichier

  retour	:                                                     
				- OK	  : Fichier de trace ouvert
				- KO	  : erreur generique
				- autre   : code de l'erreur (cf errno)
  Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) commun_deplace_fichier	|14/02/2001 | SNE	|  Creation (@fonction)
 ====================================================================================
*/
int commun_deplace_fichier(char *p_fichier_source, char *p_fichier_dest)
{
	char v_command[500];
    
	memset(v_command, 0, 500);
	sprintf(v_command, COMMUN_CMD_MOVE_FICHIERS " %s %s " , p_fichier_source, p_fichier_dest);
    switch(COMMUN_lancer_commande(v_command, NULL, COMMUN_DEV_NULL)){
		case 0:
			return OK;
		break;
		default:
			return (errno == 0?KO:errno);
		break;
	}

}

/*
 ====================================================================================
   Nom 				: commun_recopie_fichier
   Description 		: Recopie un fichier vers un autre (ou un repertoire)
   Auteur			: Sofiane NEKERE
   Date creation	: 30/01/2001
   parametres		:                                                     
    <p_fichier_source>	: Nom du fichier a copier
    <p_fichier_dest>	: Nom du fichier ou repertoire de destination

   retour	:                                                     
				OK - Le fichier est copie avec succes
				KO - Le n'est pas copie (analyser la varaible errno)
   Historique	:
	---------------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) commun_recopie_fichier	|30/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_recopie_fichier(char *p_fichier_source, char *p_fichier_dest)
{
	char v_command[500];

	sprintf(v_command, COMMUN_CMD_COPY_FICHIERS " %s %s\0", p_fichier_source, p_fichier_dest);
    switch(COMMUN_lancer_commande(v_command, NULL, COMMUN_DEV_NULL)){
		case 0:
			return OK;
		break;
		default:
			return (errno == 0?KO:errno);
		break;
	}

}

/*
 ====================================================================================
   Nom 			: COMMUN_afficher_fichier
   Description 	: Affiche le contenu d'un fichier
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <p_nom_fichier>	: Nom du fichier a afficher

  retour	:                                                     
				- OK	  : Fichier de trace ouvert
				- KO	  : erreur generique
				- autre   : code de l'erreur (cf errno)
  Historique	:
	---------------------------------------------------------------------------
	Fonction					|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_afficher_fichier	|14/02/2001 | SNE	|  Creation (@fonction)
 ====================================================================================
*/
int COMMUN_afficher_fichier(char *p_nom_fichier)
{
	char v_command[500];

	sprintf(v_command, COMMUN_CMD_CAT_FICHIER , p_nom_fichier);
    switch(COMMUN_lancer_commande(v_command, NULL, NULL)){
		case 0:
			return OK;
		break;
		default:
			return (errno == 0?KO:errno);
		break;
	}
}

/*
 ====================================================================================
   Nom 				: COMMUN_copy_fichier
   Description 		: Fonction de copie de fichiers (exportee). Cette fonction effectue
					: des controles prealables puis appelle la fonction de copie physique.
   Auteur			: Sofiane NEKERE
   Date creation	: 30/01/2001
   parametres		:                                                     
    <p_fichier_source>	: Nom du fichier a copier
    <p_fichier_dest>	: Nom du fichier ou repertoire de destination

   retour	:                                                     
				OK - Le fichier est copie avec succes
				COMMUN_CP_EXIST_DEST_FILE - le fichier destination existe
				COMMUN_CP_NO_SOURCE_FILE - le fichier a copier n'existe pas
				Autre : Erreur systeme (analyser a variable errno)
   Historique	:
	---------------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_copy_fichier	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_copy_fichier(char *p_fichier_source, char *p_fichier_dest, int p_mode_copy)
{
	int v_ret = OK;


	if (COMMUN_existe_fichier(p_fichier_source) == COMMUN_CODE_FICHIER_EXISTANT){
		if (COMMUN_existe_fichier(p_fichier_dest) == COMMUN_CODE_FICHIER_EXISTANT){
			switch(p_mode_copy){
				case COMMUN_CP_ECRASE_FICHIER:
					v_ret = COMMUN_recopie_fichier(p_fichier_source, p_fichier_dest);
				break;
			
				default:
					v_ret = COMMUN_CP_EXIST_DEST_FILE;
				break;
			}
		}
		else{
			v_ret = COMMUN_recopie_fichier(p_fichier_source, p_fichier_dest);
		}
	}
	else
		v_ret = COMMUN_CP_NO_SOURCE_FILE;
    return(v_ret);
}

/*
 ====================================================================================
   Nom 			: COMMUN_move_fichier
   Description 	: Deplace un fichier
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <p_fichier_source>	: Nom du fichier a deplacer ou a renommer
     <p_fichier_dest>	: Nouveau nom ou nouvel emplacement du fichier
	 <p_mode_copy>		: Mode de copie:
				- COMMUN_CP_ECRASE_FICHIER : Ecraser le fichier si existe a la destination
				- Autre : Ne pas deplacer si le fichier existe deja

  retour	:                                                     
				- ERR_OUV_FIC : Erreur a l'ouverture du fichier de trace
				- COMMUN_EACCES_FIC : Erreur d'acces au fichier
				- OK	  : Fichier de trace ouvert
  Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_move_fichier	|14/02/2001 | SNE	|  Creation (@fonction)
 ====================================================================================
*/
int COMMUN_move_fichier(char *p_fichier_source, char *p_fichier_dest, int p_mode_copy)
{
	int v_ret = OK;


	if (COMMUN_existe_fichier(p_fichier_source) == COMMUN_CODE_FICHIER_EXISTANT){
		if (COMMUN_existe_fichier(p_fichier_dest) == COMMUN_CODE_FICHIER_EXISTANT){
			switch(p_mode_copy){
				case COMMUN_CP_ECRASE_FICHIER:
					if ((v_ret = rename(p_fichier_source, p_fichier_dest)) == -1)
						v_ret = commun_deplace_fichier(p_fichier_source, p_fichier_dest);
				break;
			
				default:
					v_ret = COMMUN_CP_EXIST_DEST_FILE;
				break;
			}
		}
		else{
			if ((v_ret = rename(p_fichier_source, p_fichier_dest)) == -1)
				v_ret = commun_deplace_fichier(p_fichier_source, p_fichier_dest);
		}
	}
	else
		v_ret = COMMUN_CP_NO_SOURCE_FILE;
    return(v_ret);
}

/*
 ====================================================================================
   Nom 			: COMMUN_open_log
   Description 	: Ouverture du fichier de trace pour le programme en cours
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
     <nom_fich_log>		: Nom du fichier de trace
     <p_nom_prog>		: Nom du programme en cours d'execution

  retour	:                                                     
				- ERR_OUV_FIC : Erreur a l'ouverture du fichier de trace
				- COMMUN_EACCES_FIC : Erreur d'acces au fichier
				- OK	  : Fichier de trace ouvert
  Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_open_log	|18/01/2001 | SNE	| Creation (@fonction)
@(#) COMMUN_open_log	|14/02/2001 | SNE	| Suppression du parametre fic err (@fonction)
 ====================================================================================
*/
int COMMUN_open_log(char *nom_fich_log, char *p_nom_prog)
{
 
  if (p_nom_prog != NULL) strcpy(commun_nom_prog, p_nom_prog);
  COMMUN_Date_du_jour(FORMAT_DAT_LOG, NULL);

  if (nom_fich_log == NULL){
	  commun_flog = stdout;
	  return OK;
  }
  /*
	Ouverture du fichier log
  */
  if ( commun_mode_trace == TRACE_A_LECRAN || !strlen(nom_fich_log))
	  commun_flog = stdout;
  else
	  if (COMMUN_existe_fichier(nom_fich_log) != CODE_FICHIER_EXISTANT)
		  commun_flog = fopen(nom_fich_log,"wt+");
	  else
		  commun_flog = fopen(nom_fich_log,"at+");

	  if (commun_flog == NULL) 
	  {
	    commun_flog = stdout;
		fprintf(commun_flog, MESSAGE_EOUV_FIC, commun_date_j, BALISE_ERREUR, p_nom_prog, nom_fich_log);
		return ERR_OUV_FIC;
	  }

  return OK;
}

/*
 ====================================================================================
   Nom 			: COMMUN_fp_fichier_log
   Description 	: Renvoie un pointeur vers fichier de trace; cela permet au programme
				: en cours d'ecrire dans le fichier de trace a n'importe quel moment
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
					Aucun

   retour	:                                                     
				Pointeur vers le fichier de trace courant.
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_fp_fichier_log	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
FILE *COMMUN_fp_fichier_log(void)
{
	return(commun_flog);
}

/*
 ====================================================================================
   Nom 			: COMMUN_close_log
   Description 	: Fermeture du fichier de trace
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
	<nom_fich_log>	: Nom du fichier de trace

   retour	:                                                     
				- ERR_TRT_FIC : Erreur lors de la fermeture du fichier
				- TRT_OK	: Fichier de trace correctement ferme
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_close_log	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_close_log(char *nom_fich_log)
{
  COMMUN_Date_du_jour(FORMAT_DAT_LOG, NULL);

  if (commun_flog != NULL && commun_flog != stdout)
	  if (fclose(commun_flog) == 0 ){	/* les traces son redirigees a l'ecran */
		commun_mode_trace = TRACE_A_LECRAN;
		commun_flog = stdout;
  	  }
	  else {
		printf(FORMAT_BALISE "" MESSAGE_EFRM_FIC " \n", BALISE_ERREUR, commun_nom_prog, nom_fich_log);
		return ERR_TRT_FIC;
	  }
  else
	  commun_flog = stdout;
  return TRT_OK;
}

/*
 ====================================================================================
   Nom 			: COMMUN_dernier_message_erreur
   Description 	: Renvoie le dernier message d'erreur dans une variable de réception
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
	<p_result>	: Variable de reception

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction						|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_dernier_message_erreur	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_dernier_message_erreur(char *p_result)
{
	strcpy(p_result, commun_dernier_msg_erreur);
}

/*
 ====================================================================================
   Nom 			: COMMUN_open_debug
   Description 	: Ouverture du fichier de debogage
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres	: 
	<p_nom_fichier>	: Nom du fichier de trace

   retour		: 
			- OK : traitement correctement effectue
			- KO : Erreur grave (systeme)
				
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_close_debug	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_open_debug(char *p_nom_fichier)
{
	if (p_nom_fichier == NULL) {
		commun_ftrace = stdout;
	}
	else
		if (!strlen(p_nom_fichier)) {
			commun_ftrace = stdout;
		}
		else
			if ( (commun_ftrace = fopen(p_nom_fichier,"at+")) == NULL)
			{
				commun_ftrace = stdout;
			}
	return OK;
}

/*
 ====================================================================================
   Nom 			: COMMUN_close_debug
   Description 	: Fermeture de fichier de debogage
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres	: Aucun
   retour		: Aucun
				
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_close_debug	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_close_debug()
{
		if (commun_ftrace != stdout && commun_ftrace != NULL)
			fclose(commun_ftrace);
		commun_ftrace = NULL;
}

/*
 ====================================================================================
   Nom 			: COMMUN_fp_fichier_debug
   Description 	: Renvoie le pointeur vers le fichier de trace (debogage)
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres	: Aucun
   retour	:                                                     
				Pointeur vers le fichier de debogage
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#)COMMUN_fp_fichier_debug	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
FILE *COMMUN_fp_fichier_debug(void)
{
	return(commun_ftrace);
}

/*
 ====================================================================================
   Nom 			: COMMUN_ecrit_log_fix
   Description 	: Ecrit une trace dans le fichier de trace, suivant un format donne
				: avec un nombre variable d'arguments dont la liste est prealablement constituee
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
	<p_type_trace>		: Type de message de trace (cf BALISES)
	<p_format_message>	: Format d'affichage du message
	<p_arg>				: Liste d'arguments variable prealablement contituee

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_ecrit_log_fix	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_ecrit_log_fix(char p_type_trace, char *p_format_message, va_list p_arg)
{
    char v_format[COMMUN_LG_SR_MESS_ERR_LIBL+COMMUN_LG_ENTETE_MSG_LOG];

	if (commun_flog == NULL) commun_flog = stdout;

    memset(commun_dernier_msg_erreur, 0, COMMUN_LG_LIBL_ERR);
	memset(v_format, 0, COMMUN_LG_SR_MESS_ERR_LIBL+COMMUN_LG_ENTETE_MSG_LOG);
    COMMUN_Date_du_jour(FORMAT_DAT_LOG, NULL);
	sprintf(v_format, ENTETE_MESSAGE_LOG "%s \n\0", commun_date_j, p_type_trace, commun_nom_prog, p_format_message);
	
    vfprintf(commun_flog, v_format, p_arg);
	fflush(commun_flog);
    vsprintf(commun_dernier_msg_erreur, v_format, p_arg);
}

/*
 ====================================================================================
   Nom 			: COMMUN_ecrit_log_var
   Description 	: Ecrit une trace dans le fichier de trace, suivant un format donne
				: avec un nombre variable d'arguments 
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
	<p_type_trace>		: Type de message de trace (cf BALISES)
	<p_format_message>	: Format d'affichage du message
						: Liste d'arguments variable  (en fonction du format)

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_ecrit_log_var	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_ecrit_log_var(char p_type_trace, char *p_format_message,  ...)
{
    va_list v_arg;
    char v_format[COMMUN_LG_SR_MESS_ERR_LIBL+COMMUN_LG_ENTETE_MSG_LOG];

	if (commun_flog == NULL) commun_flog = stdout;

    memset(commun_dernier_msg_erreur, 0, COMMUN_LG_LIBL_ERR);
	memset(v_format, 0, COMMUN_LG_SR_MESS_ERR_LIBL+COMMUN_LG_ENTETE_MSG_LOG);
    COMMUN_Date_du_jour(FORMAT_DAT_LOG, NULL);
	
	va_start (v_arg, p_format_message);
	sprintf(v_format, ENTETE_MESSAGE_LOG "%s", commun_date_j, p_type_trace, commun_nom_prog, p_format_message);
    vfprintf(commun_flog, v_format, v_arg);
    vsprintf(commun_dernier_msg_erreur, v_format, v_arg);
	fflush(commun_flog);
    va_end (v_arg);
}

/*
 ====================================================================================
   Nom 			: COMMUN_ecrit_fichier
   Description 	: Ecrit une trace dans le fichier de trace, suivant un format donne
				: avec un nombre variable d'arguments dont la liste est prealablement constituee
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
	<p_type_trace>		: Type de message de trace (cf BALISES)
	<p_format_message>	: Format d'affichage du message
	<p_arg>				: Liste d'arguments variable prealablement contituee

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_ecrit_fichier	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_ecrit_fichier(FILE *p_fp, char p_type_trace, char *p_format_message, ...)
{
    va_list v_arg;
    char v_format[COMMUN_LG_SR_MESS_ERR_LIBL+COMMUN_LG_ENTETE_MSG_LOG];

	if (p_fp == NULL) return;

	memset(v_format, 0, COMMUN_LG_SR_MESS_ERR_LIBL+COMMUN_LG_ENTETE_MSG_LOG);
    COMMUN_Date_du_jour(FORMAT_DAT_LOG, NULL);
	
	va_start (v_arg, p_format_message);
	sprintf(v_format, ENTETE_MESSAGE_LOG "%s", commun_date_j, p_type_trace, commun_nom_prog, p_format_message);
    vfprintf(p_fp, v_format, v_arg);
	fflush(p_fp);
    va_end (v_arg);

}

/*
 ====================================================================================
   Nom 			: COMMUN_debug_trace
   Description 	: Ecrit une trace , suivant un format donne
				: avec un nombre variable d'arguments. Cette fonction peut etre utilisee
				: pour ecrire dans des fichiers de debogage 
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
	<p_niveau_trace>	: Niveau de trace
	<p_type_trace>		: Type de trace a ecrire
	<p_format_message>	: Format d'affichage du message
						: Liste d'arguments variable  (en fonction du format)

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_debug_trace	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
void COMMUN_debug_trace(int p_niveau_trace, char *p_format_message, ...)
{
	va_list v_arg;
    char v_format[100];

	memset(v_format, 0, 100);
	if (commun_niveau_debug < p_niveau_trace) return;
	if (commun_ftrace == NULL) commun_ftrace = stdout ;
	
    COMMUN_Date_du_jour(FORMAT_DAT_LOG, NULL);
	sprintf(v_format, ENTETE_MESSAGE_LOG "%s", commun_date_j, BALISE_INFORMATIVE, commun_nom_prog, p_format_message);
	
	va_start (v_arg, p_format_message);
	vfprintf(commun_ftrace, v_format, v_arg);
	fflush(commun_ftrace);

    va_end (v_arg);
}

/*
 ====================================================================================
   Nom 			: COMMUN_affiche_log
   Description 	: Affiche un message d'erreur issus du fichier des message d'erreur
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
    <p_error>  : identifiant de l'erreur
    <p_param1> : paramètre n°1 du message
    <p_param2> : paramètre n°2 du message 
    <p_param3> : paramètre n°3 du message 

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_affiche_log	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
int COMMUN_affiche_log(char p_error[], char p_param1[], char p_param2[], char p_param3[]) 
{ 

  unsigned int lg_mess = 900, i;
  int fin,
      lg_rec = 128,
	trouve = 0;

  char fic_rec[128]="\0",
       num_err[7]="\0",
       libl_err[601]="\0",
	   format_msg[1000]="";


  FILE *ferr;

  memset(commun_dernier_msg_erreur, 0, COMMUN_LG_LIBL_ERR);
  if (commun_mode_trace == TRACE_NULL_PAR){ /* Log non initialise, option par defaut*/
	  commun_mode_trace = TRACE_A_LECRAN;
	  commun_flog=stdout;
  }
  if (commun_flog == NULL) commun_flog = stdout;

  COMMUN_Date_du_jour(FORMAT_DAT_LOG, NULL);
  /* Variables non encore initialisee */
  if (!strlen(commun_error_file) ){
     fprintf(commun_flog, ENTETE_MESSAGE_LOG "" MESSAGE_ERR_NTFD "\n", commun_date_j, BALISE_ERREUR, commun_nom_prog, p_error, commun_error_file);
     sprintf(commun_dernier_msg_erreur, ENTETE_MESSAGE_LOG "" MESSAGE_ERR_NTFD "\n", commun_date_j, BALISE_ERREUR, commun_nom_prog, p_error, commun_error_file);
	 fflush(commun_flog);
     return ERR_MSG_NTFD;
  }
  if ((ferr = fopen(commun_error_file,"r")) == NULL) 
  {
    fprintf(commun_flog,  MESSAGE_EOUV_FIC "\n", commun_date_j, BALISE_ERREUR, commun_nom_prog, commun_error_file);
    return ERR_OUV_FIC;
  }

/*
   Premiere phase : recherche du libbelé de l'erreur
*/
  fin=0;
  while ( fin==0 ) 
  {
    if ( fgets(fic_rec, lg_rec, ferr) == NULL) 
    {
       fclose(ferr);
      fin=1;
    }
    else 
    {
      if (strncmp(fic_rec, "#", 1) != 0) 
      {
        strcpy(num_err, strtok(fic_rec, "@"));
        if (strcmp(num_err, p_error) == 0) 
        {
	    trouve = 1;
          strcpy(libl_err, strtok(NULL, "@"));
          fclose(ferr);
          fin=1;
        }
      }
    }
  }

  if (trouve){
    for (i=0;i<strlen(libl_err)-1;i++){
	if (libl_err[i] == '%') {
		switch(libl_err[i+1]){
			case '1':
			case '2':
			case '3':
			case '4':
				libl_err[i+1] = 's';
			default:
				break;
		}
	}
    }
  fprintf(commun_flog, "%s : ", commun_date_j);
  fprintf(commun_flog, libl_err, commun_nom_prog, p_param1, p_param2, p_param3);
  fprintf(commun_flog, "\n");
  fflush(commun_flog);
  sprintf(format_msg, "%s : %s\n\0", commun_date_j, libl_err);
  sprintf(commun_dernier_msg_erreur, format_msg, commun_nom_prog, p_param1, p_param2, p_param3);
  return TRT_OK;
  }
  else {
     fprintf(commun_flog, ENTETE_MESSAGE_LOG "" MESSAGE_ERR_NTFD "\n", commun_date_j, BALISE_ERREUR, commun_nom_prog, p_error, commun_error_file);
     sprintf(commun_dernier_msg_erreur, ENTETE_MESSAGE_LOG "" MESSAGE_ERR_NTFD "\n", commun_date_j, BALISE_ERREUR, commun_nom_prog, p_error, commun_error_file);
	 fflush(commun_flog);
     return ERR_MSG_NTFD;
  }
} /* fin de COMMUN_affiche_log */

/*
 ====================================================================================
   Nom 			: COMMUN_get_info
   Description 	: Lit la valeur d'une variable dans le fichier de configuration ASTER
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres   :                                                     
    <p_cfg_file>		: Fichier de configuration ASTER
    <p_instance>		: Nom de l'instance
    <p_info>			: Nom de la variable recherchee
	<p_var_dest>		: Variable destinee a la reception de la valeur 
	<p_cfg_separateur>	: Caractere de separation des champs
	<p_cfg_commentaire>	: Caractere de debut des lignes de commentaires

   retour	:                                                     
				OK - La variable recherchee est trouve et sa valeur est renvoyee
				KO - La variable recherchee n'a pu etre trouvee 
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_get_info	|18/01/2001 | SNE	| Creation (@fonction)
@(#) COMMUN_get_info	|26/09/2001 | SNE	| Version 'Case Insensitive' (Evol V2.1 @fonction)
 ====================================================================================
*/
int COMMUN_get_info(char *p_cfg_file, char *p_instance, char *p_info, char *p_var_dest, char *p_cfg_separateur, char p_cfg_commentaire)
{

  char fic_rec[256]="\0",
       champ1_rec[256]="\0",
       champ2_rec[256]="\0",
       v_info[256]="\0"
	   , v_instance[256];

  FILE *v_fcfg;

  int fin=0,
      lg_rec=255;

  memset(v_instance, 0, 256);
  strcpy(v_instance, p_instance);
  COMMUN_upper(v_instance);

  if ((v_fcfg = fopen(p_cfg_file,"r")) == NULL) 
  {
    return COMMUN_GI_ERR_OUV_FIC;
  }

  fin=0;
  while ( fin==0 ) 
  {
	memset(fic_rec, 0, lg_rec+1);
	memset(champ1_rec, 0, lg_rec+1);
	memset(champ2_rec, 0, lg_rec+1);
	  if ( fgets(fic_rec, lg_rec, v_fcfg) == NULL) 
    {
      fclose(v_fcfg);
      return COMMUN_GI_ERR_INFO_NTFD;
    }
    else 
    {
	   COMMUN_rtrim(fic_rec);
      if (*fic_rec != p_cfg_commentaire && *fic_rec != '\r' && *fic_rec != '\n' && strlen(fic_rec)) 
      {
		  if (strchr(fic_rec, *p_cfg_separateur) != NULL){
			strcpy(champ1_rec, strtok(fic_rec, p_cfg_separateur));
			strcpy(champ2_rec, strtok(NULL, p_cfg_separateur));
			COMMUN_upper(champ2_rec);
			if ( (strcmp(champ2_rec, v_instance) == 0) && (strcmp(champ1_rec, p_info) == 0) ) 
			{
			  strcpy(v_info, strtok(NULL, p_cfg_separateur));
			  fclose(v_fcfg);
			  fin=1;
			}
		  }
      }
    }
  }

  if ( v_info[strlen(v_info) - 1] == '\n' ) 
  {
    v_info[strlen(v_info) - 1] = '\0';
  }

   COMMUN_rtrim(v_info);
  strcpy(p_var_dest, v_info);
  return (OK);
} /* fin de COMMUN_get_info */

#ifdef _cplusplus
extern "C"{
#endif

/*
 ====================================================================================
   Nom 			: COMMUN_Date_du_jour
   Description 	: Determine la date du jour selon le format demande, la stocke, 
				: puis eventuellement la renvoie dans une variable de reception
				: 
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres   :                                                     
     <p_format>	: Format de representation de la date
					trois formats sont predefinis:
					- FORMAT_DAT_LOG	: format d'affichage dans les fichiers de trace
					- FRMT_EXT_F_LOG	: format d'insertion dans les nom de fichiers
					- FORMAT_DAT_DEF	: format par defaut (date et heure)
     <p_resultat>	: variable de reception (NULL et absente)

  retour		:                                                     
					Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_Date_du_jour	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) void __cdecl COMMUN_Date_du_jour(char *p_format, char *p_resultat)
{
  time_t v_dat_tim;

  memset(commun_date_j, 0, LG_MAX_DAT_CHAR);
  time(&v_dat_tim);
  commun_dat_tm=(*localtime(&v_dat_tim));
  strftime(commun_date_j, 30, p_format, &commun_dat_tm);
  if (p_resultat != NULL) strcpy(p_resultat, commun_date_j);
}

/*
 ====================================================================================
   Nom 			: COMMUN_get_passwd
   Description 	: Recupere le mot de passe d'un utilisateur a partir du fichier des mots
				: de passes ASTER
   Auteur		: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres   :                                                     
    <p_user_file>		: Fichier des utilisateurs/mots de passe ASTER
    <p_nom_instance>	: Nom de l'instance
    <p_nom_util>		: Code utilisateur
	<p_mot_de_passe>	: Variable destinee a la reception du mot de passe

   retour	:                                                     
				OK - Le mot de passe est trouve et est renvoye
				KO - Le mot de passe n'a pu etre recupere
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_get_passwd	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl COMMUN_get_passwd(char *p_user_file, char *p_nom_instance, char *p_nom_util, char *p_mot_de_passe) 
{
 
  char fic_rec[256]="\0",
       champ1_rec[256]="\0",
       champ2_rec[256]="\0"
	   , v_nom_instance[35]
	   , v_nom_util[35]
	   ;
 
  FILE *v_fusr;

  int fin=0,
	trouve=0,
      lg_rec=255;

  memset (champ1_rec, 0, 30);
  memset (champ2_rec, 0, 30);
  memset (v_nom_util, 0, 35);
  strcpy(p_mot_de_passe, "\0");

  strcpy(v_nom_instance, p_nom_instance);
  strcpy(v_nom_util, p_nom_util);

  COMMUN_upper(v_nom_util);
  COMMUN_upper(v_nom_instance);

  if ((v_fusr = fopen(p_user_file,"r")) == NULL) 
  {
    return COMMUN_GP_ERR_OUV_FIC;
  }

  fin=0;
  while ( fin==0 ) 
  {
    if ( fgets(fic_rec, lg_rec, v_fusr) == NULL) 
    {
      fclose(v_fusr);
      return COMMUN_GP_ERR_PASW_NTFD;
    }
    else 
    {
	   COMMUN_rtrim(fic_rec);
      if (strncmp(fic_rec, "#", 1) != 0 && strncmp(fic_rec, "\r", 1) != 0 && strncmp(fic_rec, "\n", 1) != 0 && strlen(fic_rec)) 
      {
        strcpy(champ1_rec, strtok(fic_rec, ":"));
        if (!strcmp(champ1_rec, fic_rec) ){
			strcpy(champ2_rec, strtok(NULL, ":"));
			COMMUN_upper(champ2_rec);
		}
		COMMUN_upper(champ1_rec);
        if ( (strcmp(champ1_rec, v_nom_instance) == 0) && (strcmp(champ2_rec, v_nom_util) == 0) ) 
        {
	      trouve=1;
          strncpy(p_mot_de_passe, strtok(NULL, ":"), COMMUN_LG_PASSWORD-1);
		  p_mot_de_passe[COMMUN_LG_PASSWORD] = 0;
          if ( p_mot_de_passe[strlen(p_mot_de_passe) - 1] == '\n' || p_mot_de_passe[strlen(p_mot_de_passe) - 1] == '\r') 
          {
            p_mot_de_passe[strlen(p_mot_de_passe) - 1] = '\0';
          }

          fclose(v_fusr);
          fin=1;
        }
      }
    }
  }
  return(trouve? OK:COMMUN_GP_ERR_PASW_NTFD);
} /* fin de COMMUN_get_passwd */

/*
 ====================================================================================
   Nom 			: COMMUN_lire_info
   Description 	: Lit la valeur d'une variable dans le fichier de configuration ASTER
				: Cette fonction ne tient pas compte du separateur utilise.
   Auteur		: Sofiane NEKERE
   Date creation: 05/02/2001
   parametres   :                                                     
    <p_cfg_file>		: Fichier de configuration ASTER
    <p_instance>		: Nom de l'instance
    <p_info>			: Nom de la variable recherchee
	<p_var_dest>		: Variable destinee a la reception de la valeur 

   retour	:                                                     
				OK - La variable recherchee est trouve et sa valeur est renvoyee
				KO - La variable recherchee n'a pu etre trouvee 
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_lire_info	|05/02/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl COMMUN_lire_info(char *p_cfg_file, char *p_instance, char *p_info, char *p_var_dest)
{
	int v_retour = OK;

	v_retour  = COMMUN_get_info(p_cfg_file, p_instance, p_info, p_var_dest, COMMUN_SEPARATEUR_2_POINTS, COMMUN_COMMENTAIRE_DIESE);

	if (v_retour != OK)
		v_retour  = COMMUN_get_info(p_cfg_file, p_instance, p_info, p_var_dest, COMMUN_SEPARATEUR_PT_VIRGU, COMMUN_COMMENTAIRE_DIESE);
    
	return(v_retour);
}

/*
 ====================================================================================
   Nom 			: COMMUN_lire_message_erreur
   Description 	: Cette fonction effectue une recherche par mot cle dans un fichier 
				: d'erreur 
   Auteur	: Sofiane NEKERE
   Date creation: 18/01/2001
   parametres    :                                                     
    <p_fichier_log>	: Nom du fichier a scruter 
    <p_tag_message>	: Chaine de caractère a rechercher; il est possible de mettre des modificteur de recherche:
			COMMUN_RECHERCHER_EN_DEBUT (caratere ^ en debut de chaine) : la chaine recherchee
						doit etre en debut de ligne
			COMMUN_RECHERCHER_EN_FIN (caractere $ e fin de chaine) : la chaine recherche doit se trouver en
						fin de ligne
			COMMUN_RECHERCHER_PARTOUT (aucune specification) : la chaine recherchee peut etre trouvee 
						n'importe ou dans la ligne.

    <p_resultat>	: Contient la ligne qui correspond au critere de recherche indique

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction					|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_lire_message_erreur	|18/01/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl COMMUN_lire_message_erreur(char *p_fichier_log, char *p_tag_message, char *p_resultat)
{
	FILE *fp_log;
	char ligne[101], *p_tmp;
	char position = COMMUN_RECHERCHER_PARTOUT;
	int arret=0;
	int v_retour = COMMUN_TRT_KO;
	*p_resultat = 0;

	switch(position = *p_tag_message){
		case COMMUN_RECHERCHER_EN_DEBUT:
			strcpy(p_tag_message, (p_tag_message+1));
		break;

		case COMMUN_RECHERCHER_EN_FIN:
			strcpy(p_tag_message, (p_tag_message+1));
		break;

		default:
			position = COMMUN_RECHERCHER_PARTOUT;
		break;
	}

		if ( (fp_log = fopen(p_fichier_log, "r")) != NULL){
			while (!arret){
				memset(ligne, 0, 101);
				if ( fgets(ligne, 100, fp_log) != NULL) {
					COMMUN_rtrim(ligne);
					if (p_tag_message == NULL){
						strcpy(p_resultat, ligne);
						v_retour = COMMUN_TRT_OK;
					}
					else{
						if (strlen(ligne) >= strlen(p_tag_message)){
							switch(position){
								case COMMUN_RECHERCHER_EN_DEBUT:
									if ( strncmp(p_tag_message, ligne, strlen(p_tag_message)) == 0 ){
										strcpy(p_resultat, ligne);
										arret = !arret;
										v_retour = COMMUN_TRT_OK;
									}
								break;

								case COMMUN_RECHERCHER_EN_FIN:
									if ( strncmp(p_tag_message, ligne+strlen(ligne) - strlen(p_tag_message), strlen(p_tag_message)) == 0 ){
										strcpy(p_resultat, ligne);
										arret = !arret;
										v_retour = COMMUN_TRT_OK;
									}
								break;

								default:
									for (p_tmp=ligne; p_tmp < (ligne + strlen(ligne) - strlen(p_tag_message)); p_tmp++){
										if ( strncmp(p_tag_message, p_tmp, strlen(p_tag_message)) == 0 ){
											strcpy(p_resultat, ligne);
											arret = !arret;
											v_retour = COMMUN_TRT_OK;
											break;
										}
									}
							}
						}
					}
				}
				else
					arret = !arret;
			}
			fclose(fp_log);
		}
	return(v_retour);
}

/*
 ====================================================================================
   Nom 			: COMMUN_Get_Version_Aster
   Description 	: Cette fonction renvoie la version interne d'ASTER
   Auteur		: Sofiane NEKERE
   Date creation: 26/09/2001
   parametres   :                                                     
					p_version : modifié en sortie pour indiquer la version courante d'ASTER
   retour	:
				OK
					
   Historique	:
	---------------------------------------------------------------------------
	Fonction					|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_Get_Version_Aster	|26/09/2001 | SNE	| Creation (@fonction) Evol V2.1
 ====================================================================================
*/
__declspec (dllexport) int __cdecl COMMUN_Get_Version_Aster(char *p_version)
{
	strcpy(p_version, COMMUN_VERSION_ASTER);
	return(OK);
}

/*
 ====================================================================================
   Nom 			: COMMUN_lancer_commande
   Description 	: Execute une commande via le shell et analyse le code retour 
   Auteur		: Sofiane NEKERE
   Date creation: 31/01/2001
   parametres   :                                                     
    <p_commande>		: Ligne de commande a executer

   retour	:                                                     
				OK - Le traitement s'est bien deroule
				KO - Erreur lie au systeme d'exploitation
				COMMUN_CODE_FICHIER_EXISTANT : commande non trouvee
				CODE_FICHIER_VERROUILLE : Droit d'execution refuse
				Autre : Retour du programme appele (a analyser par l'appelant)

   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_lancer_commande	|31/01/2001 | SNE	| Creation (@fonction)
@(#) COMMUN_lancer_commande	|15/02/2001 | SNE	| Ajout param <p_nom_fichier> (@fonction)
@(#) COMMUN_lancer_commande	|27/09/2001 | SNE	| Suppression du fichier dans tous les cas (@fonction)
@(#) COMMUN_lancer_commande	|12/10/2001 | SNE	| Test si nom fichier non null avant longueur de la chaine (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl COMMUN_lancer_commande(char *p_commande, char *p_nom_fichier, char *p_fichier_sortie)
{

	int v_retour;
	char v_cmd[1000] = "";
	FILE *fp = NULL;

	memset(v_cmd, 0, 1000);
	if (p_nom_fichier == NULL){
		strcpy(v_cmd, p_commande);
	}
	else{
		if ( strlen(p_nom_fichier) == 0)
			strcpy(v_cmd, p_commande);
		else
		{
			if ( (fp = fopen(p_nom_fichier, "wt+")) != NULL)
			{
				if (fputs(p_commande, fp) != EOF )
					sprintf(v_cmd, COMMUN_CMD_RUN_CMD "%s\0", p_nom_fichier);
				else
					strcpy(v_cmd, p_commande);
				fclose(fp);
				COMMUN_chmod(p_nom_fichier, COMMUN_UNIX_MODE_ADD "" COMMUN_UNIX_MODE_EXE);
			}
			else
				strcpy(v_cmd, p_commande);

		}

	}

/*
	Eventuelle redirection des resultats de la commande
*/
	if (p_fichier_sortie != NULL)
		if (strlen(p_fichier_sortie))
			sprintf(v_cmd, "%s "COMMUN_CMD_SIGN_REDIR "%s\0", v_cmd,  p_fichier_sortie);
/*
	Execution de la commande ou du script cree
*/
   switch(v_retour = system(v_cmd))  
   {
	   case 0:
	   break;
	   case -1:
	   case 127:
			switch(errno){
			   case ENOENT:
				   v_retour = COMMUN_CODE_FICHIER_EXISTANT;
			   break;

			   case EACCES:
				   v_retour = CODE_FICHIER_VERROUILLE;
			   break;

			   default:
			   break;
			}
		break;

		default:
			v_retour = (errno == 0?v_retour:errno);
		break;
   }

   /*
			Test si nom fichier non null avant longueur de la chaine (@fonction)
   */
   if (p_nom_fichier != NULL)
		if ( strlen(p_nom_fichier) != 0)
			remove(p_nom_fichier);

   return(v_retour);
}

/*
 ====================================================================================
   Nom 			: COMMUN_Extension_Shell
   Description 	: Cette fonction renvoie l'extension des fichiers scripts shell 
					BAT sous DOS/WINDOWS ou sh sous UNIX
   Auteur		: Sofiane NEKERE
   Date creation: 27/09/2001
   parametres   :                                                     
					p_extension : modifié en sortie pour indiquer la version courante d'ASTER
   retour	:
				OK
					
   Historique	:
	---------------------------------------------------------------------------
	Fonction				|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) COMMUN_Extension_Shell	|26/09/2001 | SNE	| Creation (@fonction) Evol V2.1
 ====================================================================================
*/
__declspec (dllexport) int __cdecl COMMUN_Extension_Shell(char *p_extension)
{
	strcpy(p_extension, COMMUN_EXTENSION_FIC_SHELL);
	return(OK);
}

#ifdef _cplusplus
}
#endif