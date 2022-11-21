# Controle Motor de Passo com ESP32

## Informações Gerais

| Item         | Descrição       |
| ------------ | --------------- |
| Env. Manager | PlatformIO      |
| FrameWork    | Arduino         |
| Board        | ESP32 DevKit V1 |

## ESP32

![Image](https://i.imgur.com/pnnQfdt.png)

## 485

Circuito testado em desenvolvimento:

![Image](https://i.imgur.com/5AkJ9Kn.png)

## Motor

Motor de Passo NEMA 23 - 20 Kgf.cm - TMA.MP.23020

![Image](https://i.imgur.com/anLh6PF.png)

## Driver e Configuração

Driver para Motor de Passo - TMA.DMP.542F

![Image](https://i.imgur.com/DTaSGg6.png)

### Mapa de Chaves

| SW1 - SW3               | SW4                 | SW5 - SW8           |
| ----------------------- | ------------------- | ------------------- |
| Ajuste corrente de pico | Corrente em repouso | Resolucao do driver |

### Mapa de Resolucao

| Pulso/Rev | SW5 | SW6 | SW7 | SW8 |
| --------- | --- | --- | --- | --- |
| DEFAULT   | ✔️   | ✔️   | ✔️   | ✔️   |
| 400       | ❌   | ✔️   | ✔️   | ✔️   |
| 800       | ✔️   | ❌   | ✔️   | ✔️   |
| 1600      | ❌   | ❌   | ✔️   | ✔️   |
| 3200      | ✔️   | ✔️   | ❌   | ✔️   |
| 6400      | ❌   | ✔️   | ❌   | ✔️   |
| 12800     | ✔️   | ❌   | ❌   | ✔️   |
| 25600     | ❌   | ❌   | ❌   | ✔️   |
| 1000      | ✔️   | ✔️   | ✔️   | ❌   |
| 2000      | ❌   | ✔️   | ✔️   | ❌   |
| 4000      | ✔️   | ❌   | ✔️   | ❌   |
| 5000      | ❌   | ❌   | ✔️   | ❌   |
| 8000      | ✔️   | ✔️   | ❌   | ❌   |
| 10000     | ❌   | ✔️   | ❌   | ❌   |
| 20000     | ✔️   | ❌   | ❌   | ❌   |
| 25000     | ❌   | ❌   | ❌   | ❌   |

### Configuração Utilizada

| Pulso/Rev | SW5 | SW6 | SW7 | SW8 |
| --------- | --- | --- | --- | --- |
| 5000      | ❌   | ❌   | ✔️   | ❌   |

Frequências máximas e mínimas, verificar:

``` c
#define dMAX_FREQ
#define dMIN_FREQ
```


