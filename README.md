# 🃏 SuperTrunfo

[![C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](LICENSE)

Um jogo de cartas estilo **Super Trunfo** desenvolvido em **C**, com foco em lógica de programação, manipulação de arquivos e uso de structs.  
O projeto busca recriar a dinâmica clássica do jogo, permitindo criar, editar e comparar cartas personalizadas.

---

## 📖 Sumário
- [📌 Visão geral](#-visão-geral)
- [🎮 Funcionalidades](#-funcionalidades)
- [🛠️ Tecnologias e estrutura](#️-tecnologias-e-estrutura)
- [🚀 Como compilar e executar](#-como-compilar-e-executar)
- [🧩 Estrutura das cartas](#-estrutura-das-cartas)
- [📋 Edição do baralho](#-edição-do-baralho)
- [🕹️ Como jogar](#-como-jogar)
- [🧠 Lógica do jogo](#-lógica-do-jogo)
- [✨ Melhorias futuras](#-melhorias-futuras)
- [🧰 Dependências](#-dependências)
- [🔧 Compilação manual](#-compilação-manual)
- [📸 Prévia](#-prévia-opcional)
- [🤝 Contribuição](#-contribuição)
- [📄 Licença](#-licença)
- [👤 Autor](#-autor)

---

## 📌 Visão geral

O **SuperTrunfo** é um projeto em C que simula um jogo de cartas no estilo clássico, em que os jogadores comparam atributos de cartas para determinar o vencedor de cada rodada.  
Foi desenvolvido com o objetivo de praticar conceitos fundamentais de **estruturas de dados, leitura e escrita de arquivos, menus interativos** e **organização modular de código**.

---

## 🎮 Funcionalidades

✅ Estrutura de cartas com múltiplos atributos  
✅ Edição e criação de cartas via interface de menu  
✅ Leitura e gravação de baralhos em **CSV** e **binário**  
✅ Comparação de atributos entre cartas (modo Super Trunfo)  
✅ Exibição de cartas e resultados da rodada  
✅ Interface modular com menus e mensagens interativas  

---

## 🛠️ Tecnologias e estrutura

- **Linguagem:** C (padrão C99)  
- **Compilador:** GCC  
- **Biblioteca gráfica:** [Raylib](https://www.raylib.com/) *(se estiver habilitada no projeto)*  
- **Sistema de build:** Makefile  

📂 Estrutura de diretórios:
```
supertrunfo/
├── src/          # Códigos-fonte (.c)
├── include/      # Arquivos de cabeçalho (.h)
├── assets/       # Imagens e arquivos CSV/binários
├── Makefile      # Script de compilação
└── README.md     # Este arquivo
```

---

## 🚀 Como compilar e executar

1. **Clone o repositório**
   ```bash
   git clone https://github.com/EduardoHaagP/supertrunfo.git
   cd supertrunfo
   ```

2. **Compile o projeto**
   ```bash
   make
   ```

3. **Execute o jogo**
   ```bash
   ./programa       # Linux/macOS
   programa.exe     # Windows
   ```

> 💡 Caso o Makefile não esteja disponível, você pode compilar manualmente:
> ```bash
> gcc src/*.c -Iinclude -o programa
> ```

---

## 🧩 Estrutura das cartas

Cada carta do jogo segue a seguinte estrutura:

```c
typedef struct {
    char nome[51];
    char letra;
    int supertrunfo;
    int anoConstrucao;
    int altura;
    int visitasAnuais;
    int importanciaHistorica;
    int popularidade;
    Texture2D img;
    char arqimg[100];
} cartas;
```

Esses atributos são usados para comparar cartas entre si durante as rodadas do jogo.

---

## 📋 Edição do baralho

O baralho do SuperTrunfo é armazenado em arquivos **.csv** e **.bin**, permitindo fácil manutenção e personalização das cartas.

### 🗂️ Formato CSV
Cada linha do arquivo representa uma carta, com os campos separados por vírgula:

```
nome,letra,supertrunfo,anoConstrucao,altura,visitasAnuais,importanciaHistorica,popularidade,arqimg
```

Exemplo:
```
Torre Eiffel,A,1,1889,324,7000000,10,9,torre_eiffel.png
Cristo Redentor,B,0,1931,38,2000000,9,8,cristo_redentor.png
```

Você pode:
- ✏️ Editar as cartas diretamente no arquivo `.csv`
- 💾 Converter automaticamente para `.bin` ao iniciar o jogo
- 🧭 Usar o **menu de edição** dentro do programa para alterar atributos individualmente

---

## 🕹️ Como jogar

1. **Inicie o programa** — será exibido um menu inicial.  
2. **Escolha entre as opções**:  
   - Iniciar partida  
   - Editar cartas  
   - Visualizar baralho  
   - Sair  
3. **Durante a partida**, selecione o atributo que deseja comparar com a carta do oponente.  
4. O jogo determina automaticamente o vencedor da rodada com base no valor do atributo escolhido.  
5. O modo “Super Trunfo” vence automaticamente qualquer carta que não pertença à mesma categoria.

---

## 🧠 Lógica do jogo

```c
if (carta1.supertrunfo && carta2.letra != carta1.letra) {
    // carta1 vence automaticamente
} else if (atributo1 > atributo2) {
    // carta1 vence
} else if (atributo1 < atributo2) {
    // carta2 vence
} else {
    // empate
}
```

Essa estrutura garante uma partida justa e dinâmica, respeitando a mecânica tradicional do Super Trunfo.

---

## ✨ Melhorias futuras

- 💻 Interface gráfica completa com Raylib  
- 🧾 Histórico de partidas e estatísticas  
- 🎨 Temas personalizáveis  
- 🤖 Modo contra IA  
- 🌐 Multiplayer online/local  
- 💬 Sistema de feedback e logs  

---

## 🧰 Dependências

- **GCC** (ou outro compilador compatível com C99)  
- **Make** (para compilar via Makefile)  
- **Raylib** (opcional)  

Instalação do Raylib:
```bash
sudo apt install libraylib-dev     # Linux (Ubuntu/Debian)
brew install raylib                # macOS
```

---

## 🔧 Compilação manual

```bash
gcc src/*.c -Iinclude -o supertrunfo -lraylib -lm
```
> 💡 Remova `-lraylib` caso não utilize imagens.

---

## 📸 Prévia (opcional)

Adicione imagens ou GIFs mostrando o menu, as cartas, ou o gameplay.

---

## 🤝 Contribuição

1. Fork o repositório  
2. Crie uma branch (`git checkout -b minha-feature`)  
3. Commit suas mudanças (`git commit -m "minha feature"`)  
4. Push (`git push origin minha-feature`)  
5. Abra um Pull Request  

---

## 📄 Licença

Distribuído sob a **MIT License**. Consulte [LICENSE](LICENSE).

---

## 👤 Autor

**Eduardo Haag Piassa da Silva**  
🔗 GitHub: [@EduardoHaagP](https://github.com/EduardoHaagP)

**Nathalia Rodrigues Nunes Gonçalves**  
🔗 GitHub: [@EduardoHaagP](https://github.com/EduardoHaagP)
