#include "LED.h"

#include "LED.h"

Led::Led(uint8_t pin)
{
    pino = pin;
    estado = LOW;
    pinMode(pino, OUTPUT);
}

void Led::ligar()
{
    estado = HIGH;
}

void Led::ligar(uint32_t tempoLigado_ms)
{
    estado = HIGH;
    desligarPorTempo = true;
    desligarNoMomento = millis() + tempoLigado_ms;
}

void Led::desligar()
{
    estado = LOW;
}

void Led::alternar()
{
    estado = !estado;
}

void Led::update()
{

    if (desligarPorTempo)
    {
        if (millis() >= desligarNoMomento)
        {
            estado = LOW;
            desligarPorTempo = false;
        }
    }

    if (estadoPiscar)
    {
        funcaoPiscar();
    }

    digitalWrite(pino, estado);
}

bool Led::getEstado()
{
    return estado;
}

uint8_t Led::getPino()
{
    return pino;
}

void Led::setEstado(bool estado)
{
    this->estado = estado;
}

void Led::piscar()
{
    estadoPiscar = true;
    tempoEspera = 500;
    tempoAnteriorPiscar = millis();
    estado = HIGH;
}

void Led::piscar(float frequencia)
{
}

void Led::piscar(uint8_t frequencia, uint8_t repeticoes)
{
    estadoPiscar = true;
    tempoEspera = (1000.0f / 2.0f * frequencia);
    tempoAnteriorPiscar = millis();
    estado = HIGH;
    this->repeticoes = repeticoes*2;
}

void Led::funcaoPiscar()
{
    if (millis() - tempoAnteriorPiscar >= tempoEspera)
    {
        estado = !estado;
        tempoAnteriorPiscar = millis();
        if (repeticoes > 0)
        {
            repeticoes--;
            if (repeticoes==0)
            {
                estadoPiscar = false;
                estado = LOW;
    
            }
    }



    }
}