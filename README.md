# Controle de Mão Robótica InMoov com EEG e sEMG

**Projeto de Engenharia da Computação | Robótica, Processamento de Sinais e Simulação**

## Sobre o projeto

Este projeto tem como objetivo desenvolver e estudar um sistema de controle de uma mão robótica **InMoov**, utilizando sinais eletroencefalográficos (EEG) e eletromiográficos de superfície (sEMG) simulados.

A implementação utiliza Python para gerar, processar e classificar sinais sintéticos, transformando informações relacionadas à atividade cerebral e muscular em comandos de movimentação da mão robótica no ambiente CoppeliaSim.

O projeto integra conhecimentos de robótica, programação, processamento digital de sinais, sistemas de controle e engenharia biomédica.

## Objetivos

- Simular sinais EEG e sEMG associados à atividade motora.
- Desenvolver algoritmos de processamento e classificação dos sinais.
- Identificar comandos de abertura, fechamento e repouso da mão.
- Integrar o sistema de controle ao simulador CoppeliaSim.
- Controlar e monitorar articulações individuais dos dedos.
- Registrar e analisar graficamente os resultados dos experimentos.

## Tecnologias utilizadas

| Tecnologia | Aplicação |
|---|---|
| Python | Desenvolvimento dos algoritmos |
| CoppeliaSim | Simulação da mão robótica |
| InMoov | Modelo robótico utilizado |
| NumPy | Operações numéricas e geração de sinais |
| SciPy | Filtragem e processamento de sinais |
| Matplotlib | Visualização e análise dos resultados |
| ZeroMQ Remote API | Comunicação entre Python e CoppeliaSim |

## Funcionamento do sistema

O sistema é organizado em etapas que representam o processamento de sinais biológicos e sua aplicação ao controle robótico.

**1. Geração dos sinais**

São produzidos sinais sintéticos que representam:

- **EEG:** atividade elétrica cerebral simulada, incluindo os ritmos mu e beta.
- **sEMG:** atividade muscular simulada de músculos flexores e extensores.

**2. Processamento**

Os sinais são analisados utilizando técnicas como:

- Transformada Rápida de Fourier (FFT).
- Filtragem digital passa-faixa.
- Cálculo do valor RMS (*Root Mean Square*).
- Análise da potência espectral na banda mu.
- Normalização da intensidade muscular.

**3. Classificação dos movimentos**

O algoritmo interpreta as características dos sinais e determina um dos três estados:

| Código | Comando | Descrição |
|---|---|---|
| 0 | REPOUSO | Ausência de movimento |
| 1 | FECHAR | Movimento de flexão |
| 2 | ABRIR | Movimento de extensão |

A atividade EEG simulada participa da identificação do estado motor, enquanto os sinais sEMG flexor e extensor auxiliam na determinação da direção e intensidade do movimento.

**4. Controle robótico**

Os comandos são transmitidos ao CoppeliaSim por meio da ZeroMQ Remote API.

A movimentação da mão depende da configuração das articulações e dos mecanismos de controle presentes na cena do simulador.

**5. Monitoramento**

Durante os experimentos, o sistema pode registrar a atividade dos sinais, os comandos classificados e as posições angulares das articulações.

Essas informações são utilizadas para gerar gráficos de análise.

## Estrutura do repositório

```text
Projeto-ENgenharia-da-Computacao/
│
├── classificar_eeg_semg.py
├── conectar_coppelia.py
├── controlar_mao.py
├── controle_dedos_eeg_semg.py
├── controle_flexor_extensor.py
├── controle_integrado.py
├── controle_semg.py
├── experimento_eeg_semg.py
├── monitorar_mao.py
├── simulacao_tempo_real.py
├── simular_sinais.py
├── teste_comunicacao.py
├── teste_indicador.py
└── README.md
```

### Principais arquivos

| Arquivo | Função |
|---|---|
| `conectar_coppelia.py` | Estabelece a comunicação e identifica articulações |
| `classificar_eeg_semg.py` | Gera e classifica sinais EEG e sEMG sintéticos |
| `controle_integrado.py` | Integra classificação, comandos e geração de gráficos |
| `controle_dedos_eeg_semg.py` | Realiza experimentos de controle individual dos dedos |
| `experimento_eeg_semg.py` | Executa experimentos e registra respostas articulares |
| `simulacao_tempo_real.py` | Monitora sinais simulados e posições das articulações |

Os demais scripts incluem etapas de simulação, testes de comunicação e diferentes estratégias de controle.

## Instalação e configuração

### Pré-requisitos

- Python 3
- CoppeliaSim com uma cena compatível com o modelo InMoov
- Git
- Bibliotecas Python utilizadas pelo projeto

### 1. Clonar o repositório

```bash
git clone https://github.com/masteguim/Projeto-ENgenharia-da-Computacao.git

cd Projeto-ENgenharia-da-Computacao
```

### 2. Criar um ambiente virtual

```bash
python3 -m venv .venv

source .venv/bin/activate
```

No Windows, utilize:

```powershell
.venv\Scripts\activate
```

### 3. Instalar as dependências

```bash
pip install numpy scipy matplotlib coppeliasim-zmqremoteapi-client
```

### 4. Preparar o CoppeliaSim

1. Iniciar o CoppeliaSim.
2. Carregar uma cena contendo a mão robótica InMoov.
3. Verificar os nomes das articulações e sua compatibilidade com os scripts.
4. Confirmar que a ZeroMQ Remote API está disponível.

Os scripts de controle utilizam sinais de cena, como `inmoov_comando`, `inmoov_intensidade` e `inmoov_dedo`. A cena precisa conter a lógica responsável por interpretar esses sinais e aplicar os movimentos às articulações.

## Execução

### Testar a conexão

Com o CoppeliaSim aberto:

```bash
python conectar_coppelia.py
```

O programa deverá estabelecer a conexão e listar as articulações encontradas na cena.

### Testar a classificação dos sinais

```bash
python classificar_eeg_semg.py
```

Esse script executa testes de classificação dos sinais sintéticos sem exigir conexão com o simulador.

### Executar o controle integrado

```bash
python controle_integrado.py
```

O script aguardará o início da simulação no CoppeliaSim.

Após pressionar **Play**, os sinais serão gerados, classificados e enviados ao ambiente robótico durante o experimento.

### Executar o controle individual dos dedos

```bash
python controle_dedos_eeg_semg.py
```

O experimento percorre os cinco dedos da mão, aplicando sequências de flexão, repouso e extensão.

### Monitorar os sinais e as articulações

```bash
python simulacao_tempo_real.py
```

Esse script registra sinais sintéticos e monitora posições de articulações durante a execução.

## Parâmetros de processamento

Os principais experimentos utilizam as seguintes configurações:

| Parâmetro | Valor |
|---|---|
| Frequência de amostragem EEG | 256 Hz |
| Frequência de amostragem sEMG | 1000 Hz |
| Banda mu do EEG | 8–13 Hz |
| Frequência do ritmo beta simulado | 20 Hz |
| Filtragem sEMG | 20–400 Hz |
| Filtro sEMG | Butterworth de 4ª ordem |
| Duração do controle integrado | 30 segundos |
| Duração do teste individual dos dedos | 30 segundos |

## Resultados e análise

Os experimentos permitem estudar a relação entre sinais biológicos simulados e comandos de movimentação robótica.

Entre as informações analisadas estão:

- Potência da banda mu no EEG.
- Intensidade dos sinais musculares flexores e extensores.
- Comandos classificados pelo algoritmo.
- Seleção dos dedos durante os experimentos.
- Variação angular das articulações.
- Comportamento temporal do sistema de controle.

Determinados scripts geram automaticamente arquivos gráficos, como:

```text
resultado_eeg_semg.png
resultado_dedos_eeg_semg.png
experimento_eeg_semg_inmoov.png
monitor_eeg_semg.png
```

Os arquivos são produzidos durante a execução dos respectivos experimentos.

## Limitações

O projeto utiliza sinais EEG e sEMG **sintéticos**, não provenientes de sensores biomédicos reais.

Consequentemente, os algoritmos representam uma abordagem experimental de controle motor e não constituem, nesta etapa, uma interface cérebro-computador validada com dados fisiológicos.

O funcionamento do controle robótico também depende da configuração da cena e das articulações do modelo InMoov no CoppeliaSim.

## Possibilidades de evolução

O projeto oferece uma base para futuras pesquisas e implementações envolvendo:

- Integração com sensores EEG e sEMG reais.
- Aplicação de algoritmos de aprendizado de máquina para classificação motora.
- Desenvolvimento de estratégias de controle adaptativo.
- Aprimoramento da precisão dos movimentos.
- Aplicações em próteses robóticas e tecnologias assistivas.
- Avaliação experimental com diferentes estratégias de processamento de sinais.

## Autor

**Lucas Masteguim**

Engenharia da Computação

GitHub: [@masteguim](https://github.com/masteguim)

---

*Projeto acadêmico desenvolvido para estudo e experimentação nas áreas de robótica, processamento digital de sinais e controle de sistemas robóticos.*
