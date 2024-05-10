
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
print_result() {
	local filename="$1"
	local exit_code="$2"

	if [ $exit_code -eq 0 ]; then
		echo -e "${GREEN}${filename}: ${exit_code}${NC}"
	else
		echo -e "${RED}${filename}: ${exit_code}${NC}"
	fi
}

for filename in ./maps/*; do
	if [ "$filename" != "./maps/replace" ] && [ "$filename" != "./maps/replace.sh" ] && [ "$filename" != "./maps/README.md" ]; then
    	valgrind --leak-check=full --show-leak-kinds=all --suppressions=mlx42.supp ./cub3D "$filename"
    	exit_code=$?
		print_result "$filename" "$exit_code"
	fi
done
