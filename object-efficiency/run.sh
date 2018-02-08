files=`find ./ -perm /0111`

for i in $files; do
	if [ $i == "./" ] 
	then 
		continue
	fi
	if [ ${i##*.} == "sh" ]
	then 
		continue
	fi
	$i	
done
