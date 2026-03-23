import re

with open("/home/junior/Documents/Rochelle/Securite Virus/virologie/docs/rapport_complet.md", "r") as f:
    lines = f.readlines()

new_lines = []
skip = False

for line in lines:
    line = line.replace(r"\*\*", "**")
    line = line.replace(r"\_", "_")
    line = line.replace(r"\`", "`")
    line = line.replace(r"\'", "'")
    line = line.replace(r"\-", "-")

    if "**[FIGURE 1" in line:
        new_lines.append("\n![Figure 1 - Mise en place de l'environnement](../../virologi images/Mise en place de l'environnement.png)\n*Figure 1 : Exécution de setup_env.sh et compilation des programmes cibles*\n\n")
        skip = True
    elif "**[FIGURE 2" in line:
        new_lines.append("\n![Figure 2 - État AVANT infection](../../virologi images/État AVANT infection.png)\n*Figure 2 : Contenu de TP_User avant exécution du virus*\n\n")
        skip = True
    elif "**[FIGURE 3" in line:
        new_lines.append("\n![Figure 3 - L'infection](../../virologi images/ L'infection (le plus important !).png)\n*Figure 3 : L'infection réussie des programmes cibles*\n\n")
        skip = True
    elif "**[FIGURE 4" in line:
        new_lines.append("\n![Figure 4 - Preuve d'infection](../../virologi images/Preuve d'infection.png)\n*Figure 4 : Preuve d'infection (paires MonPG et MonPG.old)*\n\n")
        skip = True
    elif "**[FIGURE 5" in line:
        new_lines.append("\n![Figure 5 - Protection anti-réinfection](../../virologi images/Protection anti-réinfection.png)\n*Figure 5 : Deuxième exécution bloquée par l'anti-réinfection*\n\n")
        skip = True
    elif "**[FIGURE 6" in line:
        new_lines.append("\n![Figure 6 - Transfert vers le programme original](../../virologi images/ Transfert vers le programme original.png)\n*Figure 6 : Transfert de l'exécution au programme légitime*\n\n")
        skip = True
    elif "**[FIGURE 7" in line:
        skip = True
    elif "**[FIGURE 8" in line:
        skip = True

    if skip and line.strip() == "":
        continue
    if skip and ("*Titre propose :*" in line or "*Capture attendue :*" in line):
        continue
    else:
        skip = False

    if not skip:
        new_lines.append(line)

with open("/home/junior/Documents/Rochelle/Securite Virus/virologie/docs/rapport_l3_virologie_avec_captures.md", "w") as f:
    f.writelines(new_lines)
