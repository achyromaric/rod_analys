__declspec (dllexport) int __cdecl PIAF_appel_systeme(char *param, char *fic_sor, char *fic_err);
__declspec (dllexport) int __cdecl PIAF_ecrit_fichier(char *p_param, char *p_fic_sor, char *p_mode, char *p_type_ecriture, char *p_type_trace);
__declspec (dllexport) int __cdecl ASTER_env_param(char *p_separateur_chemin, char *p_separateur_var_path);
__declspec (dllexport) int __cdecl ASTER_efface_fichier(char *p_nom_fichier);
__declspec (dllexport) int __cdecl ASTER_get_crypt_key(char *p_retour);
__declspec (dllexport) int __cdecl ASTER_get_crypt_masque(char *p_retour);
__declspec (dllexport) int __cdecl ASTER_get_date_fichier(char *p_fichier, char *p_type_date, char *p_date, char *p_heure);
__declspec (dllexport) int __cdecl ASTER_is_fichier_perime(char *p_fichier, char *p_date_trt , char *p_duree_conservation);
__declspec (dllexport) int __cdecl ASTER_Purge_Liste_Fichiers(char *p_nom_rep, char *p_ext_fich, char *p_dat_trt, char *p_duree_conservation);
