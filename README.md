# 🌊 C-WildWater
Deuxième année de Pré-Ingénieur CY Tech, Semestre 3 2025-2026

## 👥 Collaborateurs
- [Aymane AMARA](https://github.com/Kkirbo)
- [Néo CARDOT-BUTZ](https://github.com/cardotbutzneo)
- [Adchayan JEYAKUMAR](https://github.com/jadchayan)

## 📄 Documentation
- :scroll: [Cahier des charges](./Projet_C-WildWater_preIng2_2025_2026_v1.1.pdf)
- :ledger: [Rapport de projet](https://ucergyfr-my.sharepoint.com/:w:/g/personal/adchayan_jeyakumar_etu_cyu_fr/IQB6Im92as5eQ5P6oZGU3YcpAXwWIHeEV21_lHRHWehkfu0?rtime=SsLKMew-3kg)

## :gear: Description
Ce projet vise à gérer les données d’un réseau de distribution d’eau potable.
À partir d’un fichier en entrée, le script permet :

- de générer une paire de graphiques présentant les 10 usines les plus productives et les 50 usines les moins productives du réseau.
- d'évaluer le volume total d’eau perdu en aval d’une usine donnée.


## :toolbox: Prérequis
- **gcc**
- **make**
- **bash**
- **gnuplot** *ou* **python3** - génération de graphiques

## :rocket: Téléchargement et compilation
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
```
bash launch.sh leaks "id_usine"
```
Exemple de commande valide :
```bash
bash launch.sh leaks "Facility complex #WI400023I"
````
⚠️ Attention : les guillemets autour de l’identifiant de l’usine sont nécessaires !

## :test_tube: Sortie du programme
### Performance
Temps d'éxécution du programme :
- < 5s sur linux natif
- < 30s sur linux wsl <br>
**Attention : la performance du programme dépend essentiellement du temps des appels fonctions de votre OS**  
Le temps d'éxécution du programme peut varier d'un pc à l'autre.

### Sortie attendu
A la fin de l'éxécution, le programme sort une paire de graphiques, dans le dossier gnuplot/graphique au format .png.
Les sorties (stdin ou stderr) sont redirigées vers le nom associée dans le dossier output/













