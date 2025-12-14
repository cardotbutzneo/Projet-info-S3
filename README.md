# 🌊 C-WildWater
Deuxième année de Pré-Ingénieur CY Tech, Semestre 3 2025-2026

## 👥 Collaborateurs
- [Aymane AMARA](https://github.com/Kkirbo)
- [Néo CARDOT-BUTZ](https://github.com/cardotbutzneo)
- [Adchayan JEYAKUMAR](https://github.com/jadchayan)

## 📄 Documentation
- :scroll: [Cahier des charges](./Projet_C-WildWater_preIng2_2025_2026_v1.0.pdf)
- :ledger: [Rapport de projet]

## :gear: Description

## :toolbox: Prérequis
- **gcc**
- **make**
- **bash**
- **gnuplot** *ou* **python3** - génération de graphiques

## Téléchargement et compilation
### Téléchargement
```bash
git clone https://github.com/cardotbutzneo/C-WildWater.git
```
### Compilation
```bash
bash launch.sh -r
```
Exemple de commande valide :
```
bash launch.sh -r
bash launch.sh histo max
bash launch.sh histo all
bash launch.sh -c -a
```
Les commandes pour l'histogramme sont:
> max |
> src |
> real |
> all

La commande pour les fuites est:
> bash launch.sh leaks "id_usine"
 
Exemple de commande valide :
```bash
bash launch.sh leaks "Facility complex #WI400023I"
````
## Sortie du programme
### Performance
Temps d'éxécution du programme :
- < 5s sur linux natif
- < 30s sur linux wsl <br>
**Attention : la performance du programme dépend essentiellement du temps des appels fonctions de votre OS**  
Le temps d'éxécution du programme peut varier d'un pc à l'autre.

### Sortie attendu
A la fin de l'éxécution, le programme sort une paire de graphique, contenant les 10 usines les plus productives et les 50 les moins productives, dans le dossier gnuplot/graphique au format .png.
Les sorties (stdin ou stderr) sont redirigées vers le nom associée dans le dossier output/





