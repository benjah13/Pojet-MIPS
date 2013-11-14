simpleUnitTest.sh : script de test "unitaire" "boite noire" (ou "externe") minimal.

########################################
# Creation Aout 2012
# Update Aout 2013
########################################
# No restriction on usage nor dissemination
########################################
# Problèmes, commentaires : nicolas.castagne@phelma.grenoble-inp.fr
########################################

########################################
# Lancement rapide des tests de l'incrément 1 du projet SIMULATEUR MIPS
########################################
1/ se placer dans le figure l'exécutable a tester, par exemple le répertoire step0
2/ entrer, par exemple
	../testing/simpleUnitTest.sh -e ./simMips test/*.simcmd

Ou : 
	../testing/simpleUnitTest.sh est le chemin vers script de test
	./simMips est le chemin vers l'executable a tester (le simulateur Mips ici) 
	test/*.simcmd  designe l'ensemble des fichiers de commande du simulateur a tester .simcmd a tester

Pour lancer en mode batch : option -b :
	../testing/simpleUnitTest.sh -e ./simMips -b test/*.simcmd


Voir la suite pour des détails.


########################################
# Introduction
########################################
Le script lance un <executable> sur une liste de fichiers de <test>, l'ensemble étant passé en argument du script.


Chaque fichier de <test> doit être accompagné :
1/ d'un fichier <test>.info
	Ce fichier décrit le test en question. 
	Détails dans la section "Fichier .info" 

2/ d'un fichier <test>.res
	Ce fichier doit contenir la sortie attendue - qu'est censé générer l'<executable> 
	sur sa sortie standard quand il est exécuté sur le fichier <test>.
	C'est ce fichier qui est utilisé pour comparer la sortie attendue avec la sortie standard de l'<exécutable>.



Pour chacun des fichiers de <test> passé en argument, le script : 
	- lance l'<executable> en lui passant <test> en argument
	- détecte si l'<executable> a "planté" (segmentation fault, etc.)
	- détecte si le code de sortie renvoyé par l'<exécutable> correspond au code erreur attendu, donné dans le fichier .info
	- détecte si la sortie de l'<executable> correspond à la sortie attendue, spécifiée dans le fichier .ers

Enfin, le script génère un rapport de test avec les résultats de tous les tests.



########################################
# Paramètres et options - en anglais
########################################


Exemple :
	$ ../testing/simpleUnitTest.sh -e ./simMips -o test_summary.txt test/*.simcmd
	=> 	runs "../simMips" on all *.simcmd files in the directory test
		and outputs results into test_summary.txt

Paramètres :
simpleUnitTest.sh [-h] -e <executablefile> [-b] [-p] [-s] [-d] [-q] [-o <summaryfile>] [-x] [-w] [-c] <args_testfiles>"


Details :
"simpleUnitTest" runs the <executablefile> specified in argument onto each of the test files specified in <args_testfiles> and checks the results

The employed <executablefile> is assumed:
1/ to accept a test file as single argment
2/ to print its results onto stdout

Each testfile in <args_testfiles> should be accompanied, in the same directory, with:
1/ a file testfile.info : information on the test. See README
2/ a file testfile.res  : contains the awaited output

 The <executablefile> will be run on each testfile and :
	1/ generate a file mytestfile.out containing the output of the program (stdout)
	2/ compare the return value of the program with the awaited return value
	3/ compare the awaited output (mytestfile.res) with the obtained output (mytestfile.out)
	4/ display result and generate a report

Required parameters are :
	-e <executablefile> : name of the executable to run
 And 	
	args_testfiles	: list of test files on which to run the executable

 And options are :
	-h		: display help message and aborts
	-b		: batch mode : no user interaction
	-p		: pause mode : adds some delay in between two tests
	-d		: display debugs of tested program (forward stderr of tested program onto the Terminal)
	-q		: quiet mode : much less output while testing
	-c		: cleans the testing files before running :
					removes <summaryfile>
					removes any test output eg testfile.out
	-o <summaryFile>: if used, writes the results into summaryfile
	-x		: if used, -x is passed to diff when comparing the results. See man diff
	-w		: if used, -w is passed to diff when comparing the results. See man diff	


########################################
# Fichiers .info
########################################
A .info file is a shell script that describes the test with corresponding names
It should set two variables employed by simpleUnitTest.sh :

TEST_RETURN_CODE, which values should be
	PASS if the test should pass without an error code (zero)
	FAIL if the test should generate an error code (non zero)

TEST_COMMENT (optional)
	a comment string describing the test


Example: here is a valid .info file :
#-------
TEST_RETURN_CODE=PASS		# the test should pass w/o error
TEST_COMMENT="Test empty file"	# this comment will be displayed before performing the test
#-------

