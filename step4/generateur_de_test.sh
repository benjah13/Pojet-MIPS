echo " 


Creation des fichiers $1.info $1.res $1.out $1.simcmd
Ce test est censé renvoyer le code $2
"
[ $# -ne 2 ]
echo "le fichier $1.simcmd contient la commande $3
"

touch ./test/$1.info
echo "###############
# This file is a shell script describes the test with corresponding names
# It should set two variables employed by simpleUnitTest.sh :
#
# TEST_RETURN_CODE, which values should be
#	PASS if the test should pass without an error code (zero)
#	FAIL if the test should generate an error code (non zero)
#
# TEST_COMMENT (optional)
#	a string describing the test
###############
TEST_RETURN_CODE=$2
TEST_COMMENT=Test empty file" >>./test/$1.info

touch ./test/$1.res

touch ./test/$1.simcmd

echo "#Commande a lancer dans le script $1

$3">>./test/$1.simcmd

touch ./test/$1.out

