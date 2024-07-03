# Philosophers
####   🇧🇷 Para acessar a versão em português deste README [clique aqui](https://github.com/LeonardoSabar/Philosophers_42SP/blob/main/README-PTBR.md).
<p align="center">
<img src="https://github.com/LeonardoSabar/Philosophers_42SP/blob/main/utils/philos.jpeg" width="800px" alt="mandatory"/><br>
</p>
This project simulates the classic dining philosophers problem using threads and mutexes. The goal is to avoid deadlocks while ensuring that each philosopher can eat without conflicts.

## Code style
The code style used in this project is the [Norminette](https://github.com/42School/norminette) created by the 42 school and used in all related ANSI C projects in the context of the school.

## Table of Contents

- [**1. Description**](#1-description)
- [**2. Usage**](#2-Usage)
- [**3. Installation**](#3-installation)
- [**4. Contributing**](#4-contributing)

## 1. Description

The dining philosophers problem involves a group of philosophers sitting around a circular table. Each philosopher thinks and eats. To eat, a philosopher must pick up both forks (one on their left and one on their right). However, if all philosophers try to pick up their forks simultaneously, they can deadlock.

This project provides a solution to the problem using threads and mutexes. It ensures that philosophers can eat without causing deadlocks.

## 2. Usage

**Clone the repository:**
```sh
   git clone https://github.com/your-username/philosophers.git
```

**Compile the program:**
```sh
    cd philosophers
    make
```

**Run the simulation:**
```sh
    ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

## 3. Installation
Make sure you have gcc and make installed. If not, install them using your package manager.

## 4. Contributing
Contributions are welcome! Feel free to open issues or submit pull requests.
