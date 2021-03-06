#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FAUX = 0, VRAI = 1 } Booleen;
Booleen EchoActif = FAUX;

// Messages emis par les instructions -----------------------------------------
#define MSG_DEVELOPPE "## nouvelle specialite \"%s\" ; cout horaire \"%d\"\n" 
#define MSG_INTERRUPTION "## fin de programme\n" 
#define MSG_EMBAUCHE "## nouveau travailleur \"%s\" competent pour la specialite \"%s\"\n" 
#define MSG_SPECIALITE "## consultation des specialites\n"
#define MSG_CONSULTATION_TRAVAILLEURS "## la specialite \%s\ peut etre prise en charge par : "
#define MSG_DEMARCHE "## nouveau client \"%s\"\n"
#define MSG_CONSULTATION_COMMANDE "## consultation des commandes effectuees par \"%s\"\n"
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n"
#define MSG_SUPERVISION "## consultation de l'avancement des commandes\n"
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n"
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n"
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n"
#define MSG_SPECIALITE_TOUS "## consultation des travailleurs competents pour chaque specialite\n"
#define MSG_CLIENT_TOUS "## consultation des commandes effectuees par chaque client\n"
#define MSG_PROGGRESSION_PASSE "## une reallocation est requise\n"
// Lexemes -------------------------------------------------------------------- 
#define LGMOT 35
#define NBCHIFFREMAX 5 
typedef char Mot[LGMOT + 1];
void get_id(Mot id) {
	scanf("%s", id);
	if (EchoActif) printf(">>echo %s\n", id);
}
int get_int() {
	char buffer[NBCHIFFREMAX + 1];
	scanf("%s", buffer);
	if (EchoActif) printf(">>echo %s\n", buffer);
	return atoi(buffer);
}
// Donnees
// specialites −−−−−−−−−−−−−−−−−−−−−
#define MAX_SPECIALITES 10
typedef struct {
	Mot nom;
	int cout_horaire;
} Specialite;
typedef struct {
	Specialite tab_specialites[MAX_SPECIALITES];
	unsigned int nb_specialites;
} Specialites;
// travailleurs −−−−−−−−−−−−−−−−−−−−
#define MAX_TRAVAILLEURS 50
typedef struct {
	Mot nom;
	Booleen tags_competences[MAX_SPECIALITES];
} Travailleur;
typedef struct {
	Travailleur tab_travailleurs[MAX_TRAVAILLEURS];
	unsigned int nb_travailleurs;
} Travailleurs;
// client −−−−−−−−−−−−−−−−−−−−−−−−−−
#define MAX_CLIENTS 10
typedef struct {
	Mot tab_clients[MAX_CLIENTS];
	unsigned int nb_clients;
} Clients;
// Instructions --------------------------------------------------------------- 
// developpe --------------------------- 
void traite_developpe(Specialites* Spe) {
	get_id(Spe->tab_specialites[Spe->nb_specialites].nom);
	Spe->tab_specialites[Spe->nb_specialites].cout_horaire = get_int();
	Spe->nb_specialites += 1;

}
void traite_specialites(Specialites* list_spe) {
	unsigned int i;
	printf("specialites traitees : ");
	for (i = 0; i < list_spe->nb_specialites - 1; i++) {
		printf("%s/%d, ", list_spe->tab_specialites[i].nom, list_spe->tab_specialites[i].cout_horaire);
	}
	printf("%s/%d\n", list_spe->tab_specialites[list_spe->nb_specialites - 1].nom, list_spe->tab_specialites[list_spe->nb_specialites - 1].cout_horaire);
}

void traite_embauche(Travailleurs* Worker) {
	get_id(Worker->tab_travailleurs[Worker->nb_travailleurs].nom);
	get_id(Worker->tab_travailleurs[Worker->nb_travailleurs].tags_competences);
	Worker->nb_travailleurs += 1;
}
Clients traite_demarche() {
	Clients Customer;
	get_id(Customer.tab_clients);
	return Customer;
}

void traite_consultation_travailleurs(Travailleurs* list_worker) {
	unsigned int i;
	Mot nom_specialite;
	get_id(nom_specialite);
	if (strcmp(nom_specialite, "tous") == 0)
	{
		for (i = 0; i < list_worker->nb_travailleurs; i++) {
			printf(MSG_CONSULTATION_TRAVAILLEURS "%s\n", list_worker->tab_travailleurs[i].tags_competences, list_worker->tab_travailleurs[i].nom);
		}
	}
	else {
		printf(MSG_CONSULTATION_TRAVAILLEURS, nom_specialite);
		for (i = 0; i < list_worker->nb_travailleurs; i++) {
			if (strcmp(nom_specialite, list_worker->tab_travailleurs[i].tags_competences) == 0) {
				printf("%s\n", list_worker->tab_travailleurs[i].nom);
			}
		}

	}
}
void traite_consultation_commandes() {
	Mot nom_client;
	get_id(nom_client);
	if (strcmp(nom_client, "tous") == 0)
	{
		printf(MSG_CLIENT_TOUS, nom_client);
	}
	else {
		printf(MSG_CONSULTATION_COMMANDE, nom_client);
	}
}
void traite_nouvelle_commande() {
	Mot nom_commande;
	Mot nom_client;
	get_id(nom_commande);
	get_id(nom_client);
	printf(MSG_COMMANDE, nom_commande, nom_client);
}
void traite_supervision() {
	printf(MSG_SUPERVISION);
}
void traite_tache() {
	Mot nom_commande;
	Mot nom_specialite;
	get_id(nom_commande);
	get_id(nom_specialite);
	int nombres_d_heures = get_int();
	printf(MSG_TACHE, nom_commande, nom_specialite, nombres_d_heures);
}
void traite_charge() {
	Mot nom_travailleur;
	get_id(nom_travailleur);
	printf(MSG_CHARGE, nom_travailleur);

}
void traite_progression() {
	Mot nom_commande;
	get_id(nom_commande);
	Mot nom_specialte;
	get_id(nom_specialte);
	int heures;
	heures = get_int();
	printf(MSG_PROGRESSION, nom_commande, nom_specialte, heures);
}
// interruption ------------------------ 
void traite_interruption() {
	printf(MSG_INTERRUPTION);
}
// Fonction prennant en paramètre la nouvelle spécialité et le cout horaire

//Boucle principale ---------------------------------------------------------- 
int main(int argc, char* argv[]) {
	if (argc >= 2 && strcmp("echo", argv[1]) == 0) {
		EchoActif = VRAI;
	}
	Mot buffer;
	Specialites Spe;
	Spe.nb_specialites = 0;
	Travailleurs Worker;
	Worker.nb_travailleurs = 0;
	while (VRAI) {
		get_id(buffer);
		if (strcmp(buffer, "passe") == 0)
		{
			printf(MSG_PROGGRESSION_PASSE);
			continue;
		}
		if (strcmp(buffer, "developpe") == 0) {
			traite_developpe(&Spe);
			continue;
		}
		if (strcmp(buffer, "specialites") == 0) {
			traite_specialites(&Spe);
			continue;
		}
		if (strcmp(buffer, "embauche") == 0) {
			traite_embauche(&Worker);
			continue;
		}
		if (strcmp(buffer, "demarche") == 0) {
			traite_demarche();
			continue;
		}
		if (strcmp(buffer, "travailleurs") == 0) {
			traite_consultation_travailleurs(&Worker);
			continue;
		}
		if (strcmp(buffer, "client") == 0) {
			traite_consultation_commandes();
			continue;
		}
		if (strcmp(buffer, "commande") == 0) {
			traite_nouvelle_commande();
			continue;
		}
		if (strcmp(buffer, "supervision") == 0) {
			traite_supervision();
			continue;
		}
		if (strcmp(buffer, "charge") == 0) {
			traite_charge();
			continue;
		}
		if (strcmp(buffer, "progression") == 0) {
			traite_progression();
			continue;
		}
		if (strcmp(buffer, "tache") == 0) {
			traite_tache();
			continue;
		}
		if (strcmp(buffer, "interruption") == 0) {
			traite_interruption();
			break;
		}
		printf("!!! instruction inconnue >%s< !!!\n", buffer);
	}
	return 0;
}
