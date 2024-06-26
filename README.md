# ELECOMP2
Repositório para o projeto 2 de eletrônica da disciplina SSC0180 Eletrônica para Computação com Eduardo Simões. 

Objetivo: montar um circuito para controlar dois motores DC por meio de uma ESP32 recebendo comandos por WIFI. Com esse circuito,
será possível criar um simples carrinho de controle remoto para ser usado para projetos futuros integrando sensores e sistemas de controle
mais sofisticados como IA e algoritmos genéticos

Componentes:
- ESP32
- POnte H l298n
- Protoboard
- 2 motores 12v
- Jumpers
- 8 baterias AA 1.5v
- Suporte para 6 baterias (Série)
- Suporte para 2 baterias (Série)


Ponte H: a ponte H serve para mudar o fluxo da corrente direta de 12v indo para o motor, mudando assim o sentido de rotação. A ponte H l298n é conectada numa fonte de 12v, no caso as nossas 8 pilhas em séries, e é capaz de controlar 2 motores DC utilizando 4 entradas lógicas. Então para cada motor podemos ter as entradas

0 e 0 -> motor parado
0 e 1 -> giro horário
1 e 0 -> gito anti-horário
1 e 1 -> motor QUEIMADO

Deve ter cuidado para não mandar dois sinais 1 para as entradas lógicas pois o circuito da ponte H consiste em 4 transistors que mudam a direção da corrente, e se você abrir todos eles você acaba com um curto (embora algumas placas tenham proteção contra isso, better safe than sorry) como pode ser visto no diagram abaixo

![image](https://github.com/Petroncini/ELECOMP2/assets/59212480/d26752c9-19e2-46cb-b281-6fd30dd55da9)

ESP32: A esp serve como o microcontrolar para fazer o envio dos sinais lógicos para ponte H. No nosso projeto implementamos alguns jeitos diferentes de fazer esse controle, tanto com um roteiro pre programa de movimentos para o motor, controle através da entrada serial no computador, e o controle através de um site que manda comandos através de requisições GET com informações acerca do movimento desejado do motor. Esse último só é possível graças ao chip de Wi-FI da ESP32. 



