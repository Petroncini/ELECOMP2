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

- 0 e 0 -> motor parado
- 0 e 1 -> giro horário
- 1 e 0 -> gito anti-horário
- 1 e 1 -> motor QUEIMADO

Deve ter cuidado para não mandar dois sinais 1 para as entradas lógicas pois o circuito da ponte H consiste em 4 transistors que mudam a direção da corrente, e se você abrir todos eles você acaba com um curto (embora algumas placas tenham proteção contra isso, better safe than sorry) como pode ser visto no diagram abaixo

![image](https://github.com/Petroncini/ELECOMP2/assets/59212480/d26752c9-19e2-46cb-b281-6fd30dd55da9)

ESP32: A esp serve como o microcontrolar para fazer o envio dos sinais lógicos para ponte H. No nosso projeto implementamos alguns jeitos diferentes de fazer esse controle, tanto com um roteiro pre programa de movimentos para o motor, controle através da entrada serial no computador, e o controle através de um site que manda comandos através de requisições GET com informações acerca do movimento desejado do motor. Esse último só é possível graças ao chip de Wi-FI da ESP32. 

Circuito: O circuito é composto pelas 8 baterias de 1.5V conectadas em séries para alimentar a ponte H. É conectado então, o positivo de 12v na entrada de energia da ponte H, para fazer alimentação dos motores. Da mesma forma, o negativo das baterias é conectado ao GND da ponte H. A ponte vem com o próprio conversor de tensão, então é possível tirar uma tensão de 5v da ponte H para alimentar a ESP32 quando o circuito estive em operação. A ESP32, durante o desenvolvimento do projeto, foi alimentada usando o próprio micro-USB. Além disso, os pinos digitais 23 e 22 são ligados ao in1 e in2 da ponte H e os pinos digitais 21 e 19 são ligados ao in3 e in4 da ponte. É por meio desse pinos que a esp32 manda os sinais para fazer o controle dos motores. Também é importante conectar o GND da ESP32 ao negativo das pilhas para a corrente poder fluir para a ponte H. É recomendável também adicionar resistores na faixa de 3.3-5k ohms na saida dos pinos da ESP32 para protege-la (RIP ESP32 1 e 2);

![image](https://github.com/Petroncini/ELECOMP2/assets/59212480/62b974d3-ab72-4094-ae01-6bac41b38d00)

![image](https://github.com/Petroncini/ELECOMP2/assets/59212480/1971b7c9-0e5d-4a2a-86b5-b648ba36d79d)


Código: Nesse repositório temos dois programas que usamos para controlar os motores. O primeiro 




