import sys
import csv
import matplotlib.pyplot as plt

DATA_DIR = "graphique/data/"

# -----------------------------------------------------------
# Lecture fichier .dat
# -----------------------------------------------------------
def lire_dat(fichier):
    data = []
    with open(fichier, "r", encoding="utf-8") as f:
        reader = csv.reader(f, delimiter=';')
        for row in reader:
            if len(row) < 4:
                continue
            data.append({
                "id": row[0],
                "max": float(row[1]),
                "src": float(row[2]),
                "real": float(row[3])
            })
    return data

# -----------------------------------------------------------
# Tri selon critère
# -----------------------------------------------------------
def cle_tri(usine, arg):
    if arg == "max":
        return usine["max"]
    if arg == "src":
        return usine["src"]
    if arg == "real":
        return usine["real"]
    if arg == "all":
        return usine["max"]

# -----------------------------------------------------------
# Création graphique
# -----------------------------------------------------------
def tracer(data, arg, fichier_sortie, titre, reverse):

    data.sort(key=lambda u: cle_tri(u, arg), reverse=reverse)

    ids = [u["id"] for u in data]
    x = range(len(ids))

    plt.figure(figsize=(12, 6))
    # Couleurs à fort contraste (imposées par la consigne)
    col_real_all = "#DFDFFF"   # bleu
    col_perte = "#FFA0A0"  # rouge
    col_reste = "#D2FFD2"  # vert
    col_max = "#1f77b4"   # bleu fort
    col_src = "#2ca02c"   # vert fort
    col_real = "#d62728"  # rouge fort

    if arg == "all":
        real_vals = [u["real"] for u in data]
        perte_vals = [u["src"] - u["real"] for u in data]
        reste_vals = [u["max"] - u["src"] for u in data]


        plt.bar(x, real_vals, color=col_real_all)
        plt.bar(x, perte_vals, bottom=real_vals, color=col_perte)
        plt.bar(x,reste_vals,bottom=[r + p for r, p in zip(real_vals, perte_vals)],color=col_reste)
    else:
        valeurs = [cle_tri(u, arg) for u in data]
        couleur = col_max if arg == "max" else col_src if arg == "src" else col_real
        plt.bar(x, valeurs, color=couleur)

    plt.xticks(x, ids, rotation=-45, ha="left")
    plt.ylabel("Volume (M.m³)")
    plt.title(titre)
    plt.grid(axis="y", linestyle="--", alpha=0.6)
    plt.tight_layout()
    plt.savefig(fichier_sortie)
    plt.close()

# -----------------------------------------------------------
# MAIN
# -----------------------------------------------------------
if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("Usage : python graphique.py [max|src|real|all]")
        sys.exit(1)

    arg = sys.argv[1]
    if arg not in ("max", "src", "real", "all"):
        print("Argument invalide")
        sys.exit(1)

    # 10 meilleurs
    data_max = lire_dat(DATA_DIR + "usine_max.dat")
    tracer(
        data_max,
        arg,
        f"gnuplot/graphique/graphique_10_meilleurs_{arg}.png",
        "10 meilleures usines",
        reverse=False
    )

    # 50 pires
    data_min = lire_dat(DATA_DIR + "usine_min.dat")
    tracer(
        data_min,
        arg,
        f"gnuplot/graphique/graphique_50_pires_{arg}.png",
        "50 pires usines",
        reverse=False
    )
