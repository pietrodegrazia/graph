rm graph
g++ -std=gnu++11 -c main.cc
g++ -std=gnu++11 -O3 main.o -o graph
# ./graph < teste.txt | diff teste-resposta.txt -
# ./graph < testes/teste1000.txt | diff testes/teste1000_respostas.txt -
# time ./graph < testes/teste100a.txt
time ./graph < testes/teste100a.txt | diff testes/teste100a_respostas.txt -