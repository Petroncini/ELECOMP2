--------------------------

# ELECOMP2

Repositório para o projeto 2 de eletrônica da disciplina SSC0180 Eletrônica para Computação com Eduardo Simões.

Por:
- Caio Petroncini
- Newton Eduardo Pena Villegas
- Heitor Gomes de Oliveira

## Objetivo
O objetivo deste projeto é montar um circuito capaz de controlar dois motores DC utilizando uma ESP32 que recebe comandos via Wi-Fi. Com este circuito, pretendemos criar um protótipo de um carrinho de controle remoto, que poderá ser utilizado em projetos futuros, onde serão integrados sensores e sistemas de controle mais avançados, incluindo inteligência artificial (IA) e algoritmos genéticos.

## Componentes Utilizados
- **ESP32 devkit v1**: Microcontrolador com capacidade de comunicação Wi-Fi e Bluetooth.
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

<img width="1105" alt="image" src="https://github.com/Petroncini/ELECOMP2/assets/59212480/06c06509-ca97-46d8-b9df-a1895cdeb597">
*o circuito de verdade usa uma esp32 devkit v1 e uma  ponte H L298N

É recomendável adicionar resistores de 3.3k a 5k ohms nas saídas dos pinos da ESP32 para proteger o microcontrolador de possíveis danos.

![Esquema do Circuito](https://github.com/Petroncini/ELECOMP2/assets/59212480/62b974d3-ab72-4094-ae01-6bac41b38d00)

![Imagem do Circuito](https://github.com/Petroncini/ELECOMP2/assets/59212480/1971b7c9-0e5d-4a2a-86b5-b648ba36d79d)

## Código Fonte
Neste repositório, disponibilizamos dois programas para controlar os motores. O primeiro programa permite controle via monitor serial da IDE do Arduino. Utilizando comandos como "frente", "tras", "direita" e "esquerda" no terminal, é possível controlar o movimento dos motores. No loop principal do programa, a entrada do usuário é verificada e a função correspondente é chamada. Cada função de movimento utiliza a função `digitalWrite` para enviar sinais às entradas lógicas da ponte H, alterando a direção da corrente que passa pelos motores e, consequentemente, sua rotação.

### Considerações de segurança no código
No código, tomamos o cuidado de sempre definir os pinos como LOW antes de defini-los como HIGH. Isso evita a situação onde todos os transistores da ponte H estariam abertos simultaneamente, o que causaria um curto-circuito. Além disso, é importante manter em mente que quando um motor DC muda de direção, uma corrente oposta é induzida no fio, que esquenta os componentes e, mais importante, causa curto em qualquer coisa não protegida contra essa reversão de corrente. Por isso, e isso foi algo que aprendemos depois de ter estragado duas ESPs, é importante, antes de qualquer alteração na direção, ou seja, antes de mudar os sinais lógicos indo da ESP32 para a ponte H, que você sete todos os sinais lógicos para 0, parando os motores, e espere um tempo de 500 a 1000 milissegundos de margem de segurança. 

Então, resumindo as medidas de segurança para a montagem do circuito e no seu código:
- Coloque resistores na saída da ESP32 para evitar que a ponte H puxe corrente demais dela.
- NUNCA mande dois sinais de HIGH para os inputs de um mesmo motor; para evitar isso, rode os digitalWrites LOW antes dos HIGH.
- Desligue os motores por no mínimo 500 milissegundos antes de qualquer mudança de direção de rotação nos motores. Delicadeza é essencial.

### Programa com Interface Wi-Fi
Adicionamos um novo programa que permite controlar o carrinho via uma interface web, utilizando a capacidade Wi-Fi da ESP32. Este programa cria um servidor web simples que aceita comandos de movimento (frente, trás, esquerda, direita e parar) enviados através de requisições HTTP GET. Isso permite controlar o carrinho de qualquer dispositivo conectado à mesma rede Wi-Fi, como um smartphone ou laptop.

#### Explicação Detalhada do Programa

1. **Configuração da Rede Wi-Fi**:
   - No início do código, você define o SSID (nome) e a senha da rede Wi-Fi à qual a ESP32 irá se conectar.
   - No `setup()`, a ESP32 tenta se conectar à rede Wi-Fi utilizando essas credenciais, imprimindo mensagens no monitor serial para indicar o status da conexão.

2. **Configuração dos Pinos**:
   - Os pinos da ESP32 são configurados como saídas, especificando quais pinos controlam os motores. Além dos pinos dos motores, também é configurado um pino para um LED indicador.

3. **Inicialização do Servidor Web**:
   - Após estabelecer a conexão Wi-Fi, o servidor web é iniciado na porta 80. O endereço IP da ESP32 na rede é então impresso no monitor serial.

4. **Loop Principal**:
   - No `loop()`, o código verifica se há um cliente conectado ao servidor (um dispositivo que fez uma requisição HTTP).
   - Se uma requisição for recebida, ela é lida e analisada para determinar qual comando foi enviado (por exemplo, /FORWARD, /BACKWARD, /LEFT, /RIGHT, /STOP).
   - Com base no comando recebido, a ESP32 ajusta os pinos dos motores para executar a ação correspondente (mover para frente, para trás, virar à esquerda, virar à direita, ou parar).
   - Após processar o comando, o servidor web envia uma resposta de confirmação ao cliente.

5. **Funções de Movimento**:
   - Existem funções específicas para cada movimento (frente, trás, esquerda, direita, parar). Essas funções ajustam os pinos dos motores para criar o movimento desejado.
   - Antes de cada mudança de movimento, os pinos são todos definidos como LOW para evitar curto-circuitos e danos à ponte H e à ESP32.

### Instruções de Uso
1. Carregue o programa na ESP32 utilizando a IDE do Arduino.
2. Abra o monitor serial para verificar as mensagens de status.
3. Conecte-se à rede Wi-Fi configurada no código.
4. Utilize um navegador web em um dispositivo conectado à mesma rede e acesse o endereço IP da ESP32.
5. Envie comandos de movimento através da barra de endereços do navegador (por exemplo, `http://<IP_DA_ESP32>/FORWARD` para mover para frente).



## Vídeo

**link para os videos do projeto**

----------------------

