files=`find ./ -perm /0111`

# read_char var
read_char() {
  stty -icanon -echo
  eval "$1=\$(dd bs=1 count=1 2>/dev/null)"
  stty icanon echo
}

for i in $files; do
	if [ $i == "./" ];
	then
		continue
	fi

	if [ ${i##*.} == "sh" ];
	then
		continue
	fi

	echo "file $i ==========================="
	nm $i | c++filt
	echo "press any key to show next file"
	read_char char
done
