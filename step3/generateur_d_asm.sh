cd res
touch $1.s
echo -e "## test $1

$2">>$1.s
mips-as $1.s -o $1.o
cd ..
