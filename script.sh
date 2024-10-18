#!/bin/bash
addition(){
   sum=$(($1+$2))
   return $sum
}
read -p "Entrez un numéro : " int1
read -p "Entrez un numéro : " int2
add $int1 $int2
echo "Le résultat est : " $?
