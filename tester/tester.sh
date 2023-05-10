#!/bin/bash
all_files=("expansions pipes pipes_error quotemarks quotemarks_error") # Coloco aqui os arquivos com os códigos
all_files+=("redirects rraba")
for file in $all_files;
do
	echo "Vez de " $file
	
	while read -r tes #|| [ -n "$tes" ]; #Leio as linhas do arquivo [acrescento um \n na última linha (culpa do read)]
	do
		((total++))
		echo "Linha $i lida" "$tes" # tes é a variável do read com somente uma linha do arquivo
		((certos++))
	done < <(cat $file; echo;) #Isso <(cmd) é equivalente a $(cmd), contudo, manda para o while... vide [] sobre o porquê do cmd
done
echo $certos/$total

# int	main()
# {
# 	return (0);
# }