/*
---------------------------------------------------------------------------------------
-- Nom           : PIAF_system.c
-- Date creation : 23/12/1999
-- Creee par     : SOFIANE NEKERE (SEMA GROUP)
-- Role          : Appel systeme : lancement d'une commande systeme 
--		       
-- Parametres    :     
-- Valeur retournee : 
--			    
-- Appels		 : 
-- Version 		 : 4.0-1.6
--		--------------------------------------------------------------------
--		Fonction		|Date	    |Auteur	|Version |Commentaires 		
--		--------------------------------------------------------------------
@(#)	PIAF_system.c 	|23/12/1999 | SNE	| 1.0-1.0| Creation 
@(#)	PIAF_system.c 	|03/01/2001 | SNE	| 2.1-1.0| Portage NT - Ajout de fonction de trace
@(#)	PIAF_system.c 	|08/08/2001 | SNE	| 2.1-1.1| Ajout de la fonction ASTER_env_param
@(#)	PIAF_system.c 	|26/09/2002 | SNE	| 2.2-1.2| Nouvelles fonctions liées à la sécurité
@(#)	PIAF_system.c 	|01/07/2003 | SGN	| 3.1-1.5| Fonctions liées a la F7
@(#)	PIAF_system.c 	|17/02/2005 | PLL	| 4.0-1.6| Evolutions pour ORACLE 9i (__declspec (dllexport) X __cdecl)
---------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "commun.h"
#include "piaf_system.h"


#ifdef WIN32
	#include <process.h>
#else 
	#include <unistd.h>
	#define _P_OVERLAY	0x01
#endif

#define PIAF_EXEC_OK				0
#define PIAF_ERR_NO_CMD				-1
#define PIAF_ERR_EXEC				-2
#define PIAF_ERR_NO_MEM				-3
#define PIAF_ERR_OUV_FIC			-4
#define PIAF_SEPARATEUR				' '
#define PIAF_SYS_ECRITURE_FORMATEE	'F'
#define PIAF_SYS_ECRITURE_LIBRE		'L'
#define PIAF_SYS_NOM_PROGRAMME		"piaf_system"
#define PIAF_SYS_VERSION_FICHIER	"1.6"
#define ASTER_CRYPT_MASK			"azertyuiopmlkjhgfdsqwxcvbn1593"
#define ASTER_CRYPT_KEY				"ouskfhjqypmdekqsoffflogthxykgi"
char PIAF_sys_version_fichier[]="@(#) " PIAF_SYS_NOM_PROGRAMME " version "COMMUN_VERSION_ASTER"-"PIAF_SYS_VERSION_FICHIER" - "__DATE__ " "__TIME__;

/* Modif sgn v3.0d-1.4 */
#define ASTER_DATE_CREATION			0
#define ASTER_DATE_ACCES			1
#define ASTER_DATE_MODIFICATION		2
/* Fin modif sgn */


/*==============================================================  */
/* Nom : intNombreDeMots										  */
/* Cette fonction compte les mots qui composent une phrase 		  */
/* Definitions : 												  */
/* 	Un separateur est un caractere conventionnel permettant 	  */
/*	de constituer des ensemble de carcateres contigus			  */ 
/*		(chaines de caracteres) 			 					  */
/*	Ces ensemble de caracteres s'appellent des mots 			  */
/* 	Le separateur dans notre cas est le caractere <ESPACE> 		  */
/*==============================================================  */
int intNombreDeMots(char *phrase)
{
  char *tmp;
  int nb_mots=0, i=0;

	/* on exclut tous les espaces en debut de phrase */
   	for (tmp=phrase; 
	    *tmp == PIAF_SEPARATEUR && tmp <(phrase +strlen(phrase));
	    tmp++);

	/* Si la phrase contient autre chose que des espaces */
	/* alors on se trouve necessairement en debut du premier mot */
   	if (tmp < (phrase + strlen(phrase) )) {
		nb_mots = 1;
		for (i=0; i<(int) strlen(tmp); i++){
	 	 if (*(tmp + i) == PIAF_SEPARATEUR){
		   while ( *(tmp +i) == PIAF_SEPARATEUR && i++< (int) strlen(phrase));
		   nb_mots++;
	 	 }
		}
	}
return(nb_mots);
}

/*==============================================================  */
/* Nom : intNombreDeMots										  */
/* Cette fonction extrait le mot qui suit le mot courant 		  */
/*==============================================================  */
char *strExtraitMot(char *position)
{
   int taille_initiale=strlen(position);
   char *tmp = position;

   if (taille_initiale <= 0) return NULL;
   for (tmp=position;
	*tmp != PIAF_SEPARATEUR && tmp < (position +taille_initiale);
	 tmp++);
   
   for ( ; *tmp == PIAF_SEPARATEUR && tmp < (position +taille_initiale);
	 tmp++) *tmp=0;
   return (tmp);
}

#ifndef WIN32
int _spawnvp(int mode, const char* cmd,  char *const *arguments)
{
 pid_t num_process;
 	if ( (num_process = fork()) != 0){
     	   if (execvp(cmd, arguments) != 0){
				exit(PIAF_ERR_EXEC);
     	   }
  	}
  return ((int) num_process);
}
#endif


#ifdef _cplusplus
extern "C"{
#endif

/*
 ====================================================================================
   Nom 			: ASTER_get_crypt_key
   Description 	: Cle de cryptage des mots de passe ASTER
   Auteur		: Sofiane NEKERE
   Date creation: 08/08/2001
   parametres   :                                                     
    <p_retour>	: Variable receptacle modifiee en sortie

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) ASTER_get_crypt_key|26/09/2002 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl ASTER_get_crypt_key(char *p_retour) 
{
	int v_ret =  PIAF_EXEC_OK;

	strcpy(p_retour, ASTER_CRYPT_KEY);
	return(v_ret);
}

/*
 ====================================================================================
   Nom 		: PIAF_appel_systeme	
   Description 	: Fonction principale d'execution de commandes 
   Auteur	: Sofiane NEKERE
   Date creation: 26/12/2000
   Historique	:
		---------------------------------------------------------------------------
		Fonction			|Date	    |Initiales	|Commentaires 
		---------------------------------------------------------------------------
@(#)	PIAF_appel_systeme	|26/12/2000 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl PIAF_appel_systeme(char *param, char *fic_sor, char *fic_err)
{
 int	erreur = PIAF_EXEC_OK, 
	nbr_arg =0,
	i;
 FILE *fsortie = stdout, *ferreur=stderr;
 char **arguments = NULL;

  if (!strlen(param) ) return(PIAF_ERR_NO_CMD);
  if (strlen(fic_sor) ) {fsortie=fopen(fic_sor, "at+"); ferreur = fsortie; }
  if (strlen(fic_err) ) {ferreur=fopen(fic_err, "at+"); fsortie;}

  nbr_arg=intNombreDeMots(param);
  if (fsortie != NULL) 
	fprintf(fsortie, "\nPIAF_appel_systeme : execution ligne de commande #%s#\n", param);

/* On alloue un element de plus pour ce que la fonction execv exige un */
/* pointeur NULL synonyme de fin de liste des arguments */
  if ( (arguments = malloc((size_t) (nbr_arg+1)*sizeof(*arguments))) != NULL )
  {
	/* On constitue la liste des parametres */
	for (i=1, arguments[0] = param; i < nbr_arg; i++)
			arguments[i] = strExtraitMot(arguments[i-1]);
	arguments[nbr_arg] = NULL;

	/* On execute la commande en creant un nouveau processus */
	if ( _spawnvp(_P_OVERLAY, *arguments, arguments) == 0 )	{
			erreur=errno;
			fprintf(ferreur, "  traitement %s , erreur = %d\n"
				, *arguments
				, erreur); 
  			fclose(ferreur);
	}
	free(arguments);
  }
  else{
  	if (fsortie != NULL){if (ferreur == fsortie) ferreur = NULL;  fclose(fsortie);}
  	if (ferreur != NULL)  fclose(ferreur);
	return(PIAF_ERR_NO_MEM);
  }
  if (fsortie != NULL){if (ferreur == fsortie) ferreur = NULL;  fclose(fsortie);}
  if (ferreur != NULL)  fclose(ferreur);
  return(erreur);
}

/*
 ====================================================================================
   Nom 			: PIAF_ecrit_fichier	
   Description 	: Fonction d'ecriture de trace dans un fichier
   Auteur		: Sofiane NEKERE
   Date creation: 26/12/2000
   parametres   :                                                     
     <p_param>	: Chaine de caractere a ecrire dans le fichier
     <p_fic_sor>: Nom du fichier de sortie
     <p_mode>	: Mode d'ouverture du fichier (en extension par defaut)
   retour		:                                                     
					Aucun
   Historique	:
		---------------------------------------------------------------------------
		Fonction			|Date	    |Initiales	|Commentaires 
		---------------------------------------------------------------------------
@(#)	PIAF_ecrit_fichier	|26/12/2000 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl PIAF_ecrit_fichier(char *p_param, char *p_fic_sor, char *p_mode, char *p_type_ecriture, char *p_type_trace)
{
	FILE *fichier = NULL;
	int v_retour =  PIAF_EXEC_OK;
	char v_mode[4] = "at+";

	if (p_param == NULL ) return(PIAF_ERR_NO_CMD);

	if (p_fic_sor == NULL ) {
		return(PIAF_ERR_NO_CMD);
	}

	if (!strlen(p_fic_sor) )  {
		return(PIAF_ERR_NO_CMD);
	}

	if (p_mode != NULL) 
		if (strlen(p_mode) ) strcpy(v_mode, p_mode);

	if (!strlen(p_param) ) return(PIAF_ERR_NO_CMD);

	if ( (fichier=fopen(p_fic_sor, v_mode)) != NULL){
		switch(*p_type_ecriture){
			case PIAF_SYS_ECRITURE_FORMATEE:
				COMMUN_ecrit_fichier(fichier, *p_type_trace, "%s\n", p_param);
			break;

			default:
					if ( fprintf(fichier, "%s\n", p_param) == 0){
						v_retour =  PIAF_ERR_EXEC;
					}
			break;
		}
		fclose(fichier);
	}
	else
		v_retour = PIAF_ERR_OUV_FIC;

   return(v_retour);
}

/*
 ====================================================================================
   Nom 			: ASTER_env_param
   Description 	: Parametres lies a l'environnement d'execution (separateurs de chemin)
   Auteur		: Sofiane NEKERE
   Date creation: 08/08/2001
   parametres   :                                                     
    <p_separateur>	: Separateur nom complet de fichiers et de repertoires (/ UNIX ou \ WINDOWS)
	<p_separateur_var_path>	: Separateur pour variables d'environnement (PATH, LIBPATH...)

   retour	:                                                     
				Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) ASTER_env_param	|08/08/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl ASTER_env_param(char *p_separateur_chemin, char *p_separateur_var_path) 
{
	int v_retour =  PIAF_EXEC_OK;

	COMMUN_check_env(NULL, p_separateur_chemin, NULL, p_separateur_var_path);
	return(v_retour);
}

/*
 ====================================================================================
   Nom 			: ASTER_efface_fichier
   Description 	: Supprime le fichier dont le nom est passe en parametre 
   Auteur		: Sofiane NEKERE
   Date creation: 01/10/2001
   parametres   :                                                     
    <p_nom_fichier>	: Nom du fichier à supprimer

   retour	:
			   0 - Suppression du fichier effectuée (PIAF_EXEC_OK)
			   autre : Probleme (code errno)
			   -2 : Problème non diagnostiqué par le programme (PIAF_ERR_EXEC)
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) ASTER_efface_fichier|08/08/2001 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl ASTER_efface_fichier(char *p_nom_fichier)
{
	int v_retour;

	if ( (v_retour=remove(p_nom_fichier)) != 0 ){
		return(errno==0?errno:PIAF_ERR_EXEC);
	}
	return(PIAF_EXEC_OK);
}

/*
 ====================================================================================
   Nom 			: ASTER_get_crypt_masque
   Description 	: Cle de cryptage des mots de passe ASTER
   Auteur		: Sofiane NEKERE
   Date creation: 08/08/2001
   parametres   :                                                     
    <p_retour>	: Variable receptacle modifiee en sortie

   retour	:                                                     
				p_retour contient en retour la clé de cryptage
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) ASTER_get_crypt_key|26/09/2002 | SNE	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl ASTER_get_crypt_masque(char *p_retour) 
{
	int v_ret =  PIAF_EXEC_OK;

	strcpy(p_retour, ASTER_CRYPT_MASK);
	return(v_ret);
}

/*
 ====================================================================================
   Nom 			: ASTER_get_date_fichier
   Description 	: Recupere la date (creation/acces/modification) d'un fichier
   Auteur		: SGN
   Date creation: 21/02/2003
   parametres   :
    entree :
      <p_fichier>	    : Le fichier a traiter
	  <p_type_date>	: Le type de date que l'on veut recuperer
	sortie :
	  <p_date>	: date du fichier au format YYYYMMDD
	  <p_heure>	: heure du fichier au format HH24miss
   retour	:                                                     
	
	0			: traitement OK
	!= 0		: traitement KO
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) ASTER_get_date_fichier|21/02/2003 | SGN	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl ASTER_get_date_fichier(char *p_fichier, char *p_type_date, char *p_date, char *p_heure) 
{
    int v_ret = 0;
	int v_yyyy, v_mm, v_dd;
	int v_hh24, v_mi, v_ss;
	int v_type_date = 0;

#ifdef WIN32
	WIN32_FIND_DATA v_find_data;

    HANDLE v_hfile;
	FILETIME v_ftime, v_local_ftime;
	WORD v_fat_date, v_fat_time;

	v_hfile = FindFirstFile(p_fichier, &v_find_data);
    if (v_hfile != INVALID_HANDLE_VALUE)
    {
			
	    v_type_date = atoi(p_type_date); 
		switch(v_type_date)	{
			case ASTER_DATE_CREATION:
				v_ftime = v_find_data.ftCreationTime;
				break;
			case ASTER_DATE_ACCES:
				v_ftime = v_find_data.ftLastAccessTime;
				break;
			case ASTER_DATE_MODIFICATION:
				v_ftime = v_find_data.ftLastWriteTime;
				break;
			default:
				v_ftime = v_find_data.ftCreationTime;
				break;
		}

		v_ret = FileTimeToLocalFileTime (&v_ftime, &v_local_ftime);
		if (v_ret == 0)
			return -1;

		v_ret = FileTimeToDosDateTime (&v_local_ftime, &v_fat_date, &v_fat_time);
		if (v_ret == 0)
			return -2;
   
		FindClose(v_hfile);
    
		/* Formatage de l'heure */
		/* bits de 11 a 15 : Heure */
		v_hh24 = ((63488 & v_fat_time)>>11);
		/* bits 5 a 10 : les minutes */
		v_mi = (2016 & v_fat_time)>>5;
		/* bits 0 a 4 : les secondes */
		v_ss = (31 & v_fat_time)*2;
	
		/* Constitution de l'heure en chaine de caractere */
		sprintf(p_heure, "%02d%02d%02d", v_hh24, v_mi, v_ss);

		
		/* Formatage de la date */
	    /* bits 9 a 15 : l'annee */
	    v_yyyy = ((65024 & v_fat_date)>>9) + 1980;
	    /* bits 5 a 8 : le mois */
		v_mm = (480 & v_fat_date)>>5;
	    /* bits 0 a 4 : le jour */
		v_dd = (31 & v_fat_date);
	
		/* Constitution de la date en chaine de caractere */
		sprintf(p_date, "%04d%02d%02d", v_yyyy, v_mm, v_dd);

		v_ret = 0;
	}else{
		v_ret = -3;
	}	
#endif
	
	return v_ret;
}

/*
 ====================================================================================
   Nom 			: ASTER_is_fichier_perime
   Description 	: Determine si un fichier est perimé ou non en fonction d une date de
                : traitement et d'une duree de conservation en jour.
   Auteur		: SGN
   Date creation: 21/02/2003
   parametres   :
    <p_fichier> : Le fichier a traiter
	<p_date_trt>	: La date de traitement au format YYYYMMDD
	<p_duree_conservation> : La duree de conservation max en jour

   retour	:                                                     
	0			: fichier valable
    1			: fichier perimé
	< 0		: traitement KO
   Historique	:
	---------------------------------------------------------------------------
	Fonction			|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) ASTER_is_fichier_perime|21/02/2003 | SGN	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl ASTER_is_fichier_perime(char *p_fichier, char *p_date_trt , char *p_duree_conservation) 
{
	int v_ret = 0, v_diff = 0, v_duree = 0;
    char v_date_fichier[9] = "\0";
	char v_heure_fichier[9] = "\0";
	char v_type_date[2];

    /* Recuperation du code associer au type date modification */
	/* Modif sgn 30/06/2003 : 3.1-1.5 : itoa(ASTER_DATE_MODIFICATION, v_type_date, 10); */
	v_ret = sprintf(v_type_date, "%d\n", ASTER_DATE_MODIFICATION);
      /* fin modif sgn */

	/* Recuperation de la date de modification du fichier */
    v_ret = ASTER_get_date_fichier(p_fichier, v_type_date, v_date_fichier, v_heure_fichier); 	
    if (v_ret != 0)
      return (v_ret);

	/* Si le fichier est perimé on retourne 1 sinon 0 */
	v_diff = atoi(p_date_trt) - atoi(v_date_fichier);
	v_duree = atoi(p_duree_conservation);

	if ( v_diff > v_duree )
		return 1;
	else
		return 0;
	
	return v_ret;
}

/*
 ====================================================================================
   Nom 			: ASTER_Purge_Liste_Fichiers
   Description 	: Constitue Une liste de fichiers d'un repertoire donne et, pour chacun
				: de ces fichiers lance un traitement passe en parametre. La liste des 
				: fichiers traites peut etre filtree suivant une extension
   Auteur	: SGN
   Date creation: 24/02/2003
   parametres    :                                                     
     <p_nom_rep>	: Nom du repertoire
     <p_ext_fich>	: Filtre sur es extensions '*' pour tous les fichiers du repertoire
     <p_fct_trt>	: Nom du repertoire

  retour	: Renvoie le code retour des traitements appeles. Le traitement de la liste 
			 des fichiers est interrompu a la premier erreur.
   Historique	:
	---------------------------------------------------------------------------
	Fonction						|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) ASTER_Purge_Liste_Fichiers	|24/02/2003 | SGN	| Creation (@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl ASTER_Purge_Liste_Fichiers(char *p_nom_rep, char *p_ext_fich, char *p_dat_trt, char *p_duree_conservation) 
{
	int v_ret = TRT_OK;
#ifdef WIN32
  WIN32_FIND_DATA v_fd;
  HANDLE v_hd_p;
  char v_mask_de_recherche[120];
  char v_file_name[512];

  strcpy(v_file_name,"\0");        
  strcpy(v_mask_de_recherche,"\0");        

  if ( COMMUN_existe_repertoire(p_nom_rep) == COMMUN_CODE_REP_EXISTANT){
	  /* Si le 1er caractere de l'extension est '*' on ne rajoute pas d etoile au mask */
	  if (*p_ext_fich == '*')
	    sprintf(v_mask_de_recherche, "%s\\*.*\0", p_nom_rep);
	  else
		sprintf(v_mask_de_recherche, "%s\\*%s\0", p_nom_rep, p_ext_fich);

	  v_hd_p = FindFirstFile(v_mask_de_recherche, &v_fd);
	  if (v_hd_p != INVALID_HANDLE_VALUE){

		  /* Recuperation du nom du fichier */
		  strcpy(v_file_name,"\0");        
		  sprintf(v_file_name, "%s\\%s\0", p_nom_rep, v_fd.cFileName );

		  if (v_fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		  {
	  	    /* On regarde si le fichier est perime */
		    v_ret = ASTER_is_fichier_perime(v_file_name, p_dat_trt, p_duree_conservation);
            if (v_ret < 0)
              return (v_ret);

		    /* Si le fichier est perime l efface */
		    if (v_ret == 1) 
			  v_ret = ASTER_efface_fichier(v_file_name);
		  }

		  while (FindNextFile(v_hd_p, &v_fd))
		  {
			if (v_fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strcpy(v_file_name,"\0");        
				/* Recuperation du nom du fichier */
				sprintf(v_file_name, "%s\\%s\0", p_nom_rep, v_fd.cFileName );
				v_ret = PIAF_ecrit_fichier(v_file_name, "d:\\tmp2\\dbg1.txt", "at+", "L", "I");

		  	    /* On regarde si le fichier est perime */
				v_ret = ASTER_is_fichier_perime(v_file_name, p_dat_trt, p_duree_conservation);
				if (v_ret < 0)
					return (v_ret);

				/* Si le fichier est perime on l efface */
				if (v_ret == 1) 
					v_ret = ASTER_efface_fichier(v_file_name);
			}
		  }	
		  FindClose(v_hd_p);
	  }
  }
  
#else
   DIR *v_pDirectoryPointer;
   struct dirent *v_dp;
   char *v_pos;
/*
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

*/
#endif
 return(v_ret);
}

#ifdef _cplusplus
}
#endif
