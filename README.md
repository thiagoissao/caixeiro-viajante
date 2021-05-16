### Universidade Estadual De Maringá

### Disciplina:
  * 6903/01 - MODELAGEM E OTIMIZACAO ALGORITMICA

### Docente:
  * Ademir Aparecido Constantino

### Discentes:
  * RA: 107774 - Gabriel T. H. Santos 
  * RA: 103069 - Thiago I. Yasunaka 

### Projeto:
  * ANÁLISE DA IMPLEMENTAÇÃO DO ALGORITMO GENÉTICO COMBINADO
COM BUSCA LOCAL PARA O PROBLEMA DO CAIXEIRO VIAJANTE

### Para compilar utiliza: 

    $ g++ main.cpp

### Para executar há uso de parametros especificando:
* * ./a.out arquivoEmData/.. taxaDeMutação tamanhoMaximoDaPopulacao UsoBuscaLocal

* Legenda: rota do arquivo TX_MUT TAM_POP LOCAL_SEARCH (1 para usar e 0 para não usar)
### Exemplo prático:
	$ ./a.out data/tsp225.txt 2 5000 1

* ./a.out 		  = executavel
* data/tsp225.txt = rota do arquivo de entrada
* 2				  = taxa de mutação
* 5000 			  = tamanho máximo da população
* 1 			  = para usar busca local
