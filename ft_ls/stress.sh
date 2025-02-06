#!/bin/bash

# Cores para output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'


TEST_DIR="ls_test_dir"

cd $TEST_DIR

echo "${GREEN}Iniciando testes...${NC}"

# Função para comparar outputs
compare_output() {
    local test_name=$1
    local cmd=$2
    
    echo "Testando: $test_name"
    ls $cmd > ls_output.txt
    ../ft_ls $cmd > ft_ls_output.txt
    echo "------------------------"
}

# Teste 1: Diretório vazio
mkdir -p empty_dir
compare_output "Diretório vazio" "empty_dir"

# Teste 2: Nomes longos
long_name=$(printf 'a%.0s' {1..100})
touch "$long_name"
compare_output "Nome longo" ""

# Teste 3: Muitos arquivos
for i in {1..50}; do
    touch "file$i"
done
compare_output "Muitos arquivos" ""


compare_output "Links simbólicos" "-l"


compare_output "Permissões variadas" "-l"


compare_output "Recursão" "-R"


compare_output "Combinação -la" "-la"
compare_output "Combinação -lR" "-lR"


compare_output "Arquivos ocultos" "-a"


compare_output "Diferentes tipos" "-l"


cd ..


echo "${GREEN}Testes concluídos!${NC}"
