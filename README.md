Controle de Servo Motor com PWM - Raspberry Pi Pico

Descrição

Este programa controla um servomotor utilizando PWM no Raspberry Pi Pico. Ele posiciona o servo em 0°, 90° e 180° com pausas de 5 segundos entre cada movimento. Em seguida, realiza uma oscilacão suave entre 0° e 180°, alterando o ciclo ativo gradualmente.

Requisitos

Raspberry Pi Pico

Servomotor compatível com PWM

Software de desenvolvimento compatível (ex.: VS Code com extensões para Raspberry Pi Pico)

Biblioteca pico/stdlib.h e hardware/pwm.h

Instalação e Uso

Conecte o servomotor ao Raspberry Pi Pico:

Pino de sinal (PWM) no GPIO 22

Alimentação (VCC) em 5V

GND em GND

Compile e envie o código para a placa.

O servomotor executará os movimentos predefinidos.

Configuração do PWM

Frequência do PWM: 50Hz (período de 20ms)

Ciclo de trabalho para cada posição:

0°: 500µs (2,5%)

90°: 1470µs (7,35%)

180°: 2400µs (12%)

Observações

O LED RGB no GPIO 12 pode apresentar alteração na iluminação devido à variação do PWM.

A movimentação entre 0° e 180° é feita em incrementos suaves de 5µs para um movimento mais natural.

link repositorio: https://github.com/valtermsf90/tarefa_pwm

link video de demostração: https://drive.google.com/file/d/1eEpuMjLvJufF2UuMH2KfLOjbBHMeQRE4/view?usp=sharing

Autor

Valter Machado