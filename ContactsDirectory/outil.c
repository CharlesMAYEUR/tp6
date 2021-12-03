#include <stdio.h>   /* pour les entr�es-sorties */
#include <string.h>  /* pour les manipulations de cha�nes de caract�res */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 21.0

/**************************************************************************/
/* Compl�ter votre nom ici                                                */
/*   Nom :       CROPPI            Pr�nom :         JULIEN                */
/**************************************************************************/

extern bool modif;



/// <summary>
/// Ajout d'un contact dans le r�pertoire stock� en m�moire
/// </summary>
/// <param name="dir">: Ref : le repertoire</param>
/// <param name="rec">: Value : le contact</param>
/// <returns>ERROR si �chec ou OK si ajout r�alis�</returns>
int ajouter_un_contact_dans_rep(Directory *dir, Record rec)
{
#ifdef IMPL_TAB
	// ajouter code ici pour tableau

	// Debut ajout code

	if (dir->elts_count < MAX_RECORDS) {
		dir->tab[dir->elts_count] = rec;
		dir->elts_count++;
	}
	else {
		return(ERROR);
	}
	modif = true;


	// fin ajout de code

	
#else
#ifdef IMPL_LIST
	
	bool inserted = false;
	if (dir->elts_count == 0) {
		if (InsertElementAt(dir->list, dir->list->size, rec) != 0) {
			dir->elts_count += 1;
			modif = true;
			dir->sorted = true;
			return(OK);
		}
	}
	else {
		SingleLinkedListElem *current = GetElementAt(dir->list, 0);

		int pos = 0;

		// on cherche un point d'insertion

		while (!inserted && current != NULL) {

			// ajouter code ici pour Liste
			// Debut ajout code
			if (stcmp(rec.nom, GetElementAt(dir->list, pos, rec)) < 0) {
				InsertElementAt(dir->list, pos, rec);
				dir->elts_count += 1;
				modif = true;
				return(OK);
			}
			pos += 1;
			// fin ajout de code

		}
		// c'est le plus grand, on le place � la fin
		if (!inserted) {

			InsertElementAt(dir->list, dir->list->size, rec);
			inserted = true;
			dir->elts_count++;
			dir->sorted = true;
		}
	}


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du r�pertoire l'enregistrement dont l'indice est donn� en */
  /*   param�tre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Directory *dir, int index) {

	
	if (dir->elts_count >= 1)		/* s'il y a au moins un element ds le tableau */
	{
	// ajouter code ici pour tableau						
	// Debut ajout code
		
		for (int i = index; i < dir->elts_count - 1; i++) {
			dir->tab[i] = dir->tab[i + 1];
		}

		dir->elts_count -= 1;		/* ds ts les cas, il y a un element en moins */



	// fin ajout de code
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  
  // ajouter code ici pour Liste

	/// <summary>
    /// supprime du r�pertoire l'enregistrement contenu dans le maillon elem
    /// et fixe modif � vrai
	/// 
	/// </summary>
	/// <param name="dir">: Ref vers un r�pertoire</param>
	/// <param name="elem">: Ref vers un maillon de liste chain�e</param>
	/// <returns>0 si pas de suppression effectu�e ou 1 si une suppression r�alis�e</returns>
int supprimer_un_contact_dans_rep_liste(Directory* dir, SingleLinkedListElem* elem) {

	// Ajouter code ici pour impl�mentation liste
	// D�but ajout Code ici

	int tar = DeleteLinkedListElem(dir->list, elem);
	if (tar == 1) {
		dir->elts_count--;
		modif = true;
	}

	// Fin ajout de code

	return (0);
}
#endif
#endif


/*********************************************************************/
/// <summary>
/// Affichage d'un enregistrement sur une ligne � l'�cran
/// </summary>
/// <param name="rec"> : Contact � afficher</param>
void affichage_enreg(Record enr)
{
	// ex Dupont, Jean                 0320304050
	// l'espacement est obtenu avec des caract�res de tabulation
	// D�but ajout Code ici

	printf("%s, %s     %s", enr.nom, enr.prenom, enr.tel);


	// Fin ajout de code
} /* fin affichage_enreg */
 /*********************************************************************/
/// <summary>
/// Affichage d'un enregistrement avec alignement des mots
/// lors d'un affichage sous la forme d'une liste
/// </summary>
/// <param name="rec"> : Contact � afficher</param>
void affichage_enreg_frmt(Record enr)
{
	// Le nom est align� sur 30 caract�res
	// le pr�nom est align� sur 25 caract�res
	// le no de t�l�phone est align� sur 15 caract�res
	// ex | Dupont                |Jean                  |0320304050      
	// 
	// D�but ajout Code ici

	printf("%20s| %20s| %20s|\n", enr.nom, enr.prenom, enr.tel);


	// Fin ajout de code
} /* fin affichage_enreg_frmt */


 /*********************************************************************/
/// <summary>
/// Teste si dans l'ordre alphabetique, un enregistrement est apres un autre
/// </summary>
/// <param name="enr1">: Contact 1</param>
/// <param name="enr2">: Contact 2</param>
/// <returns>true si enr1 est apr�s enr2</returns>
bool est_sup(Record enr1, Record enr2)
{

	// Utiliser la fonction _strcmpi (string.h) pour comparer des chaines de caract�res
	// 
	// D�but ajout Code ici

	if (_strcmpi(enr1.nom, enr2.nom) == 0 && _strcmpi(enr1.prenom, enr2.prenom) > 0) {  //Si noms �gaux et prenom mal rang�s
	  //Si prenoms mal rang�s
		return(true);
	}
	else if (_strcmpi(enr1.nom, enr2.nom) > 0) { //Si noms mal rang�s
		return(true);
	}
	else {   //Sinon
		return(false);
	}

	// Fin ajout code
	return(false);
	


}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Directory *dir)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	// Debut ajout code

	if (dir->elts_count >= 2) {
		bool fin = false;
		Record tmp;
		while (fin == false) {
			fin = true;
			for (int i = 0; i < dir->elts_count - 1; i++) {
				if (est_sup(dir->tab[i], dir->tab[i + 1])) {
					tmp = dir->tab[i];
					dir->tab[i] = dir->tab[i + 1];
					dir->tab[i + 1] = tmp;
					fin = false;
				}
			}
		}
	}
	else {
		return;
	}



	// fin ajout de code
	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien � faire !
	// la liste est toujours tri�e
#endif
#endif


	dir->sorted = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le r�pertoire d'un enregistrement correspondant au  */
  /*   nom � partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au crit�re ou*/
  /*   un entier n�gatif si la recherche est n�gative				    */
  /**********************************************************************/

int rechercher_nom(Directory *dir, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de d�but de recherche dans tableau/liste dir */
	

	char tmp_nom[MAX_LASTNAME];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_LASTNAME];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


#ifdef IMPL_TAB
							// ajouter code ici pour tableau
	int ind_fin;			/* position (indice) de fin de tableau/liste dir */
	ind_fin = dir->elts_count - 1;
	strcpy_s(tmp_nom,_countof(tmp_nom), nom);
	_strupr_s(tmp_nom, _countof(tmp_nom));

	while ((i <= ind_fin) && (!trouve))
	{
		strcpy_s(tmp_nom2, _countof(tmp_nom2), dir->tab[i].nom);
		_strupr_s(tmp_nom2, _countof(tmp_nom2));
		if (strcmp(tmp_nom, tmp_nom2) == 0)
			trouve = true;						/* bingo! */
		else
			i++;					/* pas trouve, on continue */
	}
#else
#ifdef IMPL_LIST
		// ajouter code ici pour Liste
		// Debut ajout code
	
	ind_fin = dir->elts_count - 1;
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);
	_strupr_s(tmp_nom, _countof(tmp_nom));

	while ((i <= ind_fin) && (!trouve)) {
		strncpy_s(tmp_nom2, _countof(tmp_nom2), GetElementAt(dir->list, i), _TRUNCATE);
		_strupr_s(tmp_nom2, _countof(tmp_nom2));
		if (strcmp(tmp_nom, tmp_nom2) == 0) {
			trouve = true;
			return(i);
		}
		else {
			i++;
		}
	}
	return (-1);



		// fin ajout de code
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non num�riques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
// Debut ajout code

	for (int i = 0; i < strlen(s) - 1; i++) {
		if ((int)s[i] > 57 || (int)s[i] < 48) {
			for (int j = i; j < strlen(s) - 1; j++) {
				s[j] = s[j + 1];
			}
			s[strlen(s) - 1] = '\0';
		}
	}


// fin ajout de code

	return;
}

/**********************************************************************/
/* sauvegarde le r�pertoire dans le fichier dont le nom est pass� en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionn� ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Directory *dir, char file_name[])
{
	FILE *fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	// Debut ajout code

	fopen_s(&fic_rep, file_name, "w");
	for (int i = 0; i < dir->elts_count; i++) {
		fputs(dir->tab[i].nom, fic_rep);
		fputs(";", fic_rep);
		fputs(dir->tab[i].prenom, fic_rep);
		fputs(";", fic_rep);
		fputs(dir->tab[i].tel, fic_rep);
		fputs("\n", fic_rep);
}
	fclose(fic_rep);

	modif = false;


	// fin ajout de code
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste

	// Debut ajout code

	fopen_s(&fic_rep, nom_fichier, "w");
	for (int i = 0; i < dir->list->size; i++) {
		fputs(GetElementAt(dir->list, i)->pers.nom, fic_rep);
		fputs(";", fic_rep);
		fputs(GetElementAt(dir->list, i)->pers.prenom, fic_rep);
		fputs(";", fic_rep);
		fputs(GetElementAt(dir->list, i)->pers.tel, fic_rep);
		fputs("\n", fic_rep);
}
	fclose(fic_rep);

	modif = false;

	// fin ajout de code
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le r�pertoire le contenu du fichier dont le nom est  */
  /*   pass� en argument                                                */
  /*   retourne OK si le chargement a fonctionn� et ERROR sinon         */
  /**********************************************************************/

int charger(Directory *dir, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Record);
	char buffer[sizeof(Record) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if (((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL))
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (dir->elts_count < MAX_RECORDS))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, dir->tab[num_rec].nom, MAX_LASTNAME, SEPARATOR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, dir->tab[num_rec].prenom, MAX_LASTNAME, SEPARATOR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, dir->tab[num_rec].tel, MAX_TEL, SEPARATOR) == OK)
							num_rec++;		/* element � priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
				// ajouter code implemention liste
				// **** d�but ajout ****

				if (lire_champ_suivant(buffer, &idx, enr.nom, MAX_LASTNAME, SEPARATOR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, enr.prenom, MAX_LASTNAME, SEPARATOR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, enr.tel, MAX_TEL, SEPARATOR) == OK)
							num_rec++;		/* element � priori correct, on le comptabilise */
					}
				}
				InsertElementAt(dir->list, dir->list->size, enr);
				compteur++;


				// **** fin ajout ****
#endif
#endif




			}

		}
		dir->elts_count = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */