/*
---------------------------------------------------------------------------
 Fichier        : extproc_mes.c
 Date creation  : 18/01/2001

 Logiciel       : ASTER                                           
 sous-systeme   : Librairie de fonctions externes du MES
 Description    : Librairie de fonctions appelables par les procedure PL/SQL
                   
---------------------------------------------------------------------------
 Auteur         : FAU
 Version        : @(#) extproc_mes version 1.0-1.0 : FAU : --/--/1999
 Date version   : --/--/1999
 Description	: Version initiale
---------------------------------------------------------------------------
 Auteur         : SNE
 Version        : @(#) extproc_mes version 2.0-1.0 : SNE : 13/02/2001
 Date version   : 13/02/2001
 Description	: Reecriture pour Portage NT 
---------------------------------------------------------------------------
 Auteur         : PLL
 Version        : @(#) extproc_mes version 4.0-1.1 : PLL : 17/02/2005
 Date version   : 17/02/2005
 Description	: Evolutions pour ORACLE 9i (__declspec (dllexport) X __cdecl)
---------------------------------------------------------------------------

	--------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 		
	--------------------------------------------------------------------
@(#)	extproc_mes	|--/--/1999 | FAU	| Creation 
@(#)	extproc_mes	|13/02/2001 | SNE	| Reecriture pour Portage NT 
@(#)	extproc_mes	|13/02/2001 | PLL	| Evolutions pour ORACLE 9i (__declspec (dllexport) X __cdecl)
---------------------------------------------------------------------------
*/ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commun.h"

#define EXTP_NOM_PROGRAMME		"extproc_mes"
#define EXTP_VERSION_FICHIER	"1.1"

char extp_version_fichier[]="@(#) " EXTP_NOM_PROGRAMME " version "COMMUN_VERSION_ASTER"-"EXTP_VERSION_FICHIER" - "__DATE__ " "__TIME__;


__declspec (dllexport) int __cdecl cp_depeche( char *rep_batch,
               char *rep_archive,
               char *rep_depart,
               char *site_routage,
               char *filename);

__declspec (dllexport) int __cdecl purge_depeche(char *rep_batch,
                  char *rep_archive, 
                  char *filename);

__declspec (dllexport) int __cdecl cre_user(const char *cmd);

#ifdef _cplusplus
extern "C"{
#endif

/*
 ====================================================================================
   Nom 			: cp_depeche
   Description 	: Copie d'une depeche en vue de sa re-emission
   Auteur		: Florent AUBARET
   Date creation: --/--/1999
   parametres   :                                                     
     <p_indicateurs>	: 
   retour		:                                                     
					Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) cp_depeche		|--/--/1999 | FAU	| Creation (@fonction)
@(#) cp_depeche		|13/02/2001 | SNE	| Reecriture(@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl cp_depeche( char *rep_batch, char *rep_archive, char *rep_depart, char *site_routage, char *filename)
{
  char v_tmp1[1000];
  char v_tmp2[1000];
  char v_separateur[2]
	  , v_separateur_var_path[2];

  
    COMMUN_check_env(NULL, v_separateur, NULL, v_separateur_var_path);
	if (COMMUN_existe_repertoire(rep_archive) != COMMUN_CODE_REP_EXISTANT)
	  return(-1);


	if (COMMUN_existe_repertoire(rep_depart) != COMMUN_CODE_REP_EXISTANT)
	  return(-1);

    sprintf(v_tmp1, "%s%s%s\0", rep_archive, v_separateur, filename);
	if (COMMUN_existe_fichier(v_tmp1) != COMMUN_CODE_REP_EXISTANT)
	  return(-2);

    sprintf(v_tmp2, "%s%s%s\0", rep_depart, v_separateur, site_routage);
	if (COMMUN_existe_repertoire(v_tmp2) == COMMUN_CODE_REP_EXISTANT)
		COMMUN_creer_repertoire(v_tmp2);

	return(COMMUN_copy_fichier(v_tmp1, v_tmp2, COMMUN_CP_ECRASE_FICHIER));
}

/*
 ====================================================================================
   Nom 			: purge_depeche
   Description 	: Suppression d'une depeche 
   Auteur		: Florent AUBARET
   Date creation: --/--/1999
   parametres   :                                                     
     <p_indicateurs>	: 
   retour		:                                                     
					Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) purge_depeche	|--/--/1999 | FAU	| Creation (@fonction)
@(#) purge_depeche	|13/02/2001 | SNE	| Reecriture(@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl purge_depeche( char *rep_batch, char *rep_archive, char *filename)
{

  char v_tmp1[1000];
  char v_separateur[2]
	  , v_separateur_var_path[2];

  
    COMMUN_check_env(NULL, v_separateur, NULL, v_separateur_var_path);
	if (COMMUN_existe_repertoire(rep_archive) != COMMUN_CODE_REP_EXISTANT){
		sprintf(v_tmp1, "%s%s%s\0", rep_archive, v_separateur, filename);
		if (COMMUN_existe_fichier(v_tmp1) == COMMUN_CODE_FICHIER_EXISTANT)
			if (remove(v_tmp1) == 0) 
				return 0;
	}
	return -1;
}

/*
 ====================================================================================
   Nom 			: cre_user
   Description 	: Lancement de la commande de creation d'un utilisateur
				: fonction appelee a disparaitre (double emploi avec piaf_appel_systeme)
   Auteur		: Florent AUBARET
   Date creation: --/--/1999
   parametres   :                                                     
     <p_indicateurs>	: 
   retour		:                                                     
					Aucun
   Historique	:
	---------------------------------------------------------------------------
	Fonction		|Date	    |Initiales	|Commentaires 
	---------------------------------------------------------------------------
@(#) cre_user		|--/--/1999 | FAU	| Creation (@fonction)
@(#) cre_user		|13/02/2001 | SNE	| Reecriture(@fonction)
 ====================================================================================
*/
__declspec (dllexport) int __cdecl cre_user(const char *cmd) {
  int retour;
  int decision = 0;

  retour = system(cmd);

  /* interprétation du résultat */
  if ( retour == 0 ) {
    decision = 0;
    }
  else if ( retour == 256 ) {
    decision = 1;
    }
  else if (retour == 512 ) {
    decision = 2;
    }
  else if (retour == 768 ) {
    decision = 3;
    }
  else if (retour == 1024 ) {
    decision = 4;
    }
  else if (retour == 1280 ) {
    decision = 5;
    }
  else if (retour == 1536 ) {
    decision = 6;
    }
  else {
    decision = -1;
    }

  return decision;
}

#ifdef _cplusplus
}
#endif


