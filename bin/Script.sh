 #!/bin/bash


echo "Début de traitement"
myArr=("10" "25" "50" "100" "250" "500" "1000" "2500" "5000" "10000" "25000" "50000" "100000")

for idx in ${!myArr[*]}
do
    while [[ $(pgrep -x ENLegnSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
        #Init
        value=${myArr[$idx]}
        idx_fichier=$(($idx))
        echo Index : $idx / Fichier : $value
        # Creation du fichier a partir du fichier de base (fichier temporaire)
        cp vrml_base.mac base_$idx_fichier_bis.mac
        # Mise en place de la variable
        sed -e "s/%energy/$value/g" base_$idx_fichier_bis.mac > base_$idx_fichier.mac
        # Suppression fichier temporaire
        rm base_$idx_fichier_bis.mac
	./ENLegnSim Section_efficace_gamma_Silicone_${myArr[$idx]}keV 10000000 base_$idx_fichier.mac &
	sleep 5
done
echo "Fin de traitement"


