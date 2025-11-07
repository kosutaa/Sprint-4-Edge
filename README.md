# ⚽ Passa a Bola – Monitoramento IoT do Campo de Futebol Feminino

## 📘 Descrição do Projeto
O projeto **Passa a Bola – IoT** tem como objetivo demonstrar, de forma prática, a aplicação de tecnologias de **Internet das Coisas (IoT)** no contexto do futebol feminino.

A proposta é integrar sensores a uma plataforma web para **monitorar as condições ambientais do campo de futebol**, coletando informações de **temperatura**, **umidade** e **luminosidade**.

Esses dados podem ser utilizados para:
- Avaliar a **qualidade do gramado e das condições de jogo**;
- Monitorar **segurança e conforto térmico** para as atletas;
- Oferecer **informações em tempo real** no site da comunidade *Passa a Bola*, integrando tecnologia e esporte.

---

## 🌡️ Grandezas Monitoradas
| Sensor | Grandeza | Descrição |
|---------|-----------|-----------|
| **DHT22** | Temperatura (°C) | Mede a temperatura ambiente do campo |
|  | Umidade Relativa (%) | Mede o nível de umidade do ar |
| **LDR (Light Dependent Resistor)** | Luminosidade (%) | Mede a intensidade de luz incidente no campo |

---

## 🧠 Arquitetura IoT

A arquitetura do projeto é composta pelos seguintes elementos:

1. **ESP32 (dispositivo IoT)**
   - Faz a leitura dos sensores DHT22 e LDR;
   - Envia os dados via protocolo **MQTT**;
   - Conectado à rede Wi-Fi e à nuvem.

2. **Broker MQTT (HiveMQ Cloud)**
   - Responsável pela **publicação e subscrição** dos dados dos sensores;
   - Canal de comunicação entre o dispositivo e as plataformas de visualização.

3. **Plataforma de Visualização (Node-RED / HiveMQ Web Client)**
   - Recebe as mensagens publicadas pelo ESP32;
   - Exibe os valores de temperatura, umidade e luminosidade em tempo real;
   - Pode gerar **dashboards e alertas** visuais.

---

## ⚙️ Tecnologias Utilizadas
- **Microcontrolador:** ESP32 DevKit V1
- **Simulação:** [Wokwi IoT Simulator](https://wokwi.com/)
- **Protocolo de Comunicação:** MQTT
- **Broker:** HiveMQ Cloud (`broker.hivemq.com:1883`)
- **Linguagem:** C++ (Arduino Framework)
- **Sensores:**
  - DHT22 (Temperatura e Umidade)
  - LDR + Resistor 10kΩ (Luminosidade)

---

## 🧩 Montagem dos Sensores

### 🔹 DHT22
| Pino | Conexão |
|------|----------|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 15 |

### 🔹 LDR + Resistor 10kΩ (divisor de tensão)
| Pino | Conexão |
|------|----------|
| LDR | Entre 3.3V e ponto central |
| Resistor 10kΩ | Entre ponto central e GND |
| Ponto central | GPIO 34 (entrada analógica) |

---

## 📡 Comunicação MQTT

O ESP32 envia os dados a cada **5 segundos** para o tópico:
```
passabola/sensores
```

Mensagem publicada (em formato JSON):
```json
{
  "temperatura": 27.5,
  "umidade": 55.3,
  "luminosidade": 76.2
}
```

---

## 🖥️ Visualização dos Dados

### 🔹 Opção 1: HiveMQ Web Client
Acesse [https://www.hivemq.com/demos/websocket-client/](https://www.hivemq.com/demos/websocket-client/)
Preencha:
- Host: `broker.hivemq.com`
- Port: `8000`
- Topic: `passabola/sensores`

Você verá as mensagens chegando em tempo real.

### 🔹 Opção 2: Node-RED Dashboard
- Configure um **nó MQTT IN** com o mesmo tópico;
- Conecte a um **nó chart/gauge** para visualizar os dados;
- Mostre temperatura, umidade e luminosidade de forma gráfica.

---

## 🔍 Conclusão

O **Passa a Bola – IoT** demonstra a integração entre **tecnologia, esporte e comunidade**,
explorando como a **Internet das Coisas** pode enriquecer a experiência e o desempenho no futebol feminino.

Este projeto pode ser expandido futuramente para:
- Monitoramento de presença de público via sensores de movimento;
- Controle automatizado de irrigação e iluminação;
- Integração total com o site da comunidade *Passa a Bola*.

---

## 👩‍💻 Equipe
- [Seu nome]
- [Integrantes do grupo]
- Curso: **Edge Computing / WebDev**
- Instituição: [Nome da instituição]
