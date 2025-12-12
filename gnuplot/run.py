import matplotlib.pyplot as plt
import csv

# -----------------------------------------------------------
# Lecture d'un fichier .dat ou .csv
# Chaque ligne : ID;Capacité;Volume capté;Volume traité
# -----------------------------------------------------------
def lire_dat(fichier):
    ids = []
    capacites = []
    captes = []
    traites = []

    with open(fichier, "r", encoding="utf-8") as f:
        reader = csv.reader(f, delimiter=';')
        for row in reader:
            if len(row) < 4:
                continue
            ids.append(row[0])
            capacites.append(float(row[1]))
            captes.append(float(row[2]))
            traites.append(float(row[3]))

    return ids, capacites, captes, traites

# -----------------------------------------------------------
# Fonction pour tracer un graphique en barres empilées
# -----------------------------------------------------------
def tracer_graphique(fichier, sortie, titre):
    ids, capacites, captes, traites = lire_dat(fichier)

    x_pos = range(len(ids))

    plt.figure(figsize=(12, 6))

    # Couleurs pour les barres
    couleur_capacite = "#DFFFDF"  # Bleu pastel
    couleur_capte = "FFA0A0"   # Vert pastel
    couleur_traite = "DFDFFF"  # Rouge pastel

    # Tracer les barres empilées
    plt.bar(x_pos, capacites, color=couleur_capacite, label="Capacité")
    plt.bar(x_pos, captes, bottom=capacites, color=couleur_capte, label="Volume capté")
    plt.bar(x_pos, traites, bottom=[c + v for c, v in zip(capacites, captes)], color=couleur_traite, label="Volume traité")

    # Personnalisation du graphique
    plt.xticks(x_pos, ids, rotation=-45, ha='left')
    plt.ylabel("Volume (M.m³)")
    plt.title(titre)
    plt.legend(loc="upper right")
    plt.grid(axis='y', linestyle='--', alpha=0.5)
    plt.tight_layout()

    # Sauvegarder le graphique
    plt.savefig(sortie)
    plt.close()
    print(f"Graphique enregistré dans {sortie}")

# -----------------------------------------------------------
# Exemple d'utilisation
# -----------------------------------------------------------
if __name__ == "__main__":
    tracer_graphique(
        fichier="gnuplot/data/usine_max.dat",
        sortie="graphique_top_10.png",
        titre="Plant data (10 greatest)"
    )
    tracer_graphique(
        fichier="gnuplot/data/usine_min.dat",
        sortie="graphique_least_50.png",
        titre="Plant data (10 worst)"
    )