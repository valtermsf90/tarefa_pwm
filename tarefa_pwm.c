    #include "pico/stdlib.h"
    #include "hardware/pwm.h"

    #define PINO_PWM 22  // Pino do PWM
    #define DELAY_5S 5000  // Atraso de 5 segundos
    #define DELAY_10MS 10  // Atraso de 10 milissegundos

    uint16_t periodo_wrap = 20000;  // Valor máximo do contador PWM
    float divisor_de_clock = 125.0;  // Divisor de clock
    uint16_t duty_cycle = 0;  // Ciclo de trabalho do PWM
    uint numero_slice;  // Canal PWM associado ao pino
    static volatile bool controle_incremento = true;  // Direção do movimento do servo

    void alteracao_ciclo_ativo(uint estagio);
    void configuracao_pwm(void);

    int main(void){
        bool estagios_iniciais = true; // Alterna entre estágios iniciais e oscilação

        configuracao_pwm();

        gpio_set_function(PINO_PWM, GPIO_FUNC_PWM); // Configura GPIO como PWM

        while(true){
            if(estagios_iniciais){
                for(uint i = 1; i < 4; i++)
                    alteracao_ciclo_ativo(i);
                estagios_iniciais = !estagios_iniciais;
            }else{
                alteracao_ciclo_ativo(4);
            }
        }
        return 0;
    }

    void alteracao_ciclo_ativo(uint estagio){
        switch(estagio){
            case 1: // Posição 180°
                duty_cycle = periodo_wrap * 3 / 25;
                break;
            case 2: // Posição 90°
                duty_cycle = periodo_wrap * 147 / 2000;
                break;
            case 3: // Posição 0°
                duty_cycle = periodo_wrap / 40;
                break;
            case 4: // Oscilação suave entre 0° e 180°
                if(controle_incremento){
                    duty_cycle += 5;
                    if(duty_cycle == periodo_wrap * 3 / 25)
                        controle_incremento = false;
                }else{
                    duty_cycle -= 5;
                    if(duty_cycle == periodo_wrap / 40)
                        controle_incremento = true;
                }
                break;
        }
        pwm_set_gpio_level(PINO_PWM, duty_cycle);
        if(estagio < 4)
            sleep_ms(DELAY_5S);
        else
            sleep_ms(DELAY_10MS);
    }

    void configuracao_pwm(void){
        numero_slice = pwm_gpio_to_slice_num(PINO_PWM); // Obtém canal PWM
        pwm_set_clkdiv(numero_slice, divisor_de_clock); // Configura divisor de clock
        pwm_set_wrap(numero_slice, periodo_wrap); // Configura período do PWM
        pwm_set_gpio_level(PINO_PWM, duty_cycle); // Define ciclo inicial
        pwm_set_enabled(numero_slice, true); // Habilita PWM
    }
