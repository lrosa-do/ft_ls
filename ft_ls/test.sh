#!/bin/bash

# Cores para output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Cria diretório de teste
TEST_DIR="ls_test_dir"
mkdir -p $TEST_DIR
cd $TEST_DIR

echo "${GREEN}Iniciando testes...${NC}"

# Função para comparar outputs
compare_output() {
    local test_name=$1
    local cmd=$2
    
    echo "Testando: $test_name"
    ls $cmd > ls_output.txt
    ../ft_ls $cmd > ft_ls_output.txt
    
    if diff ls_output.txt ft_ls_output.txt > /dev/null; then
        echo "${GREEN}✓ Teste passou${NC}"
    else
        echo "${RED}✗ Teste falhou${NC}"
        echo "Diferenças encontradas:"
        diff ls_output.txt ft_ls_output.txt
    fi
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

# Teste 4: Caracteres especiais
touch "file with spaces"
touch "file_with_underscore"
touch "file.with.dots"
compare_output "Caracteres especiais" ""

# Teste 5: Links simbólicos
touch original_file
ln -s original_file link_to_file
mkdir original_dir
ln -s original_dir link_to_dir
compare_output "Links simbólicos" "-l"

# Teste 6: Permissões variadas
touch perm_file
chmod 755 perm_file
mkdir perm_dir
chmod 644 perm_dir
compare_output "Permissões variadas" "-l"

# Teste 7: Recursão
mkdir -p dir1/subdir1/subdir2
touch dir1/file1
touch dir1/subdir1/file2
compare_output "Recursão" "-R"

# Teste 8: Combinação de opções
compare_output "Combinação -la" "-la"
compare_output "Combinação -lR" "-lR"

# Teste 9: Arquivos ocultos
touch .hidden_file
mkdir .hidden_dir
compare_output "Arquivos ocultos" "-a"

# Teste 10: Stress test com tipos diferentes
mkfifo pipe_file 2>/dev/null
touch regular_file
chmod +x regular_file
compare_output "Diferentes tipos" "-l"

# Limpa
cd ..
rm -rf $TEST_DIR

echo "${GREEN}Testes concluídos!${NC}"
