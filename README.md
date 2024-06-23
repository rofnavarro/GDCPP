- [English](#english)
- [Português](#português)

# English

# GDCPP - Game Development in C++ with ECS Architecture

GDCPP is a C++ game development project that utilizes the ECS (Entity, Component, System) architecture to organize and manage game logic. This repository contains the source code and necessary resources to create a basic game engine using this architecture.

## Table of Contents

- [Introduction](#introduction)
- [ECS Architecture](#ecs-architecture)
- [Project Features](#project-features)
- [How to Use](#how-to-use)

## Introduction

GDCPP aims to provide a hands-on experience in game development using C++ with the ECS architecture. This architecture divides game logic into entities (objects), components (attributes), and systems (processing logic), making code organization and maintenance easier.

## ECS Architecture

The ECS architecture consists of three main elements:

- **Entity**: Represents a game object and is a collection of components.
- **Component**: Represents individual attributes of an entity, such as position, velocity, appearance, etc.
- **System**: Implements processing logic and entity manipulation based on their components.

By using the ECS architecture, game development becomes more modular, allowing for adding, removing, or modifying entity behaviors without affecting other parts of the code.

## Project Features

The GDCPP project includes the following features:

- Basic implementation of entities, components, and systems.
- Simple game example to demonstrate the use of ECS architecture.
- Well-documented and organized source code for easy understanding and maintenance.
- Guidelines and best practices for C++ game development.

## How to Use

To start using GDCPP and develop your own game, follow these steps:

1. Clone the repository:
   ```sh
   git clone git@github.com:rofnavarro/GDCPP.git
   cd GDCPP
   ```

2. Compile the source code using the makefile:
   ```sh
   make
   ```

3. Run the game:
   ```sh
   ./gd
   ```

***

# Português

# GDCPP - Desenvolvimento de Jogos em C++ com arquitetura ECS

O GDCPP é um projeto de desenvolvimento de jogos em C++ que utiliza a arquitetura ECS (Entidade, Componente e Sistema) para organizar e gerenciar a lógica do jogo. Este repositório contém o código-fonte e recursos necessários para criar um motor de jogos básico utilizando essa arquitetura.

## Sumário

- [Introdução](#introdução)
- [Arquitetura ECS](#arquitetura-ecs)
- [Recursos do Projeto](#recursos-do-projeto)
- [Como Usar](#como-usar)


## Introdução

O GDCPP é um projeto que visa proporcionar uma experiência prática no desenvolvimento de jogos em C++ utilizando a arquitetura ECS. Esta arquitetura divide a lógica do jogo em entidades (objetos), componentes (atributos) e sistemas (lógica de processamento), facilitando a organização e manutenção do código.

## Arquitetura ECS

A arquitetura ECS é composta por três principais elementos:

- **Entidade**: Representa um objeto do jogo e é uma coleção de componentes.
- **Componente**: Representa atributos individuais de uma entidade, como posição, velocidade, aparência, etc.
- **Sistema**: Implementa a lógica de processamento e manipulação de entidades com base em seus componentes.

Ao usar a arquitetura ECS, o desenvolvimento do jogo é mais modular, permitindo adicionar, remover ou modificar comportamentos de entidades sem afetar outras partes do código.

## Recursos do Projeto

O projeto GDCPP inclui os seguintes recursos:

- Implementação básica de entidades, componentes e sistemas.
- Exemplo de jogo simples para demonstrar o uso da arquitetura ECS.
- Código-fonte bem documentado e organizado para fácil entendimento e manutenção.
- Diretrizes e boas práticas para o desenvolvimento de jogos em C++.

## Como Usar

Para começar a usar o GDCPP e desenvolver seu próprio jogo, siga estas etapas:

1. Clone o repositório:
   ```sh
   git clone git@github.com:rofnavarro/GDCPP.git
   cd GDCPP
   ```

2. Compile o código-fonte usando o makefile:
   ```sh
   make
   ```

3. Execute o jogo:
   ```sh
   ./gd
   ```

4. Explore o código-fonte, adicione novas entidades, componentes e sistemas conforme necessário para o seu jogo.
