# Philosophers
####   🇺🇸 To access the english version of this README






 [click here](https://github.com/LeonardoSabar/Philosophers_42SP/blob/GitHub_Version/README.md).
<p align="center">
<img src="https://github.com/LeonardoSabar/Philosophers_42SP/blob/GitHub_Version/utils/philos.jpeg" width="800px" alt="mandatory"/><br>
</p>

Este projeto simula o clássico [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) usando [threads](https://en.wikipedia.org/wiki/Thread_(computing)) e [mutexes](https://en.wikipedia.org/wiki/Mutual_exclusion). O objetivo é evitar deadlocks enquanto garante que cada filósofo possa comer sem conflitos.

## Estilo de Código
O estilo de código usado neste projeto é o [Norminette](https://github.com/42School/norminette) , criado pela escola 42 e utilizado em todos os projetos relacionados em ANSI C no contexto da escola.

## Índice

- [**1. Descrição**](#1-description)
- [**2. Uso**](#2-Usage)
- [**3. Instalação**](#3-installation)
- [**4. Contribuição**](#4-contributing)

## 1. Descrição

O problema dos filósofos jantando envolve um grupo de filósofos sentados ao redor de uma mesa circular. Cada filósofo pensa e come. Para comer, um filósofo deve pegar os dois garfos (um à sua esquerda e outro à sua direita). No entanto, se todos os filósofos tentarem pegar seus garfos simultaneamente, eles podem entrar em deadlock.

Este projeto fornece uma solução para o problema usando threads e mutexes. Ele garante que os filósofos possam comer sem causar deadlocks.

## 2. Uso

**Clone o repositório:**
```sh
   git clone https://github.com/LeonardoSabar/Philosophers_42SP.git
```

**Compile o programa:**
```sh
    cd philosophers
    make
```

**Execute a simulação:**
```sh
    ./philo [número_de_filósofos] [tempo_para_morrer] [tempo_para_comer] [tempo_para_dormir] [número_de_vezes_que_cada_filósofo_deve_comer]
```

## 3. Instalação
Certifique-se de ter gcc e make instalados. Se não, instale-os usando seu gerenciador de pacotes.

## 4. Contribuição
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.
