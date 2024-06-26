---

# ELECOMP2

Repositório para o projeto 2 de eletrônica da disciplina SSC0180 Eletrônica para Computação com Eduardo Simões.

## Objetivo
O objetivo deste projeto é montar um circuito capaz de controlar dois motores DC utilizando uma ESP32 que recebe comandos via Wi-Fi. Com este circuito, pretendemos criar um protótipo de um carrinho de controle remoto, que poderá ser utilizado em projetos futuros, onde serão integrados sensores e sistemas de controle mais avançados, incluindo inteligência artificial (IA) e algoritmos genéticos.

## Componentes Utilizados
- **ESP32**: Microcontrolador com capacidade de comunicação Wi-Fi e Bluetooth.
- **Ponte H L298N**: Módulo controlador de motores que permite a inversão da polaridade para controle bidirecional.
- **Protoboard**: Placa de ensaio para montagem dos circuitos sem a necessidade de solda.
- **2 Motores DC 12V**: Motores elétricos que serão controlados pelo circuito.
- **Jumpers**: Cabos para realizar as conexões entre os componentes no protoboard.
- **8 Baterias AA 1.5V**: Fontes de alimentação para o circuito, conectadas em série.
- **Suporte para 6 baterias**: Conector para acomodar e conectar as baterias em série.
- **Suporte para 2 baterias**: Conector adicional para baterias.

## Descrição da Ponte H
A ponte H é um circuito que permite controlar a direção do fluxo de corrente que alimenta os motores, possibilitando a reversão do sentido de rotação. No nosso caso, utilizamos a ponte H L298N, que é um módulo popular para controle de motores. Ele suporta a conexão de uma fonte de alimentação de 12V, que no nosso projeto é fornecida pelas 8 pilhas AA conectadas em série. Este módulo é capaz de controlar dois motores DC de forma independente, utilizando 4 entradas lógicas para cada motor. As combinações de sinais para cada motor são as seguintes:

- **00**: Motor parado.
- **01**: Motor gira no sentido horário.
- **10**: Motor gira no sentido anti-horário.
- **11**: Motor pode ser danificado (evitar essa configuração).

É fundamental evitar a configuração onde ambos os sinais são 1, pois isso pode causar um curto-circuito na ponte H, potencialmente danificando o módulo e os motores. Embora alguns módulos tenham proteção contra curtos, é sempre melhor prevenir.

![Diagrama da Ponte H](https://github.com/Petroncini/ELECOMP2/assets/59212480/d26752c9-19e2-46cb-b281-6fd30dd55da9)

## ESP32 como Microcontrolador
A ESP32 é um microcontrolador versátil, equipado com capacidades de comunicação Wi-Fi e Bluetooth. No nosso projeto, a ESP32 é responsável por enviar os sinais lógicos para a ponte H, controlando assim os motores. Implementamos diferentes métodos de controle:

1. **Roteiro pré-programado**: Um conjunto de movimentos predefinidos que o carrinho segue automaticamente.
2. **Controle via entrada serial**: Utilizando o monitor serial da IDE do Arduino, podemos enviar comandos diretamente para a ESP32, que então controla os motores em tempo real.
3. **Controle via interface web**: A ESP32 hospeda um servidor web simples que aceita comandos de movimento via requisições HTTP GET. Essa funcionalidade é possibilitada pelo módulo Wi-Fi integrado na ESP32.

## Descrição do Circuito
O circuito é alimentado por 8 baterias AA de 1.5V conectadas em série, fornecendo um total de 12V. Esta fonte de alimentação é conectada à entrada de energia da ponte H L298N para alimentar os motores. O negativo das baterias é ligado ao GND da ponte H, completando o circuito de alimentação.

A ponte H possui um conversor de tensão integrado, que permite obter uma saída de 5V para alimentar a ESP32 durante a operação. No desenvolvimento do projeto, a ESP32 foi alimentada via micro-USB.

### Conexões Detalhadas
- **Pinos Digitais 23 e 22 da ESP32**: Conectados aos pinos in1 e in2 da ponte H, controlando o primeiro motor.
- **Pinos Digitais 21 e 19 da ESP32**: Conectados aos pinos in3 e in4 da ponte H, controlando o segundo motor.
- **GND da ESP32**: Conectado ao negativo das baterias para garantir um circuito comum de referência.

É recomendável adicionar resistores de 3.3k a 5k ohms nas saídas dos pinos da ESP32 para proteger o microcontrolador de possíveis danos.

![Esquema do Circuito](https://github.com/Petroncini/ELECOMP2/assets/59212480/62b974d3-ab72-4094-ae01-6bac41b38d00)

![Imagem do Circuito](https://github.com/Petroncini/ELECOMP2/assets/59212480/1971b7c9-0e5d-4a2a-86b5-b648ba36d79d)

## Código Fonte
Neste repositório, disponibilizamos dois programas para controlar os motores. O primeiro programa permite controle via monitor serial da IDE do Arduino. Utilizando comandos como "frente", "tras", "direita" e "esquerda" no terminal, é possível controlar o movimento dos motores. No loop principal do programa, a entrada do usuário é verificada e a função correspondente é chamada. Cada função de movimento utiliza a função `digitalWrite` para enviar sinais às entradas lógicas da ponte H, alterando a direção da corrente que passa pelos motores e, consequentemente, sua rotação.

### Prevenção de Curto-Circuito
No código, tomamos o cuidado de sempre definir os pinos como LOW antes de defini-los como HIGH. Isso evita a situação onde todos os transistores da ponte H estariam abertos simultaneamente, o que causaria um curto-circuito.
