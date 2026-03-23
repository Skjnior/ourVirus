import re

with open("/home/junior/Documents/Rochelle/Securite Virus/virologie/docs/rapport_complet.md", "r") as f:
    text = f.read()

# Clean up pandoc escapes
text = text.replace(r"\*\*", "**")
text = text.replace(r"\_", "_")
text = text.replace(r"\`", "`")
text = text.replace(r"\'", "'")
text = text.replace(r"\-", "-")

# Insert images
img1 = "\n\n![Figure 1 - Mise en place de l'environnement](../../virologi images/Mise en place de l'environnement.png)\n*Figure 1 : Exécution de setup_env.sh et compilation des programmes cibles*\n\n"
img2 = "\n\n![Figure 2 - État AVANT infection](../../virologi images/État AVANT infection.png)\n*Figure 2 : Contenu de TP_User avant exécution du virus*\n\n"
img3 = "\n\n![Figure 3 - L'infection](../../virologi images/ L'infection (le plus important !).png)\n*Figure 3 : L'infection réussie des programmes cibles*\n\n"
img4 = "\n\n![Figure 4 - Preuve d'infection](../../virologi images/Preuve d'infection.png)\n*Figure 4 : Preuve d'infection (paires MonPG et MonPG.old)*\n\n"
img5 = "\n\n![Figure 5 - Protection anti-réinfection](../../virologi images/Protection anti-réinfection.png)\n*Figure 5 : Deuxième exécution bloquée par l'anti-réinfection*\n\n"
img6 = "\n\n![Figure 6 - Transfert vers le programme original](../../virologi images/ Transfert vers le programme original.png)\n*Figure 6 : Transfert de l'exécution au programme légitime*\n\n"

text = text.replace("**[FIGURE 1 - a inserer apres la section 4.1 Configuration]**\n\n*Titre propose :* \"Arborescence initiale du projet dans\n`virologie/`\"\n\n*Capture attendue :* sortie `ls -la` du dossier `virologie/`.", img1)
text = text.replace("**[FIGURE 2 - a inserer apres la section 4.2 Protocole de mise en\nplace]**\n\n*Titre propose :* \"Execution du script `setup_env.sh`\"\n\n*Capture attendue :* terminal montrant les etapes de preparation.", img2)
text = text.replace("**[FIGURE 3 - a inserer apres la section 4.2, juste avant 4.3]**\n\n*Titre propose :* \"Etat du dossier `TP_User` apres preparation\"\n\n*Capture attendue :* sortie `ls -la TP_User`.", img3)
text = text.replace("**[FIGURE 4 - a inserer au debut de la section 6.1 Points\nconformes]**\n\n*Titre propose :* \"Compilation reussie du programme principal\"\n\n*Capture attendue :* commande GCC + absence d'erreur.", img4)
text = text.replace("**[FIGURE 5 - a inserer dans la section 6.1, apres le point sur les\nexecutables cibles]**\n\n*Titre propose :* \"Presence de `MonPG1` a `MonPG5` en mode\nexecutable\"\n\n*Capture attendue :* listing avec permissions.", img5)
text = text.replace("**[FIGURE 6 - a inserer dans la section 6.1, apres le point sur le\ntransfert d'execution]**\n\n*Titre propose :* \"Trace d'execution montrant la sequence\nfonctionnelle\"\n\n*Capture attendue :* sortie console de demonstration.", img6)

with open("/home/junior/Documents/Rochelle/Securite Virus/virologie/docs/rapport_final_avec_images.md", "w") as f:
    f.write(text)

