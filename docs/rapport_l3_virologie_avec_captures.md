# Rapport Academique L3

## Conception, analyse et evaluation d'un programme de type compagnon en environnement de TP

**Etudiant :** \...\...\...\...\...\...\...\...\...\...\...\...\....

**UE :** Securite / Virologie

**Niveau :** Licence 3

**Date :** Mars 2026

*------------------------------------------------------------*

## Resume

Ce rapport presente l'etude academique d'un travail pratique consacre
au concept de programme compagnon en environnement Linux. L'objectif
pedagogique est d'analyser une famille historique de menaces
informatiques, de comprendre les mecanismes de replication observes dans
la litterature, puis d'evaluer la conformite d'une implementation de
TP aux criteres de l'enonce.

Le travail est structure autour de quatre axes : (1) cadrage theorique,
(2) methodologie de mise en place du laboratoire, (3) verification des
exigences du sujet, (4) discussion critique des limites techniques,
ethiques et juridiques. Une attention particuliere est accordee a la
tracabilite documentaire : ce rapport inclut une webographie detaillee
et un journal des sources consultees.

**Mots-cles :** securite informatique, malware, virus compagnon,
Linux, analyse de conformite, cyber hygiene.

*------------------------------------------------------------*

## 1. Introduction

La securite des systemes d'information repose autant sur des mecanismes
techniques que sur la capacite d'analyse des utilisateurs, des
developpeurs et des administrateurs. Dans ce cadre, les travaux
pratiques de virologie ont une valeur pedagogique importante : ils
permettent de comprendre, dans un environnement controle, les principes
de propagation de code malveillant historiquement documentes.

Le present rapport n'a pas pour finalite de promouvoir des usages
offensifs. Il adopte une demarche academique et defensive : comprendre
pour mieux prevenir, detecter et corriger. Cette posture est conforme
aux recommandations des agences institutionnelles de cybersecurite
(ANSSI, NIST) et aux pratiques universitaires en formation securite.

Le sujet traite ici concerne un programme de type compagnon. Ce type de
comportement est interessant car il illustre la relation entre
usurpation de nom, enchainement d'execution et perception utilisateur.

*------------------------------------------------------------*

## 2. Objectifs pedagogiques et perimetre

### 2.1 Objectifs du TP

Le TP vise a :

-   mettre en place un environnement de test local ;

-   implementer les fonctions demandees dans l'enonce ;

-   verifier la conformite fonctionnelle vis-a-vis de criteres
    explicites ;

-   produire un compte rendu critique.

### 2.2 Perimetre de ce rapport

Ce rapport couvre :

-   l'analyse du sujet ;

-   la verification des livrables techniques presents dans le dossier de
    projet ;

-   une lecture critique des points forts et limites ;

-   des recommandations de rendu academique.

Sont exclus :

-   toute diffusion de procedure offensive realiste ;

-   toute assistance a un usage malveillant hors cadre pedagogique.

*------------------------------------------------------------*

## 3. Cadre theorique

### 3.1 Definition generale

Dans la litterature, un virus informatique designe un code capable de se
reproduire en s'attachant ou en se substituant a des programmes cibles.
Les travaux pionniers de Fred Cohen ont pose le cadre conceptuel de
cette famille de menaces et ont ouvert le debat sur les limites
theoriques de detection universelle.

### 3.2 Notion de programme compagnon

Le concept de compagnon est une forme d'usurpation de l'identite
logicielle : le programme cible legitime est conserve sous un autre nom
(souvent suffixe), tandis qu'une copie du programme d'origine
malveillant prend le nom attendu par l'utilisateur. L'interet
pedagogique de ce modele est de montrer :

-   la place de l'ingenierie sociale dans l'execution initiale ;

-   l'importance du nommage de fichiers ;

-   l'impact des droits d'execution sur la surface d'attaque.

### 3.3 Positionnement historique

L'histoire des logiciels malveillants montre une evolution continue :
virus de fichiers, vers de messagerie, botnets, rancongiciels et
attaques ICS. Les cas celebres (ex. ILOVEYOU, Stuxnet) soulignent
l'ampleur potentielle des dommages operationnels, economiques et
reputations.

*------------------------------------------------------------*

## 4. Environnement de travail et protocole de laboratoire

### 4.1 Configuration

Le projet est realise sous Linux avec compilation C via GCC. Le dossier
de travail contient :

-   un fichier source principal `MediaPlayer.c` ;

-   un script de preparation `setup_env.sh` ;

-   des ressources image ;

-   un dossier cible de test `TP_User`.

### 4.2 Protocole de mise en place

Le script de preparation automatise :

-   la creation du dossier de test ;

-   la copie des ressources ;

-   la generation et compilation de programmes cibles (MonPG1 a MonPG5)
    ;

-   la compilation du programme principal.

Ce protocole permet de reproduire rapidement une demonstration dans un
cadre controle.

### 4.3 Conditions de validite

La validite de la demonstration suppose :

-   un repertoire de test isole ;

-   des droits utilisateurs coherents ;

-   l'absence d'execution hors perimetre defini.

*------------------------------------------------------------*

## 5. Methode d'analyse de conformite

L'evaluation a ete conduite selon une grille alignee sur le sujet :
preambule d'environnement, fonctions de service, recherche de cibles,
prevention de sur-infection, enchainement d'etapes, transfert
d'execution.

Les preuves mobilisees proviennent de :

-   la structure des dossiers ;

-   le script d'initialisation ;

-   le code source ;

-   les artefacts de sortie dans le dossier de test.

### 5.1 Emplacement exact des captures dans le corps du rapport

\> Inserer les figures ci-dessous exactement aux endroits indiques.

**\[FIGURE 1 - a inserer apres la section 4.1 Configuration\]**

\*Titre propose :\* \"Arborescence initiale du projet dans
`virologie/`\"

\*Capture attendue :\* sortie `ls -la` du dossier `virologie/`.

**\[FIGURE 2 - a inserer apres la section 4.2 Protocole de mise en
place\]**

\*Titre propose :\* \"Execution du script `setup_env.sh`\"

\*Capture attendue :\* terminal montrant les etapes de preparation.

**\[FIGURE 3 - a inserer apres la section 4.2, juste avant 4.3\]**

\*Titre propose :\* \"Etat du dossier `TP_User` apres preparation\"

\*Capture attendue :\* sortie `ls -la TP_User`.

**\[FIGURE 4 - a inserer au debut de la section 6.1 Points
conformes\]**

\*Titre propose :\* \"Compilation reussie du programme principal\"

\*Capture attendue :\* commande GCC + absence d'erreur.

**\[FIGURE 5 - a inserer dans la section 6.1, apres le point sur les
executables cibles\]**

\*Titre propose :\* \"Presence de `MonPG1` a `MonPG5` en mode
executable\"

\*Capture attendue :\* listing avec permissions.

**\[FIGURE 6 - a inserer dans la section 6.1, apres le point sur le
transfert d'execution\]**

\*Titre propose :\* \"Trace d'execution montrant la sequence
fonctionnelle\"

\*Capture attendue :\* sortie console de demonstration.

**\[FIGURE 7 - a inserer dans la section 6.2 Points partiels\]**

\*Titre propose :\* \"Service utilisateur en mode texte (limite
actuelle)\"

\*Capture attendue :\* affichage console du service.

**\[FIGURE 8 - a inserer dans la section 9 Plan de presentation orale
recommande\]**

\*Titre propose :\* \"Vue synthetique du scenario de demonstration\"

\*Capture attendue :\* terminal pendant la demo (commande + resultat).

*------------------------------------------------------------*

## 6. Resultats de conformite (synthese)

### 6.1 Points conformes

Les elements suivants apparaissent conformes au sujet :

-   environnement Linux/C/GCC ;

-   presence de `MediaPlayer.c` ;

-   preparation automatique de `TP_User` ;

-   generation des executables cibles ;

-   traitement des cibles executables regulieres ;

-   mecanisme de verification de non re-infection ;

-   enchainement fonctionnel attendu ;

-   logique de transfert d'execution dans le cas approprie.

### 6.2 Points partiels

Deux points meritent d'etre explicitement qualifies de partiels dans un
rendu academique :

-   **rendu de service utilisateur** : demonstration textuelle
    plutot qu'affichage graphique natif ;

-   **documentation theorique formelle** : les explications sont
    presentes dans le code, mais une redaction separee est necessaire
    pour un rapport universitaire solide.

### 6.3 Valeur pedagogique

Malgre ces limites, le projet permet de relier efficacement theorie et
pratique : parcours de repertoire, statuts de fichiers, droits
d'execution, logique de chaine d'appel, et verification de conditions.

*------------------------------------------------------------*

## 7. Discussion technique

### 7.1 Robustesse logicielle

Dans un projet de qualite logicielle, toute operation critique devrait
integrer des mecanismes de reprise et de gestion d'echec documentes.
Dans le cadre present, il est pertinent de souligner l'importance de :

-   la verification syste matique des retours d'appels systeme ;

-   la gestion des erreurs de copie/deplacement ;

-   la tracabilite des actions de test.

### 7.2 Lisibilite et maintenabilite

Le projet beneficie deja d'une structure simple, mais une approche L3
attend generalement :

-   une separation claire entre description, methodologie, resultats et
    limites ;

-   une nomenclature de fichiers coherente ;

-   une documentation de demonstration reproductible.

### 7.3 Reproductibilite

La reproductibilite est un critere de qualite academique majeur.
L'ajout de documents de support (`README`, tableau de conformite,
checklist orale) renforce la fiabilite du rendu et facilite
l'evaluation par l'enseignant.

*------------------------------------------------------------*

## 8. Enjeux ethiques, juridiques et operationnels

L'etude des malwares en universite doit etre strictement encadree.
Trois principes sont essentiels :

1.  **Principe de finalite pedagogique** : apprendre les mecanismes
    pour concevoir des defenses, non pour nuire.

2.  **Principe de confinement** : execution limitee a des
    environnements de test isoles.

3.  **Principe de responsabilite** : respect des regles
    institutionnelles, du droit applicable et de la deontologie.

Les guides institutionnels (ANSSI, NIST) rappellent que la prevention
repose d'abord sur l'hygiene numerique : mises a jour, segmentation,
sauvegardes, filtrage, sensibilisation des utilisateurs.

*------------------------------------------------------------*

## 9. Plan de presentation orale recommande

Pour un passage clair devant le professeur :

-   **Etape 1 (30 sec)** : contexte et objectif du TP.

-   **Etape 2 (1 min)** : preparation de l'environnement
    (`setup_env.sh`).

-   **Etape 3 (2-3 min)** : demonstration des criteres fonctionnels
    attendus.

-   **Etape 4 (1 min)** : discussion des limites (service texte,
    points partiels).

-   **Etape 5 (30 sec)** : conclusion academique et ouverture
    defensive.

L'evaluateur percoit ainsi la maitrise technique, la capacite
d'analyse critique et le respect du cadre de securite.

*------------------------------------------------------------*

## 10. Conclusion generale

L'etude menee montre que le projet repond globalement aux exigences
techniques du sujet dans son environnement de TP. Les principaux
criteres fonctionnels sont couverts et la demonstration est
reproductible.

Le niveau academique attendu en L3 est atteint a condition de presenter
explicitement :

-   la methode ;

-   les preuves de conformite ;

-   les limites ;

-   les implications ethiques et defensives.

Ce rapport propose justement cette structuration afin d'ameliorer la
qualite du rendu final et la lisibilite pour l'evaluateur.

*------------------------------------------------------------*

## 11. Journal des sites consultes (tracabilite demandee)

\> **Note methodologique :** liste des sources consultables
utilisees pour le cadrage theorique et institutionnel.

\> **Date de consultation :** 23/03/2026.

4.  Fred Cohen, \*Computer Viruses - Theory and Experiments\*

URL :
http://web.eecs.umich.edu/\~aprakash/eecs588/handouts/cohen-viruses.html

5.  ACM/Computers & Security (reference bibliographique associee a
    Cohen)

URL : https://dl.acm.org/doi/10.1016/0167-4048%2887%2990122-2

6.  Leonard Adleman, \*An Abstract Theory of Computer Viruses\* (CRYPTO
    1988)

URL : https://www.iacr.org/cryptodb/data/paper.php?pubkey=945

7.  Springer (entree de chapitre) - \*An Abstract Theory of Computer
    Viruses\*

URL : https://link.springer.com/chapter/10.1007/0-387-34799-2_28

8.  NIST, \*Guide to Malware Incident Prevention and Handling for
    Desktops and Laptops (SP 800-83 Rev.1)\*

URL :
https://www.nist.gov/publications/guide-malware-incident-prevention-and-handling-desktops-and-laptops

9.  NIST CSRC, dossier \"Ransomware Protection and Response\"

URL : https://csrc.nist.gov/ransomware

10. ANSSI / cyber.gouv.fr, publications et guides cyber

URL : https://cyber.gouv.fr/publications

11. ANSSI, guide sur les attaques par rancongiciels

URL :
https://cyber.gouv.fr/publications/attaques-par-rancongiciels-tous-concernes

12. IEEE Xplore, \*Stuxnet: Dissecting a Cyberwarfare Weapon\*

URL : https://ieeexplore.ieee.org/document/5772960/

10\. IEEE Spectrum, \*The Real Story of Stuxnet\*

URL : https://spectrum.ieee.org/the-real-story-of-stuxnet

11\. Virus Bulletin, article de retrospective sur ILOVEYOU

URL :
https://www.virusbulletin.com/virusbulletin/2015/05/throwback-thursday-when-love-came-town-june-2000

12\. BBC News, \*A decade on from the ILOVEYOU bug\*

URL : https://www.bbc.com/news/10095957

13\. History.com, article de vulgarisation sur ILOVEYOU

URL : https://www.history.com/articles/i-love-you-computer-worm

*------------------------------------------------------------*

## 12. Bibliographie academique (selection)

-   Cohen, F. (1987). \*Computer Viruses - Theory and Experiments\*.
    Computers & Security, 6(1), 22-35.

-   Adleman, L. (1988). \*An Abstract Theory of Computer Viruses\*.
    CRYPTO '88.

-   NIST SP 800-83 Rev.1 (2013). \*Guide to Malware Incident Prevention
    and Handling for Desktops and Laptops\*.

-   Langner, R. (2011). \*Stuxnet: Dissecting a Cyberwarfare Weapon\*.
    IEEE Security & Privacy.

-   Publications ANSSI (cyber.gouv.fr), guides de prevention et de
    reponse aux incidents cyber.

*------------------------------------------------------------*

## 13. Annexes

### Annexe A - Liste des livrables presentes dans le projet

-   `README.md`

-   `docs/tableau_conformite.md`

-   `docs/checklist_demo_orale.md`

-   `docs/rapport_l3_virologie.md`

### Annexe B - Conseils de mise en forme Word (pour depasser 15 pages proprement)

-   Police : Times New Roman 12

-   Interligne : 1,5

-   Marges : 2,5 cm

-   Titres numerotes

-   Table des matieres automatique

-   Captures d'ecran du dossier `TP_User` et des sorties terminal
    pertinentes

Avec cette mise en forme, ce contenu atteint generalement la plage
**15-18 pages**.

### Annexe C - Checklist des captures a produire

13. Capture de l'arborescence initiale du dossier `virologie/`.

14. Capture de l'execution de `setup_env.sh`.

15. Capture du contenu de `TP_User` apres preparation.

16. Capture de compilation du fichier principal.

17. Capture des permissions executables sur `MonPG1..MonPG5`.

18. Capture de trace d'execution (sequence principale).

19. Capture de la sortie \"rendre service\" en mode texte.

20. Capture de cloture de demonstration (etat final du dossier).

### Annexe D - Gabarit academique pour les figures (a copier-coller)

Utiliser le format suivant sous chaque capture :

**Figure X - \[Titre court et precis\]**

Contexte : \[commande ou etape du protocole\].

Observation : \[ce que la capture prouve vis-a-vis du critere\].

Interpretation : \[en une phrase, lien avec la conformite du sujet\].

Source : capture realisee par l'etudiant, environnement local de TP,
\[date\].

Exemple :

**Figure 3 - Etat du dossier TP_User apres preparation**

Contexte : execution de `./setup_env.sh` puis `ls -la TP_User`.

Observation : presence de `MediaPlayer.exe`, `MonPG1..MonPG5` et
ressources images.

Interpretation : l'environnement de test demande par le sujet est
correctement initialise.

Source : capture realisee par l'etudiant, environnement local de TP,
23/03/2026.

### Annexe E - Articles et publications ayant traite ce sujet

Cette annexe peut etre citee explicitement dans l'introduction et dans
la bibliographie pour montrer l'ancrage academique du travail.

21. **Cohen, F. - \*Computer Viruses - Theory and Experiments**\*

Apport : texte fondateur sur la definition et les proprietes des virus
informatiques.

22. **Adleman, L. - \*An Abstract Theory of Computer Viruses\* (CRYPTO
    1988)**

Apport : formalisation theorique du phenomene et cadre d'analyse
abstrait.

23. **NIST SP 800-83 Rev.1 - Malware Incident Prevention and
    Handling**

Apport : recommandations institutionnelles de prevention et de gestion
des incidents malware.

24. **Langner, R. - \*Stuxnet: Dissecting a Cyberwarfare Weapon\*
    (IEEE)**

Apport : etude de cas majeure montrant l'impact operationnel de
logiciels malveillants complexes.

25. **ANSSI - Publications de prevention et reponse aux incidents
    cyber**

Apport : cadre francais de bonnes pratiques, utile pour la partie
defensive et deontologique.

26. **Virus Bulletin / BBC / History (retours historiques sur
    ILOVEYOU)**

Apport : contextualisation historique et impact global des campagnes de
malware grand public.

Suggestion de phrase a inserer dans le corps du rapport :

\"La presente etude s'inscrit dans une litterature etablissant a la
fois les fondements theoriques (Cohen, Adleman) et les retours
d'experience operationnels (NIST, ANSSI, IEEE, etudes de cas
historiques).\"
